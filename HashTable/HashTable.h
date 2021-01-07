#include <math.h>

struct Value {
    unsigned age;
    unsigned weight;
    Value() { age = 0; weight = 0; }
    Value(unsigned age_, unsigned weight_): age(age_), weight(weight_){};
    friend bool operator==(const Value &a, const Value &b) {
        return a.weight == b.weight && a.age == b.age;
    };
};

template<class K, class V>
class HashTable {
private:
    struct Node {
        K key;
        V value;
        Node *next;
        Node(K key_, V value_, Node* next_) : key(key_), value(value_), next(next_){};
    };
    
    void resize_table() {
        HashTable* new_table = new HashTable;       //create a new table
        new_table->table_size = table_size * 2;     //with size = 2 * (size current table)
        for (size_t j = 0; j < new_table->table_size; ++j) {   //allocate memory for every element of new table
            new_table->nodes[j] = (Node*) new Node*;
            new_table->nodes[j] = nullptr;
        }
        for (size_t i = 0; i < table_size; ++i) {      //go around the table and insert all of elements in new table
            if (nodes[i] && nodes[i]->next){ //if found a chain
                Node* tmp = nodes[i];
                while (tmp) {     //insert in order
                    new_table->insert(tmp->key, tmp->value);
                    tmp = tmp->next;
                }
            }
            else if (nodes[i]) {
                new_table->insert(nodes[i]->key, nodes[i]->value);
            }
        }
        *this = *new_table;
    };

    int get_hash(const K &key) const {
        int prime = 521;
        unsigned long int hash_result = 0;
        for (int i = 0; key[i] != 0; ++i) {
            hash_result += key[i]*pow(prime, i);
        }
        hash_result %= table_size;
        return hash_result;
    };

public:
    HashTable() {
        table_size = 5;          //create a table for 5 elements
        current_table_size = 0;
        fill_factor = static_cast<float>(current_table_size) / static_cast<float>(table_size);
        nodes = new Node*[table_size];      //allocate memory for 5 elements
        std::fill(nodes, nodes + table_size, nullptr);
    };

    ~HashTable() {
        clear();        //destructor firstable clear a table and then clear array of chains
        delete[] nodes;
    };

    HashTable(const HashTable &b) {
        table_size = b.table_size;      //initialization
        current_table_size = 0;
        nodes = new Node*[table_size];
        std::fill(nodes,nodes + table_size, nullptr);
        for (size_t i = 0; i < b.table_size; ++i) {
            if (b.nodes[i]) {
                insert(b.nodes[i]->key, b.nodes[i]->value);     //insert every element
                if (b.nodes[i]->next) {
                    while (b.nodes[i]->next) {   //if found a chain
                        b.nodes[i] = b.nodes[i]->next;
                        insert(b.nodes[i]->key, b.nodes[i]->value);
                    }
                }
            }
        }
    };

    void swap(HashTable &b) {
        std::swap(nodes, b.nodes);
        std::swap(table_size, b.table_size);
        std::swap(current_table_size, b.current_table_size);
    };

    HashTable &operator=(const HashTable &b) {
        if (*this == b) {
            return *this;
        }
        clear();
        table_size = b.table_size;
        delete[] nodes;
        nodes = new Node*[table_size];
        std::fill(nodes,nodes + table_size, nullptr);
        for (size_t i = 0; i < b.table_size; ++i) {
            if (b.nodes[i]) {
                insert(b.nodes[i]->key, b.nodes[i]->value);     //insert every element
                if (b.nodes[i]->next) {
                    while (b.nodes[i]->next) {       //if found a chain
                        b.nodes[i] = b.nodes[i]->next;
                        insert(b.nodes[i]->key, b.nodes[i]->value);
                    }
                }
            }
        }
        return *this;
    };

    void clear() {
        for (size_t i = 0; i < table_size; ++i) {
            while (nodes[i]) {       //delete every element
                Node* current = nodes[i]->next;
                delete nodes[i];
                nodes[i] = current;
            }
            nodes[i] = nullptr;
        }
        current_table_size = 0;
        fill_factor = 0;
    };

    bool erase(const K &k) {
        if (!contains(k)) {
            return false;
        }
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
    };
    
