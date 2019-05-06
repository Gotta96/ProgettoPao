#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>

template <class T>
class Container;

//template <class T>
//std::ostream& operator<<(std::ostream&,const Container<T>&);

template <class T>
class Container{
    //friend std::ostream& operator<< <T>(std::ostream&, const Container<T>&);
private:
    class nodo{
    public:
        T info;
        nodo* next;
        nodo(const T&, nodo* =nullptr);
        nodo(const nodo&);
        ~nodo();
    };

    nodo* first;

    static nodo* copy(const nodo*);

    static void destroy(nodo*);

    static bool search(nodo* ,const T&);

    static bool equal(const nodo*, const nodo*);

public:
    Container();
    Container(const T&);
    Container(const Container&);
    Container<T> operator=(const Container<T>&);     //aggiunta 19/12/18
    nodo* getFirst() const;     //aggiunta il 19/12/18*/
    ~Container();
    bool is_empty() const;
    bool remove(const T&);
    bool search(const T&) const;
    void add(const T&);
    int itemsCounter(const T&) const;
    bool operator==(const Container&) const;
    bool operator!=(const Container&) const;

    class Iterator{
        friend class Container<T>;
    private:
        nodo* pointed;
        bool pte;
        Iterator(nodo*, bool =false);
    public:
        Iterator();
        Iterator(const Container<T>&);
        Iterator &operator++();
        T& operator*();
        T* operator->();
        bool operator ==(const Iterator&) const;
        bool operator !=(const Iterator&) const;
        bool hasNext() const;
        T& next() const;
    };
    Iterator Begin();
    Iterator End();
};

template <class T>
Container<T>::nodo::nodo(const T& i, nodo* p): info(i), next(p){}

template <class T>
Container<T>::nodo::nodo(const nodo& n):info(n.info), next(n.next){}

template <class T>
Container<T>::nodo::~nodo(){
    if(next){
        delete next;
    }
}

template <class T>
typename Container<T>::nodo* Container<T>::copy(const nodo* n){
    if(!n) return nullptr;
    return new nodo(n->info, copy(n->next));
}

template <class T>
void Container<T>::destroy(nodo* n){
    if(n)
        delete n;
}

template <class T>
bool Container<T>::search(nodo* n, const T& itm){
    if(!n)
        return false;
    return (n->info == itm || search(n->next,itm));
}

template <class T>
bool Container<T>::equal(const nodo* nodol, const nodo* nodolfor){
    if(!nodol && !nodolfor)
        return true;
    if(!nodol || !nodolfor)
        return false;
    if(nodol->info==nodolfor->info)
        return equal(nodol->next, nodolfor->next);
    return false;
}

template <class T>
Container<T>::Container(): first(nullptr){}


template <class T>
Container<T>::Container(const T& itm): first(new nodo(&itm)){} //costruttore ad un parametro

template <class T>
Container<T>::Container(const Container& l1): first(copy(l1.first)){}    //costruttore di copia

template <class T>
Container<T> Container<T>::operator=(const Container<T>& cl){
    if(first != (cl.getFirst())){
        delete first;
        first = copy(cl.getFirst());
    }
    return *this;
}


template <class T>
typename Container<T>::nodo* Container<T>::getFirst() const{
    return first;
}

template <class T>
bool Container<T>::is_empty() const{
    return !first;
}

template <class T>
bool Container<T>::remove(const T& itm){
    if(is_empty())
        return false;

    if(!first->next){
        if(first->info==itm){
            delete first;
            first=nullptr;
            return true;
        }
    }
    else{
        nodo* prev=first;
        nodo* att=first->next;

        if(prev->info==itm){
            first=first->next;
            prev->next=nullptr;
            delete prev;
            return true;
        }

        while(att->next!=nullptr && (att->info) != itm){
            prev=prev->next;
            att=att->next;
        }

        if(att->info==itm){
            prev->next=att->next;
            att->next=nullptr;
            delete att;
            return true;
        }
    }

    return false;
}

template <class T>
bool Container<T>::search(const T& itm)const{
    return search(first, itm);
}

template <class T>
int Container<T>::itemsCounter(const T& i) const{
    int counter=0;
    for(auto cit=Begin(); cit != End(); cit++)
        if((**cit)==i)
            counter++;
    return counter;
}

template <class T>
void Container<T>::add(const T& itm){
    if(first!=nullptr){
        nodo* tmp=first;
         while(tmp->next != nullptr)
            tmp=tmp->next;
        tmp->next=new nodo(itm);
    }
    else
        first= new nodo(itm);
}

template <class T>
Container<T>::~Container<T>(){
    if(first)
        destroy(first);
}

//template <class T>
//std::ostream& operator<<(std::ostream& os, const Container<T>& c) {
//  return Container<T>::print(os,c.first);
//}

template <class T>
bool Container<T>::operator==(const Container& c) const{
    return equal(first, c.first);
}

template <class T>
bool Container<T>::operator!=(const Container& c) const{
    return !(equal(first, c.first));
}

template<class T>
Container<T>::Iterator::Iterator(Container::nodo *n, bool passed): pointed(n), pte(passed){}

template <class T>
Container<T>::Iterator::Iterator(const Container<T>& list): pointed(copy(list.getFirst())){
    if(!pointed && !pointed->next)
        pte=true;
    else
        pte=false;
}        //prestare attenzione al pst the end

template<class T>
typename Container<T>::Iterator Container<T>::Begin(){
    return Iterator(first);
}

template<class T>
typename Container<T>::Iterator Container<T>::End(){
    nodo *p=first;
    while(p&&p->next)
        p=p->next;
    return Iterator(p+1);
}

template<class T>
typename Container<T>::Iterator &Container<T>::Iterator::operator++(){
    if(!pte && pointed){
        if(pointed->next==nullptr){
            pointed=pointed+1;
            pte=true;
        }
        else pointed=pointed->next;
    }
    return *this;
}

template<class T>
T &Container<T>::Iterator::operator*(){
    return pointed->info;
}

template<class T>
T *Container<T>::Iterator::operator->(){
    return &(pointed->info);
}

template<class T>
bool Container<T>::Iterator::operator ==(const Container<T>::Iterator & i) const{
    return pointed==i.pointed;
}

template<class T>
bool Container<T>::Iterator::operator !=(const Container<T>::Iterator & i) const{
    return pointed!=i.pointed;
}

template <class T>
bool Container<T>::Iterator::hasNext() const{
    if(pointed->next)
        return true;
    else
        return false;
}

template <class T>
T& Container<T>::Iterator::next() const{
    if(pointed->next)
        return (pointed->next->info);
}

#endif // CONTAINER_H
