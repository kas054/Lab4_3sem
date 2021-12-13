//
// Created by PC on 21.11.2021.
//
#include <SFML/Graphics.hpp>
#include "Mission.h"
using namespace Basic;

namespace Menu{
    using namespace Pattern;

    Mission::Mission(Basic_config *conf, Table <std::string, Info> *c, Table <std::string, Info> *p ){
        config = conf;
        convoy = c;
        pirates = p;
    }

    double Mission::get_properties(std::string i) const{
        double answer;
        std::map<std::string, double> :: const_iterator it = prop.find(i);
        if (it == prop.end()) answer = 0;
        else answer = it->second;
        return answer;
    }

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
        std::string max_money = "max money", spend_money = "spend money", max_count_c = "max count convoy",
        max_count_p = "max count pirates", cur_velocity = "cur velocity", max_velocity = "max velocity";
        std::map<std::string, Ships::Ship>::iterator it;
        Ships::Ship *new_ship;
        int cost;
        it = (config->ship).find(ship_type);

        if (it == (config->ship).end()) return;

        new_ship = new Ships::Ship;
        *new_ship = it->second;
        cost = new_ship->get_property("cost");

        switch (c_p) {
            case 0: { // add ship to convoy
                //max_money - spend_money > 0 && max_count_ship_c > current_size of convoy
                if ((get_properties(max_money) - get_properties(spend_money)) > 0 && (get_properties(max_count_c) > convoy->get_count()))
                {
                    convoy->add_ship(new_ship, *get_coord_A_B(0)); // помещаем корабль на базу А
                    set_properties(spend_money, cost + get_properties(spend_money)); // change spend_money
                    break;
                }
                else
                {
                    delete new_ship;
                    return;
                }
            }
            case 1:{ // add pirates
                new_ship->change_property(cur_velocity, new_ship->get_property(max_velocity));// current velocity = max velocity
                // max_count_ship_p > current_size of pirates
                if ((get_properties(max_count_p) > pirates->get_count()))
                    pirates->add_ship(new_ship, *get_coord_A_B(0)); // помещаем корабль на базу A, потом корабли пиратов распределятся по координатам
                else{
                    delete new_ship;
                    return;
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
        this->set_properties("spend money", this->get_properties("spend money") - cost); // change spend_money
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
            set_properties("cur cargo", get_properties("cur cargo") + weight);
            //this->properties[4] += weight; // cur_cargo += weight
        }

        cur_ship->set_cur_speed(cur_ship->possible_speed()); // устанавливаем скорость на максимально возможную при текущей загрузке
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
        if ((c_p == 0 && ((this->get_properties("max money") - this->get_properties("spend money")) > 0)) || c_p == 1) {
            try {
                cur_ship->add_armament(new_armament, place);
                if (c_p == 0)
                    this->set_properties("spend money", cost + this->get_properties("spend money")); // change spend_money
            }
            catch (const char *e) { // покупка невозможна
                std::cout << *e << std::endl;
                if (c_p == 0)
                    this->set_properties("spend money", this->get_properties("spend money") - cost); // change spend_money
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
                this->set_properties("spend money", this->get_properties("spend money") - cost); // change spend_money
        }
        catch (const char *e) { // удаление невозможно
            std::cout << *e << std::endl;
            if (c_p == 0)
                this->set_properties("spend money", this->get_properties("spend money") + cost); // change spend_money
        }
    }

    void Mission::add_pirates_coordinate(double x, double y){
        Basic::Coordinate coord = {x,y};
        coordinates_pirates.push_back(coord);
    }

    void Mission::change_coord(int c_p, std::string name, double x, double y){
        Table<std::string, Info> :: Iterator it;

        switch(c_p){
            case 0:
                it = convoy->find(name);
            case 1:
                it = pirates->find(name);
        }

        if (x > get_x()) x = get_x();
        else if (x < -1 * get_x())  x = get_x() * (-1);

        if (y > get_y()) y = get_y();
        else if (y < -1 * get_y())  y = get_y() * (-1);

        it->info.cur_place.x = x;
        it->info.cur_place.y = y;
    }

    void Mission::distribution_pirates(){
        Pattern::Table<std::string, Info> :: Iterator it;
        Basic::Coordinate coord;
        int count_base = coordinates_pirates.size(), r_number;

        for (it = pirates->begin(); it != pirates->end(); it ++){
            r_number = random() % count_base;
            coord = coordinates_pirates[r_number];
            it->info.cur_place = coord;
        }
    }

    void Mission::start_coord() {

        Pattern::Table<std::string, Info> :: Iterator it = convoy->begin();
        Basic::Coordinate base_A = coordinates_A;
        int size = (int) get_properties("size B");
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

            change_coord(0, it->index, x, y);
            it ++;
        }
    }

    void Mission::update_status(){
        Ships::Security_ship *s_ship;
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

    void Mission::move_convoy(std::string direction) {
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
            change_coord(0, it->index, tmp_coord.x + change_x * velocity, tmp_coord.y + change_y * velocity);
        }
    }

    void Mission::move_pirates() {
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
            change_coord(0, it->index, tmp_coord.x + change_x * velocity, tmp_coord.y + change_y * velocity);
        }
    }

