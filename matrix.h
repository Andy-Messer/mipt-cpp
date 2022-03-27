#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include<cmath>

namespace TYPES::BIGINTEGER {
//--------------------------------------------------------------------------------------------------------------------//
/*
████████╗██╗░░██╗███████╗       ██████╗░███████╗░██████╗░██╗███╗░░██╗███╗░░██╗██╗███╗░░██╗░██████╗░
╚══██╔══╝██║░░██║██╔════╝       ██╔══██╗██╔════╝██╔════╝░██║████╗░██║████╗░██║██║████╗░██║██╔════╝░
░░░██║░░░███████║█████╗░░       ██████╦╝█████╗░░██║░░██╗░██║██╔██╗██║██╔██╗██║██║██╔██╗██║██║░░██╗░
░░░██║░░░██╔══██║██╔══╝░░       ██╔══██╗██╔══╝░░██║░░╚██╗██║██║╚████║██║╚████║██║██║╚████║██║░░╚██╗
░░░██║░░░██║░░██║███████╗       ██████╦╝███████╗╚██████╔╝██║██║░╚███║██║░╚███║██║██║░╚███║╚██████╔╝
░░░╚═╝░░░╚═╝░░╚═╝╚══════╝       ╚═════╝░╚══════╝░╚═════╝░╚═╝╚═╝░░╚══╝╚═╝░░╚══╝╚═╝╚═╝░░╚══╝░╚═════╝░

░█████╗░███████╗        ██╗░░██╗███████╗██╗░░░░░██╗░░░░░
██╔══██╗██╔════╝        ██║░░██║██╔════╝██║░░░░░██║░░░░░
██║░░██║█████╗░░        ███████║█████╗░░██║░░░░░██║░░░░░
██║░░██║██╔══╝░░        ██╔══██║██╔══╝░░██║░░░░░██║░░░░░
╚█████╔╝██║░░░░░        ██║░░██║███████╗███████╗███████╗
*/
//--------------------------------------------------------------------------------------------------------------------//


    using std::string;
    using std::vector;
//из записок Грустного кота (BIGINTEGER, edition of Sad_cat)




//--------------------------------------------------------------------------------------------------------------------//
/*
████████╗██╗░░██╗███████╗       ██████╗░██╗░██████╗░░██████╗░███████╗░██████╗████████╗      ██╗███╗░░██╗████████╗
╚══██╔══╝██║░░██║██╔════╝       ██╔══██╗██║██╔════╝░██╔════╝░██╔════╝██╔════╝╚══██╔══╝      ██║████╗░██║╚══██╔══╝
░░░██║░░░███████║█████╗░░       ██████╦╝██║██║░░██╗░██║░░██╗░█████╗░░╚█████╗░░░░██║░░░      ██║██╔██╗██║░░░██║░░░
░░░██║░░░██╔══██║██╔══╝░░       ██╔══██╗██║██║░░╚██╗██║░░╚██╗██╔══╝░░░╚═══██╗░░░██║░░░      ██║██║╚████║░░░██║░░░
░░░██║░░░██║░░██║███████╗       ██████╦╝██║╚██████╔╝╚██████╔╝███████╗██████╔╝░░░██║░░░      ██║██║░╚███║░░░██║░░░
░░░╚═╝░░░╚═╝░░╚═╝╚══════╝       ╚═════╝░╚═╝░╚═════╝░░╚═════╝░╚══════╝╚═════╝░░░░╚═╝░░░      ╚═╝╚═╝░░╚══╝░░░╚═╝░░░

██╗███╗░░██╗        ████████╗██╗░░██╗███████╗       ░██╗░░░░░░░██╗██╗██╗░░░░░██████╗░
██║████╗░██║        ╚══██╔══╝██║░░██║██╔════╝       ░██║░░██╗░░██║██║██║░░░░░██╔══██╗
██║██╔██╗██║        ░░░██║░░░███████║█████╗░░       ░╚██╗████╗██╔╝██║██║░░░░░██║░░██║
██║██║╚████║        ░░░██║░░░██╔══██║██╔══╝░░       ░░████╔═████║░██║██║░░░░░██║░░██║
██║██║░╚███║        ░░░██║░░░██║░░██║███████╗       ░░╚██╔╝░╚██╔╝░██║███████╗██████╔╝
╚═╝╚═╝░░╚══╝        ░░░╚═╝░░░╚═╝░░╚═╝╚══════╝       ░░░╚═╝░░░╚═╝░░╚═╝╚══════╝╚═════╝░

░██╗░░░░░░░██╗███████╗░██████╗████████╗
░██║░░██╗░░██║██╔════╝██╔════╝╚══██╔══╝
░╚██╗████╗██╔╝█████╗░░╚█████╗░░░░██║░░░
░░████╔═████║░██╔══╝░░░╚═══██╗░░░██║░░░
░░╚██╔╝░╚██╔╝░███████╗██████╔╝░░░██║░░░
░░░╚═╝░░░╚═╝░░╚══════╝╚═════╝░░░░╚═╝░░░
*/
//--------------------------------------------------------------------------------------------------------------------//


    class BigInteger {
    public:
        BigInteger() {
            isPositive = true;
            number = {0};
        };

        BigInteger(int newValue) : isPositive(true) {
            CheckSignAndABS(newValue);
            StitchingNumber(newValue);
        }

        BigInteger(const string &newValue) : isPositive(true) {
            CheckSign(newValue);
            LocalPars(newValue);
            Coup(newValue);
        }

        BigInteger(const BigInteger &x) {
            isPositive = x.isPositive;
            number = x.number;
        }

        BigInteger &operator=(const BigInteger &other) {
            BigInteger copy(other);
            std::swap(number, copy.number);
            std::swap(isPositive, copy.isPositive);
            return *this;
        }

        ~BigInteger() {
            number.clear();
        }

        explicit operator bool() const {
            return !(number.size() == 1 && number[0] == 0);
        }

        string toString() const {
            string s;
            CheckSign(s);
            StitchingString(s);
            return s;
        }


        bool operator!=(const BigInteger &other) const {
            return Comparator(*this, other) != 1;
        }

        bool operator<(const BigInteger &other) const {
            return Comparator(*this, other) == 3;
        }

        bool operator>(const BigInteger &other) const {
            return Comparator(*this, other) == 2;
        }

        bool operator>=(const BigInteger &other) const {
            int res = Comparator(*this, other);
            return res == 2 || res == 1;
        }

        bool operator<=(const BigInteger &other) const {
            int res = Comparator(*this, other);
            return res == 3 || res == 1;
        }

        bool operator==(const BigInteger &other) const {
            return Comparator(*this, other) == 1;
        }

        static BigInteger abs(const BigInteger &x) {
            BigInteger copy = BigInteger(x);
            copy.isPositive = true;
            return copy;
        }

        BigInteger operator-() {
            BigInteger copy = BigInteger(*this);
            copy.isPositive = !isPositive;
            copy.isPositive = number.size() == 1 && number[0] == 0;
            return copy;
        }

        BigInteger &operator--(int) {
            *this -= 1;
            return *this;
        }

        BigInteger &operator--() {
            *this -= 1;
            return *this;
        }

        BigInteger &operator++(int) {
            *this += 1;
            return *this;
        }

        BigInteger &operator++() {
            *this += 1;
            return *this;
        }

        friend BigInteger operator%(const BigInteger &first, const BigInteger &second) {
            BigInteger resultRemains(first);
            resultRemains %= second;
            return resultRemains;
        }

        friend BigInteger operator/(const BigInteger &first, const BigInteger &second) {
            BigInteger resultDivision(first);
            resultDivision /= second;
            return resultDivision;
        }

