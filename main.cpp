#include <iostream>
using namespace std;

class Fib {
private:
    string fib_repr;

    static string normalize(const string& str) {
        int value = toInt(str);
        return fromInt(value);
    }

    static int toInt(const string& str) {
        int sum = 0;
        int f1 = 1; int f2 = 2;
        for (int i = str.size() - 1; i >= 0; i--) {
            if(str[i] == '1') {
                sum += f1;
            }
            int temp = f2;
            f2 = f1 + f2;
            f1 = temp;
        }
        return sum;
    }

    static string fromInt(int num) {
        if (num == 0) return "0";
        string result;
        int a = 1, b = 2;
        while (b <= num) {
            int temp = a + b;
            a = b;
            b = temp;
        }

        bool started = false;
        while (a > 0) {
            if (num >= b) {
                result += '1';
                num -= b;
                started = true;
            } else if(started){
                result += '0';
            }
            int temp = b - a;
            b = a;
            a = temp;
        }
        return result;
    }

public:
    Fib() : fib_repr("0") {}

    Fib(const string& str) {
        string copy = str;
        copy.erase(0, copy.find_first_not_of('0'));
        fib_repr = copy;
    }

    Fib(int num) : fib_repr(fromInt(num)) {}

    Fib(const Fib& other) : fib_repr(other.fib_repr) {}

    friend ostream& operator<<(ostream& os, const Fib& f) {
        return os << f.fib_repr;
    }

    Fib& operator=(const Fib& other) {
        if (this != &other) {
            fib_repr = other.fib_repr;
        }
        return *this;
    }


    Fib operator+(const Fib& other) {
        int num1 = toInt(this->fib_repr);
        int num2 = toInt(other.fib_repr);

        return Fib(fromInt(num1 + num2));
    }

    Fib operator&(const Fib& other) {
        string num1 = normalize(this->fib_repr);
        string num2 = normalize(other.fib_repr);

        if (num1 == num2) {
            return Fib("1");
        }
        return Fib("0");
    }

    Fib operator|(const Fib& other) {
        string num1 = normalize(this->fib_repr);
        string num2 = normalize(other.fib_repr);
        string result;

        if (num1.size() < num2.size()) {
            num1.insert(0, num2.size() - num1.size(), '0');
        } else if (num1.size() > num2.size()) {
            num2.insert(0, num1.size() - num2.size(), '0');
        }

        for (int i = 0; i < num1.size(); i++) {
            if (num1[i] == '1' || num2[i] == '1') {
                result += '1';
            } else {
                result += '0';
            }
        }
        return result;
    }

    Fib operator^(const Fib& other) {
        string num1 = normalize(this->fib_repr);
        string num2 = normalize(other.fib_repr);
        string result;

        if (num1.size() < num2.size()) {
            num1.insert(0, num2.size() - num1.size(), '0');
        } else if (num1.size() > num2.size()) {
            num2.insert(0, num1.size() - num2.size(), '0');
        }

        for (int i = 0; i < num1.size(); i++) {
            if ((num1[i] == '1' && num2[i] == '0') || (num1[i] == '0' && num2[i] == '1')) {
                result += '1';
            } else {
                result += '0';
            }
        }
        return Fib(result);
    }
};

int main() {
    Fib f1("11");  // 1001 = F_6 + F_3 = 8 + 2 = 10
    Fib f2("110010");    // 10 = F_3 = 2

    Fib f3 = Fib("1001") ^ Fib("1010");

    std::cout << "f1: " << f1 << std::endl; // 1001
    std::cout << "f2: " << f2 << std::endl; // 10
    std::cout << "f3: " << f3 << std::endl; // Expected output: "10010"



    return 0;
}
