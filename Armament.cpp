//
// Created by PC on 06.11.2021.
//

#include "Armament.h"

#include <utility>

namespace Basic {
    std::ostream &operator<<(std::ostream &s, const Armament &vec) {
        //std::getline(std::cin, myName);
        s << "Type of armament: " << vec.type << "\n";
        s << "damage\t" << "speed\t" << "range\t" << "max ammunition\t" << "cur_ammunition\t" << "cost\n \t";
        for (int i = 0; i < vec.count_properties(); i++) {
            s << (vec.properties)[i] << "\t\t";
         }
        s << std::endl;
        return s;
    }

    std::ostream &operator<<(std::ostream &s, const Capitan &capitan){
        s << "Capitan: \n";
        s << "Name: " << capitan.name << "\t";
        s << "Rank: " << capitan.rank << "\n";
        return s;
    }

    Armament::Armament(std::string new_type,double damage, double speed, double range, double max_ammunition, double cost){
        type = std::move(new_type);
        properties[0] = damage;
        properties[1] = speed;
        properties[2] = range;
        properties[3] = max_ammunition;
        properties[4] = max_ammunition;
        properties[5] = cost;
    }

    double Armament::get_property(int i) const{
        double answer = 0;
        if (i < properties_count) answer = properties[i];
        return answer;
    }

    void Armament::change_status() { // с каждым шагом статус стрельбы уменьшается на скорострельность
        if (properties[6] > 0)
            properties[6] -= properties[1];
        if (properties[6] < 0) properties[6] = 0;
    }

    double Armament::shoot(){
        double answer = 0;
        if (properties[6] <= 0 && properties[4] > 0) {
            properties[6] = 1; // status
            properties[4] -= 1; // current ammunition
            answer = properties[0]; // properties[0] = damage;
        }
        return answer;
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