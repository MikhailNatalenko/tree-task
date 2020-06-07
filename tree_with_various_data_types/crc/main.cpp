#include <iostream>
#include <nlohmann/json.hpp>
#include "Node.h"


void test_memleaks()
{
    for (int i = 0; i < 10000; i++)
    {
        Node<int> a(3);
        auto b = std::make_shared <NodeString>("lake");
        auto c = std::make_shared <NodeFloat>(0.8);

        a.add_child(std::make_shared<NodeInt>(2));
        a.add_child(std::make_shared<NodeFloat>(3.1415));

        b->add_child(std::make_shared<NodeString>("Agidel"));
        b->add_child(std::make_shared<NodeInt>(8));
        b->add_child(std::make_shared<NodeFloat>(5.0));

        c->add_child(std::make_shared<NodeFloat>(0.2));
        c->add_child(std::make_shared<NodeInt>(3));
        b->add_child(c);
        a.add_child(b);
        nlohmann::json j;
        a.serialise(j);
        //std::string s = j.dump();
    }
}


int main()
{
    //test_memleaks();
    std::cout << "Hello " << std::endl;
    Node<int> a(3);
    auto b = std::make_shared <NodeString>("lake");
    auto c = std::make_shared <NodeFloat>(0.8);

    a.add_child(std::make_shared<NodeInt>(2));
    a.add_child(std::make_shared<NodeFloat>(3.1415));

    b->add_child(std::make_shared<NodeString>("Agidel"));
    b->add_child(std::make_shared<NodeInt>(8));
    b->add_child(std::make_shared<NodeFloat>(5.0));

    c->add_child(std::make_shared<NodeFloat>(0.2));
    c->add_child(std::make_shared<NodeInt>(3));
    b->add_child(c);
    a.add_child(b);
    nlohmann::json j;
    a.serialise(j);
    std::string s = j.dump();

    std::cout << s << std::endl;

    nlohmann::json mirror = nlohmann::json::parse(s);



}