        friend BigInteger operator*(const BigInteger &first, const BigInteger &second) {
            BigInteger resultComposition(first);
            resultComposition *= second;
            return resultComposition;
        }

        friend BigInteger operator+(const BigInteger &first, const BigInteger &second) {
            BigInteger summa(first);
            summa += second;
            return summa;
        }

        friend BigInteger operator-(const BigInteger &first, const BigInteger &second) {
            BigInteger difference(first);
            difference -= second;
            return difference;
        }

        BigInteger &operator%=(const BigInteger &other) {
            *this -= ((*this / other) * other);
            *this = DeleteZeros(*this);
            return *this;
        }

        BigInteger &operator/=(const BigInteger &other) {
            bool sign = this->isPositive;
            *this = DivideSec(*this, other);
            isPositive = (!((!sign || !other.isPositive) && (sign || other.isPositive)));
            if ((number.size() == 1 && number[0] == 0))
                isPositive = true;
            return *this;
        }

        BigInteger &operator*=(const BigInteger &other) {
            BigInteger resultComposition;
            for (size_t i = 0; i < other.number.size(); i++) {
                resultComposition += Multiply(*this, other.number[i], i);
            }

            resultComposition.isPositive = !((isPositive && !other.isPositive) ||
                                             (!isPositive && other.isPositive));
            if ((resultComposition.number.size() == 1 && resultComposition.number[0] == 0))
                resultComposition.isPositive = true;
            *this = resultComposition;
            return *this;
        }

        BigInteger &operator-=(const BigInteger &other) {
            bool sign = isPositive;
            if ((isPositive && other.isPositive) || (!isPositive && !other.isPositive)) {
                BigInteger copy1 = abs(*this), copy2 = abs(other);
                *this = Difference(*this, other);
                isPositive = copy1 > copy2 ? sign : !sign;
                if ((number.size() == 1 && number[0] == 0))
                    isPositive = true;
            } else {
                *this = AddUp(*this, other);
                isPositive = sign;
            }
            *this = DeleteZeros(*this);
            return *this;
        }

        BigInteger &operator+=(const BigInteger &other) {
            bool sign = this->isPositive;
            if (!(this->isPositive && other.isPositive) &&
                !(!this->isPositive && !other.isPositive)) {
                BigInteger copy1 = abs(*this), copy2 = abs(other);
                *this = Difference(*this, other);
                this->isPositive = copy1 > copy2 ? sign : other.isPositive;
                if ((number.size() == 1 && number[0] == 0))
                    isPositive = true;
            } else {
                *this = AddUp(*this, other);
                this->isPositive = sign;
            }
            *this = DeleteZeros(*this);
            return *this;
        }

    private:
        vector<int> number;
        bool isPositive;

        void CheckSign(string &s) const {
            if (!(isPositive))
                s += '-';
            if ((number.size() == 1) && number[0] == 0)
                s = "";
        }

        void StitchingString(string &s) const {
            for (size_t j = 0; j < number.size(); j++) {
                char a = number[number.size() - j - 1] + '0';
                s += a;
            }
        }

        static BigInteger &CutZeros(BigInteger &other) {
            long long i = other.number.size() - 1;
            while (other.number[i] == 0) {
                if (i == 0 && other.number[i] == 0) {
                    other.isPositive = true;
                    return other;
                }
                other.number.pop_back();
                i--;
            }
            return other;
        }

        void CheckSignAndABS(int &newValue) {
            newValue < 0 ? this->isPositive = false : this->isPositive = true;
            newValue = std::abs(newValue);
        }

        void StitchingNumber(int &newValue) {
            if (newValue == 0)
                number.push_back(0);
            while (newValue != 0) {
                number.push_back(newValue % 10), newValue /= 10;
            }
        }

        void CheckSign(const string &newValue) {
            newValue[0] == '-' ?
                    isPositive = false : isPositive = true;
        }

        void LocalPars(const string &newValue) {
            size_t i = 0;
            if (!this->isPositive)
                i++;
            for (; i < newValue.size(); i++)
                number.push_back(newValue[i] - '0');
        }

        void Coup([[maybe_unused]] const string &newValue) {
            for (size_t i = 0; i < number.size() / 2; i++)
                std::swap(number[i], number[number.size() - i - 1]);
        }

        static void Coup(BigInteger &newValue) {
            for (size_t i = 0; i < newValue.number.size() / 2; i++)
                std::swap(newValue.number[i], newValue.number[newValue.number.size() - i - 1]);
        }

        static int Comparator(const BigInteger &first, const BigInteger &second) {
            size_t n = first.number.size();
            size_t m = second.number.size();
            if (first.isPositive && second.isPositive && n == m) {
                return Compare(first, second, 1);
            }
            if (!(first.isPositive) && !(second.isPositive) && n == m) {
                return Compare(first, second, -1);
            }
            return CompareNotEqualSignOrOther(first, second);
        }

        static int CompareNotEqualSignOrOther(const BigInteger &first, const BigInteger &second) {
            if (!first.isPositive && second.isPositive) {
                return 3;
            }
            if (first.isPositive && !second.isPositive) {
                return 2;
            }
            return CompareNotEqualSizeOrOtherPlus(first, second);
        }

        static int
        CompareNotEqualSizeOrOtherPlus(const BigInteger &first, const BigInteger &second) {
            if (first.isPositive && second.isPositive &&
                first.number.size() < second.number.size()) {
                return 3;
            }
            if (first.isPositive && second.isPositive &&
                first.number.size() > second.number.size()) {
                return 2;
            }
            return CompareNotEqualSizeOrOtherMinus(first, second);
        }

        static int
        CompareNotEqualSizeOrOtherMinus(const BigInteger &first, const BigInteger &second) {
            if (!(first.isPositive) && !(second.isPositive) &&
                first.number.size() > second.number.size()) {
                return 2;
            }
            if (!(first.isPositive) && !(second.isPositive) &&
                first.number.size() < second.number.size()) {
                return 3;
            }
            return -1;
        }

        static int Compare(const BigInteger &first, const BigInteger &second, int sign) {
            size_t n = first.number.size();
            size_t m = second.number.size();
            for (size_t i = 0; i < m; i++) {
                if (first.number[n - i - 1] * sign > second.number[n - i - 1] * sign) {
                    return 2;
                } else if (first.number[n - i - 1] * sign < second.number[n - i - 1] * sign) {
                    return 3;
                }
            }
            return 1; // equal
        }

        static BigInteger DivideSec(const BigInteger &first, const BigInteger &second) {
            string s;
            BigInteger row_result = s;
            if (abs(first) < abs(second)) {
                row_result = 0;
            } else {
                BigInteger rest, current_dividend;
                int last = first.number.size(), digit;
                while (last > 0) {
                    digit = 0;
                    last--;
                    current_dividend = Multiply(rest, 10, 0) + first.number[last];
                    while (current_dividend >= abs(second)) {
                        current_dividend -= abs(second);
                        if (current_dividend >= 0) {
                            digit++;
                            rest = current_dividend;
                        }
                    }
                    if (current_dividend >= 0) {
                        rest = current_dividend;
                    }
                    row_result.number.push_back(digit);
                }
            }
            Coup(row_result);
            row_result.isPositive = true;
            row_result = DeleteZeros(row_result);
            return row_result;
        }

