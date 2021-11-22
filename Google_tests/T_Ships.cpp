//
// Created by PC on 21.11.2021.
//
#include "gtest/gtest.h"
#include "../Ship.h"
TEST(constructor, defaultConstructor)
{
    Ships::Ship a;
    ASSERT_EQ("", a.get_type());
    ASSERT_EQ("", a.get_name());
    for (int i = 0; i < a.count_properties(); i ++)
        ASSERT_EQ(0, a.get_property(i));

    Ships::Transport_ship b;
    ASSERT_EQ("", b.get_type());
    ASSERT_EQ("", b.get_name());
    for (int i = 0; i < b.count_properties(); i ++)
        ASSERT_EQ(0, b.get_property(i));

    for (int j = 0; j < b.get_size(); j ++){
        ASSERT_EQ(0, b.get_info_cargo(j));
    }

    Ships::Security_ship c;
    ASSERT_EQ("", b.get_type());
    ASSERT_EQ("", b.get_name());
    for (int i = 0; i < b.count_properties(); i ++)
        ASSERT_EQ(0, b.get_property(i));
    for (int i = 0; i < 4; i ++){
        ASSERT_EQ(nullptr, c.get_info_armament(i) );
    }

    Ships::Military_transport_ship d;
    ASSERT_EQ("", b.get_type());
    ASSERT_EQ("", b.get_name());
    for (int i = 0; i < b.count_properties(); i ++)
        ASSERT_EQ(0, b.get_property(i));
    for (int i = 0; i < 4; i ++){
        ASSERT_EQ(nullptr, c.get_info_armament(i) );
    }
    for (int j = 0; j < b.get_size(); j ++){
        ASSERT_EQ(0, b.get_info_cargo(j));
    }
}

TEST(constructor, initConstructor){
    std::string type = "type A";
}

