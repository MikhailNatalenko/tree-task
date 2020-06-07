#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

class INode 
{
public:
    virtual void append_json(nlohmann::json& obj) = 0;
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

    void append_json(nlohmann::json& obj) override
    {
        nlohmann::json j;
        j["data"] = val;

        nlohmann::json arr = nlohmann::json::array();

        for (auto child : children)
        {
            ; child->append_json(arr);
        }
        //TODO: Save const value
        j["arr"] = arr;
        obj.push_back(j);
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
    T val;

    std::vector <std::shared_ptr<INode>> children;
};