        static BigInteger Multiply(BigInteger &other, int digit, size_t order) {
            int rest = 0;
            size_t size = other.number.size();
            string s;
            BigInteger result = s;
            for (size_t i = 0; i < order; i++) {
                result.number.push_back(0);
            }
            for (size_t i = 0; i < size; i++) {
                if (other.number[i] * digit + rest <= 9) {
                    result.number.push_back(other.number[i] * digit + rest);
                    rest = 0;
                } else {
                    result.number.push_back((other.number[i] * digit + rest) % 10);
                    rest = (other.number[i] * digit + rest) / 10;
                }
            }
            if (rest != 0) {
                result.number.push_back(rest);
            }
            result = DeleteZeros(result);
            result.isPositive = true;
            return result;
        }

        BigInteger &Difference(BigInteger &first, const BigInteger &second) {
            string s;
            BigInteger firstCopy = s;
            firstCopy = abs(abs(first) > abs(second) ? first : second);
            BigInteger secondCopy;
            secondCopy.MakeLonger(abs(first), abs(second));
            size_t n = secondCopy.number.size();
            first = s;
            int prev_rest = 0;
            for (size_t i = 0; i < n; i++) {
                if (firstCopy.number[i] - prev_rest >= secondCopy.number[i]) {
                    first.number.push_back(firstCopy.number[i] - prev_rest - secondCopy.number[i]);
                    prev_rest = 0;
                } else {
                    first.number.push_back(
                            10 - prev_rest + firstCopy.number[i] - secondCopy.number[i]);
                    prev_rest = 1;
                }
            }
            first = DeleteZeros(first);
            first.isPositive = true;
            return first;
        }

        BigInteger MakeLonger(BigInteger first, BigInteger second) {
            string s;
            *this = s;
            size_t n = first.number.size();
            size_t m = second.number.size();
            if (n < m) {
                this->isPositive = first.isPositive;
                for (size_t j = 0; j < n; j++) {
                    this->number.push_back(first.number[j]);
                }
                for (size_t i = 0; i < m - n; i++) {
                    this->number.push_back(0);
                }
            } else if (m < n) {
                this->isPositive = second.isPositive;
                for (size_t j = 0; j < m; j++) {
                    this->number.push_back(second.number[j]);
                }
                for (size_t i = 0; i < n - m; i++) {
                    this->number.push_back(0);
                }
            } else {
                if (first > second) {
                    *this = second;
                    return second;
                } else {
                    *this = first;
                    return first;
                }
            }
            return *this;
        }

        static BigInteger &DeleteZeros(BigInteger &other) {
            return other.number.empty() ? other : CutZeros(other);
        }

        static BigInteger &AddUp(BigInteger &first, const BigInteger &second) {
            BigInteger firstCopy;
            firstCopy = abs(abs(first) <= abs(second) ? second : first);
            BigInteger secondCopy;
            secondCopy.MakeLonger(abs(first), abs(second));
            size_t n = secondCopy.number.size();
            string s = "";
            first = s;
            int rest = 0;

            for (size_t i = 0; i < n; i++) {
                int sum = firstCopy.number[i] + secondCopy.number[i] + rest;
                rest = sum / 10;
                first.number.push_back(sum % 10);
            }
            if (rest != 0) {
                first.number.push_back(rest);
            }
            first = DeleteZeros(first);
            first.isPositive = true;
            return first;
        }
    };

    BigInteger operator ""_bi(const char *str, size_t) {
        string number = string(str);
        return BigInteger(number);
    }

//ты кот, который смог



//--------------------------------------------------------------------------------------------------------------------//
/*
██╗████████╗░██████╗███████╗██╗░░░░░███████╗        ██╗░██████╗     ███╗░░██╗░█████╗░████████╗      ░█████╗░
██║╚══██╔══╝██╔════╝██╔════╝██║░░░░░██╔════╝        ██║██╔════╝     ████╗░██║██╔══██╗╚══██╔══╝      ██╔══██╗
██║░░░██║░░░╚█████╗░█████╗░░██║░░░░░█████╗░░        ██║╚█████╗░     ██╔██╗██║██║░░██║░░░██║░░░      ███████║
██║░░░██║░░░░╚═══██╗██╔══╝░░██║░░░░░██╔══╝░░        ██║░╚═══██╗     ██║╚████║██║░░██║░░░██║░░░      ██╔══██║
██║░░░██║░░░██████╔╝███████╗███████╗██║░░░░░        ██║██████╔╝     ██║░╚███║╚█████╔╝░░░██║░░░      ██║░░██║
╚═╝░░░╚═╝░░░╚═════╝░╚══════╝╚══════╝╚═╝░░░░░        ╚═╝╚═════╝░     ╚═╝░░╚══╝░╚════╝░░░░╚═╝░░░      ╚═╝░░╚═╝

██████╗░░█████╗░████████╗██╗░█████╗░███╗░░██╗░█████╗░██╗░░░░░       ░██╗░░░░░░░██╗░█████╗░░██████╗████████╗███████╗
██╔══██╗██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║██╔══██╗██║░░░░░       ░██║░░██╗░░██║██╔══██╗██╔════╝╚══██╔══╝██╔════╝
██████╔╝███████║░░░██║░░░██║██║░░██║██╔██╗██║███████║██║░░░░░       ░╚██╗████╗██╔╝███████║╚█████╗░░░░██║░░░█████╗░░
██╔══██╗██╔══██║░░░██║░░░██║██║░░██║██║╚████║██╔══██║██║░░░░░       ░░████╔═████║░██╔══██║░╚═══██╗░░░██║░░░██╔══╝░░
██║░░██║██║░░██║░░░██║░░░██║╚█████╔╝██║░╚███║██║░░██║███████╗       ░░╚██╔╝░╚██╔╝░██║░░██║██████╔╝░░░██║░░░███████╗
╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═╝░░╚═╝╚══════╝       ░░░╚═╝░░░╚═╝░░╚═╝░░╚═╝╚═════╝░░░░╚═╝░░░╚══════╝

░█████╗░███████╗        ████████╗██╗███╗░░░███╗███████╗       ██╗███╗░░██╗      ███╗░░░███╗██╗░░░██╗
██╔══██╗██╔════╝        ╚══██╔══╝██║████╗░████║██╔════╝       ██║████╗░██║      ████╗░████║╚██╗░██╔╝
██║░░██║█████╗░░        ░░░██║░░░██║██╔████╔██║█████╗░░       ██║██╔██╗██║      ██╔████╔██║░╚████╔╝░
██║░░██║██╔══╝░░        ░░░██║░░░██║██║╚██╔╝██║██╔══╝░░       ██║██║╚████║      ██║╚██╔╝██║░░╚██╔╝░░
╚█████╔╝██║░░░░░        ░░░██║░░░██║██║░╚═╝░██║███████╗       ██║██║░╚███║      ██║░╚═╝░██║░░░██║░░░
░╚════╝░╚═╝░░░░░        ░░░╚═╝░░░╚═╝╚═╝░░░░░╚═╝╚══════╝       ╚═╝╚═╝░░╚══╝      ╚═╝░░░░░╚═╝░░░╚═╝░░░

██╗░░░░░██╗███████╗███████╗
██║░░░░░██║██╔════╝██╔════╝
██║░░░░░██║█████╗░░█████╗░░
██║░░░░░██║██╔══╝░░██╔══╝░░
███████╗██║██║░░░░░███████╗
╚══════╝╚═╝╚═╝░░░░░╚══════╝
*/
//--------------------------------------------------------------------------------------------------------------------//


    class Rational {
    public:
        Rational() : numerator(0), denominator(1), isPositive(true) {};

        Rational(BigInteger numberUp, BigInteger numberDown = 1) : numerator(numberUp),
                                                                   denominator(numberDown),
                                                                   isPositive(true) {
            CheckSignAndCorrect(numerator, denominator);
        };

        Rational(const int numberUp, int numberDown = 1) : numerator(numberUp),
                                                           denominator(numberDown),
                                                           isPositive(true) {
            CheckSignAndCorrect(numerator, denominator);
        };

