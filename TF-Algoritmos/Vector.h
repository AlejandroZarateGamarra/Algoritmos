#pragma once
template <typename T>
class Vector {
    T* elems;
    int cap;//capacidad maxima
    int numElems;//cantidad actual
public:

    class iterator {
        int i;
        T* elems;
    public:
        iterator(int i = 0, T* elems = nullptr)
            : i(i), elems(elems) {}
        void operator ++ () {
            i++;
        }
        T operator * () {
            return elems[i];
        }
        bool operator != (iterator b) {
            return this->i != b.i;
        }
    };

    iterator begin() {
        return iterator(0, elems);
    }
    iterator end() {
        return iterator(cap, nullptr);
    }

    Vector(int cap = 10)
        : elems(new T[cap]), cap(cap) {
        numElems = 0;
    }
    ~Vector() {}
    T operator[] (int i) const {//devolución
        return elems[i];
    }
    T& operator[] (int i) {// *(arr+0)=10//asignar
        return elems[i];
    }
    void autoincrement() {
        cap += 1;
        T* aux = new T[cap];
        for (size_t i = 0; i < numElems; ++i) {
            aux[i] = elems[i];
        }
        delete elems;
        elems = aux;
    }
    void push_back(T element) {
        if (numElems == cap)
            autoincrement();
        if (numElems < cap)
            elems[numElems++] = element;
    }
    int getSize() {
        return numElems;
    }
};