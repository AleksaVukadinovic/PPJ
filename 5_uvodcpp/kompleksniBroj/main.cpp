#include <iostream>
#include "kompleksniBroj.h"

int main(){
    KompleksniBroj kb1(5.0, 2.0);
    KompleksniBroj kb2(2.0, -3.0);

    std::cout << kb1+kb2 << '\n';        

    return 0;
}