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
    virtual ~Node() {
        for (INode* child : children)
        {
            //delete child;
        }
    };

    void append_json(nlohmann::json& obj) override
    {
        nlohmann::json j;
        j["data"] = val;

        nlohmann::json arr = nlohmann::json::array();

        for (INode* child : children)
        {
            child->append_json(arr);
        }
        j["arr"] = arr;
        obj.push_back(j);
    }

    T val;

    std::vector <INode*> children;
};

