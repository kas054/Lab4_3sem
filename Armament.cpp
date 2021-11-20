//
// Created by PC on 15.11.2021.
//

#include "Armament.h"

#include <utility>

namespace Basic {
    std::ostream &operator<<(std::ostream &s, const Armament &vec) {
        //std::getline(std::cin, myName);
        s << "Type of armament: " << vec.type << "\n";
        s << "damage\t" << "speed\t" << "range\t" << "max ammunition\t" << "cur_ammunition\t" << "cost\t\n";
        for (int i = 0; i < 6; i++) {
            s << (vec.properties)[i] << "\t\t";
         }
        s << std::endl;
        return s;
    }

    Armament::Armament(std::string new_type,double damage, double speed, double range, double max_ammunition, double cost, double fire_rate){
        type = std::move(new_type);
        properties[0] = damage;
        properties[1] = speed;
        properties[2] = range;
        properties[3] = max_ammunition;
        properties[5] = cost;
        properties[7] = fire_rate;
    }

    double Armament::get_property(int i) const{
        double answer = 0;
        if (i < properties_count - 1) answer = properties[i];
        return answer;
    }

    double Armament::shoot(){
        properties[6] = 1; // status
        properties[4] -= 1; // current ammunition
        return properties[0]; // properties[0] = damage;
    }


    std::istream & operator >> (std::istream &in, Armament &armament)
    {
        std::string type;
        double property;
        in >> type;
        armament.change_type(type);
        for (int i = 0; i < armament.count_properties() - 1; i ++) {
            in >> property;
            armament.change_property(i, property);
        }
        return in;
    }

    std::ostream &operator<<(std::ostream &s, const Coordinate &coordinate){
        s << "(" << coordinate.x << ", " << coordinate.y << ")\n";
        return s;
    }

}