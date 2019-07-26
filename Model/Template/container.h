#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>



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
    ~Container();

    Container<T> operator=(const Container<T>&);     //aggiunta 19/12/18
    nodo* getFirst() const;     //aggiunta il 19/12/18*/
    bool is_empty() const;
//    bool remove(const T&);
    bool removeOne(const T&);
    bool removeOneAtIndex(const unsigned int i);
    bool search(const T&) const;
    void addInOrder(T&);
    int itemsCounter(const T&);     //aggiunere const_ness
    bool operator==(const Container&) const;
    bool operator!=(const Container&) const;

    T* searchAtIndex(unsigned int i);   //aggiungere const_ness
    int size();   //creare il const_iterator e aggiungere la const nei metodiche la richiedono, modificare i corpi delle funzioni sistemando con iteratore adeguato
    void replace(const T&, unsigned int);     //constollare se giusta

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
//        bool eraseOneAtIndex(unsigned int i);
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
    if(n->info == itm)
        return true;
    return search(n->next,itm);
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
Container<T> Container<T>::operator=(const Container& cl){
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

//template <class T>
//typename Container<T>::nodo* Container<T>::putInOrder(){    //da modificare per ridurre complessità
//    if(is_empty())
//        return nullptr;
//    nodo* tmp=first;
//    while(tmp->next){
//        if(tmp->info > tmp->next->info){
//            nodo* aux= tmp;

//        }
//    }

//}

//template <class T>
//bool Container<T>::remove(const T& itm){
//    if(is_empty())
//        return false;

//    if(!first->next){
//        if(first->info==itm){
//            delete first;
//            first=nullptr;
//            return true;
//        }
//    }
//    else{
//        nodo* prev=first;
//        nodo* att=first->next;

//        if(prev->info==itm){
//            first=first->next;
//            prev->next=nullptr;
//            delete prev;
//            return true;
//        }

//        while(att->next!=nullptr && (att->info) != itm){
//            prev=prev->next;
//            att=att->next;
//        }

//        if(att->info==itm){
//            prev->next=att->next;
//            att->next=nullptr;
//            delete att;
//            return true;
//        }
//    }

//    return false;
//}

template <class T>
bool Container<T>::removeOne(const T& itm){
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
bool Container<T>::removeOneAtIndex(const unsigned int i){
    if(is_empty())
        return false;

    if(!first->next){
        if(i==0){
            delete first;
            first=nullptr;
            return true;
        }
    }
    else{
        nodo* prev=first;
        nodo* att=first->next;

        if(i==0){
            first=first->next;
            prev->next=nullptr;
            delete prev;
            return true;
        }

        for(unsigned int k=0; att->next && k<i; k++){
            prev=prev->next;
            att=att->next;
        }

        if(att){
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
int Container<T>::itemsCounter(const T& i){
    int counter=0;
    for(auto cit=Begin(); cit != End(); cit++)
        if((**cit)==i)
            counter++;
    return counter;
}

template <class T>
void Container<T>::addInOrder(T& itm){
    if(first!=nullptr){
        nodo* tmp=first;
        while(tmp->next && (tmp->next->info < itm)){
            tmp=tmp->next;
        }
        if(!tmp->next){
            if(tmp->info > itm)
                first= new nodo(itm,tmp);
            else
                tmp->next=new nodo(itm);
        }
        else {
            tmp->next=new nodo(itm,tmp->next);
        }
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

template <class T>
T* Container<T>::searchAtIndex(unsigned int i){
    if(i>= size())
        return nullptr;
    nodo* att = first;
    for(unsigned int k=0; k<i; k++)
        att=att->next;
    return &(att->info);
}

template<class T>
int Container<T>::size(){
    int counter=0;
    Container<T>::Iterator it=Begin();
    while(it!=End()){
        counter ++;
        ++it;
    }
    return counter;
}

template<class T>
void Container<T>::replace(const T& itm, unsigned int i){
    T* att = searchAtIndex(i);
    *att=itm;
}           //da controllare

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
    return Iterator(first) ;
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

//template <class T>
//bool Container<T>::Iterator::eraseOneAtIndex(unsigned int i){
//    if
//    for(unsigned int k=0; k<i-1; i++)
//        pointed=pointed+1;
//}

#endif // CONTAINER_H
