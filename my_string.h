#pragma once

#include <iostream>
#include <cstddef>
#include <iosfwd>

class String {
    char* str_;
    std::size_t size_;
    std::size_t capacity_;
public:
    static constexpr std::size_t npos = static_cast<std::size_t>(-1);
    String(const char* str);
    String();

    ~String();

    String(const String& other);
    String(String&& other) noexcept;
    String& operator=(String other);

    std::size_t size() const {return size_;}
    const char* str() const {return str_;}
    std::size_t capacity() const {return capacity_;}

    void swap(String& other) noexcept;
    void append(const char* other_str);
    void print(std::ostream& out) const;
    std::size_t find(const char* pat) const;
    bool is_palindrome() const;
};