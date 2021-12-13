//
// Created by PC on 21.11.2021.
//
#include "gtest/gtest.h"
#include "../Ships/Ship.h"
#define EXPECT_NO_THROW(statement) \
  GTEST_TEST_NO_THROW_(statement, GTEST_NONFATAL_FAILURE_)

TEST(constructor, defaultConstructor)
{
    std::map<std::string, double> :: const_iterator it;
    const std::map<std::string, double> *mp;
    Ships::Ship a;
    ASSERT_EQ("", a.get_type());
    ASSERT_EQ("", a.get_name());
    mp = a.get_map_prop();
    for (it = mp->begin(); it != mp->end(); it ++){
        ASSERT_EQ(0, a.get_property(it->first));
    }
    //for (int i = 0; i < a.count_properties(); i ++)
       // ASSERT_EQ(0, a.get_property(i));

    Ships::Transport_ship b;
    ASSERT_EQ("", b.get_type());
    ASSERT_EQ("", b.get_name());
    mp = b.get_map_prop();
    for (it = mp->begin(); it != mp->end(); it ++){
        ASSERT_EQ(0, b.get_property(it->first));

    }

    for (int j = 0; j < b.get_size(); j ++){
        ASSERT_EQ(0, b.get_info_cargo(j));
    }

    Ships::Security_ship c;
    ASSERT_EQ("", b.get_type());
    ASSERT_EQ("", b.get_name());
    mp = c.get_map_prop();
    for (it = mp->begin(); it != mp->end(); it ++){
        ASSERT_EQ(0, c.get_property(it->first));
    }
   // for (int i = 0; i < b.count_properties(); i ++)
      //  ASSERT_EQ(0, b.get_property(i));
    for (int i = 0; i < 4; i ++){
        ASSERT_EQ(nullptr, c.get_info_armament(i) );
    }

    Ships::Military_transport_ship d;
    ASSERT_EQ("", b.get_type());
    ASSERT_EQ("", b.get_name());
    mp = d.get_map_prop();
    for (it = mp->begin(); it != mp->end(); it ++){
        ASSERT_EQ(0, d.get_property(it->first));
    }
    //for (int i = 0; i < b.count_properties(); i ++)
        //ASSERT_EQ(0, b.get_property(i));
    for (int i = 0; i < 4; i ++){
        ASSERT_EQ(nullptr, c.get_info_armament(i) );
    }
    for (int j = 0; j < b.get_size(); j ++){
        ASSERT_EQ(0, b.get_info_cargo(j));
    }
}

TEST(constructor, initConstructor){
    std::string st = "type A";
    double number = 100;

    std::map<std::string, double> :: const_iterator it;
    const std::map<std::string, double> *mp;

    Ships::Ship a = Ships::Ship(st, st, number, number, number);
    Ships::Transport_ship b = Ships::Transport_ship(st, st, number, number, number, number, number);
    Ships::Military_transport_ship d = Ships::Military_transport_ship(st, st, number, number, number, number, number);
    Ships::Security_ship c = Ships::Security_ship(st, st, number, number, number);

    //Ships::Ship a;
    ASSERT_EQ(st, a.get_type());
    ASSERT_EQ(st, a.get_name());
    mp = a.get_map_prop();
    for (it = mp->begin(); it != mp->end(); it ++){
        if (it->first == "max velocity" || it->first == "max life" || it->first == "cost")
            ASSERT_EQ(number, a.get_property(it->first));
        else
            ASSERT_EQ(0, a.get_property(it->first));
    }

   // Ships::Transport_ship b;
    ASSERT_EQ(st, b.get_type());
    ASSERT_EQ(st, b.get_name());
    mp = b.get_map_prop();
    for (it = mp->begin(); it != mp->end(); it ++){
        if (it->first == "max velocity" || it->first == "max life" || it->first == "cost")
            ASSERT_EQ(number, b.get_property(it->first));
        else
            ASSERT_EQ(0, b.get_property(it->first));
    }

    for (int j = 0; j < b.get_size(); j ++){
        if (j == 1) ASSERT_EQ(0, b.get_info_cargo(j));
        else ASSERT_EQ(number, b.get_info_cargo(j));
    }

    //Ships::Security_ship c;
    ASSERT_EQ(st, b.get_type());
    ASSERT_EQ(st, b.get_name());
    mp = c.get_map_prop();
    for (it = mp->begin(); it != mp->end(); it ++){
        if (it->first == "max velocity" || it->first == "max life" || it->first == "cost")
            ASSERT_EQ(number, c.get_property(it->first));
        else
            ASSERT_EQ(0, c.get_property(it->first));
    }
    for (int i = 0; i < 4; i ++){
        ASSERT_EQ(nullptr, c.get_info_armament(i) );
    }

    //Ships::Military_transport_ship d;
    ASSERT_EQ(st, d.get_type());
    ASSERT_EQ(st, d.get_name());
    mp = d.get_map_prop();
    for (it = mp->begin(); it != mp->end(); it ++){
        if (it->first == "max velocity" || it->first == "max life" || it->first == "cost")
            ASSERT_EQ(number, d.get_property(it->first));
        else
            ASSERT_EQ(0, d.get_property(it->first));
    }
    for (int i = 0; i < 4; i ++){
        ASSERT_EQ(nullptr, d.get_info_armament(i) );
    }
    for (int j = 0; j < d.get_size(); j ++){
        if (j == 1) ASSERT_EQ(0, d.get_info_cargo(j));
        else ASSERT_EQ(number, d.get_info_cargo(j));
    }
}

