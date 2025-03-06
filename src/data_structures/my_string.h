#ifndef MY_STRING_H
#define MY_STRING_H

#include <iostream>
#include <cstring>

class MyString {
private:
    char* string_;

public:
    MyString();
    MyString(char c);
    MyString(const char* string);
    MyString(const MyString& other);
    ~MyString();

    int Length() const;
    bool IsEmpty() const;
    const char* CStr() const;

    MyString& operator=(const MyString& other);
    char operator[](const int index) const;
    MyString operator+(const MyString& other) const;
    MyString operator+(char c) const;
    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& str2) const;
    bool operator!() const;
    bool operator!=(const char* str) const;
    MyString& operator+=(const MyString& other);
    MyString& operator+=(char c);

    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
};

#endif // MY_STRING_H
