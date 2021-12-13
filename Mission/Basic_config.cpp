//
// Created by PC on 06.12.2021.
//

#include "Mission.h"
namespace Menu {
    void Basic_config::add_ship(Ships::Ship *new_ship) {
        std::string name = new_ship->get_name();
        // m.insert(pair<string,string>("key2", "val2"));
        //mymap.insert ( std::pair<char,int>('a',100) );
        (this->ship).insert(std::pair<std::string, Ships::Ship>(name, *new_ship));
    }

    FILE *Basic_config::load_from_file(std::string fname) {
        FILE *fd;
        if (fname == "") throw "Incorrect name o file";

        try {
            load_b(fname, fd);
        }
        catch (...) {
            fd = fopen(fname.c_str(), "w+b");
        }
        return fd;
    }

    void Basic_config::load_armament(FILE *fd, Basic::Armament *armament) {
        double value = 0;
        fread(&value, sizeof(double), 1, fd);
        armament->change_property("damage", value);
        fread(&value, sizeof(double), 1, fd);
        armament->change_property("rate of fire", value);
        fread(&value, sizeof(double), 1, fd);
        armament->change_property("range", value);
        fread(&value, sizeof(double), 1, fd);
        armament->change_property("max ammunition", value);
        fread(&value, sizeof(double), 1, fd);
        armament->change_property("cur ammunition", value);
        fread(&value, sizeof(double), 1, fd);
        armament->change_property("cost", value);
        fread(&value, sizeof(double), 1, fd);
        armament->change_property("status", value);
    }

    void safe_armament(FILE *fd, Basic::Armament *armament){
        double value = 0;
        value = armament->get_property("damage");
        fwrite(&value, sizeof(double), 1, fd);
        value = armament->get_property("rate of fire");
        fwrite(&value, sizeof(double), 1, fd);
        value = armament->get_property("range");
        fwrite(&value, sizeof(double), 1, fd);
        value = armament->get_property("max ammunition");
        fwrite(&value, sizeof(double), 1, fd);
        value = armament->get_property("cur ammunition");
        fwrite(&value, sizeof(double), 1, fd);
        value = armament->get_property("cost");
        fwrite(&value, sizeof(double), 1, fd);
        value = armament->get_property("status");
        fwrite(&value, sizeof(double), 1, fd);
    }

    void Basic_config::load_b(std::string fname, FILE *fd) { // basic config
        Ships::Security_ship *sec_ship;
        Ships::Transport_ship *t_ship;
        Basic::Armament *arm = new Basic::Armament;//
        int sz_ship, sz_armament, sz_cap;
        // открываем файл на чтение и запись
        fd = fopen(fname.c_str(), "r+b");

        if (fd == nullptr) throw "No such file";

        load_armament(fd, arm);
/*
        // считываем количество
        fread(&sz_ship, sizeof(int), 1, fd);
        fread(&sz_armament, sizeof(int), 1, fd);
        fread(&sz_cap, sizeof(int), 1, fd);

        // записываем корабли
        for (int i = 0; i < sz_ship; i++) {
            Ships::Military_transport_ship *tmp_ship = new Ships::Military_transport_ship;

            load_basic_info_ship(fd, tmp_ship);

            if (tmp_ship->get_type() == "Security_ship") {
                sec_ship = dynamic_cast<Ships::Security_ship *>(tmp_ship);
                (this->ship).insert(std::make_pair(sec_ship->get_name(), *sec_ship));
            } else if (tmp_ship->get_type() == "Transport_ship") {
                this->load_transport_ship(fd, tmp_ship);
                t_ship = dynamic_cast<Ships::Transport_ship *>(tmp_ship);
                (this->ship).insert(std::make_pair(t_ship->get_name(), *t_ship));
            } else { // M_T_Ship
                this->load_transport_ship(fd, tmp_ship);
                (this->ship).insert(std::make_pair(tmp_ship->get_name(), *tmp_ship));
            }

            delete tmp_ship;
        }
*/
        // закрытие файла
        fclose(fd);
        fd = nullptr;
        delete arm;
    }