TEST(method, setters){
    std::string st = "type A", st2 = "type B";
    double num1 = 100, num2 = 9;
    std::map<std::string, double> :: const_iterator it;
    const std::map<std::string, double> *mp;

    Ships::Military_transport_ship d = Ships::Military_transport_ship(st, st, num1, num1, num1, num1, num1);

    mp = d.get_map_prop();

    for (it = mp->begin(); it != mp->end(); it ++){
        d.change_property(it->first, num2);
    }

    for (it = mp->begin(); it != mp->end(); it ++){
        ASSERT_EQ(num2, d.get_property(it->first));
    }
    /*for (int i = -2; i < d.count_properties() + 3; i ++)
        d.change_property(i, num2);
    for (int i = -2; i < d.count_properties() + 3; i ++)
        if (0 > i || i > d.count_properties() - 1)
           ASSERT_EQ(0, d.get_property(i));
        else ASSERT_EQ(num2, d.get_property(i)); */

    d.set_coef_decrease(num2);
    d.set_max_cargo(num2);
    d.set_cur_speed(num2);
    d.set_cur_cargo(num2);
    for (int j = 0; j < d.get_size(); j ++){
        ASSERT_EQ(num2, d.get_info_cargo(j));
    }
    d.set_cur_cargo(num2);
    ASSERT_EQ(num2, d.get_info_cargo(1));
}

TEST(method, get_damage){
    std::string st = "type A";
    double num1 = 100, damage = 80;

    Ships::Military_transport_ship d = Ships::Military_transport_ship(st, st, num1, 3 * num1, num1, num1, num1);

    while(d.get_property("cur life") > 0)
        ASSERT_EQ(d.get_property("cur life") - damage, d.get_damage(damage));
}

TEST(method, add_armament){
    std::string st = "type A";
    double num1 = 100, damage = 80;

    Ships::Military_transport_ship d = Ships::Military_transport_ship(st, st, num1, 3 * num1, num1, num1, num1);

    for (int i = 0 ; i < 4; i ++){
        Basic::Armament *a = new Basic::Armament;
        d.add_armament(a, i);
    }

    for (int i = 0; i < 4; i ++){
        Basic::Armament *a = new Basic::Armament;
        ASSERT_THROW( d.add_armament(a, i),const char *);
        delete a;
    }
}

TEST(method, change_armament){
    std::string st = "type A";
    double num1 = 100;

    Ships::Military_transport_ship d = Ships::Military_transport_ship(st, st, num1, 3 * num1, num1, num1, num1);
    Basic::Armament *a = new Basic::Armament;

    d.add_armament(a, 0);

    ASSERT_THROW( d.change_armament(10, "damage", 99),const char *); // invalid place
    ASSERT_THROW( d.change_armament(1, "damage", 99),const char *); // no such armament

    a = d.get_info_armament(0);
    EXPECT_NO_THROW( d.change_armament( 0, "damage", 100)); // change damage
    ASSERT_EQ(100, a->get_property("damage")); // get info about damage

    EXPECT_NO_THROW( d.change_armament( 0, "damage", 100, "new type")); // change type of armament
    ASSERT_EQ("new type", a->get_type()); // get info about type
}

