#pragma once

#include <nlohmann/json.hpp>
#include <vector>

class INode 
{

};

template <typename T>
class Node :
	public INode
{
    Node(T val) : val(val) {};
    ~Node() {
        for (auto child : children)
        {
            delete child;
        }
    };

    void append_json(nlohmann::json& obj)
    {
        nlohmann::json j;
        j["data"] = val;

        nlohmann::json arr;

        for (auto child : children)
        {

        }
    }

    T val;

    std::vector <INode*> children;
};