    void Basic_config::safe_b(FILE *fd) { // сохранение базовой конфигурации
        std::map<std::string, Ships::Ship>::iterator it;
        std::map<std::string, double> :: iterator properties;
        int len_string;
        double prop;
        const char *tmp_char;
        Ships::Ship *tmp_ship;
        Ships::Transport_ship *t_ship;

        fseek(fd, 0, SEEK_SET);
        for (it = ship.begin(); it != ship.end(); it++) {
            tmp_ship = &(it->second);
            // write type
            len_string = (tmp_ship->get_type()).length();
            tmp_char = (tmp_ship->get_type()).c_str();
            fwrite(tmp_char, sizeof(char), len_string + 1, fd);
            // write name
            len_string = (tmp_ship->get_name()).length();
            tmp_char = (tmp_ship->get_name()).c_str();
            fwrite(tmp_char, sizeof(char), len_string + 1, fd);
            // write properties
            for (int i = 0; i < tmp_ship->count_properties(); i++) {
             //   prop = tmp_ship->get_property(i);
                fwrite(&prop, sizeof(double), 1, fd);
            }
            // write information about cargo
            if (tmp_ship->get_type() == "Transport_ship") {
                t_ship = dynamic_cast<Ships::Transport_ship *>(tmp_ship);
                for (int j = 0; j < t_ship->get_size(); j++) {
                    prop = t_ship->get_info_cargo(j);
                    fwrite(&prop, sizeof(double), 1, fd);
                }
            }
        }
        fclose(fd);
        fd = nullptr;
    }

    void Basic_config::load_basic_info_ship(FILE *fd, Ships::Ship *tmp_ship) {
        char *tmp_char, *name; // for type and name
        int tmp_int; // for max_velocity, cur_velocity, max_life, cur_life, cost, len of char *

        // Тип корабля
        fread(&tmp_int, sizeof(int), 1, fd); // считали длину строки
        tmp_char = new char[tmp_int + 1];
        fread(&tmp_char, sizeof(char), tmp_int + 1, fd); // считали строку
        std::string tmp_string(tmp_char); // преобразовали в string
        tmp_ship->change_type(tmp_string);

        // Имя корабля
        fread(&tmp_int, sizeof(int), 1, fd); // считали длину строки
        name = new char[tmp_int + 1];
        fread(&name, sizeof(char), tmp_int + 1, fd); // считали строку
        std::string tmp_name(name); // преобразовали в string
        tmp_ship->change_name(tmp_name);

        for (int i = 0; i < tmp_ship->count_properties(); i++) { // считываем характеристики корабля
            fread(&tmp_int, sizeof(int), 1, fd);
           // tmp_ship->change_property(i, tmp_int);
        }

        delete tmp_char;
        delete name;
    }

    void Basic_config::load_transport_ship(FILE *fd, Ships::Transport_ship *tmp_ship) {
        int tmp_int;
        fread(&tmp_int, sizeof(int), 1, fd);
        tmp_ship->set_max_cargo(tmp_int);
        fread(&tmp_int, sizeof(int), 1, fd);
        tmp_ship->set_coef_decrease(tmp_int);
    }

    void Basic_config::safe_table(FILE *fd, Menu::Table<std::string, Menu::Info> *tab) {
        Pattern::Table<std::string, Menu::Info>::Iterator it;
        int len_string;
        double prop;
        const char *tmp_char;
        std::string tmp_string;
        Ships::Ship *tmp_ship;
        Ships::Transport_ship *t_ship;
        Ships::Security_ship *s_ship;
        Ships::Military_transport_ship *m_t_ship;

        fseek(fd, 0, SEEK_SET);

        for (it = tab->begin(); it != tab->end(); it++) {
            tmp_ship = (*it).info.ship;
            // write type
            len_string = (tmp_ship->get_type()).length();
            tmp_char = (tmp_ship->get_type()).c_str();
            fwrite(tmp_char, sizeof(char), len_string + 1, fd);
            // write name
            len_string = (tmp_ship->get_name()).length();
            tmp_char = (tmp_ship->get_name()).c_str();
            fwrite(tmp_char, sizeof(char), len_string + 1, fd);
            // write properties
            for (int i = 0; i < tmp_ship->count_properties(); i++) {
               // prop = tmp_ship->get_property(i);
                fwrite(&prop, sizeof(double), 1, fd);
            }
            // write information about cargo
            if (tmp_ship->get_type() == "Transport_ship") {
                t_ship = dynamic_cast<Ships::Transport_ship *>(tmp_ship);
                for (int j = 0; j < t_ship->get_size(); j++) {
                    prop = t_ship->get_info_cargo(j);
                    fwrite(&prop, sizeof(double), 1, fd);
                }
            } else if (tmp_ship->get_type() == "Security_ship")
                s_ship = dynamic_cast<Ships::Security_ship *>(tmp_ship);
        }

    }
}