TEST(method, change_place){
    std::string st = "type A";
    double num1 = 100;

    Ships::Military_transport_ship d = Ships::Military_transport_ship(st, st, num1, 3 * num1, num1, num1, num1);
    Basic::Armament *a = new Basic::Armament;
    Basic::Armament *b = new Basic::Armament;

    d.add_armament(a, 0);
    ASSERT_THROW( d.change_place(10, 0),std::runtime_error); // invalid place for old
    ASSERT_THROW( d.change_place(0, 10),std::runtime_error); // invalid place for new
    ASSERT_THROW( d.change_place(1, 0),std::runtime_error); // no such armament

    EXPECT_NO_THROW( d.change_place( 0, 1)); // change place
    EXPECT_NO_THROW( d.change_armament( 1, "damage", 100)); // change parameters of armament[new_place]

    d.add_armament(b, 0);
    ASSERT_THROW( d.change_place(1, 0),std::runtime_error); // new place is not free
}

TEST(method, armament_exchange){
    std::string st = "type A";
    double num1 = 100;
    Basic::Armament *a = new Basic::Armament;
    Basic::Armament *b = new Basic::Armament;

    Ships::Military_transport_ship d = Ships::Military_transport_ship(st, st, num1, 3 * num1, num1, num1, num1);


    d.add_armament(a, 0);
    d.add_armament(b, 1);

    ASSERT_THROW( d.armament_exchange(10, 0),std::runtime_error); // invalid place for first
    ASSERT_THROW( d.armament_exchange(0, 10),std::runtime_error); // invalid place for second

    ASSERT_THROW( d.armament_exchange(2, 0),std::runtime_error); // no such first
    ASSERT_THROW( d.armament_exchange(0, 2),std::runtime_error); // no such second

    EXPECT_NO_THROW( d.armament_exchange(0, 1));
}

TEST(methods, shoot){
    // for armament
    std::string new_type = "rocket";
    double damage = 2, rate = 0.3, range = 2, max_ammunition = 20, cost = 9000;
    Basic::Armament armament(new_type, damage, rate, range, max_ammunition, cost);
    // for ship
    std::string st = "type A";
    double num1 = 100;
    Basic::Armament *a = new Basic::Armament;
    Basic::Armament *b = new Basic::Armament;
    *a = armament;
    *b = armament;
    Ships::Military_transport_ship d = Ships::Military_transport_ship(st, st, num1, 3 * num1, num1, num1, num1);
    d.add_armament(a, 0);
    d.add_armament(b, 1);
    // coordinates
    typedef Basic::Coordinate place;
    place cur_coord = {10,10};

    // Корабль может попасть по клеткам (8, 10) и (12, 10) 20 раз на каждый 4 выстрел

    // Точка выстрела недоступна
    ASSERT_EQ(0, d.shoot(cur_coord, place {0,0}));
    ASSERT_EQ(0, d.shoot(cur_coord, place {10,11})); // нет оружия на левом борте
    ASSERT_EQ(0, d.shoot(cur_coord, place {10,9})); // нет оружия на правом борте
    ASSERT_EQ(0, d.shoot(cur_coord, place {7,10})); // range = 2

    for (int i = 0; i < 90; i ++ ) {
        if (i < 80) {
            if (i % 4 == 0)
                ASSERT_EQ(((d.get_info_armament(0))->get_property("damage")), d.shoot(cur_coord, place{8, 10})); //
            else
                ASSERT_EQ(0, d.shoot(cur_coord, place{8, 10}));
            d.shoot(cur_coord, place{8, 10});
            if (i % 4 == 0) ASSERT_EQ(0, d.shoot(cur_coord, place{8, 10}));
            d.change_status();
        }
        else ASSERT_EQ(0, d.shoot(cur_coord, place{8, 10})); // current ammunition = 0
    }
}