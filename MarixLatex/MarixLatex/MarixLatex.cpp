
#include <iostream>
#include "lama.h"
int main()
{

    lama::matrix a({ {1,1,1,2} });
    lama::matrix b(1,1,0);
    lama::matrix c = lama::solve_solae(a, b,1);
}
