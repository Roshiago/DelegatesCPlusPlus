#include <iostream>
#include "src/includes/CDelegates.h"

int print(const char* str) {
    std::cout << str << std::endl;
    return 0;
}

void print_void(const char* str) {
    std::cout << str << std::endl;
}

int valueBy6(int i) {
    return i * 6;
}

void valueBy6_print(int i) {
    std::cout << i * 6 << std::endl;
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

// typedef int(B::* getValueBy10)(int);
typedef ClsMethodDef(getValueBy10, B, int, int);

int main(){
    print_void("==== NON VOID DELEGATES ====");

    CDelegate<int, const char*> deleg;
    deleg += WrapFunc<int, FuncDef(int, const char*), const char*>(print);
    deleg += WrapFunc<int, FuncDef(int, const char*), const char*>(print);
    deleg += WrapFunc<int, FuncDef(int, const char*), const char*>(print);
    // deleg += WrapFunc<int, int(*)(const char*), const char*>(print);
    // deleg += WrapFunc<int, int(*)(const char*), const char*>(print);
    // deleg += WrapFunc<int, int(*)(const char*), const char*>(print);
    /*
    Will be printed HELLO WORLD 3 times
    */
    deleg("HELLO WORLD");

    CDelegate<int, int> delegClass;
    C a;
    B b;
    delegClass += WrapMethod<int, C, getValue, int>(&a, &C::getValue);
    delegClass += WrapMethod<int, B, getValueBy10, int>(&b, &B::getValueBy10);
    std::vector<int> results = delegClass(5);
    /*
    Will be printed: 
        5
        50

    */
    for(auto& i: results) {
        std::cout << i << std::endl;
    }

    CDelegate<int, int> delegClassAndFunc;
    delegClassAndFunc += WrapMethod<int, B, getValueBy10, int>(&b, &B::getValueBy10);
    delegClassAndFunc += WrapFunc<int, int(*)(int), int>(valueBy6);
    results = delegClassAndFunc(5);
    /*
    Will be printed:
        50
        30

    */
    for (auto& i : results) {
        std::cout << i << std::endl;
    }

    print_void("==== VOID DELEGATES ====");

    CDelegate<void, int> voidDelegFunc;

    voidDelegFunc += WrapFunc<void, void(*)(int), int>(valueBy6_print);
    voidDelegFunc += WrapFunc<void, void(*)(int), int>(valueBy6_print);

    voidDelegFunc(5);

    CDelegate<void, const char*> voidDelegFunc1;
    voidDelegFunc1 += WrapFunc<void, void(*)(const char*), const char*>(print_void);

    voidDelegFunc1("hello world");

    return 0;
}