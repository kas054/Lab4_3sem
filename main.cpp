#include <iostream>
#include "Table.h"
/*
namespace Pattern {

    Info::Info(const Info &inf) {
        ship = inf.ship;
        cur_place.x = (inf.cur_place).x;
        cur_place.y = (inf.cur_place).y;
    }

    Info & Info::operator = (const Info &st){
        if (this != &st){
            ship = st.ship;
        }
        return *this;
    }

    Info & Info::operator =(Info &&st){
        ship = st.ship;
        return *this;
    }

    // копирующий конструктор Table<IND, INF>

    template <class IND, class INF>
    Table<IND, INF>::Table(const Table<IND, INF> &vector2) : current_size(vector2.current_size), max_size(vector2.max_size)
    {
        elements = new Table_element<IND, INF>[current_size];
        for (int i = 0; i < current_size; i++)
            elements[i] = vector2.elements[i];
    }

    // перемещающий консруктор Table<IND, INF>
    template <class IND, class INF>
    Table<IND, INF>::Table(Table<IND, INF> &&vector2) : current_size(vector2.current_size), max_size(vector2.max_size), elements(vector2.elements){
        vector2.elements = nullptr;
    }

    // операторы присваивания
    template <class IND, class INF>
    Table<IND, INF> & Table<IND, INF>::operator = (const Table<IND, INF> &st){
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

    template <class IND, class INF>
    Table<IND, INF> & Table<IND, INF>::operator =(Table<IND, INF> &&st)
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

    // метод get_pos
    template <class IND, class INF>
    int Table<IND, INF>::get_pos(const IND &s) const {
        for (int i = 0; i < current_size; i ++)
            if (elements[i].index == s)
                return i;
        return -1;
    }

    // метод [] (l-value)
    template <class IND, class INF>
    INF & Table<IND, INF>::operator[](IND &s){
        const char *error = "No such element";
        int i = get_pos(s);
        if (i < 0) throw error;
        else return elements[i].info;
    }

    // метод [] (r-value)
    template <class IND, class INF>
    const INF & Table<IND, INF>::operator[](const IND &s) const{
        int i = get_pos(s);
        if (i < 0)
            throw "No such element";
        return elements[i].info;
    }

    // вывод Table<std::string string, Info>?
    std::ostream & operator <<(std::ostream &s, const Table<std::string, Info> &tab){
        Table<std::string, Info>::Iterator it;
        for (it = tab.begin();it != tab.end(); ++it)
            s << (*it).index << " - " << it->info << "\n";
        return s;
    }

    // удаление корабля
    template <>
    void Table<std::string, struct Info>::del_ship(const std::string &name) {
        //Table<std::string, struct Info>::Iterator it;
        int i = get_pos(name);
        if (i < 0) throw "No such element";
        else{
            delete &(elements[i]);
            elements[i] = elements[current_size-1];
            current_size -=1;
        }
    }

    // получение описателя корабля по имени
    template <>
    Ships::Ship *Table<std::string, struct Info>::description_ship(const std::string &name) {
        struct Info get_info = (*this)[name];
        return get_info.ship;
    }

    //добавить корабль
    template <>
    void Table<std::string, struct Info>::add_ship(Ships::Ship *new_ship, Basic::Coordinate coordinates){
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

    // методы итератора
    template <class IND, class INF>
    Iterator<IND, INF> Table<IND, INF>::begin( ) const {
        return Iterator(this->elements);
    }

    template <class IND, class INF>
    Iterator<IND, INF> Table<IND, INF>::end( ) const{
        return Iterator(this->elements + current_size);
    }

    template <class IND, class INF>
    Iterator<IND, INF> Table<IND, INF>::find(const IND &s) const{
        int i = get_pos(s);
        if(i < 0)
            i = current_size;
        return Iterator(this->elements + i);
    }

    //methods for Iterator
    template <class IND, class INF>
    int Iterator<IND, INF>::operator !=(const Iterator<IND, INF> &it) const{
        return cur != it.cur;
    }

    template <class IND, class INF>
    int Iterator<IND, INF>::operator ==(const Iterator<IND, INF> &it) const{
        return cur == it.cur;
    }

    template <class IND, class INF>
    Table_element<IND, INF> & Iterator<IND, INF>::operator *( ){
        return *cur;
    }

    template <class IND, class INF>
    Table_element<IND, INF>* Iterator<IND, INF>::operator ->( ){
        return cur;
    }

    template <class IND, class INF>
    Iterator<IND, INF> & Iterator<IND, INF>::operator ++( ){
        ++cur;
        return *this;
    }

    template <class IND, class INF>
    Iterator<IND, INF> Iterator<IND, INF>::operator ++(int)
    {
        Iterator<IND, INF> result(*this);
        ++cur;
        return result;
    }
} */
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
