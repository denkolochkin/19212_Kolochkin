#include <iostream>
#include <math.h>
#include <string>
#include "HashTable.h"

typedef std::string Key;

HashTable::HashTable() {
    table_size = 3;
    current_table_size = 0;
    chains_count = 0;
    nodes = new Node*[table_size];
    std::fill(nodes,nodes + table_size, nullptr);
};

HashTable::~HashTable(){
    clear();
    delete[] nodes;
};

HashTable::HashTable(const HashTable &b){
        table_size = b.table_size;
        current_table_size = b.current_table_size;
        chains_count = b.chains_count;
        fill_factor = b.fill_factor;
        nodes = new Node*;
        for (int i = 0; i <= b.chains_count; ++i) {
            nodes[i] = b.nodes[i];
        }
}

void HashTable::swap(HashTable &b){
    std::swap(nodes, b.nodes);
    std::swap(table_size, b.table_size);
    std::swap(current_table_size, b.current_table_size);
    std::swap(chains_count, b.chains_count);
};

HashTable& HashTable::operator=(HashTable &b){
        table_size = b.table_size;
        current_table_size = b.current_table_size;
        chains_count = b.chains_count;
        fill_factor = b.fill_factor;
        nodes = new Node*;
        for (int i = 0; i <= b.chains_count; ++i) {
            nodes[i] = b.nodes[i];
        }
        return *this;
};

void HashTable::clear() {
    Node* prev;
    for (int i = 0; i <= chains_count; ++i) {
        if (nodes[i] != nullptr) {
            if(nodes[i]->next != nullptr) {
                prev = nodes[i];
                while (nodes[i]->next != nullptr) {
                    nodes[i] = nodes[i]->next;
                    delete prev;
                    prev = nodes[i];
                }
                delete nodes[i];
                nodes[i] = nullptr;
            }
            else {
                delete nodes[i];
                nodes[i] = nullptr;
            }
        }
    }
    current_table_size = 0;
};

bool HashTable::erase(const Key &k) {
    int index = get_hash(k);
    if (!nodes[index])
        return false;
    if (nodes[index]->key == k) {
        Node *tmp = nodes[index];
        nodes[index] = nodes[index]->next;
        delete tmp;
        return true;
    } else {
        Node* prev = nodes[index];
        Node* deleted = nodes[index];
        while (deleted->key != k) {
            prev = deleted;
            deleted = deleted->next;
        }
        prev->next = deleted->next;
        delete deleted;
        return true;
    }
}

HashTable& HashTable::resize_table(const Key &k, const Value &value) {
    HashTable* new_table = new HashTable;
    new_table->table_size = table_size * 2;
    for (int j = 0; j < new_table->table_size; ++j) {
        new_table->nodes[j] = (Node*) new Node*;
        new_table->nodes[j] = nullptr;
    }
    new_table->insert(k, value);
    for (int i = 0; i < table_size; ++i) {
        if (nodes[i] != nullptr && nodes[i]->next != nullptr) {
            Node* tmp = nodes[i];
            while (tmp != nullptr){
                new_table->insert(tmp->key, tmp->value);
                tmp = tmp->next;
            }
        }
        else if (nodes[i] != nullptr){
            new_table->insert(nodes[i]->key, nodes[i]->value);
        }
    }
    return *new_table;
}

bool HashTable::insert(const Key &k, const Value &value) {
    if (fill_factor >= 0.75) {
        *this = resize_table(k ,value);
        return true;
    }
    int index = get_hash(k);
    if (nodes[index] != nullptr)  {
        Node* tmp = nodes[index]->next;
        Node* prev = nodes[index];
        while (tmp != nullptr){
            prev = tmp;
            tmp = prev->next;
        }
        tmp = new Node(k, value, nullptr);
        prev->next = tmp;
        current_table_size++;
        fill_factor = static_cast<float>(current_table_size) / static_cast<float>(table_size);
        return true;
    } else {
        nodes[index] = new Node(k, value, nullptr);
        chains_count++;
        current_table_size++;
        fill_factor = static_cast<float>(current_table_size) / static_cast<float>(table_size);
        return true;
    }
};

bool HashTable::contains(const Key &k) const{
    int index;
    index = get_hash(k);
    if (!nodes[index]) return false;
    if (nodes[index] != nullptr) {
        if (nodes[index]->key == k) return true;
        else {
            while (nodes[index]->next != nullptr) {
                nodes[index] = nodes[index]->next;
                if (nodes[index]->key == k) return true;
            }
        }
    }
    return false;
};

Value& HashTable::operator[](const Key &k){
    int index = get_hash(k);
    if (nodes[index] == nullptr) {
        insert(k, Value(19,175));
        return nodes[index]->value;
    }
    else {
        return nodes[index]->value;
    }
};

Value& HashTable::at(const Key &k) {
    int index = get_hash(k);
    try {
        if (!nodes[index]) {
            throw 0;
        }
        if (nodes[index]->key == k) {
            return nodes[index]->value;
        } else {
            while (nodes[index]->next != nullptr) {
                nodes[index] = nodes[index]->next;
                if (nodes[index]->key == k) {
                    return nodes[index]->value;
                }
            }
        }
    }
    catch (int) {
        std::cout<<"nullptr"<<std::endl;
        Value s(0,0);
        return s;
    }
};

const Value& HashTable::at(const Key &k) const{
    int index = get_hash(k);
    if (nodes[index]->key == k) {
        return nodes[index]->value;
    }
    else {
        while (nodes[index]->next != nullptr) {
            nodes[index] = nodes[index]->next;
            if (nodes[index]->key == k)
                return nodes[index]->value;
        }
    }
};

size_t HashTable::size() const {
    return table_size;
};

bool HashTable::empty() const {
    if (table_size == 0) return true;
        else
            return false;
};

bool operator==(const HashTable &a, const HashTable &b){
    if (a.current_table_size != b.current_table_size)
        return false;
    for (int i = 0; i < a.table_size; ++i) {
        if (a.nodes[i] != nullptr) {
            if (a.nodes[i]->next == nullptr) {
                if (!b.contains(a.nodes[i]->key)) return false;
            } else {
                Node *tmp = a.nodes[i];
                while (tmp != nullptr) {
                    if (!b.contains(a.nodes[i]->key)) return false;
                    tmp = tmp->next;
                }
            }
        }
    }

    return true;
}

bool operator!=(const HashTable &a, const HashTable &b){
    if (!(a == b))
        return true;
    return false;
};

int HashTable::get_hash(const Key &key) const {
    int prime = 521;
    unsigned long int hash_result = 0;
    for (int i = 0; key[i] != 0; ++i) {
        hash_result += key[i]*pow(prime, i);
    }
    hash_result %= table_size;
    return hash_result;
}

bool operator==(const Value &a, const Value &b){
    if (a.weight == b.weight && a.age == b.age)
        return true;
    return false;
};
