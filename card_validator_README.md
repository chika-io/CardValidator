# 💳 Bank Card Validator — Luhn's Algorithm

A command-line C++ program that validates bank card numbers using the **Luhn Algorithm** (ISO/IEC 7812) and identifies the card network.

> Built by [Ukpai Chika Nwakaibeya](https://github.com/chika-io)

---

## Features

- Validates any card number using **Luhn's Algorithm**
- Detects card network: **Visa, Mastercard, American Express, Discover, Verve**
- Accepts card numbers with or without spaces and dashes
- **Masks** the card number for privacy (shows only last 4 digits)
- Input validation with helpful error messages
- Supports multiple validations per session

---

## What is Luhn's Algorithm?

The **Luhn Algorithm** is a simple checksum formula used to validate identification numbers — particularly credit and debit card numbers.

**Steps:**
1. Starting from the **second-to-last digit**, double every second digit going left
2. If doubling a digit gives a result **greater than 9**, subtract 9
3. **Sum all digits** (both doubled and unchanged)
4. If the total is **divisible by 10** → the card is **VALID**

---

## Getting Started

### Prerequisites
- A C++ compiler supporting C++17 (e.g., g++, clang++)

### Compile & Run

```bash
# Compile
g++ -std=c++17 -o card_validator card_validator.cpp

# Run
./card_validator
```

---

## Example Usage

```
╔═════════════════════════════════════════╗
║    BANK CARD VALIDATOR                  ║
║    Luhn's Algorithm  |  github.com/chika-io  ║
╚═════════════════════════════════════════╝

── Card Validation ─────────────────────

Enter card number (spaces/dashes allowed):
> 4532 0151 1283 0366

┌──────────────────────────────────────────┐
│  Card Number  : **** **** ****0366        │
│  Network      : Visa                      │
│  Length       : 16 digits                 │
│  Status       : ✔  VALID                  │
└──────────────────────────────────────────┘

✔  This card number passes the Luhn check.
```

---

## Supported Card Networks

| Network         | Prefix             | Length     |
|-----------------|--------------------|------------|
| Visa            | 4                  | 13 or 16   |
| Mastercard      | 51–55, 2221–2720   | 16         |
| American Express| 34, 37             | 15         |
| Discover        | 6011, 622126+, 65  | 16         |
| Verve           | 5061, 6500–6504    | 16 or 19   |

---

## Project Structure

```
card-validator/
│
├── card_validator.cpp   # Main application file
└── README.md            # Project documentation
```

---

## Skills Demonstrated

- C++ programming (strings, loops, functions)
- Implementation of a real-world algorithm (Luhn / ISO 7812)
- Input sanitization and validation
- CLI application design

---

## Disclaimer

This tool is for **educational purposes only**. It does not verify whether a card is active, funded, or belongs to a real account — only whether the number passes the Luhn checksum.

---

## License

This project is open source and available under the [MIT License](LICENSE).
