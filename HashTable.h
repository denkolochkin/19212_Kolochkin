#include <iostream>
#include <math.h>
#include <string>

typedef std::string Key;

template<typename T>
T* begin(std::pair<T *, T *> const &p) { return p.first; }

template<typename T>
T* end(std::pair<T *, T *> const &p) { return p.second; }


struct Value {
    unsigned age;
    unsigned weight;
    Value(unsigned age_, unsigned weight_): age(age_), weight(weight_){};
};

bool operator==(const Value &a, const Value &b);

struct Node {
    Key key;
    Value value;
    Node *next;
    Node(Key key_, Value value_, Node* next_) :key(key_), value(value_), next(next_){};
};


class HashTable {
public:
    HashTable();
    ~HashTable();
    HashTable(const HashTable &b);

    void swap(HashTable &b);

    HashTable &operator=(HashTable &b);

    void clear() ;

    bool erase(const Key &k) ;

    HashTable& resize_table(const Key &k, const Value &value);

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

private:
    Node** nodes = new Node*;
    int table_size;
    int current_table_size;
    int chains_count;
    float fill_factor;
};
