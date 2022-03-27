//
// Created by Admin on 06.04.2021.
//

#ifndef STRING_STRING_H

#include <iostream>
#include <cstring>
#include <algorithm>


class String {
private:

    //ячейки памяти, которые доступны
    size_t size_In_Storage_ = 0;


    // реальный размер строки
    size_t real_Size_Of_Line_ = 0;


    //строка
    char *str = nullptr;

    void ExpandStorage(size_t newSize) {// Этот метод должен быть приватный, так как пользователю снаружи не следует знать о нём
        size_t copySizeStorage = size_In_Storage_;

        bool mark = 0;
        while (copySizeStorage + newSize > size_In_Storage_) {
            (size_In_Storage_ += 1) *= 2;
            mark = 1;// А есть случаи, когда это не произойдёт?
        }
        if (mark) {
            char *copy = str;
            str = new char[++size_In_Storage_];
            if (copy != nullptr) {
                memcpy(str, copy, real_Size_Of_Line_);
                delete[] copy;
            }
        }

    }

    void DecreaseStorage() {// аналогично
        if (real_Size_Of_Line_ > 0) {
            bool mark = 0;
            while (real_Size_Of_Line_ < size_In_Storage_ / 4) {
                (size_In_Storage_ /= 2);
                mark = 1;
            }
            if (mark) {
                char *copy = str;
                str = new char[++size_In_Storage_];
                if (copy != nullptr) {
                    memcpy(str, copy, real_Size_Of_Line_);
                    delete[] copy;
                }
            }

        }
    }


    [[nodiscard]] size_t size() const {
        return size_In_Storage_;
    };

public:

    //Конструктор по умолчанию
    String() = default;

    //Конструктор от двух параметров: число n и символ c - создает строку из n копий символа c.
    explicit String(size_t sz, char c = '\0') : real_Size_Of_Line_(sz),
                                                str(new char[sz]) {
        size_In_Storage_ = sz;
        memset(str, c, real_Size_Of_Line_);
    };


    //Конструктор от C-style строки (const char*).
    String(const char *s) : String(strlen(s), '\0') {
        memcpy(str, s, real_Size_Of_Line_);
    };

    String(const char s) : String(1, '\0') {
        str[0] = s;
    };


    //копирующий конструктор
    String(const String &s) : String(s.real_Size_Of_Line_, '\0') {
        memcpy(str, s.str, real_Size_Of_Line_);
        DecreaseStorage();
    };


    //оператор присваивания
    String &operator=(const String &other) {
        String copy = other;
        swap(copy);
        DecreaseStorage();
        return *this;
    };

    void swap(String &s) {
        std::swap(real_Size_Of_Line_, s.real_Size_Of_Line_);
        std::swap(size_In_Storage_, s.size_In_Storage_);
        std::swap(str, s.str);
    };


    bool operator!=(const String &other);

    friend bool operator==(const String &My, const String &other);

    friend String operator+(const String &first,
                            const String &second);

    //Квадратные скобки, корректно работающие как для константных, так и для неконстантных строк.
    const char &operator[](size_t index) const {
        return str[index];
    };

    char &operator[](size_t index) {
        return str[index];
    };


    //Метод length(), возвращающий размер строки.
    [[nodiscard]] size_t length() const {
        return real_Size_Of_Line_;
    };

    //Методы push_back(char) и pop_back(). Учетное время работы должно быть O(1).
    void push_back(char c) {
        if (real_Size_Of_Line_ + 1 >= size_In_Storage_) {
            size_t newSize = real_Size_Of_Line_ + 2 - size_In_Storage_;
            real_Size_Of_Line_++;
            this->ExpandStorage(newSize);
            str[real_Size_Of_Line_ - 1] = c;
        } else {
            real_Size_Of_Line_++;
            str[real_Size_Of_Line_ - 1] = c;
        }
    };

    void pop_back() {
        if (real_Size_Of_Line_ != 0) {
            real_Size_Of_Line_--;
        }
        DecreaseStorage();
    };


    //Методы front() и back(), возвращающие ссылку на начальный и на последний символы строки соответственно.
    char &front() {
        return str[0];
    };

    const char &front() const {
        return str[0];
    };

    char &back() {
        return str[real_Size_Of_Line_ - 1];
    };