        friend Rational operator+(const Rational &first, const Rational &second);

        friend Rational operator*(const Rational &first, const Rational &second);

        friend Rational operator-(const Rational &first, const Rational &second);

        friend Rational operator/(const Rational &first, const Rational &second);

        friend Rational operator%(const Rational &first, const Rational &second);

        Rational &operator+=(const Rational &other) {
            if (isPositive == other.isPositive)
                numerator = numerator * other.denominator + denominator * other.numerator;
            else
                numerator = numerator * other.denominator - denominator * other.numerator;
            denominator = other.denominator * denominator;
            CheckSignAndCorrect(*this);
            return *this;
        };

        friend std::istream &operator>>(std::istream &in, Rational &value) {
            string s;
            in >> s;
            string first = "";
            for (size_t i; i < s.size(); i++) {
                first += s[i];
                if (s.at(i) == '/')break;
            }
            string second = s.substr(first.size() + 1, (s.size() - first.size() - 1));
            value = Rational(BigInteger(first), BigInteger(second));
            return in;
        }

        friend std::ostream &operator<<(std::ostream &out, const Rational &value) {
            string str = value.toString();
            out << str;
            return out;
        }

        Rational &operator-=(const Rational &other) {
            if (isPositive != other.isPositive)
                numerator = numerator * other.denominator + denominator * other.numerator;
            else
                numerator = numerator * other.denominator - denominator * other.numerator;
            denominator = other.denominator * denominator;
            CheckSignAndCorrect(*this);
            return *this;
        };

        Rational &operator*=(const Rational &other) {
            numerator *= other.numerator;
            denominator *= other.denominator;
            isPositive = other.isPositive ? isPositive : !isPositive;
            CheckSignAndCorrect(*this);
            return *this;
        };

        Rational &operator/=(const Rational &other) {
            BigInteger numeratorOther = other.numerator;
            numerator *= other.denominator;
            denominator *= numeratorOther;
            isPositive = other.isPositive ? isPositive : !isPositive;
            CheckSignAndCorrect(*this);
            return *this;
        };

        const Rational operator-() const {
            Rational copy = Rational(*this);
            copy.isPositive = !copy.isPositive;
            copy.MakeShort();
            return copy;
        };

        Rational &operator%=(const Rational &other) {
            BigInteger numeratorOther = other.numerator;
            *this -= ((*this / other) * other);
            isPositive = other.isPositive ? isPositive : !isPositive;
            CheckSignAndCorrect(*this);
            return *this;
        };

        bool operator==(const Rational &other) const {
            if (this->isPositive == other.isPositive) {
                if (this->numerator == other.numerator && this->denominator == other.denominator) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        };

        bool operator!=(const Rational &other) const {
            return !(*this == other);
        };

        bool operator<(const Rational &other) const {
            if (this->isPositive == other.isPositive) {
                return this->numerator * other.denominator < this->denominator * other.numerator;
            } else {
                return !this->isPositive;
            }
        };

        bool operator<=(const Rational &other) const {
            if (this->isPositive == other.isPositive) {
                return this->numerator * other.denominator <= this->denominator * other.numerator;
            } else {
                return !this->isPositive;
            }
        };

        bool operator>(const Rational &other) const {
            return !(*this <= other);
        };

        bool operator>=(const Rational &other) const {
            return !(*this < other);
        };

//--------------------------------------------------------------------------------------------------------------------//
/*
    ███████╗██████╗░██████╗░░█████╗░██████╗░        ░█████╗░██╗░░░░░░█████╗░░██████╗███████╗
    ██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔══██╗        ██╔══██╗██║░░░░░██╔══██╗██╔════╝██╔════╝
    █████╗░░██████╔╝██████╔╝██║░░██║██████╔╝        ██║░░╚═╝██║░░░░░██║░░██║╚█████╗░█████╗░░
    ██╔══╝░░██╔══██╗██╔══██╗██║░░██║██╔══██╗        ██║░░██╗██║░░░░░██║░░██║░╚═══██╗██╔══╝░░
    ███████╗██║░░██║██║░░██║╚█████╔╝██║░░██║        ╚█████╔╝███████╗╚█████╔╝██████╔╝███████╗
    ╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░╚═╝░░╚═╝        ░╚════╝░╚══════╝░╚════╝░╚═════╝░╚══════╝
*/
//--------------------------------------------------------------------------------------------------------------------//

        const string toString() const {
            string result = "", numeratorString = this->numerator.toString(), denominatorString = this->denominator.toString();
            if (!this->isPositive)result += "-";
            result += numeratorString;
            if (denominator != 1 && numerator != 0)
                result += '/' + denominatorString;
            return result;
        };

        const string asDecimal(size_t precision = 0) const {
            string ans;
            BigInteger numeratorCopy = numerator, denominatorCopy = denominator;
            if (precision > 0) {
                if (numeratorCopy / denominatorCopy == 0) {
                    BigInteger n = numeratorCopy;
                    for (size_t i = 0; i < precision; ++i) {
                        n *= 10;
                    }
                    BigInteger result = n / denominatorCopy;
                    string after = result.toString();
                    if (after.size() < precision) {
                        after = string(precision - after.size(), '0') + after;
                    }
                    ans = "0." + after;
                    if (!isPositive && numeratorCopy != 0 && result != 0)ans = '-' + ans;
                } else {
                    if (numeratorCopy % denominatorCopy != 0) {
                        BigInteger n = numeratorCopy;
                        for (size_t i = 0; i < precision; ++i) {
                            n *= 10;
                        }
                        BigInteger result = n / denominatorCopy;
                        ans = result.toString();
                        ans = ans.substr(0, ans.size() - precision) + '.' +
                              ans.substr(ans.size() - precision, precision);

                        if (!isPositive && numeratorCopy != 0)ans = '-' + ans;
                    } else {
                        numeratorCopy /= denominatorCopy;
                        string afterStr;
                        if (afterStr.size() < precision) {
                            afterStr = string(precision - afterStr.size(), '0') + afterStr;
                        }
                        ans = numeratorCopy.toString() + '.' + afterStr;
                        if (!isPositive && numeratorCopy != 0)ans = '-' + ans;
                    }
                }
            } else {
                numeratorCopy /= denominatorCopy;
                ans = numeratorCopy.toString();
                if (!isPositive && numeratorCopy != 0)ans = '-' + ans;
            }

            return ans;
        }
//--------------------------------------------------------------------------------------------------------------------//
/*
    ███████╗██████╗░██████╗░░█████╗░██████╗░        ░█████╗░██╗░░░░░░█████╗░░██████╗███████╗
    ██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔══██╗        ██╔══██╗██║░░░░░██╔══██╗██╔════╝██╔════╝
    █████╗░░██████╔╝██████╔╝██║░░██║██████╔╝        ██║░░╚═╝██║░░░░░██║░░██║╚█████╗░█████╗░░
    ██╔══╝░░██╔══██╗██╔══██╗██║░░██║██╔══██╗        ██║░░██╗██║░░░░░██║░░██║░╚═══██╗██╔══╝░░
    ███████╗██║░░██║██║░░██║╚█████╔╝██║░░██║        ╚█████╔╝███████╗╚█████╔╝██████╔╝███████╗
    ╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░╚═╝░░╚═╝        ░╚════╝░╚══════╝░╚════╝░╚═════╝░╚══════╝
*/
//--------------------------------------------------------------------------------------------------------------------//
        bool &CheckSignAndCorrect(BigInteger &numberUp, BigInteger &numberDown) {
            if (!isPositive) {
                numberUp *= -1;
                isPositive = 1;
            }
            numberUp * numberDown < 0 ? isPositive = false : isPositive = true;
            if (numberUp < 0) numberUp *= -1;
            if (numberDown < 0) numberDown *= -1;
            MakeShort();
            return isPositive;
        }

        bool &CheckSignAndCorrect(Rational &copy) {
            return CheckSignAndCorrect(copy.numerator, copy.denominator);
        }

        static Rational abs(const Rational &x) {
            Rational copy = Rational(x.numerator, x.denominator);
            copy.isPositive = true;
            return copy;
        }

        void MakeShort() {
            if (this->numerator == 0)this->denominator = 1;
            BigInteger x = GCD(this->numerator, this->denominator);
            if (x != 0) {
                this->numerator /= x;
                this->denominator /= x;
            }
        }

        BigInteger GCD(BigInteger a, BigInteger b) {
            while (b > 0 && a > 0) {
                if (a > b) a %= b;
                else b %= a;
            }
            return a + b;
        }

        explicit operator double() {
            double result = atof((*this).asDecimal(17).c_str());
            return result;
        }

    private:
        BigInteger numerator;//числитель
        BigInteger denominator;//знаменатель
        bool isPositive;//знак
    };

