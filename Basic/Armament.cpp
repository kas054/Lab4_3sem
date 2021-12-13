//
// Created by PC on 06.11.2021.
//

#include "Armament.h"

#include <utility>

namespace Basic {
    std::ostream &operator<<(std::ostream &s, const Armament &vec) {
        //std::getline(std::cin, myName);
        s << "Type of armament: " << vec.type << "\n";
        s << "damage\t" << "speed\t" << "range\t" << "max ammunition\t" << "cur_ammunition\t" << "cost\t" << "status\n";
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

    void Armament::change_property(std::string property, double new_value){
        std::vector<std::string> :: iterator it = prop.begin();
        for (int i = 0; i < prop.size(); i ++){
            if (*it == property) properties[i] = new_value;
            it ++;
        }
    }

    double Armament::get_property(std::string property) const{
        std::vector<std::string> :: const_iterator it = prop.begin();
        double answer = 0;
        for (int i = 0; i < prop.size(); i ++) {
            if (*it == property) {
                answer = properties[i];
                break;
            }
            it++;
        }
        return answer;
    }

    void Armament::change_status() { // с каждым шагом статус стрельбы уменьшается на скорострельность
        double c_status = get_property("status"), c_rate_f =  get_property("rate of fire"), new_status;
        if ( c_status > 0){
            new_status = c_status - c_rate_f;
            change_property("status", new_status);
        }
        if ( get_property("status") < 0) change_property("status", 0);
    }

    double Armament::shoot(){
        double answer = 0, c_ammunition = get_property("cur ammunition");
        if ( get_property("status") <= 0 && c_ammunition > 0){
            change_property("status", 1);
            change_property("cur ammunition",c_ammunition - 1);
            answer = get_property("damage");
        }
        return answer;
    }

    std::istream & operator >> (std::istream &in, Armament &armament)
    {
        std::vector<std::string> :: iterator it = armament.prop.begin();
        std::string type;
        double property;
        in >> type;
        armament.change_type(type);
        for (int i = 0; i < armament.count_properties(); i ++) {
            in >> property;
            armament.change_property(*it, property);
            it ++;
        }
        return in;
    }

    std::ostream &operator<<(std::ostream &s, const Coordinate &coordinate){
        s << "(" << coordinate.x << ", " << coordinate.y << ")\n";
        return s;
    }
}