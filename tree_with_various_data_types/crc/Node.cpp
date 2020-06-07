#include "Node.h"

using namespace treetask;

std::pair<status_t, std::shared_ptr<INode>> treetask::parse_children(nlohmann::json& obj)
{
    std::cout << __func__ << obj << std::endl;

    if (!obj.contains("arr"))
        return { status_t::EMPTY_VAL , nullptr };

    if (!obj.contains("data"))
        return { status_t::EMPTY_VAL , nullptr };

    nlohmann::json val = obj["data"];
    std::cout << "VAL: " << val << std::endl;
    std::shared_ptr<INode> current;

    switch (val.type())
    {
    case nlohmann::detail::value_t::string:
        current = std::make_shared<Node<std::string>>(val.get<std::string>());
        ;
        break;

    case nlohmann::detail::value_t::number_unsigned:
    case nlohmann::detail::value_t::number_integer:
        current = std::make_shared<Node<int>>(val.get<int>());
        break;

    case nlohmann::detail::value_t::number_float:
        current = std::make_shared<Node<float>>(val.get<float>());
        break;

    default:
        std::cout << "Something wrong was parsed" << std::endl;
        return { status_t::BAD_TOKEN , nullptr };
    }

    auto get_arr = obj.at("arr");

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
        if (child.first == status_t::BAD_TOKEN)
        {
            return { status_t::BAD_TOKEN, current };
        }
    }
    return { status_t::OK, current };
}