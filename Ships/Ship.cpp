//
// Created by PC on 08.11.2021.
//
#include "Ship.h"
#include <utility>
#include <cmath>
namespace Ships{
    using namespace Basic;
    Ship::Ship(std::string new_type, std::string name, double max_velocity, double max_life, double cost) {
        ship_type = std::move(new_type);
        this->name = std::move(name);
        prop["max velocity"] = max_velocity;
        prop["max life"] = max_life;
        prop["cost"] = cost;
    }

    void Ship::set_velocity(double velocity){
        double m_velocity = prop["max velocity"];
        if (velocity > m_velocity) velocity = m_velocity;
        else if (velocity < 0) velocity = 0;
        prop["cur velocity"] = velocity;
    }

    double Ship::get_property(std::string i) const {
        double answer;
        std::map<std::string, double> :: const_iterator it = prop.find(i);
        if (it == prop.end()) answer = 0;
        else answer = it->second;
        return answer;
    }

    double Ship::get_damage(double damage){
        double c_life = get_property("cur life") - damage;
        change_property("cur life", c_life);
        return get_property("cur life");
    }

    std::ostream &operator<<(std::ostream &s, const Ships::Ship &ship){
        std::map<std::string, double> :: const_iterator it;
        s << "\t\t Name of ship: " << ship.get_name() << "\n";
        s << "\t\t Type of ship: " << ship.get_type() << "\n";
        s << "\t\t Capitan: " << ship.capitan << "\n";
        for (it = ship.prop.begin(); it != ship.prop.end(); it ++){
            s << it->first << ": " << it->second << "\n";
        }
        s << std::endl;
        return s;
    }

    Transport_ship::Transport_ship( std::string new_type, std::string name, double max_velocity,
    double max_life, double cost, double max_cargo, double coef_decrease): Ship::Ship(new_type,name,max_velocity, max_life, cost){
        cargo[0] = max_cargo;
        cargo[2] = coef_decrease;
    }

    double Transport_ship::get_info_cargo(int i) const {
        double answer;
        if (0 > i || i > count_properties() - 1) answer = 0;
        else answer = cargo[i];
        return answer;
    }

    double Transport_ship::possible_speed(){ // максимально возможная скорость при текущей загрузке корабля
        return (cargo[1] / cargo[0]) * get_property("max velocity") * cargo[2];
    }

    void Transport_ship::set_cur_speed(double new_speed){
        double m_pos_speed = possible_speed();
        if (new_speed < 0 ) new_speed = 0;
        else if (new_speed > m_pos_speed) new_speed = m_pos_speed;
        Ship::set_velocity(new_speed);
    }

     Security_ship:: ~Security_ship(){
         for (int i = 0; i < 4; i ++)
             delete armaments[i];
     }

     void Security_ship::change_armament(std::string place, std::string property, double new_value, std::string type) {
         // номер оружия, свойство оружия, новое значение, тип оружия
         int i = -1;

         if (place == "stern") i = 0;
         else if (place == "bow") i = 1;
         else if (place == "right") i = 2;
         else if (place == "left") i = 3;

         if (i < 0 || i > 3) throw "Invalid place for armament";
         Basic::Armament *armament = armaments[i];
         if (armament != nullptr) {
             if (type == "") armament->change_property(property, new_value);
             else armament->change_type(type);
         }
         else throw "No such armament";
     }

     Basic::Armament *Security_ship::get_info_armament(std::string place) const{
         int i = -1;

         if (place == "stern") i = 0;
         else if (place == "bow") i = 1;
         else if (place == "right") i = 2;
         else if (place == "left") i = 3;

         if (i < 0 || i > 3) throw std::runtime_error("Invalid place for armament");
         return armaments[i];
     }

    Basic::Armament *Security_ship::get_info_armament(int i) const{
        if (i < 0 || i > 3) throw std::runtime_error("Invalid place for armament");
        return armaments[i];
    }

     void Security_ship::change_place(std::string old_, std::string new_){
         int old_place = -1, new_place = -1;

         if (old_ == "stern") old_place = 0;
         else if (old_== "bow") old_place = 1;
         else if (old_ == "right") old_place = 2;
         else if (old_ == "left") old_place = 3;

         if (new_ == "stern") new_place = 0;
         else if (new_  == "bow") new_place = 1;
         else if (new_ == "right") new_place = 2;
         else if (new_  == "left") new_place = 3;

         if (old_place < 0 || old_place > 3 ) throw std::runtime_error("Invalid place for old place");
         else if (new_place < 0 || new_place > 3 ) throw std::runtime_error("Invalid place for new place");

         if (armaments[old_place] == nullptr) throw std::runtime_error("No armament in this place");
         if (armaments[new_place] != nullptr) throw std::runtime_error("This place is not free");

         armaments[new_place] = armaments[old_place];
         armaments[old_place] = nullptr;
     }

