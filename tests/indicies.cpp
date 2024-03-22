// Compilation command: g++ tests\indicies.cpp cube.cpp input_handler.cpp -o tests\solved_indicies.exe -O3 -std=c++20

#include <iostream>

#include "cube.h"
#include "input_handler.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Command usage: ./indicies <filepath>\n";
        return 1;
    }
    Cube solved_cube(input_handler::get_cube_from_file(argv[1]));

    std::cout << "Solved edges: " << solved_cube.edge_index() << "\nSolved Corners: " << solved_cube.corner_index() << '\n';

    return 0;
}