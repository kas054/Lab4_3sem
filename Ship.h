//
// Created by PC on 08.11.2021.
//

#ifndef LAB4_3SEM_SHIP_H
#define LAB4_3SEM_SHIP_H
#include <utility>

#include "Armament.h"
namespace Ships {
    class Ship {
    private:
        std::string ship_type = "";
        std::string name = "";
        struct Basic::Capitan capitan = {"", ""};
        static const int properties_count = 5;
        double properties[properties_count] = {0}; // max_velocity - 0, cur_velocity - 1, max_life - 2, cur_life - 3, cost - 4
    public:
        Ship() {};
        Ship(std::string new_type, std::string name,
             double max_velocity, double max_life, double cost);

        double get_property(int i) const;

        int count_properties() const { return properties_count; }

        std::string get_type() const { return ship_type; }

        std::string get_name() const { return name; }

        void change_property(int i, int new_value)  { if (i < properties_count - 1 && i > 0) properties[i] = new_value; }

        void change_type(std::string new_type) { ship_type = std::move(new_type); }

        void change_name(std::string new_name) { name = std::move(new_name); }

        void set_velocity(double velocity);

        void get_damage(double damage) {properties[3] -= damage;} //properties[3] - current life

        void print_properties() const;

    };

    class Transport_ship: public virtual Ship {
    private:
        static const int size = 3;
        double cargo[size] = {0}; //max_cargo - 0, cur_cargo - 1, coef_decrease - 2; (from 1% to 20%)
    public:
        Transport_ship(){}
        Transport_ship(std::string new_type, std::string name, double max_velocity,
                       double max_life, double cost, double max_cargo, double coef_decrease);

        void set_max_cargo(double new_value) { cargo[0] = new_value; }

        void set_coef_decrease(double new_value) { cargo[2] = new_value; }

        double get_info_cargo(int i) const;

        double possible_speed();

        void set_cur_speed(double new_speed);

        void set_cur_cargo(double add_cargo) {if (add_cargo <= cargo[0] - cargo[1]) cargo[1] += add_cargo;}

       friend std::ostream &operator<<(std::ostream &s, const Transport_ship &ship);
    };

    class Security_ship: public virtual Ship {
    private:
        Basic::Armament *armaments[4] = {nullptr}; // Расположение орудий: корма - 0, нос - 1, правый борт - 2, левый борт - 3
    public:
        Security_ship() {}

        Security_ship(std::string new_type, std::string name,double max_velocity, double max_life, double cost): Ship(new_type,name,max_velocity, max_life, cost) {}

        void add_armament(Basic::Armament &new_armament, int place);

        void change_armament(int i, int property, double new_value, std::string type = ""); // номер оружия, свойство оружия, новое значение, тип оружия

        Basic::Armament *get_info_armament(int i) const;

        void change_place(int old_place, int new_place);

        double shoot(Basic::Coordinate cur_coord, Basic::Coordinate pirate); // return total damage

        friend std::ostream &operator<<(std::ostream &s, const Security_ship &ship);

        void change_status();

        void armament_exchange(int first, int second);
    };

    class Military_transport_ship: public Security_ship, public Transport_ship {
    public:
        Military_transport_ship() {}
        Military_transport_ship(std::string new_type, std::string name, double max_velocity,
                                 double max_life, double cost, double max_cargo, double coef_decrease);

        friend std::ostream &operator<<(std::ostream &s, const Military_transport_ship &ship);

    };
}

#endif //LAB4_3SEM_SHIP_H
