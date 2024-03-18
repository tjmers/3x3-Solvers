// Compilation command: g++ cube.cpp input_handler.cpp tests\turns.cpp -o tests\turns.exe -O3 -std=c++20

#include <iostream>

#include "../cube.h"
#include "../input_handler.h"

void t_perm(Cube& cube);


int main(int argc, char** argv)
{

    Cube cube(input_handler::get_cube_from_file("inputs\\solved.txt"));

    cube.display();

    cube.r(1);
    cube.display();

    cube.r(-1);
    cube.display();

    Cube* cube2 = cube.lC(1);
    cube2->l(-1);
    t_perm(*cube2);

    cube.display();
    cube2->display();
    
    delete cube2;

    std::cout << "Expected Order: Solved, R, Solved, Solved, TPerm\n";

    return 0;
}



void t_perm(Cube& cube)
{
    cube.r(1);
    cube.u(1);
    cube.r(-1);
    cube.u(-1);
    cube.r(-1);
    cube.f(1);
    cube.r(2);
    cube.u(-1);
    cube.r(-1);
    cube.u(-1);
    cube.r(1);
    cube.u(1);
    cube.r(-1);
    cube.f(-1);
}