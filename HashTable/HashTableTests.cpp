#include "gtest/gtest.h"
#include "HashTable.h"

namespace{
    class HashTableTest : public ::testing::Test {
    protected:
        HashTable<std::string, Value> a;
    };

    TEST_F(HashTableTest, empty){
        HashTable<std::string, Value> b;
        Value value(19, 170);
        std::string key = "lorem";
        b.insert(key, value);
        b.clear();
        EXPECT_TRUE(b.empty());
    }

    TEST_F(HashTableTest, brackets_false){
        Value value(19, 170);
        Value b = a["lor"];
        EXPECT_FALSE(b == value);
    }

    TEST_F(HashTableTest, brackets_true){
        Value value(19, 170);
        std::string key = "lorem";
        a.insert(key, value);
        Value b = a["lorem"];
        EXPECT_TRUE(b == value);
    }

    TEST_F(HashTableTest, erase){
        Value value(19, 170);
        std::string key = "lorem";
        a.insert(key, value);
        a.erase(key);
        EXPECT_FALSE(a.contains(key));
        EXPECT_FALSE(a.erase("asd"));
    }

    TEST_F(HashTableTest, new_erase){
        Value value_1(19, 170);
        Value value_2(20, 160);
        std::string key_1 = "qwe";
        std::string key_2 = "ewq";
        a.insert(key_1, value_1);
        a.insert(key_2, value_2);
        a.erase(key_2);
        EXPECT_FALSE(a.contains(key_2));
    }

    TEST_F(HashTableTest, const_at){
        std::string key_1 = "lor";
        std::string key_2 = "em";
        std::string key_3 = "ips";
        std::string key_4 = "um";
        std::string key_5 = "lorem";
        a.insert(key_1, Value(19, 170));
        a.insert(key_2, Value(19, 170));
        a.insert(key_3, Value(19, 170));
        a.insert(key_4, Value(19,170));
        a.insert(key_5, Value(19,170));
        const HashTable<std::string, Value> b = a;
        EXPECT_EQ(b.at(key_1), Value(19, 170));
    }

    TEST_F(HashTableTest, at_false){
        Value value1(19, 170);
        Value value2(18, 120);
        std::string key1 = "test";
        std::string key2 = "lorem";
        a.insert(key1, value1);
        a.insert(key2, value2);
        EXPECT_FALSE(a.at(key1) == value2);
    }

    TEST_F(HashTableTest, at){
        HashTable<std::string, Value> k;
        Value value(19, 170);
        std::string key = "qwe";
        std::string key1 = "ewq";
        k.insert(key, value);
        k.insert(key1, value);
        EXPECT_EQ(k.at(key1), value);
    }

    TEST_F(HashTableTest, equal){
        HashTable<std::string, Value> g;
        HashTable<std::string, Value> j;
        g.insert("qwe", Value(1, 1));
        g.insert("ewq", Value(1, 1));
        j.insert("qwe", Value(1, 1));
        j.insert("ewq", Value(1, 1));
        EXPECT_TRUE(j == g);
    }

    TEST_F(HashTableTest, not_equal){
        HashTable<std::string, Value> c;
        Value value(19, 175);
        std::string key = "qwe";
        std::string key1 = "ewq";
        c.insert(key, value);
        c.insert(key1, value);
        c = a;
        EXPECT_FALSE(a != c);
    }

    TEST_F(HashTableTest, swap){
        HashTable<std::string, Value> a;
        HashTable<std::string, Value> b;
        Value value(1,1);
        a.insert("som", value);
        b.insert("lorem", value);
        a.swap(b);
        EXPECT_TRUE(a.contains("lorem"));
    }

