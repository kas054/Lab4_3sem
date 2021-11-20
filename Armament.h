//
// Created by PC on 15.11.2021.
//

#ifndef LAB4_3SEM_ARMAMENT_H
#define LAB4_3SEM_ARMAMENT_H
#include <iostream>
#include <string>
namespace Basic {
    class Armament {
    private:
        std::string type = "";
        static const int properties_count = 8;
        double properties[properties_count] = {0}; //damage - 0, speed - 1, range - 2, max_ammunition - 3, cur_ammunition - 4, cost - 5, status - 6, rate of fire - 7
    public:
        Armament() {};
        Armament(std::string new_type,double damage, double speed,
                 double range, double max_ammunition, double cost, double fire_rate);

        double get_property(int i) const;

        int count_properties() const { return properties_count; }

        std::string get_type() const { return type; }

        void change_property(int i, double new_value) { if (i < properties_count - 1) properties[i] = new_value; }

        void change_type(std::string new_type) { type = new_type; }

        double shoot();

        friend std::ostream &operator<<(std::ostream &, const Armament &);

        void change_status() { if (properties[6] > 0) properties[6] -= properties[7]; } // с каждым шагом статус стрельбы уменьшается на скорострельность

        friend std::istream &operator>>(std::istream &, Armament &);
    };

    struct Coordinate{
        double x;
        double y;
    };

    struct Capitan{
        std::string name;
        std::string rank;
    };

    std::ostream &operator<<(std::ostream &, const Capitan &);
    std::ostream &operator<<(std::ostream &, const Coordinate &);
}

#endif //LAB4_3SEM_ARMAMENT_H
