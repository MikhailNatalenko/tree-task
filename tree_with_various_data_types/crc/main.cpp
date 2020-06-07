#include <iostream>
#include <nlohmann/json.hpp>
#include "Node.h"

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

void test_memleaks()
{
    for (int i = 0; i < 10000; i++)
    {
        Node<int> a(3);
        a.children.push_back(std::make_shared<Node<int>>(2));
        a.children.push_back(std::make_shared<Node<float>>(3.1415));    
    }
}

int main()
{
    test_memleaks();
    Node<int> a(3);
    Node<int> b(2);
    Node<float> c(3.1415);
    a.children.push_back(std::make_shared<Node<int>>(2));
    a.children.push_back(std::make_shared<Node<float>>(3.1415));

    nlohmann::json j;
    a.append_json(j);
    std::string s = j.dump();


    nlohmann::json mirror = nlohmann::json::parse(s);


    std::cout << mirror;

}

