#include "HashTable.h"

#include <cmath>
#include <string>

typedef std::string Key;

HashTable::HashTable() {
    table_size = 5;          //create a table for 5 elements
    current_table_size = 0;
    fill_factor = static_cast<float>(current_table_size) / static_cast<float>(table_size);
    nodes = new Node*[table_size];      //allocate memory for 5 elements
    std::fill(nodes,nodes + table_size, nullptr);
}

HashTable::~HashTable() {
    clear();        //destructor firstable clear a table and then clear array of chains
    delete[] nodes;
}

HashTable::HashTable(const HashTable &b) {       //copy constructor
    table_size = b.table_size;      //initialization
    current_table_size = 0;
    nodes = new Node*[table_size];
    std::fill(nodes,nodes + table_size, nullptr);
    for (size_t i = 0; i < b.table_size; ++i) {
        if (b.nodes[i] != nullptr) {
            insert(b.nodes[i]->key, b.nodes[i]->value);     //insert every element
            if (b.nodes[i]->next != nullptr){
                while (b.nodes[i]->next != nullptr) {   //if found a chain
                    b.nodes[i] = b.nodes[i]->next;
                    insert(b.nodes[i]->key, b.nodes[i]->value);
                }
            }
        }
    }
}

void HashTable::swap(HashTable &b) {     //swap all elements of table
    std::swap(nodes, b.nodes);
    std::swap(table_size, b.table_size);
    std::swap(current_table_size, b.current_table_size);
}

HashTable& HashTable::operator=(const HashTable &b) {
    if (*this == b)
        return *this;
    clear();
    table_size = b.table_size;
    delete[] nodes;
    nodes = new Node*[table_size];
    std::fill(nodes,nodes + table_size, nullptr);
    for (size_t i = 0; i < b.table_size; ++i) {
        if (b.nodes[i] != nullptr) {
            insert(b.nodes[i]->key, b.nodes[i]->value);     //insert every element
            if (b.nodes[i]->next != nullptr) {
                while (b.nodes[i]->next != nullptr) {       //if found a chain
                    b.nodes[i] = b.nodes[i]->next;
                    insert(b.nodes[i]->key, b.nodes[i]->value);
                }
            }
        }
    }
    return *this;
}

void HashTable::clear() {
    for (size_t i = 0; i < table_size; ++i) {
        while (nodes[i] != nullptr) {       //delete every element
            Node* current = nodes[i]->next;
            delete nodes[i];
            nodes[i] = current;
        }
        nodes[i] = nullptr;
    }
    current_table_size = 0;
    fill_factor = 0;
}

bool HashTable::erase(const Key &k) {
    if (!contains(k)) 
        return false;
    int index = get_hash(k);
    if (nodes[index]->key == k) {       //if first in chain element is necessary
        Node *tmp = nodes[index];       //then just delete a first
        nodes[index] = nodes[index]->next;
        delete tmp;
        return true;
    }
    else {
        Node* prev = nodes[index];      //else find a necessary and delete
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

void HashTable::resize_table() {
    HashTable* new_table = new HashTable;       //create a new table
    new_table->table_size = table_size * 2;     //with size = 2 * (size current table)
    for (size_t j = 0; j < new_table->table_size; ++j) {   //allocate memory for every element of new table
        new_table->nodes[j] = (Node*) new Node*;
        new_table->nodes[j] = nullptr;
    }
    for (size_t i = 0; i < table_size; ++i) {      //go around the table and insert all of elements in new table
        if (nodes[i] != nullptr && nodes[i]->next != nullptr) { //if found a chain
            Node* tmp = nodes[i];
            while (tmp != nullptr){     //insert in order
                new_table->insert(tmp->key, tmp->value);
                tmp = tmp->next;
            }
        }
        else if (nodes[i] != nullptr) {
            new_table->insert(nodes[i]->key, nodes[i]->value);
        }
    }
    *this = *new_table;
}

bool HashTable::insert(const Key &k, const Value &value) {
    if (fill_factor >= 0.75)
        resize_table();
    if (contains(k))
        return false;
    int index = get_hash(k);
    if (nodes[index] != nullptr) {   //if get in chain
        Node* tmp = nodes[index]->next;
        Node* prev = nodes[index];
        while (tmp != nullptr) {     //find end of chain
            prev = tmp;
            tmp = prev->next;
        }
        tmp = new Node(k, value, nullptr);  //tmp points on end of chain (new element of chain)
        prev->next = tmp;
        current_table_size++;
        fill_factor = static_cast<float>(current_table_size) / static_cast<float>(table_size);
        return true;
    }
    else {
        nodes[index] = new Node(k, value, nullptr);     //else just insert on a free place
        current_table_size++;
        fill_factor = static_cast<float>(current_table_size) / static_cast<float>(table_size);
        return true;
    }
}

bool HashTable::contains(const Key &k) const {
    int index;
    index = get_hash(k);
    if (!nodes[index]) return false;
    if (nodes[index] != nullptr) {
        if (nodes[index]->key == k)     //if not a chain
            return true;
        else {
            while (nodes[index]->next != nullptr) {     //else find necessary element
                nodes[index] = nodes[index]->next;
                if (nodes[index]->key == k)
                    return true;
            }
        }
    }
    return false;       //if not found - false
}

Value& HashTable::operator[](const Key &k) {
    int index = get_hash(k);
    if (nodes[index] == nullptr) {
        insert(k, Value());       //default value
        return nodes[index]->value;
    }
    else {
        return nodes[index]->value;
    }
}

Value& HashTable::at(const Key &k) {
    int index = get_hash(k);
    if (nodes[index]->key == k) {
        return nodes[index]->value;
    }
    else{
        while (nodes[index]->next != nullptr) {
            nodes[index] = nodes[index]->next;
            if (nodes[index]->key == k){
                return nodes[index]->value;
            }
        }
    }
}

const Value& HashTable::at(const Key &k) const {
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
}

size_t HashTable::size() const {
    return current_table_size;
}

bool HashTable::empty() const {
    if (current_table_size == 0) return true;
    else
        return false;
}

bool operator==(const HashTable &a, const HashTable &b) {
    if (a.current_table_size != b.current_table_size)       //sizes isn't equal -> tables isn't equal
        return false;
    for (size_t i = 0; i < a.table_size; ++i) {
        if (a.nodes[i] != nullptr) {        //if not a chain
            if (a.nodes[i]->next == nullptr) {
                if (!b.contains(a.nodes[i]->key)) return false;     //compare
            }
            else {
                HashTable::Node *tmp = a.nodes[i];         //if a chain
                while (tmp != nullptr) {
                    if (!b.contains(a.nodes[i]->key)) return false;     //compare all of elements in a chain
                    tmp = tmp->next;
                }
            }
        }
    }
    return true;
}

bool operator!=(const HashTable &a, const HashTable &b) {
    if (!(a == b))
        return true;
    return false;
}

int HashTable::get_hash(const Key &key) const {     //polynomial hash functions
    int prime = 521;                                //hash = (primeˆ0 * key[0] + primeˆ1 * key[1] + ... + primeˆ(n-1) * key[n-1]) % (size of table)
    unsigned long int hash_result = 0;              //prime - big prime number
    for (int i = 0; key[i] != 0; ++i) {             //n-1 - lenght of key
        hash_result += key[i]*pow(prime, i);
    }
    hash_result %= table_size;
    return hash_result;
}



