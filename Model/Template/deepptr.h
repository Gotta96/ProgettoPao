#ifndef DEEPTR_H
#define DEEPTR_H

#include <iostream>

//template <class T>
//class DeepPtr;

//template <class T>
//std::ostream& operator<<(std::ostream&, const DeepPtr<T>&);

//dichiarazione del template

template <class T>
class DeepPtr{
//    friend std::ostream& operator<< <T>(std::ostream&, const DeepPtr<T>&);
private:
    T* pted;     //T puntato
public:
    DeepPtr(const T* const =nullptr);
    DeepPtr(const DeepPtr&);
    T* operator->() const;
    T& operator*() const;
    ~DeepPtr();
    DeepPtr& operator=(const DeepPtr&);
    bool operator==(const DeepPtr&) const;
    bool operator!=(const DeepPtr&) const;
    std::string printDptr() const;
};

template <class T>
DeepPtr<T>::DeepPtr(const T* const itm){
  if(itm)
      pted=itm->clone();
  else pted=nullptr;
}


template <class T>
DeepPtr<T>::DeepPtr(const DeepPtr& dptr){
      pted=dptr->clone();
}

template <class T>
DeepPtr<T>::~DeepPtr(){
    if(pted)
        delete pted;      //elimina il T puntato dal mio puntatore con gestione della memoria
}

template <class T>
T* DeepPtr<T>::operator->() const{
       return pted;
}

template <class T>
T& DeepPtr<T>::operator*() const{
        return *pted;   //controllo se l'elemento puntato dal nostro Deeptr esiste, in caso positivo ritorno l'oggetto puntato altrimenti oggetto vuoto
}

template <class T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr& dptr){
        if(this != &dptr){
            if(pted)
                delete pted;
            pted = dptr->clone();
    }
    return *this;
}

template <class T>
bool DeepPtr<T>::operator==(const DeepPtr& dptr) const{
    return *pted==*(dptr.pted);
}

template <class T>
bool DeepPtr<T>::operator!=(const DeepPtr& dptr) const{
    return *pted!=*(dptr.pted);
}

template <class T>
std::string DeepPtr<T>::printDptr() const{
    return pted->print();
}

//template <class T>
//std::ostream& operator<<(std::ostream& os, const DeepPtr<T>& dptr){
//    return os << *dptr;
//}

/*in relazione riportare il polimorfismo dovuto alla gerarchia che noi creiamo
 * che si riperquote sul nostro template*/

//21/18/18 aggiunto operatore di output per Deepptr

#endif // DEEPTR_H
