#ifndef BASIC_BINARY_CLASS
#define BASIC_BINARY_CLASS

#include<iostream>
#include<fstream>
#include<sstream>
#include<QByteArray>

class Bint{
public:
    int data;
    Bint(){}
    Bint(int x): data(x){}
    explicit operator int(){
        return data;
    }
    friend std::istream& operator >>(std::istream& fin, Bint& x){
        fin.read(reinterpret_cast<char*>(&x.data),sizeof(int));
        return fin;
    }
    friend std::ostream& operator <<(std::ostream& fout, Bint& x){
        fout.write(reinterpret_cast<char*>(&x.data),sizeof(int));
        return fout;
    }
};

template<int size>
class Bchar{
public:
    char data[size];
    Bchar(){}
    Bchar(char* x){
        for (int i=0;i<size;i++) data[i]=x[i];
    }
    explicit operator char*(){
        return data;
    }
    friend std::istream& operator >>(std::istream& fin, Bchar& x){
        for (int i=0;i<size;i++) fin>>x.data[i];
        return fin;
    }
    friend std::ostream& operator <<(std::ostream& fout, Bchar& x){
        for (int i=0;i<size;i++) fout<<x.data[i];
        return fout;
    }
};


#endif
