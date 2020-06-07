#include <iostream>
#include <nlohmann/json.hpp>
#include "Node.h"


void test_memleaks()
{
    for (int i = 0; i < 10000; i++)
    {
        treetask::Node<int> a(3);
        auto b = std::make_shared <treetask::NodeString>("lake");
        auto c = std::make_shared <treetask::NodeFloat>(0.8);

        a.add_child(std::make_shared<treetask::NodeInt>(2));
        a.add_child(std::make_shared<treetask::NodeFloat>(3.1415));

        b->add_child(std::make_shared<treetask::NodeString>("Agidel"));
        b->add_child(std::make_shared<treetask::NodeInt>(8));
        b->add_child(std::make_shared<treetask::NodeFloat>(5.0));

        c->add_child(std::make_shared<treetask::NodeFloat>(0.2));
        c->add_child(std::make_shared<treetask::NodeInt>(3));
        b->add_child(c);
        a.add_child(b);
        nlohmann::json j;
        a.serialise(j);
        //std::string s = j.dump();
    }
}







int main()
{
    std::cout << "Hello " << std::endl;
    treetask::Node<int> a(3);
    auto b = std::make_shared <treetask::NodeString>("lake");
    auto c = std::make_shared <treetask::NodeFloat>(0.8);

    a.add_child(std::make_shared<treetask::NodeInt>(2));
    a.add_child(std::make_shared<treetask::NodeFloat>(3.1415));

    b->add_child(std::make_shared<treetask::NodeString>("Agidel"));
    b->add_child(std::make_shared<treetask::NodeInt>(8));
    b->add_child(std::make_shared<treetask::NodeFloat>(5.0));

    c->add_child(std::make_shared<treetask::NodeFloat>(0.2));
    c->add_child(std::make_shared<treetask::NodeInt>(3));
    b->add_child(c);
    a.add_child(b);
    nlohmann::json j;
    a.serialise(j);
    std::string s = j.dump();

    std::cout << s << std::endl;

    nlohmann::json mirror = nlohmann::json::parse(s);

    auto parse_res = treetask::parse_children(mirror);
    if (parse_res.first == treetask::status_t::OK)
    {
        auto mirror_obj = parse_res.second;

        std::cout << "parse_res: " << std::endl << std::endl;
        nlohmann::json mirror_json;
        (*mirror_obj).serialise(mirror_json);
        std::string s2 = mirror_json.dump();
        std::cout << s2 << std::endl;
    }

}

