import org.junit.jupiter.api.Test;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.security.NoSuchAlgorithmException;
import java.util.List;

import static org.junit.Assert.*;

class SignatureTest {
    static String pathSign = "Sign.txt";
    static String pathPublicKey = "PublicKey.txt";
    static String pathPublicKeyTest = "PublicKeyTest.txt";
    static String pathPrivateKey = "PrivateKey.txt";
    static String pathPrivateKeyTest = "PrivateKeyTest.txt";
    static String pathFragment = "Signed information.txt";
    @Test
    void encryptionAndDecryption() throws IOException, NoSuchAlgorithmException {
        Main.generate(1000,pathPublicKeyTest,pathPrivateKeyTest);

        Main.makeSign(pathFragment, pathPublicKey, pathPrivateKey, pathSign);

        assertTrue(Main.checkSign(pathFragment, pathPublicKey, pathSign));
        assertFalse(Main.checkSign(pathFragment, pathPublicKeyTest, pathSign));
    }
}
