#include <iostream>
#include "CDelegates.h"

int print(const char* str) {
    std::cout << str << std::endl;
    return 0;
}

class C {
public:
    int getValue(int i) {
        return i;
    }
};

typedef int(C::* getValue)(int);

class B {
public:
    int getValueBy10(int i) {
        return i*10;
    }
};

typedef int(B::* getValueBy10)(int);

int main(){
    CDelegate<int, const char*> deleg;
    deleg += WrapFunc<int, int(*)(const char*), const char*>(print);
    deleg += WrapFunc<int, int(*)(const char*), const char*>(print);
    deleg += WrapFunc<int, int(*)(const char*), const char*>(print);
    /*
    Will be printed HELLO WORLD 3 times
    */
    deleg("HELLO WORLD");

    CDelegate<int, int> delegClass;
    C a;
    B b;
    delegClass += WrapMethod<int, C, getValue, int>(&a, &C::getValue);
    delegClass += WrapMethod<int, B, getValueBy10, int>(&b, &B::getValueBy10);
    std::list<int> results = delegClass(5);
    /*
    Will be printed: 
        5
        50
        
    */
    for (std::list<int>::iterator i = results.begin(); i != results.end(); i++) {
        std::cout << *i << std::endl;
    }

    return 0;
}