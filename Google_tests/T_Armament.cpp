//
// Created by PC on 21.11.2021.
//

#include "gtest/gtest.h"
#include "../Basic/Armament.h"

TEST(armament, defaultConstructor)
{
    Basic::Armament a;
    ASSERT_EQ("", a.get_type());
   /* for (int i = 0; i < a.count_properties(); i ++)
        ASSERT_EQ(0, a.get_property(i));*/
}

TEST(armament, initConstructors){
    std::string new_type = "rocket";
    double damage = 2, rate = 0.3, range = 2, max_ammunition = 20, cost = 9000;
    double error = 0.01;
    Basic::Armament a(new_type, damage, rate, range, max_ammunition, cost);

    ASSERT_EQ("rocket", a.get_type());
    ASSERT_EQ(2, a.get_property("damage")); // damage
    ASSERT_NEAR(0.3,a.get_property("rate of fire") , error); // rate
    ASSERT_EQ(2, a.get_property("range")); // range
    ASSERT_EQ(20, a.get_property("max ammunition")); // max ammunition
    ASSERT_EQ(20, a.get_property("cur ammunition")); // current ammunition
    ASSERT_EQ(9000, a.get_property("cost")); // cost
}

TEST(armament, setters)
{
   /* Basic::Armament a;
    double value = 100, error = 0.1;
    std::string new_type = "rocket";

    for (int i = -2; i < a.count_properties() + 3; i ++){
        a.change_property(i, value);
        if (0 < i && i < a.count_properties())
            ASSERT_NEAR(100,a.get_property(i) , error);
    }
    a.change_type(new_type);
    ASSERT_EQ(new_type, a.get_type());*/
}

TEST(armament, change_status){
    std::string new_type = "rocket";
    double damage = 2, speed = 0.3, range = 2, max_ammunition = 20, cost = 9000;
    double error = 0.01;
    Basic::Armament a(new_type, damage, speed, range, max_ammunition, cost);

    for (int i = 0; i < 25; i ++ ) {
        if (i % 4 == 0) ASSERT_EQ(0, a.get_property("status"));
        else if (i % 4 == 1) ASSERT_EQ(0.7, a.get_property("status"));
        else if (i % 4 == 2) ASSERT_NEAR(0.4,a.get_property("status") , error);
        else if (i % 4 == 3) ASSERT_NEAR(0.1,a.get_property("status") , error);
        a.shoot();
        if (i % 4 == 0) ASSERT_EQ(1, a.get_property("status"));
        a.change_status();
    }
}

TEST(armament, shoot){
    std::string new_type = "rocket";
    double damage = 2, speed = 0.5, range = 2, max_ammunition = 20, cost = 9000;
    double error = 0.01;
    Basic::Armament a(new_type, damage, speed, range, max_ammunition, cost);

    for ( int i = 0; i < 3; i ++){
        if (i % 3 == 0){
            ASSERT_EQ(0, a.get_property("status"));
            ASSERT_EQ(a.get_property("damage"), a.shoot());
            ASSERT_EQ(1, a.get_property("status"));
        }
        else if (i % 3 == 1){
            ASSERT_EQ(0.5, a.get_property("status"));
            ASSERT_EQ(0, a.shoot());
        }
        else{
            ASSERT_EQ(0, a.get_property("status"));
            ASSERT_EQ(a.get_property("damage"), a.shoot());
        }
        a.change_status();
    }
}