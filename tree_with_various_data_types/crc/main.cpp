#include <iostream>
#include <nlohmann/json.hpp>


using json = nlohmann::json;


void test_json()
{
    // create an array using push_back
    json j;
    j.push_back("foo");
    j.push_back(1);
    j.push_back(true);

    // also use emplace_back
    j.emplace_back(1.78);

    // iterate the array
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        std::cout << *it << '\n';
    }

    // range-based for
    for (auto& element : j) {
        std::cout << element << '\n';
    }

    // getter/setter
    const auto tmp = j[0].get<std::string>();
    j[1] = 42;
    bool foo = j.at(2);

    // comparison
    j == "[\"foo\", 42, true]"_json;  // true

    // other stuff
    j.size();     // 3 entries
    j.empty();    // false
    j.type();     // json::value_t::array
    j.clear();    // the array is empty again

    // convenience type checkers
    j.is_null();
    j.is_boolean();
    j.is_number();
    j.is_object();
    j.is_array();
    j.is_string();

    // create an object
    json o;
    o["foo"] = 23;
    o["bar"] = false;
    o["baz"] = 3.141;

    // also use emplace
    o.emplace("weather", "sunny");

    // special iterator member functions for objects
    for (json::iterator it = o.begin(); it != o.end(); ++it) {
        std::cout << it.key() << " : " << it.value() << "\n";
    }

    // the same code as range for
    for (auto& el : o.items()) {
        std::cout << el.key() << " : " << el.value() << "\n";
    }



    // find an entry
    if (o.contains("foo")) {
        // there is an entry with key "foo"
    }

    // or via find and an iterator
    if (o.find("foo") != o.end()) {
        // there is an entry with key "foo"
    }

    // or simpler using count()
    int foo_present = o.count("foo"); // 1
    int fob_present = o.count("fob"); // 0

    // delete an entry
    o.erase("foo");
}


struct INode
{
    virtual void append_json(nlohmann::json & obj) = 0;
    //TODO: safe ptr
    virtual void add_node(INode & node) = 0;
};


//TODO: use class instead
template <typename T>
struct Node : INode
{
    Node(T val) : val(val) {};
    ~Node() {
        for (auto node : siblings)
        {
            delete node;
        }
    };

    void append_json(nlohmann::json& obj) 
    {
        for (auto node : siblings)
        {
            append_json();
        }
    }

    T val;

    std::vector <INode*> siblings;
};

int main()
{
    std::cout << "Hello World!\n";
    test_json();
}

