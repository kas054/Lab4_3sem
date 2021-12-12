//
// Created by PC on 12.12.2021.
//

#include "Mission.h"
#include <cstdlib>
namespace Menu {

    void Manage::distribution_pirates() {

        Pattern::Table<std::string, Info> :: Iterator it;
        Pattern::Table<std::string, Info> *pirates = mission->pirates;
        Basic::Coordinate coord;
        int count_base = mission->coordinates_pirates.size(), r_number;

        for (it = pirates->begin(); it != pirates->end(); it ++){
            r_number = random() % count_base;
            coord = mission->coordinates_pirates[r_number];
            it->info.cur_place = coord;
        }
    }

    void Manage::start_coord() {

        Pattern::Table<std::string, Info> *convoy = mission->convoy;
        Pattern::Table<std::string, Info> :: Iterator it = convoy->begin();
        Basic::Coordinate base_A = mission->coordinates_A;
        int size = (int) mission->get_properties("size B");
        int len;
        double x, y;

        convoy->get_count() % size == 0 ? len = convoy->get_count() : len = convoy->get_count() + 1 ;

        for (int i = 0; i < convoy->get_count(); i ++){

            if (i % 3 == 0) {
                x = base_A.x + len;
                y = base_A.y;
            }

            else if (i % 3 == 1){
                x = base_A.x + len;
                y = base_A.y + 1;
            }

            else {
                x = base_A.x + len;
                y = base_A.y - 1;
                len -= 1; // переход на новый ряд
            }

            mission->change_coord(0, it->index, x, y);
            it ++;
        }
    }

    void Manage::update_status(){
        Ships::Security_ship *s_ship;
        Pattern::Table<std::string, Info> *convoy = mission->convoy;
        Pattern::Table<std::string, Info> *pirates = mission->pirates;
        Pattern::Table<std::string, Info> :: Iterator it;

        for (it = convoy->begin(); it != convoy->end(); it ++){
            if (it->info.ship->get_type() == "Security_ship"){
                s_ship = dynamic_cast<Ships::Security_ship *>(it->info.ship);
                s_ship->change_status();
            }
        }

        for (it = pirates->begin(); it != pirates->end(); it ++){
            s_ship = dynamic_cast<Ships::Security_ship *>(it->info.ship);
            s_ship->change_status();
        }
    }

    void Manage::move_convoy(std::string direction) {
        Pattern::Table<std::string, Info> *convoy = mission->convoy;
        Pattern::Table<std::string, Info> :: Iterator it;
        Basic::Coordinate tmp_coord;
        double change_x = 0, change_y = 0, velocity;

        if (direction == "up") change_y = 1;
        else if (direction == "down") change_y = -1;
        else if (direction == "left") change_x = -1;
        else if(direction == "right") change_x = 1;

        for (it = convoy->begin(); it != convoy->end(); it ++){
            velocity = it->info.ship->get_property("cur velocity");
            tmp_coord = it->info.cur_place;
            mission->change_coord(0, it->index, tmp_coord.x + change_x * velocity, tmp_coord.y + change_y * velocity);
        }
    }

    void Manage::move_pirates() {
        Pattern::Table<std::string, Info> *pirates = mission->convoy;
        Pattern::Table<std::string, Info> :: Iterator it;
        Basic::Coordinate tmp_coord;
        double change_x = 0, change_y = 0, velocity, direction;


        for (it = pirates->begin(); it != pirates->end(); it ++){

            direction = rand() % 4;

            if (direction == 0) change_y = 1;
            else if (direction == 1) change_y = -1;
            else if (direction == 2) change_x = -1;
            else if(direction == 3) change_x = 1;

            velocity = it->info.ship->get_property("cur velocity");
            tmp_coord = it->info.cur_place;
            mission->change_coord(0, it->index, tmp_coord.x + change_x * velocity, tmp_coord.y + change_y * velocity);
        }
    }