    Rational operator+(const Rational &first, const Rational &second) {
        Rational summa(first);
        summa += second;
        summa.MakeShort();
        return summa;
    }

    Rational operator*(const Rational &first, const Rational &second) {
        Rational resultComposition(first);
        resultComposition *= second;
        resultComposition.MakeShort();
        return resultComposition;
    }

    Rational operator-(const Rational &first, const Rational &second) {
        Rational difference(first);
        difference -= second;
        difference.MakeShort();
        return difference;
    }

    Rational operator/(const Rational &first, const Rational &second) {
        Rational resultDivision(first);
        resultDivision /= second;
        resultDivision.MakeShort();
        return resultDivision;
    }

    Rational operator%(const Rational &first, const Rational &second) {
        Rational resultDivision(first);
        resultDivision %= second;
        resultDivision.MakeShort();
        return resultDivision;
    }
//--------------------------------------------------------------------------------------------------------------------//
/*
███████╗██╗░░░██╗███████╗██████╗░██╗░░░██╗████████╗██╗░░██╗██╗███╗░░██╗░██████╗░        ██╗░██████╗
██╔════╝██║░░░██║██╔════╝██╔══██╗╚██╗░██╔╝╚══██╔══╝██║░░██║██║████╗░██║██╔════╝░        ██║██╔════╝
█████╗░░╚██╗░██╔╝█████╗░░██████╔╝░╚████╔╝░░░░██║░░░███████║██║██╔██╗██║██║░░██╗░        ██║╚█████╗░
██╔══╝░░░╚████╔╝░██╔══╝░░██╔══██╗░░╚██╔╝░░░░░██║░░░██╔══██║██║██║╚████║██║░░╚██╗        ██║░╚═══██╗
███████╗░░╚██╔╝░░███████╗██║░░██║░░░██║░░░░░░██║░░░██║░░██║██║██║░╚███║╚██████╔╝        ██║██████╔╝
╚══════╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝░░░╚═╝░░░░░░╚═╝░░░╚═╝░░╚═╝╚═╝╚═╝░░╚══╝░╚═════╝░        ╚═╝╚═════╝░

██╗███╗░░██╗        ██╗░░░██╗░█████╗░██╗███╗░░██╗       ██╗███╗░░██╗        ████████╗██╗░░██╗██╗░██████╗
██║████╗░██║        ██║░░░██║██╔══██╗██║████╗░██║       ██║████╗░██║        ╚══██╔══╝██║░░██║██║██╔════╝
██║██╔██╗██║        ╚██╗░██╔╝███████║██║██╔██╗██║       ██║██╔██╗██║        ░░░██║░░░███████║██║╚█████╗░
██║██║╚████║        ░╚████╔╝░██╔══██║██║██║╚████║       ██║██║╚████║        ░░░██║░░░██╔══██║██║░╚═══██╗
██║██║░╚███║        ░░╚██╔╝░░██║░░██║██║██║░╚███║       ██║██║░╚███║        ░░░██║░░░██║░░██║██║██████╔╝
╚═╝╚═╝░░╚══╝        ░░░╚═╝░░░╚═╝░░╚═╝╚═╝╚═╝░░╚══╝╚      ═╝╚═╝░░╚══╝░        ░░╚═╝░░░╚═╝░░╚═╝╚═╝╚═════╝░

░██╗░░░░░░░██╗░█████╗░██████╗░██╗░░░░░██████╗░
░██║░░██╗░░██║██╔══██╗██╔══██╗██║░░░░░██╔══██╗
░╚██╗████╗██╔╝██║░░██║██████╔╝██║░░░░░██║░░██║
░░████╔═████║░██║░░██║██╔══██╗██║░░░░░██║░░██║
░░╚██╔╝░╚██╔╝░╚█████╔╝██║░░██║███████╗██████╔╝
░░░╚═╝░░░╚═╝░░░╚════╝░╚═╝░░╚═╝╚══════╝╚═════╝░
*/
//--------------------------------------------------------------------------------------------------------------------//

}
/*
 * Проверка на равенство: операторы == и !=.
Конструктор по умолчанию, создающий единичную матрицу. Для неквадратных матриц конструктор по умолчанию не требуется.
Конструктор, создающий матрицу из vector<vector<T> >. Должно быть можно создать матрицу из vector<vector<int> >.
Сложение, вычитание, операторы +=, -=. Сложение и вычитание матриц несоответствующих размеров не должно компилироваться.
Умножение на число.
Умножение матриц, работающие за max(M,N,K)**3. Для квадратных матриц должен поддерживаться еще и оператор *=. Попытка перемножить матрицы несоответствующих размеров должна приводить к ошибке компиляции.
Метод det(), возвращающий определитель матрицы за O(N**3). Взятие определителя от неквадратной матрицы не должно компилироваться.
Метод transposed(), возвращающий транспонированную матрицу.
Метод rank() - вычислить ранг матрицы.
Метод trace() - вычислить след матрицы.
Методы inverted() и invert() - вернуть обратную матрицу и обратить данную матрицу.
Методы getRow(long long) и getColumn(long long), возвращающие std::vector<Field> из соответствующих значений.
К матрице должен быть дважды применим оператор [], причём это должно работать как для неконстантных, так и для константных матриц. В первом случае содержимое матрицы должно быть можно таким способом поменять.
Другие способы изменения содержимого матрицы, кроме описанных выше, должны отсутствовать. Однако не запрещается реализовать дополнительные методы для выполнения каких-либо иных алгебраических операций или для удобства работы, если по названию и сигнатуре этих методов будет без комментариев понятно их действие.
Квадратные матрицы размера N должно быть можно объявлять всего с одним обязательным шаблонным параметром: SquareMatrix<N>.
 */

namespace TOOLS {

/*------------------------------------------------------------------------------------------------*/
    typedef long long ll;
    ll const sizeOfTree = 2e5 + 1;
    ll const INF = 1e18;
/*------------------------------------------------------------------------------------------------*/

    namespace FLOWS {

/*------------------------------------------------------------------------------------------------*/
#ifndef IN_OUT

        std::ifstream in;
        std::ofstream out;

#define IN_OUT 1
#endif //IN_OUT

    }

    //сдвигает элементы вектора по кругу
    template<class T>
    T &_slide(T &Vec, int timer = 1) {
        T newT;
        for (auto x:Vec) {
            if (timer == 0)
                newT.push_back(x);
            else {
                Vec.push_back(x);
                timer--;
            }
        }
        Vec = newT;
        return Vec;
    }

