#include <iostream>
#include "CDelegates.h"

int print(const char* str) {
    std::cout << str << std::endl;
    return 0;
}

int main(){
    CDelegate<int, const char*> deleg;
    deleg += WrapFunc<int, int(*)(const char*), const char*>(print);
    deleg += WrapFunc<int, int(*)(const char*), const char*>(print);
    deleg += WrapFunc<int, int(*)(const char*), const char*>(print);
    /*
    Will be printed HELLO WORLD 3 times
    */
    deleg("HELLO WORLD");
    return 0;
}