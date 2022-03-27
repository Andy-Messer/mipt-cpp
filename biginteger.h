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
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

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

    friend std::istream &operator>>(std::istream &in, BigInteger &value) {
        string s;
        in >> s;
        value = BigInteger(s);
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const BigInteger &value) {
        string str = value.toString();
        out << str;
        return out;
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
            //исправил копирование
            if (abs(other) > abs(*this)) {
                if (sign == 0) {
                    sign = true;
                } else {
                    sign = false;
                }
            }
            *this = Difference(*this, other);
            isPositive = sign;
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
        if (!(this->isPositive && other.isPositive) && !(!this->isPositive && !other.isPositive)) {
            if (abs(other) > abs(*this)) {
                sign = !sign;
            }
            *this = Difference(*this, other);
            this->isPositive = sign;
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

    static int CompareNotEqualSizeOrOtherPlus(const BigInteger &first, const BigInteger &second) {
        if (first.isPositive && second.isPositive && first.number.size() < second.number.size()) {
            return 3;
        }
        if (first.isPositive && second.isPositive && first.number.size() > second.number.size()) {
            return 2;
        }
        return CompareNotEqualSizeOrOtherMinus(first, second);
    }

    static int CompareNotEqualSizeOrOtherMinus(const BigInteger &first, const BigInteger &second) {
        if (!(first.isPositive) && !(second.isPositive) && first.number.size() > second.number.size()) {
            return 2;
        }
        if (!(first.isPositive) && !(second.isPositive) && first.number.size() < second.number.size()) {
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
                first.number.push_back(10 - prev_rest + firstCopy.number[i] - secondCopy.number[i]);
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
            for (size_t j = 0; j < n; j++) {// Можно сразу расширить вместо постепенного расширения, быстрее будет
                //если и делать ускорение, то хранить по блокам, а не по цифрам, в данном моменте ускорение хоть и будет, но нашей целью не было выйграть во времени. Оставлю так
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

    Rational(BigInteger numberUp, BigInteger numberDown = 1) : numerator(numberUp), denominator(numberDown),
                                                               isPositive(true) {
        CheckSignAndCorrect(numerator, denominator);
    };

    Rational(const int numberUp, int numberDown = 1) : numerator(numberUp), denominator(numberDown),
                                                       isPositive(true) {
        CheckSignAndCorrect(numerator, denominator);
    };


    Rational &operator+=(const Rational &other) {
        if (isPositive == other.isPositive)
            numerator = numerator * other.denominator + denominator * other.numerator;
        else
            numerator = numerator * other.denominator - denominator * other.numerator;
        denominator = other.denominator * denominator;
        CheckSignAndCorrect(*this);
        return *this;
    };

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
            BigInteger n = numeratorCopy;
            for (size_t i = 0; i < precision; ++i) {
                n *= 10;
            }
            BigInteger result = n / denominatorCopy;
            if (numeratorCopy < denominatorCopy) {// Это проверяется просто сравнением, исправил
                string after = result.toString();
                if (after.size() < precision) {
                    after = string(precision - after.size(), '0') + after;
                }
                ans = "0." + after;
                if (!isPositive && numeratorCopy != 0 && result != 0)ans = '-' + ans;
            } else {
                ans = result.toString();
                ans = ans.substr(0, ans.size() - precision) + '.' + ans.substr(ans.size() - precision, precision);
                if (!isPositive && numeratorCopy != 0)ans = '-' + ans;
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

    explicit operator double() {// stod, и точности накинь хотя бы до 32
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