    TEST_F(HashTableTest, resize){
        HashTable<std::string, Value> a;
        Value value(1,1);
        a.insert("lor",value);
        a.insert("em",value);
        a.insert("ip",value);
        a.insert("sum",value);
        a.insert("lorem",value);
        EXPECT_TRUE(a.contains("lor") == a.contains("em") == a.contains("sum"));
        EXPECT_TRUE(a.contains("ip") == a.contains("lorem"));
        EXPECT_TRUE(a.size() == 5);
    }
    TEST_F(HashTableTest, new_resize){
        HashTable<std::string, Value> a;
        Value value(1,1);
        a.insert("lor", value);
        a.insert("em", value);
        a.insert("ip", value);
        a.insert("sum", value);
        a.insert("lorem", value);
        a.insert("mor", value);
        a.insert("mus", value);
        EXPECT_TRUE(a.contains("lor") == a.contains("em") == a.contains("sum"));
        EXPECT_TRUE(a.contains("ip") == a.contains("lorem") == a.contains("mor"));
        EXPECT_TRUE(a.contains("mus"));
        EXPECT_TRUE(a.size() == 7);
    }

    TEST_F(HashTableTest, operator_equal) {
        HashTable<std::string, Value> a;
        Value value(1,1);
        a.insert("lor", value);
        a.insert("em", value);
        a.insert("ip", value);
        a.insert("sum", value);
        a.insert("lorem", value);
        a.insert("mor", value);
        a.insert("rom", value);
        HashTable<std::string, Value> b;
        b = a;
        EXPECT_TRUE(b.contains("lor") == b.contains("em") == b.contains("sum"));
        EXPECT_TRUE(b.contains("ip") == b.contains("lorem") == b.contains("mor"));
        EXPECT_TRUE(b.contains("rom"));
    }

    TEST_F(HashTableTest, template_contains) {
        HashTable<std::string, std::string> a;
        std::string value = "Apple";
        std::string key = "Orange";
        a.insert(key, value);
        EXPECT_TRUE(a.contains(key));
        EXPECT_TRUE(a.size() == 1);
    }

    TEST_F(HashTableTest, template_at) {
        HashTable<std::string, int> a;
        std::string key = "lorem";
        a.insert(key, 6);
        EXPECT_TRUE(a.at(key) == 6);
        EXPECT_TRUE(a.size() == 1);
    }

    TEST_F(HashTableTest, iterator_begin) {
        HashTable<std::string, Value> a;
        std::string key = "ipsum";
        a.insert(key, Value(19, 170));
        EXPECT_TRUE((*a.begin()).key == key);
    }

    TEST_F(HashTableTest, iterator) {
        HashTable<std::string, Value> a;
        std::string key_1 = "World";
        std::string key_2 = "lorem";
        a.insert(key_1, Value(19, 170));
        a.insert(key_2, Value(18, 190));
        EXPECT_TRUE((*a.begin()).key == key_1);
        EXPECT_TRUE((*a.begin()).value.weight == 170);
        EXPECT_TRUE(a.size() == 2);
    }

    TEST_F(HashTableTest, iterator_erase) {
        HashTable<std::string, Value> a;
        std::string key_1 = "World";
        std::string key_2 = "lorem";
        a.insert(key_1, Value(19, 170));
        a.insert(key_2, Value(18, 190));
        EXPECT_TRUE((*a.begin()).key == key_1);
        a.clear();
        std::string key_3 = "lor";
        std::string key_4 = "ips";
        a.insert(key_3, Value(23, 164));
        a.insert(key_4, Value(21, 180));
        auto i = a.begin();
        EXPECT_TRUE((*i).value.age == 21);
        EXPECT_TRUE((*i).key == key_4);
        ++i;
        EXPECT_TRUE((*i).value.age == 23);
        EXPECT_TRUE((*i).key == key_3);
    }

    TEST_F(HashTableTest, iterator_size) {
        HashTable<std::string, Value> a;
        std::string key_1 = "World";
        std::string key_2 = "lorem";
        std::string key_3 = "lor";
        std::string key_4 = "ips";
        a.insert(key_1, Value(19, 170));
        a.insert(key_2, Value(18, 190));
        a.insert(key_3, Value(23, 164));
        a.insert(key_4, Value(21, 180));
        size_t s = 0;
        for (auto i = a.begin(); i != a.end(); i++) {
            s++;
        }
        EXPECT_TRUE(s == a.size());
    }

}
