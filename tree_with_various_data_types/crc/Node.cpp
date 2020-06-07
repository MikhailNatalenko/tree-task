#include "Node.h"

using namespace treetask;

std::pair<status_t, std::shared_ptr<INode>> treetask::parse_children(nlohmann::json& mirror)
{
    std::cout << __func__ << mirror << std::endl;
    if (!mirror.contains("arr"))
        return { status_t::BAD_TOKEN , nullptr };

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
        auto child = treetask::parse_children(arr);

        if (child.first == status_t::OK)
        {
            (*current).add_child(child.second);
        }
    }
    return { status_t::OK, current };
}