    //ускоряшка
    void _acceleration() {
        std::ios_base::sync_with_stdio(0);
        std::cin.tie(0);
        std::cout.tie(0);
    }

    //открываем файлик на считывание
    void _file_open() {
        using namespace FLOWS;
        in.open("in.in");
        out.open("out.out");
    }

    //закрываем файлик
    void _file_close() {
        using namespace FLOWS;
        in.close();
        out.close();
    }

    //берет остаток числа
    template<typename T>
    const T &mod(T &value, int &N) {
        value %= dynamic_cast<T>(N);
        return value;
    }

/*-------------------------------------------------------------------------------- Prime checkers */

    constexpr bool PrimeStatus(int n) {
        int i = 2;
        while (i <= std::sqrt(n)) {
            if (n % i == 0) {
                return false;
            }
            ++i;
        }

        return true;
    };

/*------------------------------------------------------------------------------------------------*/
}


namespace FIELDS::GALOIS {


/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/* Start --------------------------------------------------------------------------------- Finite */

    template<long long N>
    class Finite {
    private:

        using _typeOfField = Finite<N>;
        long long _value;

/*------------------------------------------------------------------------------- Check for Prime */
        template<bool IsPrime = TOOLS::PrimeStatus(N), typename Dummy = void>
        struct NonPrimeCrash {
            static void Check() {};
        };

        template<typename Dummy>
        struct NonPrimeCrash<false, Dummy> {
            static void Check();
        };

/*----------------------------- This function will crash program on compilation if N is not prime */
        static void CheckForPrime() { NonPrimeCrash<>::Check(); }

        template<long long _N>
        friend std::ostream &operator<<(std::ostream &, Finite<_N> const &);

        template<long long _N>
        friend std::istream &operator>>(std::istream &, Finite<_N> &);


    public:

/*---------------------------------------------------------------------------------- Constructors */
        Finite();

        Finite(const int);

        Finite(const Finite<N> &);

/*------------------------------------------------------------------------- Operators overloading */

        _typeOfField operator-() const;

        _typeOfField operator+(const _typeOfField &) const;

        _typeOfField &operator+=(const _typeOfField &);

        _typeOfField operator-(const _typeOfField &) const;

        _typeOfField &operator-=(const _typeOfField &);

        _typeOfField operator*(const _typeOfField &) const;

        _typeOfField &operator*=(const _typeOfField &);

        _typeOfField operator^(long long) const;

        _typeOfField &operator^=(long long);

        _typeOfField &operator--(int) {
            (*this -= 1);
            _value %= N;
            return *this;
        }

        _typeOfField &operator--() {
            (*this -= 1);
            _value %= N;
            return *this;
        }

        _typeOfField &operator++(int) {
            (*this += 1);
            _value %= N;
            return *this;
        }

        _typeOfField &operator++() {
            (*this += 1);
            _value %= N;
            return *this;
        }

/*--------------------------------------------------------------------------------- bool operator */

        bool operator!=(const _typeOfField &) const;



/*------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------- Only if N is prime */
/*------------------------------------------------------------------------------------------------*/
        _typeOfField inverse() const;

        _typeOfField operator/(const _typeOfField &) const;

        _typeOfField &operator/=(const _typeOfField &);


/*------------------------------------------------------------------------------------------------*/

        long long GetValue() const;

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
    };


/*------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------- IMPLEMENTATION */
/*------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------- Constructors */
    template<long long N>
    Finite<N>::Finite() : _value(0) {}

    template<long long N>
    Finite<N>::Finite(int value) : _value((value % N+N)%N == 0 ? 0 : (value % N + N) % N) {}

    template<long long N>
    Finite<N>::Finite(const Finite<N> &finite) : _value(finite._value) {}

/*------------------------------------------------------------------------------------ Operations */

    template<long long N>
    Finite<N> Finite<N>::operator-() const {
        return Finite<N>(N - _value);
    }

    template<long long N>
    Finite<N> Finite<N>::operator+(const _typeOfField &right) const {
        return Finite<N>((_value + right._value) % N);
    }

    template<long long N>
    Finite<N> &Finite<N>::operator+=(const _typeOfField &right) {
        _value = (_value + right._value) % N;
        return (*this);
    }

    template<long long N>
    Finite<N> Finite<N>::operator-(const _typeOfField &right) const {
        return Finite<N>((_value + N - right._value) % N);
    }

    template<long long N>
    Finite<N> &Finite<N>::operator-=(const _typeOfField &right) {
        _value = (_value + N - right._value) % N;
        return (*this);
    }

    template<long long N>
    Finite<N> Finite<N>::operator*(const _typeOfField &right) const {
       //std::cout<<" ( "<< _value<<" * "<<right._value<<" ) % "<<N<<" = ";
        return Finite<N>(((_value + N) * right._value) % N);
    }

    template<long long N>
    Finite<N> &Finite<N>::operator*=(const _typeOfField &right) {
        _value = (_value * right._value) % N;
        return (*this);
    }

    template<long long N>
    Finite<N> Finite<N>::operator^(long long pow) const {
        if (pow == 0) { return Finite<N>(1); }
        if (pow == 1) { return (*this); }
        if (pow % 2 == 0) {
            Finite<N> result = (*this) ^(pow / 2);
            result *= result;
            return result;
        } else {
            Finite<N> result = (*this) ^(pow - 1);
            result *= (*this);
            return result;
        }
    }

    template<long long N>
    Finite<N> &Finite<N>::operator^=(long long pow) {
        return (*this) = (*this) ^ pow;
    }


    /*--------------------------------------------------------------------------------------- Compare */
    template<long long N>
    bool Finite<N>::operator!=(const _typeOfField &right) const {
        return _value != right._value;
    }


/*------------------------------------------------------------------------------------- For Prime */
    template<long long N>
    Finite<N> Finite<N>::inverse() const {
        CheckForPrime();
        return (*this) ^ (N - 2);
    }

    template<long long N>
    Finite<N> Finite<N>::operator/(const _typeOfField &right) const {
        CheckForPrime();
        return ((right) ^ (N - 2)) * (*this);
    }

    template<long long N>
    Finite<N> &Finite<N>::operator/=(const _typeOfField &right) {
        CheckForPrime();
        return (*this) = ((right) ^ (N - 2)) * (*this);
    }

    template<long long N>
    long long Finite<N>::GetValue() const {
        return _value;
    }


/*------------------------------------------------------------------------------------------------*/

    template<long long N>
    std::ostream &operator<<(std::ostream &out, Finite<N> const &element) {
        out << element.GetValue();
        return out;
    }

    template<long long N>
    std::istream &operator>>(std::istream &in, Finite<N> &element) {
        in >> element._value;
        element._value %= N;
        return in;
    }

/*------------------------------------------------------------------------------------------------*/
}


namespace MATRIX {
/*------------------------------------------------------------------------------------------------*/
    using namespace TYPES::BIGINTEGER;
    using namespace FIELDS::GALOIS;

/*------------------------------------------------------------------------------------------------*/





    template<long long N, long long M, typename Field = Rational>
    class Matrix {

    public:

/*----------------------------------------------------------------------------------- Input Output */
        template<long long _N, long long _M, typename _Field>
        friend std::ostream &operator<<(std::ostream &, Matrix<_N, _M, _Field> const &);

        template<long long _N, long long _M, typename _Field>
        friend std::istream &operator>>(std::istream &, Matrix<_N, _M, _Field> &);

/*-------------------------------------------------------------------------- Table, Type of Matrix */
        std::vector<std::vector<Field> > _table;

