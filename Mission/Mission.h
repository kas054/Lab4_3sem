//
// Created by PC on 21.11.2021.
//

#ifndef LAB4_3SEM_MISSION_H
#define LAB4_3SEM_MISSION_H
#include "../Table/Table.h"
#include <vector>
#include <map>
namespace Menu {

    using Pattern::Info;
    using Pattern::Table;

    class Mission {

        friend class Manage;
        friend class Basic_config;

    private:
        class Basic_config *config;
        Basic::Capitan commander;
        Table <std::string, Info> *convoy;
        Table <std::string, Info> *pirates;
        std::map<std::string, double> prop = {{"max money", 0}, {"spend money", 0}, {"full cargo", 0}, {"min cargo", 0},{"cur cargo", 0},
                                         {"delivered cargo", 0},{"max count convoy", 0},{"max count pirates", 0}, {"size A", 0}, {"size B", 0}};
        /* 0 - max_money, 1 - spend_money, 2 - full_cargo, 3 - min_cargo, 4 - cur_cargo,
          5 - delivered_cargo, 6 - max_count_ship_c, 7 - max_count_ship_p, 8 - size A, 9 - size B */
        Basic::Coordinate coordinates_A = {0, 0};
        Basic::Coordinate coordinates_B = {0, 0};
        std::vector<Basic::Coordinate> coordinates_pirates;
        // параметры появления пиратов?
    public:
        Mission() : convoy(nullptr), pirates(nullptr) {};

        float p_count() const {return prop.size();}

        double get_properties(std::string i) const;

        void set_properties(std::string i, int new_value) { if (prop.find(i) != prop.end()) prop[i] = new_value; }

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

        void add_pirates_coordinate(double x, double y);

        void change_coord(int c_p, std::string name, double x, double y);

        void distribution_pirates();

        void start_coord();

        void update_status();

        void move_convoy(std::string direction);

        void move_pirates();

        void lose_ship(int c_p, std::string name);

        void check_cur_life();

        void rich_base_B();

        void pirates_shoot();

        void convoy_shoot(std::vector<std::string> &convoy_ship, std::string pirate);
    };

    class Basic_config {
    public:
        std::map<std::string, Ships::Ship> ship;

        std::vector<Basic::Armament> armament;

        std::vector<Basic::Capitan> capitan;

        void add_ship(Ships::Ship *ship);

        FILE * load_from_file(std::string fname = "");

        void load_b(std::string fname, FILE *fd);

        void safe_b(FILE *fd);

        void load_basic_info_ship(FILE *fd, Ships::Ship *tmp_ship);

        void load_transport_ship(FILE *, Ships::Transport_ship *);

        void safe_table(FILE *fd, Menu::Table<std::string, Menu::Info> *tab);

        void load_armament(FILE *fd, Basic::Armament *armament);

        void safe_armament(FILE *fd, Basic::Armament *armament);

    };

}
#endif //LAB4_3SEM_MISSION_H
