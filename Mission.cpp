//
// Created by PC on 21.11.2021.
//

#include "Mission.h"
using namespace Basic;

namespace Menu{
    using namespace Pattern;

    const Basic::Coordinate *Mission::get_coord_A_B(int i) const {
        const Basic::Coordinate *answer;
        if (i == 0) answer =  &coordinates_A;
        else if (i == 1) answer = &coordinates_B;
        else throw "No such base";
        return answer;
    }

    void Mission::set_coord_A_B(int i, int x, int y){
        if (i == 0) {
            coordinates_A.x = x;
            coordinates_A.y = y;
        }
        else if (i == 1){
            coordinates_B.x = x;
            coordinates_B.y = y;
        }
        else throw "No such base";
    }

    // Изменение характеристик корабля по его названию
    void Mission::change_ship_property(int c_p, std::string name, std::string ship_property_index, double new_value){
        Ships::Ship *cur_ship;
        switch(c_p) {
            case 0:
                cur_ship = convoy->description_ship(name);
            case 1:
                cur_ship = pirates->description_ship(name);
        }
        cur_ship->change_property(ship_property_index, new_value);
    }

    void  Mission::change_name_ship(int c_p, std::string name, std::string new_name){
        Ships::Ship *cur_ship;
        switch(c_p) {
            case 0:
                cur_ship = convoy->description_ship(name);
            case 1:
                cur_ship = pirates->description_ship(name);
        }
        cur_ship->change_name(new_name);
    }

    void Mission::change_ship_type(int c_p, std::string name, std::string new_type){
        Ships::Ship *cur_ship;
        switch(c_p) {
            case 0:
                cur_ship = convoy->description_ship(name);
            case 1:
                cur_ship = pirates->description_ship(name);
        }
        cur_ship->change_type(new_type);
    }

    void Mission::change_ship_cap(int c_p, std::string name, std::string name_cap){
        Ships::Ship *cur_ship;
        std::vector <Basic::Capitan> :: const_iterator vec_it;
        switch(c_p) {
            case 0:
                cur_ship = convoy->description_ship(name);
            case 1:
                cur_ship = pirates->description_ship(name);
        }
        for (vec_it = (config->capitan).cbegin(); vec_it != config->capitan.cend(); ++vec_it){
            if (vec_it->name == name_cap) {
                cur_ship->change_cap(*vec_it);
                break;
            }
        }
    }

    Ships::Ship *Mission::get_ship(int c_p, std::string name) const{
        Ships::Ship *cur_ship = nullptr;
        switch(c_p) {
            case 0:
                cur_ship = convoy->description_ship(name);
            case 1:
                cur_ship = pirates->description_ship(name);
        }
        return cur_ship;
    }

    void Mission::buy_ship(int c_p, std::string ship_type) {
        std::map<std::string, Ships::Ship>::iterator it;
        Ships::Ship *new_ship;
        int cost;
        it = (config->ship).find(ship_type);

        if (it == (config->ship).end()) throw "No such ship";

        new_ship = new Ships::Ship;
        *new_ship = it->second;
        cost = new_ship->get_property("cost");

        switch (c_p) {
            case 0: { // add ship to convoy
                //max_money - spend_money > 0 && max_count_ship_c > current_size of convoy
                if ((this->get_properties(0) - this->get_properties(1)) > 0 &&
                    (this->get_properties(6) > convoy->get_count())) {
                    convoy->add_ship(new_ship, *get_coord_A_B(0)); // помещаем корабль на базу А
                    this->set_properties(1, cost + this->get_properties(1)); // change spend_money
                } else {
                    delete new_ship;
                    throw "You do not have money or free place in convoy";
                }
            }
            case 1:{ // add pirates
                // max_count_ship_p > current_size of pirates
                if ((this->get_properties(7) > pirates->get_count()))
                    convoy->add_ship(new_ship, *get_coord_A_B(1)); // помещаем корабль на базу B
                else{
                    delete new_ship;
                    throw "Too many pirates";
                }
            }
        }
    }

    void Mission::sell_ship(std::string name){
        Table <std::string, Info> :: Iterator it;
        int cost;
        it = convoy->find(name);

        if (it == convoy->end()) throw "No such ship";

        cost = (*it).info.ship->get_property("cost");
        this->set_properties(1, this->get_properties(1) - cost); // change spend_money
        convoy->del_ship(name);
    }

