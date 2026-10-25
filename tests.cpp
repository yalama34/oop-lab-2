#include <gtest/gtest.h>
#include "my_string.h"
#include <cstring>
#include <sstream>
#include <utility>

TEST(StringBaseTest, CreateZeroSize){
    String s;
    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.capacity(), 1);
    ASSERT_NE(s.str(), nullptr);
    ASSERT_EQ(s.str()[0], '\0');
    ASSERT_EQ(String("").size(), 0);
    ASSERT_EQ(String(nullptr).size(), 0);
}

TEST(StringBaseTest, CreateSingleElement){
    String s("a");
    ASSERT_EQ(s.size(), 1);
    ASSERT_EQ(s.capacity(), 1);
    ASSERT_EQ(s.str()[0], 'a');
    ASSERT_EQ(s.str()[1], '\0');
}

TEST(StringBaseTest, CopyConstructor){
    String s1("abc");
    String s2(s1);
    ASSERT_EQ(s2.size(), 3);
    ASSERT_EQ(std::strcmp(s2.str(), "abc"), 0);
    ASSERT_NE(s2.str(), s1.str());
    s1.append("d");
    ASSERT_EQ(std::strcmp(s2.str(), "abc"), 0);
}

TEST(StringBaseTest, MoveConstructor){
    String s1("abc");
    const char* str = s1.str();
    String s2(std::move(s1));
    ASSERT_EQ(s2.str(), str);
    ASSERT_EQ(s2.size(), 3);
    ASSERT_EQ(std::strcmp(s2.str(), "abc"), 0);
    ASSERT_EQ(s1.str(), nullptr);
    ASSERT_EQ(s1.size(), 0);
    ASSERT_EQ(s1.capacity(), 0);
    s1.append("x");
    ASSERT_EQ(std::strcmp(s1.str(), "x"), 0);
}

TEST(StringBaseTest, CopyAssignment){
    String s1("abc");
    String s2("old value");
    s2 = s1;
    ASSERT_EQ(s2.size(), 3);
    ASSERT_EQ(std::strcmp(s2.str(), "abc"), 0);
    ASSERT_NE(s2.str(), s1.str());
    s2.append("d");
    ASSERT_EQ(std::strcmp(s1.str(), "abc"), 0);
}

TEST(StringBaseTest, MoveAssignment){
    String s1("abc");
    const char* str = s1.str();
    String s2("old value");
    s2 = std::move(s1);
    ASSERT_EQ(s2.str(), str);
    ASSERT_EQ(s2.size(), 3);
    ASSERT_EQ(std::strcmp(s2.str(), "abc"), 0);
    ASSERT_EQ(s1.str(), nullptr);
    ASSERT_EQ(s1.size(), 0);
    ASSERT_EQ(s1.capacity(), 0);
}

TEST(StringEdgeCasesTest, SelfAssignment){
    String s("abc");
    s = s;
    ASSERT_EQ(s.size(), 3);
    ASSERT_EQ(std::strcmp(s.str(), "abc"), 0);
    String s2;
    s2 = s2;
    ASSERT_EQ(s2.size(), 0);
    ASSERT_EQ(s2.str()[0], '\0');
}

TEST(StringBaseTest, SwapStrings){
    String a("abc");
    String b;
    a.swap(b);
    ASSERT_EQ(a.size(), 0);
    ASSERT_EQ(a.str()[0], '\0');
    ASSERT_EQ(b.size(), 3);
    ASSERT_EQ(std::strcmp(b.str(), "abc"), 0);
    b.swap(b);
    ASSERT_EQ(std::strcmp(b.str(), "abc"), 0);
}

TEST(StringEdgeCasesTest, AppendValues){
    String s("a");
    s.append("");
    s.append(nullptr);
    ASSERT_EQ(std::strcmp(s.str(), "a"), 0);
    ASSERT_EQ(s.capacity(), 1);
    s.append("b");
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.capacity(), 2);
    ASSERT_EQ(std::strcmp(s.str(), "ab"), 0);
    s.append("c");
    ASSERT_EQ(s.size(), 3);
    ASSERT_EQ(s.capacity(), 4);
    ASSERT_EQ(std::strcmp(s.str(), "abc"), 0);
    s.append(s.str());
    ASSERT_EQ(s.size(), 6);
    ASSERT_EQ(std::strcmp(s.str(), "abcabc"), 0);
}

TEST(StringEdgeCasesTest, FindSubstring){
    String s("ababa");
    ASSERT_EQ(s.find(""), 0);
    ASSERT_EQ(s.find("aba"), 0);
    ASSERT_EQ(s.find("baba"), 1);
    ASSERT_EQ(s.find("a"), 0);
    ASSERT_EQ(s.find("ababa"), 0);
    ASSERT_EQ(s.find("bababa"), String::npos);
    ASSERT_EQ(s.find("x"), String::npos);
    ASSERT_EQ(s.find(nullptr), String::npos);
    ASSERT_EQ(String().find(""), 0);
    ASSERT_EQ(String().find("a"), String::npos);
    ASSERT_EQ(String("abc").find("c"), 2);
}

TEST(StringBaseTest, PrintValues){
    std::ostringstream out;
    String().print(out);
    ASSERT_EQ(out.str(), "");
    String("abc").print(out);
    ASSERT_EQ(out.str(), "abc");
}

TEST(StringVariantTest, IsPalindrome){
    ASSERT_TRUE(String().is_palindrome());
    ASSERT_TRUE(String("a").is_palindrome());
    ASSERT_TRUE(String("aa").is_palindrome());
    ASSERT_TRUE(String("aba").is_palindrome());
    ASSERT_TRUE(String("abba").is_palindrome());
    ASSERT_TRUE(String("level").is_palindrome());
    ASSERT_FALSE(String("ab").is_palindrome());
    ASSERT_FALSE(String("abca").is_palindrome());
    ASSERT_FALSE(String("hello").is_palindrome());
}
