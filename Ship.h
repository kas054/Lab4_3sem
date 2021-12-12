//
// Created by PC on 08.11.2021.
//

#ifndef LAB4_3SEM_SHIP_H
#define LAB4_3SEM_SHIP_H
#include <utility>
#include <map>
#include "Armament.h"

namespace Ships {
    class Ship {
    private:
        std::string ship_type;
        std::string name;
        Basic::Capitan capitan;
        static const int properties_count = 5;
        std::map<std::string, double> prop = {{"max velocity", 0}, {"cur velocity", 0}, {"max life",0}, {"cur life",0}, {"cost", 0}};

    public:
        /**
         * init constructor
         */
        Ship(): ship_type(""), name("") {};
        /**
         * constructor
         * \param new_type new type of ship
         * \throw "hdfjghjdf" dsa
         * \returns name of smth
         */
        Ship(std::string new_type, std::string name,
             double max_velocity, double max_life, double cost);
        /**
         * virtual destructor
         */
        virtual ~Ship() {};

        /**
         * getter of properties map
         * @return map prop
         */

      const std::map<std::string, double> *get_map_prop() const {return &prop;}

        /**
         * getter of ship's property
         * @param i number of property
         * @return property[i]
         */

        double get_property(std::string i) const;

        /**
         * getter of ship's Capitan
         * @return ship's Capitan
         */

        const Basic::Capitan get_capitan() const {return capitan;}

        /**
         * getter of property's count
         * @return property's count
         */

        int count_properties() const { return properties_count; }

        /**
         * getter of type of ship
         * @return type of ship
         */

        std::string get_type() const { return ship_type; }

        /**
         * getter of ship's name
         * @return name of ship
         */

        std::string get_name() const { return name; }

        /**
         * change property of ship
         * @param i number of property
         * @param new_value new value of property
         */

        void change_property(std::string i, int new_value)  { if (prop.find(i) != prop.end()) prop[i] = new_value; }
        /**
         * change type of ship
         * @param new_type new type of ship
         */

        void change_type(std::string new_type) { ship_type = std::move(new_type); }
        /**
         * change Capitan of ship
         * @param new_cap new capitan
         */

        void change_cap(Basic::Capitan new_cap) {capitan = new_cap;}

        /**
         * change name of ship
         * @param new_name new name of ship
         */

        void change_name(std::string new_name) { name = std::move(new_name); }

        /**
         * set current velocity in the available range
         * @param velocity new current velocity
         */

        void set_velocity(double velocity);

        /**
         * get damage
         * @param damage damage received
         * @return current life
         */

        double get_damage(double damage); //{properties[3] -= damage; return properties[3];} //properties[3] - current life

        /**
         * overload << for class Ship
         * @return ostream
         */

        friend std::ostream &operator<<(std::ostream &, const Ship &);
    };

    class Transport_ship: public virtual Ship {
    private:
        static const int size = 3;
        double cargo[size] = {0}; //max_cargo - 0, cur_cargo - 1, coef_decrease - 2; (from 1% to 20%) * max velocity
    public:
        /**
         * init constructor
         */
        Transport_ship(){}

        /**
         * constructor
         * @param new_type type of ship
         * @param name name of ship
         * @param max_velocity maximum velocity
         * @param max_life maximum life
         * @param cost cost of ship
         * @param max_cargo maximum cargo
         * @param coef_decrease coefficient of velocity decrease
         */
        Transport_ship(std::string new_type, std::string name, double max_velocity,
                       double max_life, double cost, double max_cargo, double coef_decrease);

        /**
         * set maximum cargo
         * @param new_value new value of maximum cargo
         */
        void set_max_cargo(double new_value) { cargo[0] = new_value; }

        /**
         * set coefficient of velocity decrease
         * @param new_value new coefficient of velocity decrease
         */
        void set_coef_decrease(double new_value) { cargo[2] = new_value; }

        /**
         * get information about cargo
         * @param i number of property
         * @return max cargo, cur cargo, coefficient of decrease
         */
        double get_info_cargo(int i) const;

        /**
         * get count of properties of cargo
         * @return count of cargo's properties
         */
        int get_size() {return size;}

        /**
         * maximum possible speed at the current loading of the ship
         * @return maximum possible speed at the current loading of the ship
         */
        double possible_speed();

