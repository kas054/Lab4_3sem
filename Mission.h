//
// Created by PC on 21.11.2021.
//

#ifndef LAB4_3SEM_MISSION_H
#define LAB4_3SEM_MISSION_H
#include "Table.h"
#include <vector>
#include <map>
namespace Menu {
    using Pattern::Info;
    using Pattern::Table;
    class Mission {
        friend class Basic_config;
    private:
        class Basic_config *config;
        Basic::Capitan commander;
        Table <std::string, Info> *convoy;
        Table <std::string, Info> *pirates;
        /* 0 - max_money, 1 - spend_money, 2 - full_cargo, 3 - min_cargo, 4 - cur_cargo,
          5 - delivered_cargo, 6 - max_count_ship_c, 7 - max_count_ship_p, 8 - size A, 9 - size B */
        int properties[10] = {0};
        Basic::Coordinate coordinates_A = {0, 0};
        Basic::Coordinate coordinates_B = {0, 0};
        std::vector<Basic::Coordinate> coordinates_pirates;
        // параметры появления пиратов?
    public:
        Mission() : convoy(nullptr), pirates(nullptr) {};

        float p_count() const {return sizeof(properties) / sizeof(int);}

        double get_properties(int i) const { if (i < p_count()  && i >= 0) return properties[i]; else return 0;} // i - номер характеристики

        void set_properties(int i, int new_value) { if (i < p_count()  && i >= 0) properties[i] = new_value; }

       const Basic::Coordinate *get_coord_A_B(int i) const; // i == 0: A, i == 1: B

        void set_coord_A_B(int i, int x, int y);

        void change_ship_property(int c_p, std::string name, std::string ship_property_index, double new_value); //c_p == 0: конвой, c_p == 1: пираты

        void change_name_ship(int c_p, std::string name, std::string new_name);

        void change_ship_type(int c_p, std::string name, std::string new_type);

        void change_ship_cap(int c_p, std::string name, std::string name_cap);

        Ships::Ship *get_ship(int c_p, std::string name) const;

        void buy_ship(int c_p, std::string ship_type);

        void sell_ship(std::string name);

        void del_ship(int c_p, std::string name);

        void add_cargo(std::string name, int weight);

        void auto_cargo();

        void buy_armament(int c_p, std::string name, int place, std::string armament); // place- расположение оружия

        void change_armament(int c_p, std::string name, int place, std::string property, int new_value, std::string type = "");

        void sell_armament(int c_p, std::string name, int place);

    };

    class Basic_config {
    public:
        std::map<std::string, Ships::Ship> ship;

        std::vector<Basic::Armament> armament;

        std::vector<Basic::Capitan> capitan;

        void add_ship(Ships::Ship *ship);

        /**
         * open file or create new
         * @param fname file name
         * @return file pointer
         */
        FILE * load_from_file(std::string fname = "");
        /**
         * load basic configurations
         */
        void load_b(std::string fname, FILE *fd);

        void safe_b(FILE *fd);
        /**
         * load information about ship
         * @param fd File name
         * @param tmp_ship current ship
         */
        void load_basic_info_ship(FILE *fd, Ships::Ship *tmp_ship);
        /**
         * load information about cargo
         */
        void load_transport_ship(FILE *, Ships::Transport_ship *);

        /**
         * save mission
         * @param fd file name
         */
        void safe_table(FILE *fd, Menu::Table<std::string, Menu::Info> *tab);
    };
}
#endif //LAB4_3SEM_MISSION_H
