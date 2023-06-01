#include <iostream>
#include <vector>
#include <sstream>
#include <tgmath.h>

using namespace std;

const int MAX_BASE = 36;

string getBaseXFrom10(string numStr, int toBase) {
    const int charConversion = 48;
    istringstream iss(numStr);
    unsigned long long num;
    iss >> num;    
    string reversedConvertedStr;
    while (num > 0) {
        int tempDigit = num % toBase;
        if (tempDigit > 9) {
            tempDigit += 7;
        }
        reversedConvertedStr += tempDigit + charConversion;
        num /= toBase;
    }
    string resultStr = "";
    for (int i = reversedConvertedStr.size() - 1; i >= 0; i--) {
        resultStr += reversedConvertedStr[i];
    }
    return resultStr;
}

string toBase10(string num, int fromBase) {
    unsigned long long base10Result = 0;
    int power = num.length() - 1;
    int digitAmount;
    for (int i = 0; i < num.length(); i++) {
        if ((int)num[i] <= 57) {
            digitAmount = (int)num[i] - 48;
        } else {
            digitAmount = (int)num[i] - 48 - 7;
        }
        base10Result += digitAmount * pow(fromBase, power);
        power--;
    }
    return to_string(base10Result);
}

int mainMenu() {
    int choise;
    do
    {
        cout << "1. Convert from one base to another" << endl;
        cout << "2. RBG to hexadecimal" << endl;
        cout << "3. Hexadecimal to RGB" << endl;
        cout << "4. List numbers of chosen base" << endl;
        cout << "5. Quit" << endl;
        cout << "Choose: " << endl;
        cin >> choise;
    } while (choise < 1 || choise > 5);
    
}

bool isValidBase(int base) {
    if (base > MAX_BASE || base < 2) {
        cout << "Base must be between 2 and " << MAX_BASE << endl;
        return false;
    }
    return true;
}

bool isValidBaseInput(string num, int fromBase) {
    bool isValid = true;
    for (char ch : num) {        
        if (ch < 48) {                        
            isValid = false;
        }
        if (fromBase <= 10 && (ch - 48 > fromBase)) {
            isValid = false;
        }
        if (fromBase >= 11 && ((ch >= 58 && ch <= 64) || (ch > 65 + (fromBase - 11)))) {
            isValid = false;
        }
        if (fromBase > 10 && (ch < 48 || ((ch > 57 && ch < 65) || (ch > 65 + (fromBase - 11))))) {
            isValid = false;
        }
    }
    if (!isValid) {
        cout << "This is not a valid base-" << fromBase << " number." << endl;
        return false;
    }
    return true;
}

void baseToBase() {
    string num;
    int toBase;
    int fromBase;
    string result;
        do {
            cout << "Convert from base (max " << MAX_BASE << "): ";
            cin >> fromBase;
        } while (!isValidBase(fromBase));

        do {
            cout << "Convert to base (max " << MAX_BASE << "): ";
            cin >> toBase;
        } while (!isValidBase(fromBase));

        cout << "Converting from base " << fromBase << " to base " << toBase << "." << endl;
        do {
            cout << "Enter base " << fromBase << "-number to convert: ";
            cin >> num;
        } while (!isValidBaseInput(num, fromBase));

        if (fromBase == 10) {
            result = getBaseXFrom10(num, toBase);
        } else {
            string base10Str = toBase10(num, fromBase);
            result = getBaseXFrom10(base10Str, toBase);            
        }

        cout << "\n\nbase-" << fromBase << " (" << num << ") " << " in base-" << toBase << " is:\n" << result << endl;   
}

void countNumbers() {
    int base;
    do
    {
        cout << "Chose base: ";            
        cin >> base;
    } while (!isValidBase(base));

    cout << "Count up to number (base 10): ";
    int maxCount; cin >> maxCount;
    for (int i = 0; i < maxCount; i++) {
        cout << i + 1 << " = ";
        cout << getBaseXFrom10(to_string(i+1), base) << endl;
    }
}

void rgbToHex() {
    cout << "not implemented";
}

void hexToRgb() {
    cout << "not implemented" << endl;
}

int main() {
    while (true) {
        int menuChoise = mainMenu();
        switch (menuChoise) {
            case 1:
                baseToBase();
                break;
            case 2:
                rgbToHex();
                break;
            case 3:
                hexToRgb();
                break;
            case 4:
                countNumbers();
                break;
            case 5:
                return 0;
                break;
        }
    }
    return 0;
}