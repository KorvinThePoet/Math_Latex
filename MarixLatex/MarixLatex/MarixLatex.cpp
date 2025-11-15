
#include <iostream>
#include "lama.h"
int main()
{
    std::cout << "Hello World!\n";
    lama::matrix a(10,10,1);
    a.print();
    a.print(1);
}
