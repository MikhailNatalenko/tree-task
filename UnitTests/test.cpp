#include "pch.h"
#include "../tree_with_various_data_types/crc/Node.h"

TEST(TestCaseName, MirrorTest2) {
  
    treetask::Node<int> a(3);
    a.add_child(std::make_shared<treetask::Node<int>>(2));
    a.add_child(std::make_shared<treetask::Node<std::string>>("hello"));

    nlohmann::json j;
    a.serialise(j);
    std::string s = j.dump();

    nlohmann::json mirror = nlohmann::json::parse(s);
    auto parse_res = treetask::parse_children(mirror);

    if (parse_res.first == treetask::status_t::EMPTY_VAL)
    {
        EXPECT_EQ(1, 0);
    }
    EXPECT_EQ(parse_res.first, treetask::status_t::OK);

    auto mirror_obj = parse_res.second;

    nlohmann::json mirror_json;
    (*mirror_obj).serialise(mirror_json);
    std::string s2 = mirror_json.dump();

    EXPECT_EQ(s, s2);
}