     void  Security_ship::add_armament(Armament *new_armament, std::string place1){
        Basic::Armament * add_armament = nullptr;
        int place = -1;

        if (place1 == "stern") place = 0;
        else if (place1 == "bow") place = 1;
        else if (place1 == "right") place = 2;
        else if (place1 == "left") place = 3;

        if (place < 0 || place > 4) throw "No such place";
        if (armaments[place] == nullptr) {
            add_armament = new Basic::Armament;
            *add_armament = *new_armament;
            armaments[place] = add_armament;
        }
        else throw "This place is not free";
     }

    void  Security_ship::remove_armament(std::string place1) {
        int place = -1;

        if (place1 == "stern") place = 0;
        else if (place1 == "bow") place = 1;
        else if (place1 == "right") place = 2;
        else if (place1 == "left") place = 3;

        if (place < 0 || place > 4) throw "No such place";
        if (armaments[place] == nullptr) throw "Place is free";
        delete armaments[place];
        armaments[place] = nullptr;
    }

     double Security_ship::shoot(Coordinate cur_coord, Coordinate pirate){ // корабли ориентированы слева направо
         // определить, может ли корабль выстрелить по данной точке: равны координаты по х или по у
         double answer = 0;
         double distance = std::sqrt(pow(cur_coord.x - pirate.x,2) + pow(cur_coord.y - pirate.y, 2));
         Armament *cur_armament = nullptr;

         if (cur_coord.x == pirate.x) { // выстрел из левого или правого борта
             if (pirate.y > cur_coord.y) cur_armament = armaments[3]; // выстрел с левого борта
             else cur_armament = armaments[2]; // выстрел с правого борта
         }

         else if (cur_coord.y == pirate.y) { // выстрел с кормы или носа
             if (pirate.x > cur_coord.x) cur_armament = armaments[1]; // выстрел с носа корабля
             else cur_armament = armaments[0]; // выстрел с кормы корабля
         }

         // определить, долетит ли снаряд
         if (cur_armament != nullptr) // на выбранном месте расположено оружие
             if (cur_armament->get_property("range") >= distance) // property[2] - range, property[6] - status
                 answer = cur_armament->shoot();
         return answer;
     }

     void Security_ship::change_status(){
         for (int i = 0; i < 4; i ++)
             if (armaments[i] != nullptr) armaments[i]->change_status();
     }

    std::ostream &operator<<(std::ostream &s, const Transport_ship &ship){
         s << ship;
         s << "Max cargo: " << (ship.cargo)[0] << " Current cargo: " << (ship.cargo)[1] << " Coefficient of decrease: " << (ship.cargo)[2] <<"\n";
         return s;
     }

    std::ostream &operator<<(std::ostream &s, const Security_ship &ship){
        s << ship;
        s << "stern \t" << "bow \t" << "right board \t" << "left board \n";
        for (int i = 0; i < 4; i ++){
            if ((ship.armaments)[i] != nullptr) s << (ship.armaments[i])->get_type() << " \t";
            else s << "---- \t";
        }
        return s;
    }

    void Security_ship::armament_exchange(int first, int second){
        if (first < 0 || first > 3 ) throw std::runtime_error("Invalid place for first place");
        else if (second < 0 || second > 3 ) throw std::runtime_error("Invalid place for second place");

        if (armaments[first] == nullptr) throw std::runtime_error("No armament in this place");
        if (armaments[second] == nullptr) throw std::runtime_error("No armament in this place");

        Armament *tmp_armament = armaments[first];
        armaments[first] = armaments[second];
        armaments[second] = tmp_armament;
    }

    Military_transport_ship::Military_transport_ship( std::string new_type, std::string name, double max_velocity,
                                                      double max_life, double cost, double max_cargo, double coef_decrease):
            Transport_ship( new_type, name, max_velocity,max_life, cost,max_cargo,coef_decrease),
            Security_ship(new_type,name,max_velocity, max_life, cost), Ship(new_type,name,max_velocity, max_life, cost){}


    std::ostream &operator<<(std::ostream &s, const Military_transport_ship &ship){
        s << ship;
        s << "Max cargo: " << ship.get_info_cargo(0) << " Current cargo: " << ship.get_info_cargo(1) << " Coefficient of decrease: " << ship.get_info_cargo(2) <<"\n";
        s << "stern \t" << "bow \t" << "right board \t" << "left board \n";
        for (int i = 0; i < 4; i ++){
            if (ship.get_info_armament(i) != nullptr) s << (ship.get_info_armament(i))->get_type() << " \t";
            else s << "---- \t";
        }
        return s;
    }
}
