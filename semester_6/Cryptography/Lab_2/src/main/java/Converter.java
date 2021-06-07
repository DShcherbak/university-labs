public class Converter {
    public static byte[] intToByte(int[] integerArray, int length) {
        byte[] result = new byte[length];
        for (int i = 0; i < length; i++) {
            result[i] = (byte) ((integerArray[i / 4] >>> (i % 4) * 8) & 0xff);
        }
        return result;
    }

    public static int[] byteToInt(byte[] bytes, int length) {
        int[] result = new int[length];

        int counter = 0;
        for (int i = 0; i < result.length; i++) {
            result[i] = ((bytes[counter++] & 0xff)) |
                            ((bytes[counter++] & 0xff) << 8) |
                            ((bytes[counter++] & 0xff) << 16) |
                            ((bytes[counter++] & 0xff) << 24);
        }
        return result;
    }

    public static byte[] stringToBytes(String s) {
        int length = s.length();
        byte[] result = new byte[length / 2];
        for (int i = 0; i < length; i += 2) {
            result[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4)
                    + Character.digit(s.charAt(i + 1), 16));
        }
        return result;
    }

    public static String bytesToString(byte[] bytes) {
        StringBuilder sb = new StringBuilder(bytes.length * 2);
        for (byte b : bytes)
            sb.append(String.format("%02x ", b & 0xff));
        return sb.toString();
    }

    public static int[] bytesToWords(byte[] userKey, int length) {
        int[] result = new int[length];

        for (int i = 0, offset = 0; i < length; i++)
            result[i] = ((userKey[offset++] & 0xFF)) |
                            ((userKey[offset++] & 0xFF) << 8) |
                            ((userKey[offset++] & 0xFF) << 16) |
                            ((userKey[offset++] & 0xFF) << 24);

        return result;
    }
}
