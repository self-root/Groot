#include "secretservice.h"
#include <QDebug>
#include <QtConcurrent>

SecretService::SecretService(QObject *parent)
    : QObject{parent}
{
    connect(&storingWatcher, &QFutureWatcher<bool>::finished, this, &SecretService::onStored);
    connect(&restoringWatcher, &QFutureWatcher<QString>::finished, this, &SecretService::onRestored);
    connect(&removeWatcher, &QFutureWatcher<void>::finished, this, &SecretService::onRemoved);
}

void SecretService::store()
{

    QFuture<bool> storingJob = QtConcurrent::run([this](){
        QJniObject jniToken = QJniObject::fromString(mSecret);
        QJniObject alias = QJniObject::fromString(this->mAlias);
        QJniObject res = QJniObject::callStaticMethod<jbyteArray>(
                    "xyz/irootsoftware/keymanager/KKeyManager",
                    "encrypt",
                    "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;",
                    jniToken.object<jstring>(),
                    alias.object<jstring>());
        qDebug() << "Token encrypted...";

        QString encrypted = res.toString();
        qDebug() << "Encrypted: " << encrypted;


        QFile tokenFile(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/token.tk");
        if (tokenFile.open(QIODevice::WriteOnly))
        {
            tokenFile.write(encrypted.toStdString().c_str());
        }

        return true;
    });
    storingWatcher.setFuture(storingJob);

}

void SecretService::restore()
{

    QFuture<QString> restoring = QtConcurrent::run([this](){
        QFile tokenFile(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/token.tk");

        if (tokenFile.open(QIODevice::ReadOnly))
        {
            QByteArray data = tokenFile.readAll();
            tokenFile.close();
            QString token(data.data());
            if (token.isEmpty())
            {
                qDebug() << "Token is empty";
                return QString();
            }
            qDebug() << "Decrypting... data size: " << data.size();
            qDebug() << "Data: " << data;
            QJniObject alias = QJniObject::fromString(this->mAlias);


            QJniObject encrypted = QJniObject::fromString(token);
            QJniObject decrypted = QJniObject::callStaticMethod<jstring>(
                        "xyz/irootsoftware/keymanager/KKeyManager",
                        "decrypt",
                        "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;",
                        encrypted.object<jstring>(),
                        alias.object<jstring>());

            QString decryptedToken = decrypted.toString();

            qDebug() << "Token decrypted: " << decryptedToken;

            return decryptedToken;

        }
        qDebug() << "No token";
        return QString();

    });
    restoringWatcher.setFuture(restoring);
}

void SecretService::remove()
{
    if (mAlias.isEmpty())
        return;
    QFile tokenFile(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/token.tk");
    tokenFile.remove();
    emit removed();

}

void SecretService::onStored()
{
    bool s = storingWatcher.result();
    if (!s)
        emit error();
    else
        emit stored();
}

void SecretService::onRestored()
{
    qDebug()<< "Secret managet: onRestored -> " << restoringWatcher.result();
    emit restored(restoringWatcher.result());
}

void SecretService::onRemoved()
{
    emit removed();
}

void SecretService::setSecret(const QString &newSecret)
{
    mSecret = newSecret;
}

void SecretService::setAlias(const QString &newAlias)
{
    mAlias = newAlias;
}

