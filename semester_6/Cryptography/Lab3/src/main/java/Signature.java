import java.io.*;
import java.math.BigInteger;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.PublicKey;
import java.security.SecureRandom;
import java.util.Arrays;

public class Signature {

    static BigInteger one = new BigInteger("1");
    static BigInteger two = new BigInteger("2");


    public static boolean checkSign(String path, String pathPublicKey, String pathSign) throws IOException, NoSuchAlgorithmException {
        System.out.println("checking sign");
        Key PublicKey = new Key(pathPublicKey);
        Key Sign = new Key(pathSign);
        BigInteger q = PublicKey.get(0);
        BigInteger p = PublicKey.get(1);
        BigInteger g = PublicKey.get(2);
        BigInteger y = PublicKey.get(3);
        BigInteger r = Sign.get(0);
        BigInteger s = Sign.get(1);

        MessageDigest md5 = MessageDigest.getInstance("MD5");
        md5.update(Files.readAllBytes(Paths.get(path)));
        byte[] digest = md5.digest( );
        BigInteger Hm = new BigInteger( 1, digest );

        // Compute w, such that s*w mod q = 1. w is called the modular multiplicative inverse of s modulo q
        BigInteger w = s.modInverse(q);

        // Compute u1 = H(m)*w mod q
        BigInteger u1 = Hm.multiply(w).mod(q);

        // Compute u2 = r*w mod q
        BigInteger u2 = r.multiply(w).mod(q);

        // Compute v = (((g^u1)*(y^u2)) mod p) mod q
        BigInteger v = g.mod(p).modPow(u1, p).multiply(y.mod(p).modPow(u2, p)).mod(p).mod(q);

        if (r.equals(v)) {
            System.out.println("Schnorr signature is valid");
            return true;
        } else {
            System.out.println("Schnorr signature is not valid");
            return false;
        }
    }

    public static void makeSign(String path, String pathPublicKey, String pathPrivateKey, String pathSign) throws IOException, NoSuchAlgorithmException {
        Key PublicKey = new Key(pathPublicKey);
        Key PrivateKey = new Key(pathPrivateKey);
        BigInteger p = PublicKey.get(1);
        BigInteger q = PublicKey.get(0);
        BigInteger g = PublicKey.get(2);
        BigInteger x = PublicKey.get(3);
        BigInteger y = PrivateKey.get(0);

        SecureRandom sr = new SecureRandom();


        BigInteger k = new BigInteger(q.bitLength(), sr).mod(q).add(BigInteger.ONE);
        BigInteger r = g.modPow(k, p).mod(q);
        BigInteger notK = k.modInverse(q);

        MessageDigest md5 = MessageDigest.getInstance("MD5");
        md5.update(Files.readAllBytes(Paths.get(path)));
        byte[] digest = md5.digest( );
        BigInteger Hm = new BigInteger( 1, digest );
        BigInteger s;
        do
        {
            k = new BigInteger(160, new SecureRandom()).mod(q.subtract(BigInteger.ONE)).add(BigInteger.ONE);

            r = g.modPow(k, p).mod(q);

            if (r.compareTo(BigInteger.ZERO) == 0)
                continue;


            s = notK.multiply(Hm.add(r.multiply(x))).mod(q);

            if (s.compareTo(BigInteger.ZERO) == 0)
                continue;

            break;
        }
        while (true);

        Key Sign = new Key(new BigInteger[]{r, s});
        Sign.writeToFile(pathSign);
        System.out.println("Success!");
    }

    public static void generate(int bitLength, String pathPublicKey, String pathPrivateKey) throws FileNotFoundException {
        System.out.println("generating:");


        BigInteger q, p, a, g, x, y;
        int certainty = 100;
        SecureRandom sr = new SecureRandom();
        q = new BigInteger(bitLength, certainty, sr);

        p = generateP(q);

        g = generateG(bitLength, p, q);

        x = new BigInteger(bitLength, sr).modPow(BigInteger.ONE, q);

        y = g.modPow(x, p);

        Key PublicKey = new Key(new BigInteger[]{q, p, g, y});
        PublicKey.writeToFile(pathPublicKey);
        System.out.println("general public info : (");
        System.out.println(p);
        System.out.println(q);
        System.out.println(g);
        System.out.println(")");
        System.out.print("message public key : ");
        System.out.println(y);

        Key PrivateKey = new Key(new BigInteger[]{x});
        PrivateKey.writeToFile(pathPrivateKey);
        System.out.println("private key:");
        System.out.println(x);
    }

    private static BigInteger generateG(int bitLength,BigInteger p, BigInteger q) {
        BigInteger k, g;
        SecureRandom sr = new SecureRandom();
        while (true) {
            k = (two.add(new BigInteger(bitLength, 100, sr))).mod(p);
            BigInteger power = (p.subtract(BigInteger.ONE)).divide(q);
            g = k.modPow(power, p);
            if (g.compareTo(BigInteger.ONE) != 0)
                return g;
        }
    }

    public static BigInteger generateP(BigInteger q){
        BigInteger qp = BigInteger.ONE;
        BigInteger p;
        while (true){
            p = q.multiply(qp).multiply(two).add(one);
            if (p.isProbablePrime(100))
                return p;
            qp = qp.add(one);
        }
    }
}