        using _typeOfMatrix = Matrix<N, M, Field>;

/*------------------------------------------------------------------------------- Check for Prime */
        template<typename U>
        struct _FiniteCheck {
            static void Check() {}
        };

        template<typename U, U n>
        struct _FiniteCheck<Finite<n>> {
            static void Check() {
                bool isPrime = TOOLS::PrimeStatus(n);
                if (isPrime) CheckTrue();
            }

            static void CheckTrue() {};
        };

/*---------------------------- This function will crash if Filed = Finite<N> where N is not prime */
        static void _CheckFinite() { _FiniteCheck<Field>::Check(); }

        template<long long _N, long long _M>
        struct _SizeCheck {
            static void Check();
        };

        template<long long _N>
        struct _SizeCheck<_N, _N> {
            static void Check() {}
        };

/*------------------------------------------------------------ This function will crash if N != M */
        static void _CheckSize() { _SizeCheck<N, M>::Check(); };
/*-------------------------------------------------------------------------- SecondField must be: */
/*----------------------------------------------------------------- long long ~ (this is for rank) */
/*----------------------------------------------- vector <Field> ~ (this is for finding solution) */
/*-------------------------------------- vector <vector <Field> > ~ (this is for inverted matrix) */
        template<typename SecondField>
        void _GaussMethod(SecondField &) const;

        template<typename SecondField>
        void _SwapRows(SecondField &, size_t first, size_t second) {
            _table[first].swap(_table[second]);
        }
        
        void _SwapRows(Field &determinant, size_t first, size_t second) {
            _table[first].swap(_table[second]);
            determinant = -determinant;
        }

        void _SwapRows(Matrix<N, M, Field> &secondMatrix, size_t first,
                                             size_t second) {
            _table[first].swap(_table[second]);
            secondMatrix._table[first].swap(secondMatrix._table[second]);
        }

        template<typename SecondField>
        void
        _SumWithAnotherRow([[maybe_unused]] SecondField &secondField, size_t row_from, size_t row_to, Field element) {
            for (size_t index = 0; index < M; index++) {
                _table[row_to][index] = _table[row_to][index] + _table[row_from][index] * element;
            }
        }

        void
        _SumWithAnotherRow(Matrix<N, M, Field> &secondMatrix, size_t row_from,
                                                 size_t row_to, Field element) {
            for (size_t index = 0; index < M; index++) {
                _table[row_to][index] = _table[row_to][index] + _table[row_from][index] * element;
                secondMatrix._table[row_to][index] = secondMatrix._table[row_to][index] +
                                                     secondMatrix._table[row_from][index] * element;
            }
        }

        template<typename SecondField>
        void _ChangingResult([[maybe_unused]] SecondField &something, [[maybe_unused]] size_t row_pos,
                             [[maybe_unused]] size_t column_pos) {}

        void _ChangingResult(long long &rank, size_t row_pos, size_t column_pos) {
            rank = static_cast<long long>(row_pos < column_pos ? row_pos : column_pos);
        }

        template<typename SecondField>
        void _DivideRowByNumber([[maybe_unused]] SecondField &rank, size_t row, Field element) {
            for (size_t index = 0; index < M; index++) {
                _table[row][index] /= element;
            }
        }
        
        void _DivideRowByNumber(Field &determinant, size_t row, Field element) {
            for (size_t index = 0; index < M; index++) {
                _table[row][index] /= element;
            }
            determinant *= element;
        }
        
        void _DivideRowByNumber(Matrix<N, M, Field> &secondMatrix, size_t row,
                                                      Field element) {
            for (size_t index = 0; index < M; index++) {
                _table[row][index] /= element;
                secondMatrix._table[row][index] /= element;
            }
        }

/*------------------------------------------------------------------------------------------------*/

        Matrix();

        Matrix(Field);

        Matrix<N, M, Field>(std::vector<std::vector<Field>> array) {
            _table = array;

            for (size_t i = 0; i < array.size(); ++i) {
                for (size_t j = array[i].size(); j < M; ++j) {
                    _table[i].push_back(static_cast<Field>(0));
                }
            }

            for (size_t i = array.size(); i < N; ++i) {
                std::vector<Field> row;

                for (size_t j = 0; j < M; ++j) {
                    row.push_back(static_cast<Field>(0));
                }
                _table.push_back(row);
            }
        }

        Matrix<N, M, Field>(std::vector<std::vector<int>> array) {
            for (size_t i = 0; i < array.size(); ++i) {
                for (size_t j = array[i].size(); j < M; ++j) {
                    _table[i][j]=(static_cast<Field>(array[i][j]));
                }
            }

            for (size_t i = 0; i < array.size(); ++i) {
                for (size_t j = array[i].size(); j < M; ++j) {
                    _table[i].push_back(static_cast<Field>(0));
                }
            }

            for (size_t i = array.size(); i < N; ++i) {
                std::vector<Field> row;

                for (size_t j = 0; j < M; ++j) {
                    row.push_back(static_cast<Field>(0));
                }
                _table.push_back(row);
            }
        }

        Matrix(const Matrix<N, M, Field> &);

        _typeOfMatrix operator+(const _typeOfMatrix &) const;

        _typeOfMatrix &operator+=(const _typeOfMatrix &);

        _typeOfMatrix operator-(const _typeOfMatrix &) const;

        _typeOfMatrix &operator-=(const _typeOfMatrix &);

        _typeOfMatrix operator*(Field) const;

        _typeOfMatrix &operator*=(Field);

        template<long long K>
        Matrix<N, K, Field> operator*(const Matrix<M, K, Field> &) const;

        template<long long K>
        Matrix<N, K, Field> &operator*=(const Matrix<M, K, Field> &);

        friend Matrix<N, M, Field> operator*(const Field left, const Matrix<N, M, Field> &right) {
            Matrix<N, M, Field> result = right;

            for (size_t indexRow = 0; indexRow < N; indexRow++) {
                for (size_t indexColumn = 0; indexColumn < M; indexColumn++) {
                    result._table[indexRow][indexColumn] *= left;
                }
            }

            return result;
        }

        friend Matrix<N, M, Field> operator*(const Matrix<N, M, Field> &left, const Field right) {
            Matrix<N, M, Field> result = left;

            for (size_t indexRow = 0; indexRow < N; indexRow++) {
                for (size_t indexColumn = 0; indexColumn < M; indexColumn++) {
                    result._table[indexRow][indexColumn] *= right;
                }
            }

            return result;
        }

        Field det() const;

        Matrix<M, N, Field> transposed() const;

        long long rank() const;

        _typeOfMatrix inverted() const;

        _typeOfMatrix invert();

        Field trace();

        std::vector<Field> getRow(long long);

        std::vector<Field> getColumn(long long);

        std::vector<Field> &operator[](const size_t);

        const std::vector<Field> &operator[](const size_t) const;

        template<long long U, long long T>
        bool operator==(const Matrix<U, T, Field> &second) const {
            if (N != U || M != T) {
                return false;
            } else {

                for (size_t i = 0; i < N; ++i) {
                    for (size_t j = 0; j < M; ++j) {
                        if (_table[i][j] != second._table[i][j]) {
                            return false;
                        }
                    }
                }

                return true;
            }
        }

        bool operator!=(const Matrix<N, M, Field> &second) const {
            return !(*this == second);
        }
    };







//----------------------------------------------------------------------------------------------------------------------

    template<long long N, typename Field = Rational>
    using SquareMatrix = Matrix<N, N, Field>;

    template<long long N, long long M, typename Field>
    Matrix<N, M, Field>::Matrix() {
        _CheckFinite();
        _table.resize(N, std::vector<Field>(N));
    }