    const char &back() const {
        return str[real_Size_Of_Line_ - 1];
    };


    //Оператор +=, позволяющий добавить к строке символ или другую строку. Добавление символа должно работать за амортизированное O(1).
    String &operator+=(const String &other) {
        if (real_Size_Of_Line_ + other.real_Size_Of_Line_ > size_In_Storage_) {
            size_t newSize = real_Size_Of_Line_ + other.real_Size_Of_Line_ -
                             size_In_Storage_;
            ExpandStorage(newSize);
        }
        memcpy(str + real_Size_Of_Line_, other.str, (other.real_Size_Of_Line_));
        real_Size_Of_Line_ += other.real_Size_Of_Line_;
        return (*this);
    };

    String &operator+=(const char &other) {
        this->push_back(other);
        return *this;
    };


    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //Методы find(substring) и rfind(substring), позволяющие найти самое левое и самое правое вхождение подстроки substring в данную строку.
    //Возвращают индекс найденного вхождения. Если вхождений не найдено, нужно вернуть length() (фиктивный индекс).
    size_t find(const String &other) const {
        if (str != nullptr) {
            size_t glob_index = 0, local_index;
            while (glob_index < real_Size_Of_Line_) {
                local_index = 0;
                while (glob_index < real_Size_Of_Line_ &&
                       str[glob_index] == other[local_index]) {
                    glob_index++;
                    local_index++;
                }
                if (local_index == other.real_Size_Of_Line_) {
                    return glob_index - local_index;
                }
                glob_index++;
            }
        }
        return real_Size_Of_Line_;
    };

    size_t rfind(const String &other) const {
        if (str != nullptr) {
            size_t glob_index = real_Size_Of_Line_, local_index;
            for (size_t i = glob_index; i > 0; i--) {
                local_index = 0;
                size_t start = i - 1;
                while (start < real_Size_Of_Line_ &&
                       str[start] == other[local_index]) {
                    start++;
                    local_index++;
                }
                if (local_index == other.real_Size_Of_Line_) {
                    return start - local_index;
                }
            }
        }
        return real_Size_Of_Line_;
    };


    //+Метод substr(start, count), возвращающий подстроку начиная с индекса start и состоящую из count символов.
    String substr(size_t start, size_t count) const {
        String copy;
        size_t newSize = count + 1;
        copy.ExpandStorage(newSize);
        copy.real_Size_Of_Line_ = newSize;
        memcpy(copy.str, str + start, count);
        copy.str[count] = '\0';
        return copy;
    };


    //Метод empty(), проверяющий, пуста ли строка.++
    bool empty() const {
        return real_Size_Of_Line_ == 0;
    }


    //Метод clear(), позволяющий очистить строку.+
    void clear() {
        real_Size_Of_Line_ = 0;
        size_In_Storage_ = 0;
        delete[]this->str;
        str = nullptr;
    }


    //Операторы вывода в поток « и ввода из потока ».++
    friend std::ostream &operator<<(std::ostream &out, const String &s);

    friend std::istream &operator>>(std::istream &in, String &s);


    //Деструктор++
    ~String() {
        clear();
    };

};

//Оператор ==, позволяющий проверять строки на совпадение.++
bool operator==(const String &My, const String &other) {
    long long h = std::strcmp(My.str, other.str);
    if (h == 0) {
        return 1;
    }
    return 0;
};

bool String::operator!=(const String &other) {
    long long h = std::strcmp(this->str, other.str);
    if (h == 0) {
        return 0;
    }
    return 1;
};

//Оператор +, позволяющий складывать строки с символами, символы со строками и строки со строками.
//+
String operator+(const String &first,
                 const String &second) {
    String copy = first;
    copy += second;
    return copy;
};

//++
std::ostream &operator<<(std::ostream &out, const String &s) {
    for (size_t i = 0; i < s.length(); ++i) {
        out << s[i];
    }
    return out;
}

std::istream &operator>>(std::istream &in, String &s) {
    s.clear();
    char c;
    while (in.get(c)) {
        if (!isspace(c)) {
            s.push_back(c);
        } else {
            break;
        }
    }
    return in;
}

#define STRING_STRING_H

#endif //STRING_STRING_H
