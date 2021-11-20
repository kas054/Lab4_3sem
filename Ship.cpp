//
// Created by PC on 08.11.2021.
//
#include "Ship.h"
#include <cmath>
#include <utility>

namespace Ships{
    using namespace Basic;
    Ship::Ship(std::string new_type, std::string name, double max_velocity, double max_life, double cost) {
        ship_type = std::move(new_type);
        this->name = std::move(name);
        properties[0] = max_velocity;
        properties[2] = max_life;
        properties[4] = cost;
    }

    void Ship::set_velocity(double velocity){
        if (velocity > this->get_property(0)) velocity = get_property(0); // properties[0] - max velocity
        else if (velocity < 0) velocity = 0;
        this->properties[1] = velocity; // properties[1] - current velocity
    }

    double Ship::get_property(int i) const {
        double answer;
        if (0 > i || i > count_properties() - 1) answer = 0;
        else answer = properties[i];
        return answer;
    }

    void Ship::print_properties() const{
        std::cout << "\t\t Type of ship: " << get_type() << "\n";
        std::cout << "\t\t Capitan: " << capitan << "\n";
        std::cout <<"\t\t max velocity \t current velocity \t max life \t current life \t cost \n\t\t ";
        for (int i = 0; i < 5; i ++){
            std::cout << properties[i] <<" \t ";
        }
        std::cout<<std::endl;
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
        return (cargo[1] / cargo[0]) * get_property(0) * cargo[2];
    }

    void Transport_ship::set_cur_speed(double new_speed){
        double m_pos_speed = possible_speed();
        if (new_speed < 0 ) new_speed = 0;
        else if (new_speed > m_pos_speed) new_speed = m_pos_speed;
        Ship::set_velocity(new_speed);
    }

    void Security_ship::change_armament(int i, int property, double new_value, std::string type) {
        // номер оружия, свойство оружия, новое значение, тип оружия
        if (i < 0 || i > 3) throw std::runtime_error("Invalid place for armament");
        Basic::Armament *armament = armaments[i];
        if (type == "") armament->change_property(property, new_value);
        else armament->change_type(type);
    }

    Basic::Armament *Security_ship::get_info_armament(int i) const{
        if (i < 0 || i > 3) throw std::runtime_error("Invalid place for armament");
        return armaments[i];
    }

    void Security_ship::change_place(int old_place, int new_place){

        if (old_place < 0 || old_place > 3 ) throw std::runtime_error("Invalid place for old place");
        else if (new_place < 0 || new_place > 3 ) throw std::runtime_error("Invalid place for new place");

        if (armaments[old_place] == nullptr) throw std::runtime_error("No armament in this place");
        if (armaments[new_place] != nullptr) throw std::runtime_error("This place is not free");

        armaments[new_place] = armaments[old_place];
        armaments[old_place] = nullptr;
    }

    void  Security_ship::add_armament(Armament &new_armament, int place){
        if (armaments[place] == nullptr) armaments[place] = &new_armament;
        else throw std::runtime_error("This place is not free");
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
            if (cur_armament->get_property(2) >= distance) // property[2] - range, property[6] - status
                answer = cur_armament->shoot();
        return answer;
    }

    void Security_ship::change_status(){
        for (int i = 0; i < 4; i ++)
            if (armaments[i] != nullptr) change_status();
    }

    std::ostream &operator<<(std::ostream &s, const Transport_ship &ship){
        ship.print_properties();
        s << "Max cargo: " << (ship.cargo)[0] << " Current cargo: " << (ship.cargo)[1] << " Coefficient of decrease: " << (ship.cargo)[2] <<"\n";
        return s;
    }

    std::ostream &operator<<(std::ostream &s, const Security_ship &ship){
        ship.print_properties();
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
            Transport_ship( new_type, name, max_velocity,max_life, cost,max_cargo,coef_decrease){}


    std::ostream &operator<<(std::ostream &s, const Military_transport_ship &ship){
        ship.print_properties();
        s << "Max cargo: " << ship.get_info_cargo(0) << " Current cargo: " << ship.get_info_cargo(1) << " Coefficient of decrease: " << ship.get_info_cargo(2) <<"\n";
        s << "stern \t" << "bow \t" << "right board \t" << "left board \n";
        for (int i = 0; i < 4; i ++){
            if (ship.get_info_armament(i) != nullptr) s << (ship.get_info_armament(i))->get_type() << " \t";
            else s << "---- \t";
        }
        return s;
    }
}
