import crypto.MontgomeryArithmetic;
import crypto.Program;
import org.junit.jupiter.api.Test;


import java.io.IOException;
import java.math.BigInteger;
import java.security.NoSuchAlgorithmException;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;


class ArithmeticTests {
    
    @Test
    public void testMath() throws IOException, NoSuchAlgorithmException {

        BigInteger A = BigInteger.valueOf(3253);
        assertTrue(Program.checkFermat(A, 5));
        assertTrue(Program.millerRabin(A, 5));


        BigInteger B = BigInteger.valueOf(156);
        BigInteger N = BigInteger.valueOf(11);
        BigInteger c1 = Program.Karatsuba(A, B).mod(N);

        MontgomeryArithmetic ma = new MontgomeryArithmetic(N);
        BigInteger c2 = ma.multiplication(A, B);

        assertTrue(c1.equals(c2));
        assertTrue(ma.power(A,BigInteger.valueOf(5)).equals(BigInteger.valueOf(10)));


    }

    @Test
    void testFermat(){
        assertTrue(Program.checkFermat(BigInteger.valueOf(3253), 5));
        assertTrue(Program.checkFermat(BigInteger.valueOf(13), 5));
        assertTrue(Program.checkFermat(BigInteger.valueOf(17), 5));
        assertFalse(Program.checkFermat(BigInteger.valueOf(18), 10));
        assertFalse(Program.checkFermat(BigInteger.valueOf(24), 10));
    }

    @Test
    void testMillerRabin(){
        assertTrue(Program.millerRabin(BigInteger.valueOf(3253), 5));
        assertTrue(Program.millerRabin(BigInteger.valueOf(13), 5));
        assertTrue(Program.millerRabin(BigInteger.valueOf(17), 5));
        assertFalse(Program.millerRabin(BigInteger.valueOf(18), 5));
        assertFalse(Program.millerRabin(BigInteger.valueOf(24), 5));
    }
}
