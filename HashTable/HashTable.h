#include <iostream>
#include <math.h>
#include <string>

typedef std::string Key;

class HashTable{
public:
    struct Value {
        unsigned age;
        unsigned weight;
        Value(unsigned age_, unsigned weight_): age(age_), weight(weight_){};
    };

    HashTable();

    ~HashTable();

    HashTable(const HashTable &b);

    void swap(HashTable &b);

    HashTable &operator=(const HashTable &b);

    void clear() ;

    bool erase(const Key &k) ;

    void resize_table(const Key &k, const Value &value);

    bool insert(const Key &k, const Value &value);

    bool contains(const Key &k) const;

    Value &operator[](const Key &k);

    Value &at(const Key &k);

    const Value &at(const Key &k) const;

    size_t size() const;

    friend bool operator==(const HashTable &a, const HashTable &b);

    friend bool operator!=(const HashTable &a, const HashTable &b);

    bool empty() const;

    int get_hash(const std::string &key) const;

    friend bool operator==(const HashTable::Value &a, const HashTable::Value &b);

private:
    struct Node{
        Key key;
        Value value;
        Node *next;
        Node(Key key_, Value value_, Node* next_) :key(key_), value(value_), next(next_){};
    };
    Node** nodes = new Node*;
    int table_size;
    int current_table_size;
    int chains_count;
    float fill_factor;
};
