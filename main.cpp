#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// g++ main.cpp

string multiply(string num1, string num2) {
    bool negative = false;
    if (num1[0] == '-') {
        num1.erase(0,1);
        negative = !negative;
    }
    if (num2[0] == '-') {
        num2.erase(0,1);
        negative = !negative;
    }

    string res(num1.size() + num2.size(), '0');
    for (int i = num1.size()-1; i >= 0; i--) {
        int carry = 0;
        for (int j = num2.size()-1; j >= 0; j--) {
            int sum = (res[i + j + 1]-'0') + (num1[i]-'0') * (num2[j]-'0') + carry;
            res[i + j + 1] = sum % 10 + '0';
            carry = sum / 10;
        }
        res[i] += carry;
    }

    int i = 0;
    while(res[i] == '0' && i < res.size()) i++;

    if (i != res.size()) return negative ? "-" + res.substr(i) : res.substr(i);
    return "0";
}

string factorial(int n) {
    string res = "1";
    for (int i = 2; i <= n; i++) {
        res = multiply(res, to_string(i));
    }
    return res;
}

string exponent(string base, int exp) {
    string res = "1";
    for (int i = 0; i < exp; i++) {
        res = multiply(res, base);
    }
    return res;
} 

int main() {
    string running = "y";
    while (running != "n" && running != "no") {
        string ans = "";
        char action;
        int valid_action = 0;
        while (!valid_action) {
            cout << "Please enter a valid action\n\tMutiply: m\n\tFactorial: f\n\tExponent: e" << endl;
            cin >> action;
            if (action == 'm' || action == 'f' || action == 'e') valid_action = 1;
        }
        
        if (action == 'm') {
            string num1, num2;
            cout << "Enter num1 and num2" << endl;
            cin >> num1 >> num2;
            ans = multiply(num1, num2);
        }
        else if (action == 'f') {
            int n;
            cout << "Enter n" << endl;
            cin >> n;
            while (n < 0 || cin.fail()) {
                cout << "n must be a positive integer or 0" << endl;
                cin >> n;
            }
            ans = factorial(n);
        }
        else if (action == 'e') {
            string base;
            int exp;
            cout << "Enter base" << endl; 
            cin >> base;
            cout << "Enter exponent" << endl;
            cin >> exp;
            while (exp < 0 || cin.fail()) {
                cout << "Negative exponents are currently not supported" << endl;
                cin >> exp;
            }
            ans = exponent(base, exp);
        }

        cout << "Your answer is: " << ans << endl << endl;

        cout << "Would you like to calculate another result?\n\tYes: any character\n\tNo: n or no" << endl;
        cin >> running;
        cout << endl;
    }

    return 0;
}