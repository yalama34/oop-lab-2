#include "my_string.h"

String::String()
    : size_(0),
      capacity_(1) {
    str_ = new char[capacity_ + 1];
    str_[0] = '\0';
}

String::String(const char* str)
    : size_(0),
      capacity_(1) {
    if (str == nullptr) {
        str_ = new char[capacity_ + 1];
        str_[0] = '\0';
        return;
    }
    for(std::size_t i = 0; str[i] != '\0'; i++){
        if (size_ == capacity_) {
            capacity_ *= 2;
        }
        size_++;
    }
    str_ = new char[capacity_ + 1];
    for (std::size_t i = 0; i < size_; i++) {
        str_[i] = str[i];
    }
    str_[size_] = '\0';
}

String::~String() {
    delete[] str_;
}

String::String(const String& other)
    : size_(other.size()),
      capacity_(other.capacity()){
    str_ = new char[capacity_ + 1];
    for (std::size_t i = 0; i < size_; i++){
        str_[i] = other.str()[i];
    }
    str_[size_] = '\0';
}

String::String(String&& other) noexcept
    : size_(other.size()),
      capacity_(other.capacity()){
    str_ = other.str_;
    other.str_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

void String::swap(String& other) noexcept {
    std::size_t temp_s = size_;
    size_ = other.size_;
    other.size_ = temp_s;

    std::size_t temp_c = capacity_;
    capacity_ = other.capacity_;
    other.capacity_ = temp_c;

    char* temp_str = str_;
    str_ = other.str_;
    other.str_ = temp_str;
}

String& String::operator=(String other) {
    swap(other);
    return *this;
}

void String::append(const char* other_str) {
    if (other_str == nullptr) {
        return;
    }
    std::size_t other_size = 0;
    while (other_str[other_size] != '\0') {
        ++other_size;
    }
    if (other_size == 0) {
        return;
    }
    std::size_t new_size = size_ + other_size;
    if (new_size > capacity_ || str_ == nullptr) {
        std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_;
        while (new_capacity < new_size) {
            if (new_capacity > std::numeric_limits<std::size_t>::max() / 2) {
                new_capacity = new_size;
                break;
            }
            new_capacity *= 2;
        }
        char* temp = new char[new_capacity + 1];
        for (std::size_t i = 0; i < size_; ++i) {
            temp[i] = str_[i];
        }
        for (std::size_t i = 0; i < other_size; ++i) {
            temp[size_ + i] = other_str[i];
        }
        temp[new_size] = '\0';
        delete[] str_;
        str_ = temp;
        capacity_ = new_capacity;
    } else {
        for (std::size_t i = 0; i < other_size; ++i) {
            str_[size_ + i] = other_str[i];
        }
        str_[new_size] = '\0';
    }
    size_ = new_size;
}

void String::print(std::ostream& out) const {
    for (std::size_t i = 0; i < size_; i++) {
        out << str_[i];
    }
}

std::size_t first_match_count(const char* str1, const char* str2, std::size_t min_size) {
    std::size_t result = 0;
    for (std::size_t i = 0; i < min_size; i++) {
        if (str1[i] != str2[i]) {
            return result;
        }
        ++result;
    }
    return result;
}

std::size_t String::find(const char* substr) const {
    if (substr == nullptr) {
        return npos;
    }
    std::size_t substr_size = 0;
    while (substr[substr_size] != '\0') {
        ++substr_size;
    }
    if (substr_size == 0) {
        return 0;
    }
    if (substr_size > size_) {
        return npos;
    }
    for (std::size_t i = 0; i <= size_ - substr_size; ++i) {
        if (first_match_count(str_ + i, substr, substr_size) == substr_size) {
            return i;
        }
    }
    return npos;
}

bool String::is_palindrome() const {
    std::size_t left = 0;
    std::size_t right = size_;
    while (left < right) {
        if (str_[left] != str_[right - 1]) return false;
        left++;
        right--;
    }
    return true;
}