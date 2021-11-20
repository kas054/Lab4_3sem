//
// Created by PC on 08.11.2021.
//

#ifndef LAB4_3SEM_TABLE_H
#define LAB4_3SEM_TABLE_H
#include "Ship.h"
namespace Table {
    template <class S>
    struct Table_element{
        S ship;
        std::string name;
        Basic::Coordinate cur_place;
    };

    template <class S>
    class Table {
    private:
        static const int QUOTA = 10;
        int max_size; // максимальный размер вектора
        int current_size;
        Table_element <Ships::Ship> **ships;
    public:
        Table(): current_size(0), ships(new Table_element <Ships::Ship> *[QUOTA]), max_size(QUOTA) {};
        Table(int size, S *array_of_new_ships, std::string *names, Basic::Coordinate *places);

        Table(const Table &); // копирующий конструктор
        Table(Table &&); // перемещающий конструктор
        Table &operator =(const Table &);
        Table &operator =(Table &&);
        ~Table() { delete[] ships; };

        int get_count() const { return current_size; };
        void del_ship(int i);
        void add_ship(S new_ship, Basic::Coordinate coordinates);
        Ships::Ship &description_ship(std::string name) const;
    };
}
#endif //LAB4_3SEM_TABLE_H
