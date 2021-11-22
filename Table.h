//
// Created by PC on 08.11.2021.
//

#ifndef LAB4_3SEM_TABLE_H
#define LAB4_3SEM_TABLE_H
#include "Ship.h"
namespace Table {

    struct Info{
        Ships::Ship *ship;
        Basic::Coordinate cur_place;

        Info(): ship(nullptr), cur_place({0,0}){}
        Info(Ships::Ship *s, Basic::Coordinate p): ship(s), cur_place(p) {}
        Info(const Info &inf);

        ~Info() {delete ship;}

        void print(){ std::cout << *ship << "\n" << cur_place <<std::endl;}
    };

    template <class IND, class INF>
    struct Table_element{
        IND index; // std::string
        INF info; // struct Info
        Table_element(): index(""), info(INF()) {}
        Table_element(const IND &name, const INF &inf): index(name), info(inf) {}
    };

    template <class IND, class INF>
    class Iterator{
    private:
        Table_element<IND, INF> *cur; // текущий элемент массива
    public:
        // конструкторы
        Iterator(): cur(nullptr){}
        Iterator(Table_element<IND, INF> *a): cur(a){}
        // операторы сравнения
        int operator !=(const Iterator<IND, INF> &) const;
        int operator ==(const Iterator<IND, INF> &) const;
        // доступ к элементам массива по указателю
        Table_element<IND, INF> & operator *();
        Table_element<IND, INF> * operator ->();
        // перемещение итератора на следующую позицию в массиве
        Iterator<IND, INF> & operator ++(); // префиксный
        Iterator<IND, INF> operator ++(int); // постфиксный
    };

    template <class IND, class INF>
    class Table {
        friend class Iterator<IND, INF>;
    private:
        static const int QUOTA = 10;
        int max_size, current_size;
        Table_element<IND, INF> *elements;
        int get_pos(const IND &) const;
    public:
        // конструкторы
        Table(): current_size(0), elements(new Table_element<IND, INF>[QUOTA]), max_size(QUOTA) {}; // пустой
        Table(const Table<IND, INF> &); // копирующий конструктор
        Table(Table<IND, INF> &&); // перемещающий конструктор
        // деструктор
        ~Table() {delete [] elements;}
        // операторы присваивания
        Table<IND, INF> &operator =(const Table<IND, INF> &);
        Table<IND, INF> &operator =(Table<IND, INF> &&);
        // операторы индексирования
        INF &operator[](const IND &); // l-value
        const INF &operator[](const IND &) const; // r -value
        // вывод
        friend std::ostream & operator <<(std::ostream &, const Table<IND, INF> &);
        // объявления для итератора
        typedef Iterator<IND, INF> Iterator;
        // методы итератора
        Iterator begin();
        Iterator end();
        Iterator find(const IND &) const;
        // методы таблицы
        int get_count() const { return current_size; };
        void del_ship(int i);
        void add_ship(Ships::Ship *new_ship, Basic::Coordinate coordinates);
        Ships::Ship &description_ship(std::string name) const;

    };
    /*Table <Ships::Ship> a;

    Ships::Transport_ship *transport = new Ships::Transport_ship();

    Ships::Ship ship = *transport;
    Ships::Transport_ship *tmp = dynamic_cast<Ships::Transport_ship *>(&ship); */


}
#endif //LAB4_3SEM_TABLE_H
