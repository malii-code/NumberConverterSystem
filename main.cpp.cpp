#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unordered_map>

// The NumberConverter class encapsulates all the number system conversion logic.
// This object-oriented approach improves code organization and reusability.
class NumberConverter {
public:
    // This function converts a number from any base (binary, octal, hex) to decimal.
    // It serves as the core "bridge" for all other conversions.
    // Parameters:
    //   - input: The number to convert as a string.
    //   - base: The base of the input number (e.g., 2 for binary, 8 for octal).
    // Returns:
    //   The decimal equivalent as a long long. Returns -1 on error.
    long long toDecimal(const std::string& input, int base) {
        long long decimal = 0;
        long long power = 1;
        
        // Create a copy of the input string to reverse it for easier processing.
        std::string s = input;
        std::reverse(s.begin(), s.end());

        // Iterate through the string from right to left (least significant digit to most).
        for (char c : s) {
            int digit;
            // Use a pre-defined map for hexadecimal character-to-value conversion.
            if (base == 16) {
                if (hexToDecimalMap.count(c)) {
                    digit = hexToDecimalMap.at(c);
                } else {
                    std::cerr << "Error: Invalid hexadecimal digit '" << c << "'\n";
                    return -1; // Return -1 to signal an error.
                }
            } else {
                // For other bases, convert the character '0'-'9' to an integer.
                digit = c - '0';
            }

            // Validate that the digit is valid for the given base.
            if (digit < 0 || digit >= base) {
                std::cerr << "Error: Invalid digit '" << c << "' for base " << base << "\n";
                return -1;
            }

            // Calculate the positional value and add it to the total decimal number.
            decimal += digit * power;
            // Update the power for the next position.
            power *= base;
        }
        return decimal;
    }

    // This function converts a decimal number to any target base (binary, octal, hex).
    // It works by repeatedly dividing the decimal number by the target base.
    // Parameters:
    //   - decimal: The decimal number to convert.
    //   - base: The target base (2, 8, or 16).
    // Returns:
    //   The converted number as a string.
    std::string fromDecimal(long long decimal, int base) {
        if (decimal == 0) {
            return "0";
        }
        std::string result = "";
        while (decimal > 0) {
            int remainder = decimal % base;
            // Use a map to handle hex characters for remainders 10-15.
            if (base == 16) {
                result += decimalToHexMap.at(remainder);
            } else {
                result += std::to_string(remainder);
            }
            decimal /= base;
        }
        // The digits are generated in reverse order, so we reverse the string.
        std::reverse(result.begin(), result.end());
        return result;
    }

private:
    // Maps used for efficient hexadecimal character-to-value conversion.
    // This is a cleaner approach than using a series of if/else statements.
    std::unordered_map<char, int> hexToDecimalMap = {
        {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
        {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15},
        {'a', 10}, {'b', 11}, {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}
    };
    std::unordered_map<int, char> decimalToHexMap = {
        {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'},
        {10, 'A'}, {11, 'B'}, {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'}
    };
};

// A helper function to handle conversions between non-decimal bases.
// This function reduces code duplication in the main menu loop.
void performConversion(NumberConverter& converter, int fromBase, int toBase, const std::string& fromName, const std::string& toName) {
    std::string input;
    std::cout << "Enter " << fromName << " number: ";
    std::cin >> input;

    long long decimalValue = converter.toDecimal(input, fromBase);
    // Only proceed if the conversion to decimal was successful.
    if (decimalValue != -1) {
        std::string result = converter.fromDecimal(decimalValue, toBase);
        std::cout << toName << " equivalent: " << result << "\n";
    }
}

// The main entry point of the program.
// It manages the user interface, displays the menu, and calls the appropriate
// conversion functions based on the user's choice.
int main() {
    NumberConverter converter;
    int choice;
    std::string input;

    do {
        std::cout << "\nNumber System Converter\n";
        std::cout << "-----------------------\n";
        std::cout << "1. Binary to Decimal\n";
        std::cout << "2. Decimal to Binary\n";
        std::cout << "3. Octal to Decimal\n";
        std::cout << "4. Decimal to Octal\n";
        std::cout << "5. Hexadecimal to Decimal\n";
        std::cout << "6. Decimal to Hexadecimal\n";
        std::cout << "7. Binary to Octal\n";
        std::cout << "8. Octal to Binary\n";
        std::cout << "9. Binary to Hexadecimal\n";
        std::cout << "10. Hexadecimal to Binary\n";
        std::cout << "11. Octal to Hexadecimal\n";
        std::cout << "12. Hexadecimal to Octal\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                performConversion(converter, 2, 10, "binary", "Decimal");
                break;
            case 2:
                performConversion(converter, 10, 2, "decimal", "Binary");
                break;
            case 3:
                performConversion(converter, 8, 10, "octal", "Decimal");
                break;
            case 4:
                performConversion(converter, 10, 8, "decimal", "Octal");
                break;
            case 5:
                performConversion(converter, 16, 10, "hexadecimal", "Decimal");
                break;
            case 6:
                performConversion(converter, 10, 16, "decimal", "Hexadecimal");
                break;
            case 7:
                performConversion(converter, 2, 8, "binary", "Octal");
                break;
            case 8:
                performConversion(converter, 8, 2, "octal", "Binary");
                break;
            case 9:
                performConversion(converter, 2, 16, "binary", "Hexadecimal");
                break;
            case 10:
                performConversion(converter, 16, 2, "hexadecimal", "Binary");
                break;
            case 11:
                performConversion(converter, 8, 16, "octal", "Hexadecimal");
                break;
            case 12:
                performConversion(converter, 16, 8, "hexadecimal", "Octal");
                break;
            case 0:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}