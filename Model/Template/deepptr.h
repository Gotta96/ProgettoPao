#ifndef DEEPTR_H
#define DEEPTR_H

#include <iostream>

//dichiarazione del template

template <class T>
class DeepPtr{
private:
    T* pted;     //T puntato
public:
    DeepPtr(T* =nullptr);   //non esegue copia profonda
    DeepPtr(const DeepPtr&);    //esegue copia profonda
    DeepPtr& operator=(const DeepPtr&);
    T* operator->() const;
    T& operator*() const;
    ~DeepPtr();
    bool operator==(const DeepPtr&) const;
    bool operator!=(const DeepPtr&) const;
    bool operator>(const DeepPtr&) const;
    bool operator<(const DeepPtr&) const;
};

template <class T>
DeepPtr<T>::DeepPtr(T* itm): pted(itm){}

template <class T>
DeepPtr<T>::DeepPtr(const DeepPtr& dptr){
      if(dptr== nullptr)
          pted=nullptr;
      else
          pted=dptr.pted->clone();
}

template <class T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr& dptr){
        if(this != &dptr){
            if(pted)
                delete pted;
            pted = dptr.pted->clone();
    }
    return *this;
}

template <class T>
T* DeepPtr<T>::operator->() const{
       return pted;
}

template <class T>
T& DeepPtr<T>::operator*() const{
        return *pted;
}

template <class T>
DeepPtr<T>::~DeepPtr(){
    if(pted)
        delete pted;      //elimina il T puntato dal mio puntatore con gestione della memoria
}

template <class T>
bool DeepPtr<T>::operator==(const DeepPtr& dptr) const{
    return *pted==*(dptr.pted);
}

template <class T>
bool DeepPtr<T>::operator!=(const DeepPtr& dptr) const{
    return *pted!=*(dptr.pted);
}

template<class T>
bool DeepPtr<T>::operator<(const DeepPtr& dptr) const{
    return *pted<*(dptr.pted);
}

template<class T>
bool DeepPtr<T>::operator>(const DeepPtr& dptr) const{
    return *pted>*(dptr.pted);
}

#endif // DEEPTR_H