    bool insert(const K &k, const V &value) {
        if (fill_factor >= 0.75) {
            resize_table();
        }
        if (contains(k)) {
            return false;
        }
        int index = get_hash(k);
        if (nodes[index]) {   //if get in chain
            Node* tmp = nodes[index]->next;
            Node* prev = nodes[index];
            while (tmp) {     //find end of chain
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
    };

    bool contains(const K &k) const {
        int index;
        index = get_hash(k);
        if (!nodes[index]) {
            return false;
        }
        if (nodes[index]) {
            if (nodes[index]->key == k) {       //if not a chain
                return true;
            }
            else {
                while (nodes[index]->next) {     //else find necessary element
                    nodes[index] = nodes[index]->next;
                    if (nodes[index]->key == k) {
                        return true;
                    }
                }
            }
        }
        return false;       //if not found - false
    };

    V &operator[](const K &k) {
        int index = get_hash(k);
        if (!nodes[index]) {
            insert(k, Value());       //default value
            return nodes[index]->value;
        }
        else {
            return nodes[index]->value;
        }
    };

    V &at(const K &k) {
        int index = get_hash(k);
        if (nodes[index]->key == k) {
            return nodes[index]->value;
        }
        else {
            while (nodes[index]->next) {
                nodes[index] = nodes[index]->next;
                if (nodes[index]->key == k) {
                    return nodes[index]->value;
                }
            }
        }
    };

    const V &at(const K &k) const {
        int index = get_hash(k);
        if (nodes[index]->key == k) {
            return nodes[index]->value;
        }
        else {
            while (nodes[index]->next) {
                nodes[index] = nodes[index]->next;
                if (nodes[index]->key == k) {
                    return nodes[index]->value;
                }
            }
        }
    };

    size_t size() const { return current_table_size; };

    friend bool operator==(const HashTable &a, const HashTable &b) {
        if (a.current_table_size != b.current_table_size) {     //sizes aren't equal -> tables aren't equal.
            return false;
        }
        for (size_t i = 0; i < a.table_size; ++i) {
            if (a.nodes[i]) {       //if not a chain
                if (!a.nodes[i]->next) {
                    if (!b.contains(a.nodes[i]->key)) { //compare.
                        return false;
                    }
                }
                else {
                    HashTable::Node *tmp = a.nodes[i];         //if a chain.
                    while (tmp) {
                        if (!b.contains(a.nodes[i]->key)) {     //compare all of elements in a chain.
                            return false;
                        }
                        tmp = tmp->next;
                    }
                }
            }
        }
        return true;
    };

    friend bool operator!=(const HashTable &a, const HashTable &b) { return !(a == b); };

    bool empty() const { return current_table_size == 0; };
    
    class Iterator {
    public:
        Iterator(Node **nodes_, size_t node_index_, size_t chain_index_, size_t size_) :
                                                                                         node(nodes_),
                                                                                         node_index(node_index_),
                                                                                         chain_index(chain_index_),
                                                                                         size(size_){};
        ~Iterator(){};

        Iterator(const Iterator &a) {
            node = a.node;
            node_index = a.node_index;
            chain_index= a.chain_index;
            size = a.size;
        }

        Iterator &operator=(const Iterator &a) {
            if (&a != this) {
                node = a.node;
                node_index = a.node_index;
                chain_index= a.chain_index;
                size = a.size;
            }
            return *this;
        }

        friend bool operator==(const Iterator &a, const Iterator &b) {
            return a.node == b.node &&
                   a.chain_index == b.chain_index &&
                   a.node_index == b.node_index &&
                   a.size == b.size;
        }

        friend bool operator!=(const Iterator &a, const Iterator &b) { return !(a == b); }

        Node &operator*() {
            auto *tmp = node[chain_index];
            for (size_t i = 0; i < node_index; ++i) {
                assert(tmp);
                tmp = tmp->next;
            }
            return *tmp;
        }

        Iterator &operator++() {
            Node *tmp = node[chain_index];
            for (size_t i = 0; i < node_index; ++i) {
                assert(tmp);
                tmp = tmp->next;
            }
            if (!(tmp->next)) {
                for (size_t i = chain_index + 1; i < size; ++i) {
                    if (node[i]) {
                        node_index = 0;
                        chain_index = i;
                        return *this;
                    }
                }
            }
            ++node_index;
            return *this;
        }

    private:
        Node** node;
        size_t node_index;
        size_t chain_index;
        size_t size;
    };

    Iterator begin() {
        for (size_t i = 0; i < table_size; ++i) {
            if (nodes[i]) {
                return Iterator(nodes, 0, i, table_size);
            }
        }
        return Iterator(nodes, 0, table_size, table_size);
    };

    Iterator end() {
        for (size_t i = table_size - 1; i >= 0; --i) {
            if (nodes[i]) {
                Node *tmp = nodes[i];
                size_t t = 0;
                while (tmp) {
                    tmp = tmp->next;
                    ++t;
                }
                return Iterator(nodes, t, i, table_size);
            }
        }
        return Iterator(nodes, 0, table_size, table_size);
    }

private:
    Node** nodes = new Node*;
    size_t table_size;
    size_t current_table_size;
    float fill_factor;
};
