#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>



class INode 
{
public:
    virtual void append_json(nlohmann::json& obj, bool starter) = 0;
    virtual ~INode() {
    };

};

template <typename T>
class Node :
	public INode
{
public:
    Node(T val) : val(val) {};
    Node(const Node<T> & obj) : val(obj.val), children(obj.children){};
    //TODO: Test it
    Node(Node<T>&& obj) : val(obj.val), children(std::move(obj.children)) {};

    virtual ~Node() {};

    void serialise(nlohmann::json& obj)
    {
        append_json(obj, true);
    }

    void append_json(nlohmann::json& obj, bool starter = false) override
    {

        nlohmann::json arr = nlohmann::json::array();

        for (auto child : children)
        {
            ; child->append_json(arr, false);
        }
        //TODO: Save const value

        if (!starter)
        {
            nlohmann::json j;   
            j["arr"] = arr;
            j["data"] = val;
            obj.push_back(j);
        }
        else 
        {
            obj["arr"] = arr;
            obj["data"] = val;
        }
    }


    void parse_children(nlohmann::json & obj)
    {
        for (auto& node : obj.items())
        {
            //TODO EXceptions
            std::shared_ptr<INode> value (new Node(node["data"]));
            if (node.key() == "arr")
            {

            }
        }
    }

    void add_child(std::shared_ptr<INode> child)
    {
        children.push_back(child);
    }

    T val;

    std::vector <std::shared_ptr<INode>> children;
};

using NodeString = Node<std::string>;
using NodeInt = Node<int>;
using NodeFloat = Node<float>;