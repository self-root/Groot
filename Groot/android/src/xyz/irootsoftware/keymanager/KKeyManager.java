package xyz.irootsoftware.keymanager;


import android.security.keystore.KeyGenParameterSpec;
import android.security.keystore.KeyProperties;

import javax.crypto.*;
import javax.crypto.spec.IvParameterSpec;
import java.io.IOException;
import java.security.*;
import java.security.cert.CertificateException;

public class KKeyManager {
    /**
     * @brief Get the secret key from the AndroidKeystore or generate one if it doesn't exist
     * @param alias Alias of the secret key
     * @return The Secret key
     */
    public static SecretKey getSecretKey(String alias) throws NoSuchAlgorithmException, InvalidAlgorithmParameterException, KeyStoreException, CertificateException, IOException, UnrecoverableEntryException {
        KeyStore keystore = KeyStore.getInstance("AndroidKeystore");
        keystore.load(null);

        KeyStore.Entry entry = keystore.getEntry(alias, null);

        if (entry == null)
        {
            System.out.println("No entry yet");
            KeyGenerator keyGen = KeyGenerator.getInstance(KeyProperties.KEY_ALGORITHM_AES);
            keyGen.init(new KeyGenParameterSpec.Builder(alias, KeyProperties.PURPOSE_ENCRYPT | KeyProperties.PURPOSE_DECRYPT)
                    .setBlockModes(KeyProperties.BLOCK_MODE_CBC)
                    .setEncryptionPaddings(KeyProperties.ENCRYPTION_PADDING_PKCS7)
                    .setKeySize(256)
                    .build());

            SecretKey secretKey = keyGen.generateKey();
            return secretKey;
        }
        System.out.println("Entry already exist");
        if (entry instanceof KeyStore.SecretKeyEntry)
        {

            System.out.println("Is a secret key entry");

            SecretKey key = ((KeyStore.SecretKeyEntry) entry).getSecretKey();

            return key;
        }

        else {
            return null;
        }
    }

    /**
     * @brief Encrypt data using AES 256 encryption, Save the IV at the beginning of the encrypted data
     * @param plainText The data to be encrypted
     * @param keyAlias
     * @return The encrypted byte
     */
    public static String encrypt(String plainText, String keyAlias) throws InvalidAlgorithmParameterException, UnrecoverableEntryException, CertificateException, NoSuchAlgorithmException, KeyStoreException, IOException, NoSuchPaddingException, InvalidKeyException, IllegalBlockSizeException, BadPaddingException {
        byte[] data = plainText.getBytes();

        SecretKey secretKey = getSecretKey(keyAlias);

        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS7Padding");

        cipher.init(Cipher.ENCRYPT_MODE, secretKey);
        byte[] iv = cipher.getIV();

        byte[] encrypted = cipher.doFinal(data);
        System.out.println("encrypted_: " + encrypted);
        byte[] ivPlusEncrypted = new byte[iv.length + encrypted.length];

        // The first 16 byte will be the IV
        System.out.println("IV+ENCR len: " + ivPlusEncrypted.length);
        System.out.println("IV len: " + iv.length);
        System.arraycopy(iv, 0, ivPlusEncrypted, 0, iv.length);
        System.arraycopy(encrypted, 0, ivPlusEncrypted, iv.length, encrypted.length);

        System.out.println("Hex: " + bytesToHex(ivPlusEncrypted));
        System.out.println("iv_encr byte: " + ivPlusEncrypted);

        return bytesToHex(ivPlusEncrypted);
    }


    /**
     * @brief Decrypt byte array
     * @param encrypted The encrypted byte containing the IV at the first 16 bytes
     * @param keyAlias The decrypted data into string
     * @return
     * @throws InvalidAlgorithmParameterException
     * @throws UnrecoverableEntryException
     * @throws CertificateException
     * @throws NoSuchAlgorithmException
     * @throws KeyStoreException
     * @throws IOException
     * @throws NoSuchPaddingException
     * @throws InvalidKeyException
     * @throws IllegalBlockSizeException
     * @throws BadPaddingException
     */
    public static  String decrypt(String encrypted__, String keyAlias)
            throws InvalidAlgorithmParameterException,
            UnrecoverableEntryException,
            CertificateException,
            NoSuchAlgorithmException,
            KeyStoreException,
            IOException,
            NoSuchPaddingException,
            InvalidKeyException, IllegalBlockSizeException, BadPaddingException {
        byte[] encrypted = hexToBytes(encrypted__);
        System.out.println("Hex: " + encrypted__);
        System.out.println("iv_encr byte: " + encrypted);
        System.out.println("Encrypted len: " + encrypted.length);
        SecretKey secretKey = getSecretKey(keyAlias);
        byte[] iv = new byte[16];
        System.arraycopy(encrypted, 0, iv, 0, iv.length);
        byte[] encrypted_ = new byte[encrypted.length - iv.length];
        System.out.println("encrypted_: " + encrypted_);
        System.arraycopy(encrypted, iv.length, encrypted_, 0, encrypted_.length);
        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS7Padding");

        cipher.init(Cipher.DECRYPT_MODE, secretKey, new IvParameterSpec(iv));

        byte[] decrypted = cipher.doFinal(encrypted_);

        return new String(decrypted);
    }

    /**
     * Just remove a key from the Android keystore
     * @param alias The alias of the entry
     * @throws KeyStoreException
     * @throws CertificateException
     * @throws IOException
     * @throws NoSuchAlgorithmException
     */
    public static void removeKey(String alias) throws KeyStoreException, CertificateException, IOException, NoSuchAlgorithmException {
        KeyStore keyStore = KeyStore.getInstance("AndroidKeystore");
        keyStore.load(null);
        keyStore.deleteEntry(alias);
    }

    public static String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

    public static byte[] hexToBytes(String hex) {
        int len = hex.length();
        byte[] bytes = new byte[len / 2];
        for (int i = 0; i < len; i += 2) {
            bytes[i / 2] = (byte) ((Character.digit(hex.charAt(i), 16) << 4)
                    + Character.digit(hex.charAt(i+1), 16));
        }
        return bytes;
    }
    public static void testEncryption() throws InvalidAlgorithmParameterException, UnrecoverableEntryException, NoSuchPaddingException, IllegalBlockSizeException, CertificateException, NoSuchAlgorithmException, KeyStoreException, IOException, BadPaddingException, InvalidKeyException {
        String str = "A great Software idea!";
        String alias = "myappkkey333";
        System.out.println("Plain: " + str);
        System.out.println("Encryption...");
        String encrypted = encrypt(str, alias);

        System.out.println("Encrypted: " + new String(encrypted));
        System.out.println("Decryption...");
        String decrypted = decrypt(encrypted, alias);
        System.out.println("Decrypted...");
        System.out.println("Recovered: " + decrypted);
    }
}
