import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class EncryptionTest {
    @Test
    void run() {
        Program.runEncryption();
        Program.runDecryption();
        Assertions.assertEquals(Program.originalText, Program.decryptedText);
    }
}
