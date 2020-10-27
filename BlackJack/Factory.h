#include <unordered_map>
#include <string>

template<class Product, class Id>
struct DefaultErrorPolice {
    static Product *IdNotFound (const Id &name) {
        throw std::string ("BUSTED!");
    }
};

template<class Product, class Id, class Creator, class ErrorPolice = DefaultErrorPolice<Product, Id>>
class Factory {
public:
    Product *makeStrategy (const Id &name) {
        auto it = creators_.find (name);
        if (it == creators_.end ()) {
            return ErrorPolice::IdNotFound (name);
        }
        return it->second ();
    };

    void addCreator(const Id &name, Creator c) {
        creators_.insert_or_assign (name, c);
    };

    static Factory *getInstance () {
        static Factory f;
        return &f;
    };
    
private:
    Factory () = default;
    ~Factory () = default;
    Factory (const Factory &);
    Factory &operator= (const Factory &);
    std::unordered_map<Id, Creator> creators_;
};
