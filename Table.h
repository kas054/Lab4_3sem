//
// Created by PC on 08.11.2021.
//

#ifndef LAB4_3SEM_TABLE_H
#define LAB4_3SEM_TABLE_H
#include "Ship.h"
namespace Pattern {

    class Info{
    public:
        Ships::Ship *ship;
        Basic::Coordinate cur_place;

        Info(): ship(nullptr), cur_place({0,0}){}
        Info(Ships::Ship *s, Basic::Coordinate p): ship(s), cur_place(p) {}
        Info(const Info &inf){
            ship = inf.ship;
            cur_place.x = (inf.cur_place).x;
            cur_place.y = (inf.cur_place).y;
        }

        Info &operator=(const Info &st){
            if (this != &st){
                ship = st.ship;
            }
            return *this;
        }

        Info &operator=(Info &&st){
            ship = st.ship;
            return *this;
        }

        ~Info() {delete ship;}

        friend std::ostream & operator <<(std::ostream &s, const Info &inf) {
            std::cout << inf.ship << "\n" << inf.cur_place <<std::endl;
            return s;
        }
    };

    template <class IND, class INF>
    struct Table_element{
        IND index; // std::string
        INF info; // class Info
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
        int operator !=(const Iterator<IND, INF> &it) const{
            return cur != it.cur;
        }
        int operator ==(const Iterator<IND, INF> &it) const{
            return cur == it.cur;
        }
        // доступ к элементам массива по указателю
        Table_element<IND, INF> & operator *(){
            return *cur;
        }
        Table_element<IND, INF> * operator ->(){ return cur; }
        // перемещение итератора на следующую позицию в массиве
        Iterator<IND, INF> & operator ++(){ // префиксный
        ++cur;
        return *this;
    }
        Iterator<IND, INF> operator ++(int) // постфиксный
        {
            Iterator<IND, INF> result(*this);
            ++cur;
            return result;
        }
    };

    template <class IND, class INF>
    class Table {
        friend class Iterator<IND, INF>;
    private:
        static const int QUOTA = 10;
        int max_size, current_size;
        Table_element<IND, INF> *elements;
        int get_pos(const IND &s) const {
            for (int i = 0; i < current_size; i ++)
                if (elements[i].index == s)
                    return i;
            return -1;
        }
    public:
        // конструкторы
        Table(): current_size(0), elements(new Table_element<IND, INF>[QUOTA]), max_size(QUOTA) {}; // пустой
        Table(const Table<IND, INF> &vector2): current_size(vector2.current_size), max_size(vector2.max_size) // копирующий консруктор
        {
            elements = new Table_element<IND, INF>[current_size];
            for (int i = 0; i < current_size; i++)
                elements[i] = vector2.elements[i];
        }
        Table(Table<IND, INF> &&vector2): current_size(vector2.current_size), max_size(vector2.max_size), elements(vector2.elements){ // перемещающий конструктор
            vector2.elements = nullptr;
        }
        // деструктор
        ~Table() {delete [] elements;}
        // операторы присваивания
        Table<IND, INF> &operator =(const Table<IND, INF> &st){
            if (this != &st){
                current_size = st.current_size;
                max_size = st.max_size;
                delete[] elements;
                elements = new Table_element<IND, INF>[max_size];
                for (int i = 0; i < current_size; ++i)
                    elements[i] = st.vector[i];
            }
            return *this;
        }
        Table<IND, INF> &operator =(Table<IND, INF> &&st)
        {
            int tmp = current_size;
            current_size = st.current_size;
            st.current_size = tmp;
            tmp = max_size;
            max_size = st.max_size;
            st.max_size = tmp;
            Table_element<IND, INF> *ptr = elements;
            elements = st.elements;
            st.elements = ptr;
            return *this;
        }
        // операторы индексирования
        INF &operator[](IND &s) // l-value
        {
            const char *error = "No such element";
            int i = get_pos(s);
            if (i < 0) throw error;
            else return elements[i].info;
        }
        const INF &operator[](const IND &s) const // r-value
        {
            int i = get_pos(s);
            if (i < 0)
            throw "No such element";
            return elements[i].info;
        }
        // вывод
        template <class Id, class If>
        friend std::ostream & operator <<(std::ostream &s, const Table<Id,If> &tab){
            Table<std::string, Info>::Iterator it;
            for (it = tab.begin();it != tab.end(); ++it)
                s << (*it).index << " - " << it->info << "\n";
            return s;
        }
        // объявления для итератора
        typedef Iterator<IND, INF> Iterator;
        // методы итератора
        Iterator begin() const { return Iterator(this->elements);}
        Iterator end() const { return Iterator(this->elements + current_size);}
        Iterator find(const IND &s) const {
            int i = get_pos(s);
            if(i < 0)
                i = current_size;
            return Iterator(this->elements + i);
        }
        // методы таблицы
        int get_count() const { return current_size; };
        void del_ship(const std::string &name){
            //Table<std::string, struct Info>::Iterator it;
            int i = get_pos(name);
            if (i < 0) throw "No such element";
            else{
                delete &(elements[i]);
                elements[i] = elements[current_size-1];
                current_size -=1;
            }
        }
        void add_ship(Ships::Ship *new_ship, Basic::Coordinate coordinates){
            typedef Table_element<std::string, struct Info>  Tab_elem;

            Info new_info= {new_ship, coordinates}; //
            Tab_elem new_elem = {new_ship->get_name(), new_info};//

            if (current_size == max_size) {
                max_size += QUOTA;
                Tab_elem *old = elements;
                elements = new Tab_elem [max_size];
                for (int i = 0; i < current_size; i ++) elements[i] = old[i];
                delete [] old;
            }
            elements[current_size] = new_elem;
            current_size += 1;
        }
        Ships::Ship *description_ship(const std::string  &name){
            struct Info get_info = (*this)[name];
            return get_info.ship;
        }

    };
     /*
       Table <std::string, struct Info> a;
       Ships::Transport_ship *transport = new Ships::Transport_ship();
       Ships::Ship ship = *transport;
       Ships::Transport_ship *tmp = dynamic_cast<Ships::Transport_ship *>(&ship); */
}
#endif //LAB4_3SEM_TABLE_H