    void Mission::lose_ship(int c_p, std::string name){
        Ships::Transport_ship *t_ship;
        Pattern::Table<std::string, Info> :: Iterator it;
        double cargo =get_properties("cur cargo");

        switch(c_p){

            case 0:
            {
                it = convoy->find(name);

                if (it->info.ship->get_type() == "Transport ship" || it->info.ship->get_type() == "M_T ship"){ // если на корабле был груз, то вычитаем его
                    t_ship = dynamic_cast<Ships::Transport_ship *>(it->info.ship);
                    cargo -= t_ship->get_info_cargo(1);
                }
                set_properties("cur cargo", cargo);
                convoy->del_ship(name);
            }

            case 1:
                pirates->del_ship(name);
        }

    }

    void Mission::check_cur_life(){
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

    void Mission::rich_base_B(){

        Ships::Transport_ship *t_ship;
        Basic::Coordinate &coord = coordinates_B;
        double size = get_properties("size B"), cargo = 0;
        Pattern::Table<std::string, Info> :: Iterator it;

        for (it = convoy->begin(); it != convoy->end(); it ++){

            if (it->info.cur_place.x >= coord.x - size && it->info.cur_place.x <= coord.x + size)
                if (it->info.cur_place.y >= coord.y - size && it->info.cur_place.y <= coord.y + size) { // корабль находится на базе В

                    if (it->info.ship->get_type() == "Transport ship" || it->info.ship->get_type() == "M_T ship"){ // на корабле есть груз
                        t_ship = dynamic_cast<Ships::Transport_ship *>(it->info.ship);
                        cargo = t_ship->get_info_cargo(1); // current cargo
                        set_properties("delivered cargo",cargo);
                    }
                    lose_ship(0,it->index);
                }
        }
    }

    void Mission::pirates_shoot() {
        Ships::Security_ship *s_ship;
        Pattern::Table<std::string, Info> :: Iterator it_p, it_c;

        for (it_p = pirates->begin(); it_p != pirates->end(); it_p++){
            s_ship = dynamic_cast<Ships::Security_ship *>(it_p->info.ship);
            for (it_c = convoy->begin(); it_c != convoy->end(); it_c ++){
                s_ship->shoot(it_p->info.cur_place, it_c->info.cur_place);
                s_ship->change_status();
            }
        }
    }

    void Mission::convoy_shoot(std::vector<std::string> &convoy_ship, std::string pirate) {
        Ships::Security_ship *s_ship = nullptr;
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

    void Mission::draw() {

        int x, y;
        x = this->get_x();
        y = this->get_y();

        sf::RenderWindow window(sf::VideoMode((x +10) * 64, (y+ 10) * 64), "Convoy");

        sf::Sprite sprite;

        sf::Image water_image, base_c_imagine, pirates_imagine, convoy_imagine, base_p_imagine;

        water_image.loadFromFile("../Mission/Imagine/water.png");
        base_c_imagine.loadFromFile("../Mission/Imagine/Base_convoy.png");
        base_p_imagine.loadFromFile("../Mission/Imagine/base_b.png");
        pirates_imagine.loadFromFile("../Mission/Imagine/pirates8.png");
        convoy_imagine.loadFromFile("../Mission/Imagine/security3.png");


        sf::Texture water_texture;
        sf::Texture base_c_texture;
        sf::Texture base_p_texture;
        sf::Texture pirates_texture;
        sf::Texture convoy_texture;

        water_texture.loadFromImage(water_image);
        base_c_texture.loadFromImage(base_c_imagine);
        base_p_texture.loadFromImage(base_p_imagine);
        pirates_texture.loadFromImage(pirates_imagine);
        convoy_texture.loadFromImage(convoy_imagine);

        while (window.isOpen())
        {
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();

            for (int i = 0; i < x; i ++){
                for (int j = 0; j < y; j ++){
                    sprite.setTexture(water_texture);
                    sprite.setPosition(j * 64, i * 64);
                    window.draw(sprite);
                }
            }

            std::vector<Basic::Coordinate> :: iterator base_pirates;

            // Базы пиратов
            for (base_pirates = coordinates_pirates.begin(); base_pirates != coordinates_pirates.end(); base_pirates ++) {
                sprite.setTexture(base_p_texture);
                sprite.setPosition(base_pirates->x * 64, base_pirates->y * 64);
                window.draw(sprite);
            }

            // База конвоя А
            for (int i = 0; i < get_properties("size A"); i ++){
                for (int j = 0; j < get_properties("size A"); j ++){
                    sprite.setTexture(base_c_texture);
                    sprite.setPosition((get_coord_A_B(0)->x + i) * 64, (get_coord_A_B(0)->y + j)* 64);
                    window.draw(sprite);
                }
            }

            // База конвоя B
            for (int i = 0; i < get_properties("size B"); i ++){
                for (int j = 0; j < get_properties("size B"); j ++){
                    sprite.setTexture(base_c_texture);
                    sprite.setPosition((get_coord_A_B(1)->x + i) * 64, (get_coord_A_B(1)->y + j)* 64);
                    window.draw(sprite);
                }
            }


            Table <std::string, Info> :: Iterator it;

            // Корабли конвоя
            for (it = convoy->begin(); it != convoy->end(); it ++){
                sprite.setTexture(convoy_texture);
                sprite.setPosition(it->info.cur_place.x * 64, it->info.cur_place.y * 64);
                window.draw(sprite);
            }

            // Корабли пиратов
            for (it = pirates->begin(); it != pirates->end(); it ++){
                sprite.setTexture(pirates_texture);
                sprite.setPosition(it->info.cur_place.x * 64, it->info.cur_place.y * 64);
                window.draw(sprite);
            }

            window.display();
        }
    }
}