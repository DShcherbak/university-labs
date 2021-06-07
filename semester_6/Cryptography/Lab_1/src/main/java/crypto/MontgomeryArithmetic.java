package crypto;

import java.math.BigInteger;

public class MontgomeryArithmetic {

    BigInteger N;
    BigInteger R;
    BigInteger N1; //N'
    BigInteger R1; //R^-1
    BigInteger R2; // R^2 % N
    int power;

    public MontgomeryArithmetic(BigInteger N){
        power = N.bitLength();
        this.N = N;
        R = BigInteger.ONE.shiftLeft(power);
        var result = Program.expandedEuclid(N, R);
        N1 = result.x.negate();
        R2 = R.multiply(R).mod(N);
    }

    //По суті, (X * R^-1) % N, без самої операції взяття за модулем N
    public BigInteger toMontgomery(BigInteger x){
        BigInteger x_n_mod_R = modR(x.multiply(N1)); //(x * N') mod R
        BigInteger result = x.add(x_n_mod_R.multiply(N)).shiftRight(power);
        while (result.compareTo(N) >= 0) { // must be only one iteration
            result = result.subtract(N);
        }
        return result;
    }

    private BigInteger modR(BigInteger x){
        BigInteger result = BigInteger.ZERO;
        for(int i = power - 1; i >= 0; i--){
            if(x.bitLength() > i){
                BigInteger flipped = x.flipBit(i);
                boolean currentBit = flipped.compareTo(x) < 0;
                result = result.shiftLeft(1);
                if(currentBit){
                    result = result.add(BigInteger.ONE);
                }
            }
        }
        return result;
    }

    public BigInteger multiplication(BigInteger a, BigInteger b){
        BigInteger a1 = toMontgomery(a.multiply(R2));
        BigInteger b1 = toMontgomery(b.multiply(R2));
        BigInteger c1 = toMontgomery(a1.multiply(b1));
        BigInteger c = toMontgomery(c1);
        return c;
    }

    public BigInteger power(BigInteger a, BigInteger exponent){
        BigInteger a1 =  toMontgomery(a.multiply(R2));
        BigInteger x1 = toMontgomery(R2);
        for (int i = exponent.bitLength() - 1; i >= 0; i--) {
            x1 = toMontgomery(x1.multiply(x1));
            if (exponent.testBit(i)) {
                x1 = toMontgomery(x1.multiply(a1));
            }
        }
        return toMontgomery(x1);
    }


}
