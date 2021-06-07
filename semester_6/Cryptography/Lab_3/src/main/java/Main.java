import java.io.FileNotFoundException;
import java.io.IOException;
import java.math.BigInteger;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.spec.ECField;
import java.util.Scanner;
import java.security.*;

public class Main {
    static String pathSign = "Sign.txt";
    static String pathPublicKey = "PublicKey.txt";
    static String pathPrivateKey = "PrivateKey.txt";

    public static boolean checkSign(String path, String pathPublicKey, String pathSign) throws IOException, NoSuchAlgorithmException {
        System.out.println("checking sign");
        Key PublicKey = new Key(pathPublicKey);
        Key Sign = new Key(pathSign);
        BigInteger p = PublicKey.get(0);
        BigInteger q = PublicKey.get(1);
        BigInteger g = PublicKey.get(2);
        BigInteger y = PublicKey.get(3);
        BigInteger r = Sign.get(0);
        BigInteger s = Sign.get(1);

        MessageDigest md5 = MessageDigest.getInstance("MD5");
        md5.update(Files.readAllBytes(Paths.get(path)));
        byte[] digest = md5.digest( );
        BigInteger Hm = new BigInteger( 1, digest );

        // w = s^-1 mod q
        BigInteger w = s.modInverse(q);

        // u1 = H(m)*w mod q
        BigInteger u1 = Hm.multiply(w).mod(q);

        // u2 = r*w mod q
        BigInteger u2 = r.multiply(w).mod(q);

        // v = (((g^u1)*(y^u2)) mod p) mod q
        BigInteger gu1 = g.modPow(u1, p);
        BigInteger yu2 = y.modPow(u2, p);
        BigInteger v = gu1.multiply(yu2).mod(p).mod(q);

        if (r.equals(v)) {
            System.out.println("DSA is valid");
            return true;
        } else {
            System.out.println("DSA is not valid");
            return false;
        }
    }

    public static void makeSign(String path, String pathPublicKey, String pathPrivateKey, String pathSign) throws IOException, NoSuchAlgorithmException {
        Key PublicKey = new Key(pathPublicKey);
        Key PrivateKey = new Key(pathPrivateKey);
        BigInteger p = PublicKey.get(0);
        BigInteger q = PublicKey.get(1);
        BigInteger g = PublicKey.get(2);
        BigInteger x = PrivateKey.get(0);

        SecureRandom sr = new SecureRandom();

        BigInteger k = new BigInteger(q.bitLength(), sr).mod(q).add(BigInteger.ONE);
        BigInteger r;
        BigInteger notK;

        MessageDigest md5 = MessageDigest.getInstance("MD5");
        md5.update(Files.readAllBytes(Paths.get(path)));
        byte[] digest = md5.digest( );
        BigInteger Hm = new BigInteger( 1, digest );
        BigInteger s;
        do
        {
            k = new BigInteger(160, new SecureRandom()).mod(q.subtract(BigInteger.ONE)).add(BigInteger.ONE);
            notK = k.modInverse(q);
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
        System.out.println("Signing complete!");
    }

    public static void generate(int bitLength, String pathPublicKey, String pathPrivateKey) throws FileNotFoundException {
        int certainty = 100;
        SecureRandom sr = new SecureRandom();
        BigInteger q = new BigInteger(bitLength, certainty, sr);

        BigInteger p = generateP(q);

        BigInteger g = generateG(bitLength, p, q);

        BigInteger x = new BigInteger(bitLength, sr).mod(q);

        BigInteger y = g.modPow(x, p);

        Key PublicKey = new Key(new BigInteger[]{p,q, g, y});
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
            k = BigInteger.TWO.add(new BigInteger(bitLength, 100, sr)).mod(p);
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
            p = q.multiply(qp).multiply(BigInteger.TWO).add(BigInteger.ONE);
            if (p.isProbablePrime(100))
                return p;
            qp = qp.add(BigInteger.ONE);
        }
    }

    public static void main(String[] args) throws NoSuchAlgorithmException, IOException {

        String fileToSign = "Signed information.txt";
        int bitSize = 4;

        generate(bitSize, pathPublicKey, pathPrivateKey);
        makeSign(fileToSign, pathPublicKey, pathPrivateKey, pathSign);
        checkSign(fileToSign, pathPublicKey, pathSign);
    }
}