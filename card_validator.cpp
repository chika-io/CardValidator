/*
 * ============================================
 *   Bank Card Validator — Luhn's Algorithm
 *   Author : Ukpai Chika Nwakaibeya
 *   GitHub : https://github.com/chika-io
 *   Lang   : C++17
 * ============================================
 *
 * Validates a bank card number using the Luhn
 * Algorithm (ISO/IEC 7812) and identifies the
 * card network (Visa, Mastercard, Amex, etc.)
 *
 * Compile : g++ -std=c++17 -o card_validator card_validator.cpp
 * Run     : ./card_validator
 * ============================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// ─────────────────────────────────────────────
//  CARD NETWORK DETECTION
// ─────────────────────────────────────────────

struct CardNetwork {
    string name;
    string icon;
};

CardNetwork detectNetwork(const string& number) {
    int len = number.length();

    // Visa: starts with 4, length 13 or 16
    if (number[0] == '4' && (len == 13 || len == 16))
        return {"Visa", "💳"};

    // Mastercard: starts with 51-55 or 2221-2720, length 16
    if (len == 16) {
        int prefix2 = stoi(number.substr(0, 2));
        int prefix4 = stoi(number.substr(0, 4));
        if (prefix2 >= 51 && prefix2 <= 55)
            return {"Mastercard", "💳"};
        if (prefix4 >= 2221 && prefix4 <= 2720)
            return {"Mastercard", "💳"};
    }

    // American Express: starts with 34 or 37, length 15
    if (len == 15) {
        string prefix2 = number.substr(0, 2);
        if (prefix2 == "34" || prefix2 == "37")
            return {"American Express", "💳"};
    }

    // Discover: starts with 6011, 622126-622925, 644-649, 65, length 16
    if (len == 16) {
        string prefix4 = number.substr(0, 4);
        string prefix2 = number.substr(0, 2);
        int prefix6 = stoi(number.substr(0, 6));
        if (prefix4 == "6011") return {"Discover", "💳"};
        if (prefix6 >= 622126 && prefix6 <= 622925) return {"Discover", "💳"};
        if (prefix2 == "65") return {"Discover", "💳"};
        string prefix3 = number.substr(0, 3);
        int p3 = stoi(prefix3);
        if (p3 >= 644 && p3 <= 649) return {"Discover", "💳"};
    }

    // Verve: starts with 5061, 6500, 6501, 6504 (Nigerian card), length 16 or 19
    if (len == 16 || len == 19) {
        string prefix4 = number.substr(0, 4);
        if (prefix4 == "5061" || prefix4 == "6500" ||
            prefix4 == "6501" || prefix4 == "6504")
            return {"Verve", "💳"};
    }

    return {"Unknown Network", "❓"};
}

// ─────────────────────────────────────────────
//  LUHN'S ALGORITHM
//
//  Steps:
//  1. Starting from the second-to-last digit,
//     double every second digit going left.
//  2. If doubling gives a number > 9, subtract 9.
//  3. Sum all digits (doubled and unchanged).
//  4. If total % 10 == 0 → VALID.
// ─────────────────────────────────────────────

bool luhnCheck(const string& number) {
    int total = 0;
    int len   = number.length();
    bool doubleIt = false;   // start doubling from second-to-last digit

    for (int i = len - 1; i >= 0; i--) {
        int digit = number[i] - '0';

        if (doubleIt) {
            digit *= 2;
            if (digit > 9) digit -= 9;
        }

        total    += digit;
        doubleIt  = !doubleIt;
    }

    return (total % 10 == 0);
}

// ─────────────────────────────────────────────
//  HELPERS
// ─────────────────────────────────────────────

void printBanner() {
    cout << "\n";
    cout << "  ╔═════════════════════════════════════════╗\n";
    cout << "  ║    BANK CARD VALIDATOR                  ║\n";
    cout << "  ║    Luhn's Algorithm  |  github.com/chika-io  ║\n";
    cout << "  ╚═════════════════════════════════════════╝\n\n";
}

// Sanitize input: remove spaces and dashes
string sanitize(const string& input) {
    string result;
    for (char c : input) {
        if (isdigit(c)) result += c;
    }
    return result;
}

// Format card number with spaces every 4 digits
string formatCard(const string& number) {
    string formatted;
    for (int i = 0; i < (int)number.length(); i++) {
        if (i > 0 && i % 4 == 0) formatted += ' ';
        formatted += number[i];
    }
    return formatted;
}

// Mask card number: show only last 4 digits
string maskCard(const string& number) {
    string masked;
    int len = number.length();
    for (int i = 0; i < len - 4; i++) {
        if (i > 0 && i % 4 == 0) masked += ' ';
        masked += '*';
    }
    if (len >= 4) {
        if ((len - 4) % 4 != 0) masked += ' ';
        masked += number.substr(len - 4);
    }
    return masked;
}

bool isValidInput(const string& number) {
    if (number.empty()) return false;
    for (char c : number) {
        if (!isdigit(c)) return false;
    }
    // Standard card lengths
    int len = number.length();
    return (len >= 13 && len <= 19);
}

void printResult(const string& number, bool valid) {
    CardNetwork network = detectNetwork(number);

    cout << "\n  ┌──────────────────────────────────────────┐\n";
    cout << "  │  Card Number  : " << left << setw(26) << maskCard(number) << "│\n";
    cout << "  │  Network      : " << left << setw(26) << network.name     << "│\n";
    cout << "  │  Length       : " << left << setw(26) << (to_string(number.length()) + " digits") << "│\n";

    if (valid) {
        cout << "  │  Status       : ✔  VALID                  │\n";
    } else {
        cout << "  │  Status       : ✖  INVALID                │\n";
    }

    cout << "  └──────────────────────────────────────────┘\n\n";

    if (valid) {
        cout << "  ✔  This card number passes the Luhn check.\n\n";
    } else {
        cout << "  ✖  This card number fails the Luhn check.\n";
        cout << "     It may contain a typo or be fabricated.\n\n";
    }
}

// ─────────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────────

int main() {
    printBanner();

    char again = 'y';

    while (tolower(again) == 'y') {

        cout << "  ── Card Validation ─────────────────────\n\n";
        cout << "  Enter card number (spaces/dashes allowed):\n  > ";

        string input;
        getline(cin, input);

        string number = sanitize(input);

        if (!isValidInput(number)) {
            cout << "\n  ⚠  Invalid input. Card numbers must be\n";
            cout << "     13–19 digits. Please try again.\n\n";
        } else {
            bool valid = luhnCheck(number);
            printResult(number, valid);
        }

        cout << "  ─────────────────────────────────────────\n";
        cout << "  Validate another card? (y/n): ";
        string choice;
        getline(cin, choice);
        again = choice.empty() ? 'n' : choice[0];
        cout << "\n";
    }

    cout << "  Thanks for using Card Validator. Goodbye!\n\n";
    return 0;
}
