#include "my_string.h"

MyString::MyString() : string_(nullptr) {}

MyString::MyString(char c) {
    string_ = new char[2];
    string_[0] = c;
    string_[1] = '\0';
}

MyString::MyString(const char* string) {
    string_ = new char[strlen(string) + 1];
    strcpy(string_, string);
}

MyString::MyString(const MyString& other) {
    string_ = new char[strlen(other.string_) + 1];
    strcpy(string_, other.string_);
}

MyString::~MyString() {
    delete[] string_;
}

MyString& MyString::operator=(const MyString& other) {
    string_ = new char[strlen(other.string_) + 1];
    strcpy(string_, other.string_);
    return *this;
}

char MyString::operator[](const int index) const {
    return string_[index];
}

MyString MyString::operator+(const MyString& other) const {
    MyString result;
    result.string_ = new char[Length() + other.Length() + 1];
    strcpy(result.string_, string_);
    strcat(result.string_, other.string_);
    return result;
}

bool MyString::operator!=(const MyString& str2) const {
    return strcmp(string_, str2.string_);
}

MyString MyString::operator+(char c) const {
    MyString result;
    result.string_ = new char[Length() + 2];
    strcpy(result.string_, string_);
    result.string_[Length()] = c;
    result.string_[Length() + 1] = '\0';
    return result;
}

bool MyString::operator==(const MyString& other) const {
    return strcmp(string_, other.string_) == 0;
}

bool MyString::operator!() const {
    return string_ == nullptr;
}

bool MyString::IsEmpty() const {
    return Length() == 0;
}

bool MyString::operator!=(const char* str) const {
    return !(*this == str);
}

MyString& MyString::operator+=(const MyString& other) {
    char* new_string = new char[Length() + other.Length() + 1];
    strcpy(new_string, string_);
    strcat(new_string, other.string_);
    delete[] string_;
    string_ = new_string;
    return *this;
}

MyString& MyString::operator+=(char c) {
    char* new_string = new char[Length() + 2];
    strcpy(new_string, string_);
    new_string[Length()] = c;
    new_string[Length() + 1] = '\0';
    delete[] string_;
    string_ = new_string;
    return *this;
}

const char* MyString::CStr() const {
    return string_;
}

int MyString::Length() const {
    return strlen(string_);
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    os << str.CStr();
    return os;
}
