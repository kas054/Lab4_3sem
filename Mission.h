//
// Created by PC on 21.11.2021.
//

#ifndef LAB4_3SEM_MISSION_H
#define LAB4_3SEM_MISSION_H
#include "Table.h"
namespace Menu {
    using Table::Table;
    template<class S>
    class Mission {
    private:
        static const int QUOTA = 10;
        int max_size; // максимальный размер вектора
        int current_size;

        Basic::Capitan commander;
        Table <Ships::Ship> &convoy;
        Table <Ships::Ship> &pirates;
        /* max_money, spend_money, full_cargo, min_cargo, lost_cargo,
           delivered_cargo, max_count_ship_c, max_count_ship_p, size A, size B */
        int properties[10] = {0};
        Basic::Coordinate coordinates_A = {0, 0};
        Basic::Coordinate coordinates_B = {0, 0};
        Basic::Coordinate *coordinates_pirates;
        // параметры появления пиратов?
    public:
        Mission() : current_size(0), coordinates_pirates(new Basic::Coordinate[QUOTA]), max_size(QUOTA) {};

        Mission(const Mission &);

        Mission(Mission &&);

        Mission &operator=(const Mission &);

        Mission &operator=(Mission &&);

        ~Mission() { delete[] coordinates_pirates; };

        double get_properties(int i) const; // i - номер характеристики
        void set_properties(int i, int new_value);

        Basic::Coordinate get_coord_A_B(int i) const; // i == 0: A, i == 1: B
        void set_coord_A_B(int i, int x, int y);

        void change_ship(int c_p, int table_index, int ship_property_index); //c_p == 0: конвой, c_p == 1: пираты
        Ships::Ship &get_ship(int c_p, int table_index) const;

        void buy_ship(std::string ship_type);

        void sell_ship(int c_p, int table_index);

        void del_ship(int c_p, int table_index);

        void add_cargo(int table_index, int weight);

        void aouto_cargo();

        void buy_armament(int c_p, int table_index, int i, int property, int new_value, std::string type = "");

        void sell_armament(int c_p, int table_index, int i);

        Ships::Ship &create_pirate();
    };

}
#endif //LAB4_3SEM_MISSION_H
