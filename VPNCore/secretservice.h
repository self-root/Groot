#ifndef SECRETSERVICE_H
#define SECRETSERVICE_H

#include <QObject>
#include <QFuture>
#include <QFutureWatcher>
#include "VPNCore_global.h"

class VPNCORE_EXPORT SecretService : public QObject
{
    Q_OBJECT
public:
    explicit SecretService(QObject *parent = nullptr);

    void setSecret(const QString &newSecret);

    void setAlias(const QString &newAlias);

    void store();

    void restore();

    void remove();

private:
    QString mSecret;
    QString mAlias;
    QFutureWatcher<bool> storingWatcher;
    QFutureWatcher<QString> restoringWatcher;
    QFutureWatcher<void> removeWatcher;

private slots:
    void onStored();
    void onRestored();
    void onRemoved();
Q_SIGNALS:
    void stored();
    void restored(const QString &secret);
    void error();
    void removed();

};


#endif // SECRETSERVICE_H
