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


enum class status_t {
    OK,
    BAD_TOKEN
};


std::pair<status_t, std::shared_ptr<INode>> parse_children(nlohmann::json & mirror)
{
    std::cout << __func__ << mirror <<std::endl;
    if (!mirror.contains("arr"))
        return { status_t::BAD_TOKEN , nullptr};

    if (!mirror.contains("data"))
        return { status_t::BAD_TOKEN , nullptr };

    nlohmann::json val = mirror["data"];
    std::cout << "VAL: " << val << std::endl;
    std::shared_ptr<INode> current;

    switch (val.type())
    {
    case nlohmann::detail::value_t::string:
        current = std::make_shared<NodeString>(val.get<std::string>());
        ;
        break;

    case nlohmann::detail::value_t::number_unsigned:
    case nlohmann::detail::value_t::number_integer:
        current = std::make_shared<NodeInt>(val.get<int>());
        break;

    case nlohmann::detail::value_t::number_float:
        current = std::make_shared<NodeFloat>(val.get<float>());
        break;

    default:
        std::cout << "Something wrong was parsed" << std::endl;
        return { status_t::BAD_TOKEN , nullptr };
    }

    auto get_arr = mirror.at("arr");

    for (auto& node : get_arr.items())
    {
        //nlohmann::json val = node.value();
        //std::cout << " - :" << val.type() << " || "<< val << std::endl;
        

        nlohmann::json arr = node.value();
        auto child = parse_children(arr);

        if (child.first == status_t::OK)
        {
            (*current).add_child(child.second);
        }
    }
    return { status_t::OK, current };
}


int main()
{
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

    auto parse_res = parse_children(mirror);
    if (parse_res.first == status_t::OK)
    {
        auto mirror_obj = parse_res.second;

        std::cout << "parse_res: " << std::endl << std::endl;
        nlohmann::json mirror_json;
        (*mirror_obj).serialise(mirror_json);
        std::string s2 = mirror_json.dump();
        std::cout << s2 << std::endl;
    }

}