        /**
         * set current speed
         * @param new_speed new speed of ship
         */
        void set_cur_speed(double new_speed);

        /**
         * cet current cargo
         * @param add_cargo added cargo
         */
        void set_cur_cargo(double add_cargo) {if (add_cargo <= cargo[0] - cargo[1]) cargo[1] += add_cargo;}

        /**
         * overload << for class Transport ship
         * @param s ostream
         * @param ship current ship
         * @return ostream
         */
        friend std::ostream &operator<<(std::ostream &s, const Transport_ship &ship);
    };

    class Security_ship: public virtual Ship {
    private:
        Basic::Armament *armaments[4] = {nullptr}; // Расположение орудий: корма - 0, нос - 1, правый борт - 2, левый борт - 3
    public:
        /**
         * init constructor
         */
        Security_ship() {}

        /**
         * destructor
         */
        ~Security_ship();

        /**
         * constructor
         * @param new_type type of ship
         * @param name name of ship
         * @param max_velocity maximum velocity
         * @param max_life maximum life
         * @param cost cost of ship
         */
        Security_ship(std::string new_type, std::string name,double max_velocity, double max_life, double cost): Ship(new_type,name,max_velocity, max_life, cost) {}

        /**
         * add armament to a ship
         * @param new_armament added armament
         * @param place location of weapons on the ship
         * @throw "This place is not free"
         * @throw "No such place"
         */
        void add_armament(Basic::Armament *new_armament, int place);

        /**
         * remove armament from a ship
         * @param place location of weapons on the ship
         * @throw "No such place"
         */
        void remove_armament(int place);

        /**
         * change armament on a ship
         * @param i armament's index in the list
         * @param property changing property of armament
         * @param new_value new value of property
         * @param type new type of armament
         * @throw "Invalid place for armament"
         * @thro "No such place"
         */
        void change_armament(int i, std::string property, double new_value, std::string type = ""); // номер оружия, свойство оружия, новое значение, тип оружия

        /**
         * get information about armament
         * @param i armament's index in the list
         * @return armament
         * @throw "Invalid place for armament"
         */

        Basic::Armament *get_info_armament(int i) const;

        /**
         * change place of armament
         * @param old_place current place of armament
         * @param new_place new place of armament
         * @throw "Invalid place for old place"
         * @throw "Invalid place for new place"
         * @throw "No armament in this place"
         * @throw "This place is not free"
         */
        void change_place(int old_place, int new_place);

        /**
         * make a shoot
         * @param cur_coord current coordinates of this ship
         * @param pirate coordinates of pirates
         * @return total damage from all armaments
         */
        double shoot(Basic::Coordinate cur_coord, Basic::Coordinate pirate); // return total damage

        /**
         * overloaded << for class Security_ship
         * @param s ostream
         * @param ship Security ship
         * @return ostream
         */
        friend std::ostream &operator<<(std::ostream &s, const Security_ship &ship);

        /**
         * change status of armaments
         */
        void change_status();

        /**
         * change place between two armaments
         * @param first first armament
         * @param second second armament
         * @throw "Invalid place for old place"
         * @throw "Invalid place for new place"
         * @throw "No armament in this place"
         */
        void armament_exchange(int first, int second);
    };

    class Military_transport_ship: public Security_ship, public Transport_ship {
    public:
        /**
         * init constructor
         */
        Military_transport_ship() {}
        /**
         * destructor
         */
        ~Military_transport_ship() {}
        /**
         * constructor
         * @param new_type type of ship
         * @param name name of ship
         * @param max_velocity maximum velocity of ship
         * @param max_life maximum life of ship
         * @param cost cost of ship
         * @param max_cargo maximum cargo
         * @param coef_decrease  coefficient of decrease
         */
        Military_transport_ship(std::string new_type, std::string name, double max_velocity,
                                 double max_life, double cost, double max_cargo, double coef_decrease);

        /**
         * overloaded << for class Military_transport_ship
         * @param s ostream
         * @param ship Military_transport_ship
         * @return ostream
         */
        friend std::ostream &operator<<(std::ostream &s, const Military_transport_ship &ship);

    };
}

#endif //LAB4_3SEM_SHIP_H
