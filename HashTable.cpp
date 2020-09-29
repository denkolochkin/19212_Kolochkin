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
    for (int i = 0; i <= chains_count; ++i) {
        while(nodes[i] != nullptr) {
            Node *tmp = nodes[i]->next;
            delete nodes[i];
            nodes[i]=tmp;
        }
    }
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
    HashTable tmp;

    tmp.table_size = b.table_size;
    tmp.current_table_size = b.current_table_size;
    tmp.chains_count = b.chains_count;
    tmp.fill_factor = b.fill_factor;
    tmp.nodes = b.nodes;

    b.table_size = table_size;
    b.current_table_size = current_table_size;
    b.chains_count = chains_count;
    b.fill_factor = fill_factor;
    b.nodes = nodes;

    table_size = tmp.table_size;
    current_table_size = tmp.current_table_size;
    chains_count = tmp.chains_count;
    fill_factor = tmp.fill_factor;
    nodes = tmp.nodes;

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
    for (int i = 0; i <= chains_count; ++i) {
        while(nodes[i] != nullptr) {
            Node *tmp = nodes[i]->next;
            delete nodes[i];
            nodes[i]=tmp;
        }
        nodes[i] = nullptr;
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

void HashTable::resize_table(HashTable* old_table ,const Key &k, const Value &value){
    HashTable new_table;
    new_table.table_size = old_table->table_size * 2;
    for (int j = 0; j < new_table.table_size; ++j) {
        new_table.nodes[j] = (Node*) new Node*;
        new_table.nodes[j] = nullptr;
    }
    std::fill(new_table.nodes,new_table.nodes + new_table.table_size, nullptr);
    new_table.insert(k, value);

    for (int i = 0; i < old_table->table_size; ++i) {
        if (old_table->nodes[i] != nullptr && old_table->nodes[i]->next != nullptr) {
            Node* tmp = old_table->nodes[i];
            while (tmp != nullptr){
                new_table.insert(tmp->key, tmp->value);
                tmp = tmp->next;
            }
        }
        else if (old_table->nodes[i] != nullptr){
            new_table.insert(old_table->nodes[i]->key, old_table->nodes[i]->value);
        }
    }
    old_table->clear();
    *old_table = new_table;
}

bool HashTable::insert(const Key &k, const Value &value) {
    if (fill_factor >= 0.75) {
        resize_table(this, k ,value);
        return true;
    }
    int index = get_hash(k);
    if (nodes[index] != NULL)  {
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

bool HashTable::contains (const Key &k) const{
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
    long int hash_result = 0;
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