    void Mission::del_ship(int c_p, std::string name){ // remove from Basic_config
        Table <std::string, Info> :: Iterator it;
        std::string type;
        std::map<std::string, Ships::Ship> :: iterator map_it;

        switch (c_p){
            case 0: {
                it = convoy->find(name);
                if (it == convoy->end()) throw "No such ship";
            }
            case 1: {
                it = pirates->find(name);
                if (it == pirates->end()) throw "No such ship";
            }
        }
        type = (*it).info.ship->get_type();

        map_it = (config->ship).find(type);

        if (map_it == (config->ship).end()) throw "No such ship";

        sell_ship( name);
        config->ship.erase(map_it);
    }

    void Mission::add_cargo(std::string name, int weight){
        Table <std::string, Info> :: Iterator it;
        Ships::Transport_ship *cur_ship;

        it = convoy->find(name);
        if (it == convoy->end()) throw "No such ship";

        cur_ship = dynamic_cast<Ships::Transport_ship *>((*it).info.ship);

        // max_cargo >= cur_cargo + weight
        if (cur_ship->get_info_cargo(0) >= cur_ship->get_info_cargo(1) + weight) {
            cur_ship->set_cur_cargo(weight);
            this->properties[4] += weight; // cur_cargo += weight
        }
    }

    void Mission::buy_armament(int c_p, std::string name, int place, std::string armament){
        Table<std::string, Info> :: Iterator it;
        std::vector <Basic::Armament> :: const_iterator vec_it;
        Ships::Security_ship *cur_ship;
        Basic::Armament *new_armament = nullptr;
        int cost;

        switch(c_p){
            case 0: {
                it = convoy->find(name);
                if (it == convoy->end()) throw "No such ship";
            }
            case 1: {
                it = pirates->find(name);
                if (it == pirates->end()) throw "No such ship";
            }
        }

        cur_ship = dynamic_cast<Ships::Security_ship *>((*it).info.ship);

        for (vec_it = (config->armament).cbegin(); vec_it != config->armament.cend(); ++vec_it){
            if (vec_it->get_type() == armament) {
                new_armament = new Basic::Armament;
                *new_armament = *vec_it;
                break;
            }
        }

        cost = vec_it->get_property("cost");
        //max_money - spend_money > 0
        if ((c_p == 0 && ((this->get_properties(0) - this->get_properties(1)) > 0)) || c_p == 1) {
            try {
                cur_ship->add_armament(new_armament, place);
                if (c_p == 0)
                    this->set_properties(1, cost + this->get_properties(1)); // change spend_money
            }
            catch (const char *e) { // покупка невозможна
                std::cout << *e << std::endl;
                if (c_p == 0)
                    this->set_properties(1, this->get_properties(1) - cost); // change spend_money
                delete new_armament;
            }
        }

    }

    void Mission::change_armament(int c_p, std::string name, int place, std::string property, int new_value, std::string type){
        Table<std::string, Info> :: Iterator it;
        std::vector <Basic::Armament> :: iterator vec_it;
        Ships::Security_ship *cur_ship;

        switch(c_p){
            case 0: {
                it = convoy->find(name);
                if (it == convoy->end()) throw "No such ship";
            }
            case 1: {
                it = pirates->find(name);
                if (it == pirates->end()) throw "No such ship";
            }
        }

        cur_ship = dynamic_cast<Ships::Security_ship *>((*it).info.ship);
        try {
            cur_ship->change_armament(place, property, new_value, type);
        }
        catch (const char *e) {
            std::cout << *e << std::endl;
        }
    }

    void Mission::sell_armament(int c_p, std::string name, int place){
        Table<std::string, Info> :: Iterator it;
        Ships::Security_ship *cur_ship;
        Basic::Armament *cur_armament;
        int cost;

        switch(c_p){
            case 0: {
                it = convoy->find(name);
                if (it == convoy->end()) throw "No such ship";
            }
            case 1: {
                it = pirates->find(name);
                if (it == pirates->end()) throw "No such ship";
            }
        }
        cur_ship = dynamic_cast<Ships::Security_ship *>((*it).info.ship);

        try {
            cur_armament = cur_ship->get_info_armament(place);
        }
        catch (const char *e) {
            std::cout << *e << std::endl;
        }

        cost = cur_armament->get_property("cost");

        try {
            cur_ship->remove_armament(place);
            if (c_p == 0)
                this->set_properties(1, this->get_properties(1) - cost); // change spend_money
        }
        catch (const char *e) { // удаление невозможно
            std::cout << *e << std::endl;
            if (c_p == 0)
                this->set_properties(1, this->get_properties(1) + cost); // change spend_money
        }
    }
}