    template<long long N, long long M, typename Field>
    Matrix<N, M, Field>::Matrix(Field element) {
        _CheckFinite();
        _table.resize(N, std::vector<Field>(N, element));
    }

    template<long long N, long long M, typename Field>
    Matrix<N, M, Field>::Matrix(const _typeOfMatrix &right) {
        _CheckFinite();
        _table = right._table;
    }

    template<long long N, long long M, typename Field>
    Matrix<N, M, Field> Matrix<N, M, Field>::operator+(const _typeOfMatrix &right) const {
        Matrix<N, M, Field> result(*this);

        result += right;

        return result;
    }

    template<long long N, long long M, typename Field>
    Matrix<N, M, Field> &Matrix<N, M, Field>::operator+=(const _typeOfMatrix &right) {
        for (size_t indexRow = 0; indexRow < N; indexRow++) {
            for (size_t indexColumn = 0; indexColumn < M; indexColumn++) {
                _table[indexRow][indexColumn] += right._table[indexRow][indexColumn];
            }
        }

        return (*this);
    }

    template<long long N, long long M, typename Field>
    Matrix<N, M, Field> Matrix<N, M, Field>::operator-(const _typeOfMatrix &right) const {
        Matrix<N, M, Field> result(*this);

        result -= right;

        return result;
    }

    template<long long N, long long M, typename Field>
    Matrix<N, M, Field> &Matrix<N, M, Field>::operator-=(const _typeOfMatrix &right) {
        for (size_t indexRow = 0; indexRow < N; indexRow++) {
            for (size_t indexColumn = 0; indexColumn < M; indexColumn++) {
                _table[indexRow][indexColumn] -= right._table[indexRow][indexColumn];
            }
        }

        return (*this);
    }

    template<long long N, long long M, typename Field>
    Matrix<N, M, Field> Matrix<N, M, Field>::operator*(Field right) const {
        Matrix<N, M, Field> result(*this);

        result *= right;

        return result;
    }

    template<long long N, long long M, typename Field>
    Matrix<N, M, Field> &Matrix<N, M, Field>::operator*=(Field right) {
        for (size_t indexRow = 0; indexRow < N; indexRow++) {
            for (size_t indexColumn = 0; indexColumn < M; indexColumn++) {
                _table[indexRow][indexColumn] *= right;
            }
        }

        return (*this);
    }

    template<long long N, long long M, typename Field>
    template<long long K>
    Matrix<N, K, Field> Matrix<N, M, Field>::operator*(const Matrix<M, K, Field> &right) const {
        Matrix<N, K, Field> result;

        for (size_t indexRow = 0; indexRow < N; indexRow++) {
            for (size_t indexColumn = 0; indexColumn < K; indexColumn++) {
                for (size_t indexM = 0; indexM < M; indexM++) {
                    result._table[indexRow][indexColumn] += _table[indexRow][indexM] *
                                                            right._table[indexM][indexColumn];
                }
            }
        }

        return result;
    }

    template<long long N, long long M, typename Field>
    template<long long K>
    Matrix<N, K, Field> &Matrix<N, M, Field>::operator*=(const Matrix<M, K, Field> &right) {
        return (*this) = (*this) * right;
    }

    template<long long N, long long M, typename Field>
    template<typename SecondField>
    void Matrix<N, M, Field>::_GaussMethod(SecondField &result) const {
        Matrix<N, M, Field> matrix(*this);

        size_t row = 0;
        size_t column = 0;

        while (row < N && column < M) {

            // Finding nonzero element table[i][row]
            size_t index_nonzero_row = row;

            for (; index_nonzero_row < N; index_nonzero_row++) {
                if (matrix._table[index_nonzero_row][column] != static_cast<Field>(0)) {
                    break;
                }
            }

            if (index_nonzero_row == N) {
                column++;
                continue;
            }

            // Swaping this row
            if (index_nonzero_row != row) {
                matrix._SwapRows<SecondField>(result, row, index_nonzero_row);
            }

            // Making 1 in this element
            matrix._DivideRowByNumber(result, row, matrix._table[row][column]);

            // Making zeroes under that element
            for (size_t index_row = 0; index_row < N; index_row++) {
                if (index_row == row) {
                    continue;
                }

                matrix._SumWithAnotherRow(result, row, index_row,
                                                       -(matrix._table[index_row][column]));
            }

            row++;
            column++;
        }

        matrix._ChangingResult(result, row, column);
    }

    template<long long N, long long M, typename Field>
    Field Matrix<N, M, Field>::det() const {
        _CheckSize();

        Field determinant = 1u;

        _GaussMethod(determinant);

        return determinant;
    }

    template<long long N, long long M, typename Field>
    Matrix<M, N, Field> Matrix<N, M, Field>::transposed() const {
        Matrix<M, N, Field> result;

        for (size_t indexRow = 0; indexRow < N; indexRow++) {
            for (size_t indexColumn = 0; indexColumn < M; indexColumn++) {
                result._table[indexColumn][indexRow] = _table[indexRow][indexColumn];
            }
        }

        return result;
    }

    template<long long N, long long M, typename Field>
    long long Matrix<N, M, Field>::rank() const {
        long long rank = 0;

        _GaussMethod(rank);

        return rank;
    }

    template<long long N, long long M, typename Field>
    Matrix<N, M, Field> Matrix<N, M, Field>::inverted() const {
        _CheckSize();

        Matrix<N, M, Field> result;
        for (size_t row = 0; row < N; row++) {
            for (size_t column = 0; column < M; column++) {
                result._table[row][column] = (row == column ? 1u : 0u);
            }
        }

        _GaussMethod(result);

        return result;
    }

    template<long long N, long long M, typename Field>
    Matrix<N, M, Field> Matrix<N, M, Field>::invert() {
        _CheckSize();

        return (*this) = (*this).inverted();
    }

    template<long long N, long long M, typename Field>
    Field Matrix<N, M, Field>::trace() {
        _CheckSize();

        Field result;
        for (size_t index = 0; index < N; index++) {
            result += _table[index][index];
        }

        return result;
    }

    template<long long N, long long M, typename Field>
    std::vector<Field> Matrix<N, M, Field>::getRow(long long numRow) {
        return _table[numRow];
    }

    template<long long N, long long M, typename Field>
    std::vector<Field> Matrix<N, M, Field>::getColumn(long long numColumn) {
        std::vector<Field> result(M);
        for (size_t index = 0; index < N; index++) {
            result[index] = _table[numColumn][index];
        }
        return result;
    }

    template<long long N, long long M, typename Field>
    std::vector<Field> &Matrix<N, M, Field>::operator[](const size_t index) {
        return _table[index];
    }


    template<long long N, long long M, typename Field>
    const std::vector<Field> &Matrix<N, M, Field>::operator[](const size_t index) const {
        return _table[index];
    }


    //Вывод матрицы
    template<long long N, long long M, typename Field>
    std::ostream &operator<<(std::ostream &out, Matrix<N, M, Field> const &element) {
        for (size_t indexRow = 0; indexRow < N; indexRow++) {
            for (size_t indexColumn = 0; indexColumn < M; indexColumn++) {
                out << element._table[indexRow][indexColumn] << " ";
            }
            out << "\n";
        }
        return out;
    }

    //Ввод матрицы
    template<long long N, long long M, typename Field>
    std::istream &operator>>(std::istream &in, Matrix<N, M, Field> &element) {
        for (size_t indexRow = 0; indexRow < N; indexRow++) {
            for (size_t indexColumn = 0; indexColumn < M; indexColumn++) {
                in >> element._table[indexRow][indexColumn];
            }
        }
        return in;
    }

}

using namespace FIELDS::GALOIS;
using namespace MATRIX;