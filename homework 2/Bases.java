/**
 * CS 2110 Spring 2019 HW2
 * Part 2 - Coding with bases
 *
 * @author Ishan Arya
 * <p>
 * Global rules for this file:
 * - You may not use more than 2 conditionals per method. Conditionals are
 * if-statements, else-if statements, or ternary expressions. The else block
 * associated with an if-statement does not count toward this sum. Boolean
 * expressions outside of if-statements, else-if statements and ternary
 * expressions do not count toward this sum either.
 * - You may not use more than 2 looping constructs per method. Looping
 * constructs include for loops, while loops and do-while loops.
 * - You may not use nested loops.
 * - You may not declare any file-level variables.
 * - You may not declare any objects, other than String in select methods.
 * - You may not use switch statements.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any other method from this or
 * another file to implement any method.
 * - The only Java API methods you are allowed to invoke are:
 * String.length()
 * String.charAt()
 * - You may not invoke the above methods from string literals.
 * Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 * is a single digit.
 * <p>
 * Method-specific rules for this file:
 * - You may not use multiplication, division or modulus in any method, EXCEPT
 * decimalStringToInt.
 * - You may declare exactly one String variable each in intToBinaryString, intToOctalString,
 * and intToHexString.
 */
public class Bases {
    /**
     * Convert a string containing ASCII characters (in binary) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid binary numbers, and able to fit in a 32-bit signed integer.
     * <p>
     * Example: binaryStringToInt("111"); // => 7
     */
    public static int binaryStringToInt(String binary) {
        int total = 0;
        for (int i = binary.length() - 1; i >= 0; i--) {
            char thisChar = binary.charAt(i);
            int digit = (int) thisChar - 48;
            int decimalValue = digit << (binary.length() - 1 - i);
            total += decimalValue;
        }

        return total;
    }

    /**
     * Convert a string containing ASCII characters (in decimal) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid decimal numbers, and able to fit in a 32-bit signed integer.
     * <p>
     * Example: decimalStringToInt("123"); // => 123
     * <p>
     * You may use multiplication, division, and modulus in this method.
     */
    public static int decimalStringToInt(String decimal) {
        int total = 0;
        int multiplier = 1;
        for (int i = decimal.length() - 1; i >= 0; i--) {
            char thisChar = decimal.charAt(i);
            int digit = (int) thisChar - 48;
            int decimalValue = digit * multiplier;
            total += decimalValue;
            multiplier *= 10;
        }

        return total;
    }

    /**
     * Convert a string containing ASCII characters (in octal) to an int.
     * The input string will only contain the numbers 0-7. You do not need to handle
     * negative numbers. The strings we will pass in will be valid octal numbers, and
     * able to fit in a 32-bit signed integer.
     * <p>
     * Example: octalStringToInt("17"); // => 15
     */
    public static int octalStringToInt(String octal) {
        int total = 0;
        int shift = 0;
        for (int i = octal.length() - 1; i >= 0; i--) {
            char thisChar = octal.charAt(i);
            int digit = (int) thisChar - 48;
            int decimalValue = digit << shift;
            total += decimalValue;
            shift += 3;
        }

        return total;
    }

    /**
     * Convert a string containing ASCII characters (in hex) to an int.
     * The input string will only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid hexadecimal numbers, and able to fit in a 32-bit signed integer.
     * <p>
     * Example: hexStringToInt("A6"); // => 166
     */
    public static int hexStringToInt(String hex) {
        int total = 0;
        int shift = 0;
        for (int i = hex.length() - 1; i >= 0; i--) {
            char thisChar = hex.charAt(i);
            int digit = (int) thisChar - 48;
            if (digit > 9) {
                digit -= 7;
            }
            int decimalValue = digit << shift;
            total += decimalValue;
            shift += 4;
        }

        return total;
    }

    /**
     * Convert a int into a String containing ASCII characters (in binary).
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters necessary to
     * represent the number that was passed in.
     * <p>
     * Example: intToBinaryString(7); // => "111"
     * <p>
     * You may declare one String variable in this method.
     */
    public static String intToBinaryString(int binary) {
        if (binary == 0) {
            return "0";
        }
        String binaryString = "";
        while (binary > 0) {
            binaryString = (binary & 1) + binaryString;
            binary = binary >> 1;
        }

        return binaryString;
    }

    /**
     * Convert a int into a String containing ASCII characters (in octal).
     * The output string should only contain numbrs 0-7.
     * Tou do not need to handle negative numbers.
     * The String returned should contain the minimum numbers of characters necessary to
     * represent the number that was passed in.
     * <p>
     * Example: intToOctalString(17); // => "21"
     */
    public static String intToOctalString(int octal) {
        if (octal == 0) {
            return "0";
        }
        String octalString = "";
        while (octal > 0) {
            octalString = (octal & 7) + octalString;
            octal = octal >> 3;
        }

        return octalString;
    }

    /**
     * Convert a int into a String containing ASCII characters (in hexadecimal).
     * The output string should only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters necessary to
     * represent the number that was passed in.
     * <p>
     * Example: intToHexString(166); // => "A6"
     * <p>
     * You may declare one String variable in this method.
     */
    public static String intToHexString(int hex) {
        if (hex == 0) {
            return "0";
        }
        String hexString = "";
        while (hex > 0) {
            char currentDigit = (char) ((hex & 15) + 48);
            if (currentDigit > 57) {
                currentDigit += 7;
            }
            hexString = currentDigit + hexString;
            hex = hex >> 4;
        }

        return hexString;
    }
}
