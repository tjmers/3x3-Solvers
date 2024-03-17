// compilation command: g++ input_handler.cpp cube.cpp tests\validation.cpp -o tests\validation.exe -O3 -std=c++20

#include <iostream>

#include "../cube.h"
#include "../input_handler.h"

int main(int argc, char** argv)
{

    if (argc != 2)
    {
        std::cout << "Command Usage: ./validation <filepath>\n";
        return 1;
    }

    std::string cube_string = input_handler::get_cube_from_file(argv[1]);

    try
    {
        Cube cube(cube_string);
        std::cout << "GOOD\n";
    }
    catch (std::exception e)
    {
        std::cout << "NO GOOD\n";
    }




    return 0;
}