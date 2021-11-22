//
// Created by PC on 08.11.2021.
//

#include "Table.h"
namespace Table {

    Info::Info(const Info &inf) {
        ship = inf.ship;
        cur_place.x = (inf.cur_place).x;
        cur_place.y = (inf.cur_place).y;
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
    INF & Table<IND, INF>::operator[ ](const IND &s){
        const char *error = "No such element";
        int i = get_pos(s);
        if (i < 0) throw error;
        else return elements[i].info;
    }

    // метод [] (r-value)
    template <class IND, class INF>
    const INF & Table<IND, INF>::operator[ ](const IND &s) const{
        int i = getPos(s);
        if (i < 0)
            throw "No such element";
        return elements[i].info;
    }

    // методы итератора
    template <class IND, class INF>
    Iterator<IND, INF> Table<IND, INF>::begin( ) {
        return Iterator(this->elements);
    }

    template <class IND, class INF>
    Iterator<IND, INF> Table<IND, INF>::end( ){
        return Iterator(this->elements + current_size);
    }

    template <class IND, class INF>
    Iterator<IND, INF> Table<IND, INF>::find(const IND &s) const{
        int i = getPos(s);
        if(i < 0)
            i = current_size;
        return Iterator(this->arr + i);
    }

























    /* methods for Iterator
    template <class S>
    int Iterator<S>::operator !=(const Iterator<S> &it) const{
        return cur != it.cur;
    }

    template <class S>
    int Iterator<S>::operator ==(const Iterator<S> &it) const{
        return cur == it.cur;
    }

    template <class S>
    Table_element<S> & Iterator<S>::operator *( ){
        return *cur;
    }

    template <class S>
    Table_element<S>* Iterator<S>::operator ->( ){
        return cur;
    }

    template <class S>
    Iterator<S> & Iterator<S>::operator ++( ){
        ++cur;
        return *this;
    }

    template <class S>
    Iterator<S> Iterator<S>::operator ++(int)
   {
        Iterator<S> res(*this);
        ++cur;
        return res;
    } */

    //methods for Table
    /*template <class S>
    S & Table<S>::operator[](const std::string &s){
        int i = getPos(s);
        if (i < 0){
            i = cur;
            if (cur >= cnt){
                Pair<IND, INF> *old = arr;
                arr = new Pair<IND, INF>[cnt += QUOTA];
                for (i = 0; i < cur; ++i)
                    arr[i] = old[i];
                delete[] old;
            }
            arr[cur].first = s;
            ++cur;
        }
        return arr[i].second;
    } */




    /*template <>
    Table<Ships::Ship>::~Table(){
        for (int i = 0; i , current_size; i ++){
            delete
        }
    }*/



    /*template <class T, class S>
    Table<T,S>::Table(Table<T, S> &&tab2) : current_size(tab2.current_size), max_size(tab2.max_size) {
        vector = new T [current_size];
        for (int i = 0; i < current_size; i++)
            vector[i] = vector2.vector[i];

   } */
}