// compilation command: g++ cube.cpp input_handler.cpp tests\display.cpp -o tests\display.exe -O3 -std=c++20


#include <iostream>

#include "../input_handler.h"
#include "../cube.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Command usage: ./display <filepath>\n";
        return 1;
    }

    Cube cube(input_handler::get_cube_from_file(argv[1]));
    cube.display();

    return 0;
}