    void Manage::lose_ship(int c_p, std::string name){
        Ships::Transport_ship *t_ship;
        Pattern::Table<std::string, Info> :: Iterator it;
        double cargo = mission->get_properties("cur cargo");

        switch(c_p){

            case 0:
            {
                it = mission->convoy->find(name);

                if (it->info.ship->get_type() == "Transport ship" || it->info.ship->get_type() == "M_T ship"){ // если на корабле был груз, то вычитаем его
                    t_ship = dynamic_cast<Ships::Transport_ship *>(it->info.ship);
                    cargo -= t_ship->get_info_cargo(1);
                }
                mission->set_properties("cur cargo", cargo);
                mission->convoy->del_ship(name);
            }

            case 1:
                mission->pirates->del_ship(name);
        }

    }

    void Manage::check_cur_life(){
        Pattern::Table<std::string, Info> *convoy = mission->convoy;
        Pattern::Table<std::string, Info> *pirates = mission->pirates;
        Pattern::Table<std::string, Info> :: Iterator it;

        for (it = convoy->begin(); it != convoy->end(); it ++){
            if (it->info.ship->get_property("cur life") == 0)
                lose_ship(0, it->index);
        }

        for (it = pirates->begin(); it != pirates->end(); it ++){
            if (it->info.ship->get_property("cur life") == 0)
                lose_ship(1, it->index);
        }
    }

    void Manage::rich_base_B(){

        Ships::Transport_ship *t_ship;
        Basic::Coordinate &coord = mission->coordinates_B;
        double size = mission->get_properties("size B"), cargo = 0;
        Pattern::Table<std::string, Info> *convoy = mission->convoy;
        Pattern::Table<std::string, Info> :: Iterator it;

        for (it = convoy->begin(); it != convoy->end(); it ++){

            if (it->info.cur_place.x >= coord.x - size && it->info.cur_place.x <= coord.x + size)
                if (it->info.cur_place.y >= coord.y - size && it->info.cur_place.y <= coord.y + size) { // корабль находится на базе В

                    if (it->info.ship->get_type() == "Transport ship" || it->info.ship->get_type() == "M_T ship"){ // на корабле есть груз
                        t_ship = dynamic_cast<Ships::Transport_ship *>(it->info.ship);
                        cargo = t_ship->get_info_cargo(1); // current cargo
                        mission->set_properties("delivered cargo",cargo);
                    }
                    lose_ship(0,it->index);
                }
        }
    }

    void Manage::pirates_shoot() {
        Ships::Security_ship *s_ship;
        Pattern::Table<std::string, Info> *convoy = mission->convoy;
        Pattern::Table<std::string, Info> *pirates = mission->pirates;
        Pattern::Table<std::string, Info> :: Iterator it_p, it_c;

        for (it_p = pirates->begin(); it_p != pirates->end(); it_p++){
            s_ship = dynamic_cast<Ships::Security_ship *>(it_p->info.ship);
            for (it_c = convoy->begin(); it_c != convoy->end(); it_c ++){
                s_ship->shoot(it_p->info.cur_place, it_c->info.cur_place);
                s_ship->change_status();
            }
        }
    }

    void Manage::convoy_shoot(std::vector<std::string> &convoy_ship, std::string pirate) {
        Ships::Security_ship *s_ship = nullptr;
        Pattern::Table<std::string, Info> *convoy = mission->convoy;
        Pattern::Table<std::string, Info> *pirates = mission->pirates;
        Pattern::Table<std::string, Info> :: Iterator it_p, it_c;

        it_p = pirates->find(pirate);

        for (int i = 0; i < convoy_ship.size(); i ++) {
            it_c = convoy->find(convoy_ship[i]);
            if (it_c->info.ship->get_type() == "Security ship") {
                s_ship = dynamic_cast<Ships::Security_ship *>(it_c->info.ship);
                s_ship->shoot(it_c->info.cur_place, it_p->info.cur_place);
            }
        }
    }
}