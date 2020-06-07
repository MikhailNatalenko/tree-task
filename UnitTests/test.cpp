#include "pch.h"
#include "../tree_with_various_data_types/crc/Node.h"

TEST(TestCaseName, MirrorTest) {
  
    Node<int> a(3);
    a.add_child(std::make_shared<Node<int>>(2));
    a.add_child(std::make_shared<Node<float>>(3.1415));

    nlohmann::json j;
    a.append_json(j);
    std::string s = j.dump();

            
    nlohmann::json mirror = nlohmann::json::parse(s);
    
    EXPECT_EQ(mirror[0]["data"], 3);
    EXPECT_EQ(mirror[0]["arr"][0]["data"], 2);
}


