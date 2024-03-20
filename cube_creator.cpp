// Compilation command: g++ cube_creator.cpp cube.cpp input_handler.cpp -o cube_creator.exe -O3 -std=c++20

#include <cstring>
#include <fstream>
#include <iostream>

#include "input_handler.h"
#include "cube.h"


int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cerr << "Command use: ./cube_creator <moves> <output_file>\n";
        return 1;
    }

    Cube cube(input_handler::get_cube_from_file("inputs/solved.txt"));

    int n = strlen(argv[1]);
    for (int i = 0; i < n; ++i)
    {
        char c = argv[1][i];
        int a = 1;
        if (i + 1 != n)
        {
            if (argv[1][i + 1] == '\'')
            {
                a = -1;
                ++i;
            }
            if (argv[1][i + 1] == '2')
            {
                a = 2;
                ++i;
            }
        }

        switch (c)
        {
            case 'R':
                cube.r(a);
                break;
            case 'L':
                cube.l(a);
                break;
            case 'U':
                cube.u(a);
                break;
            case 'D':
                cube.d(a);
                break;
            case 'F':
                cube.f(a);
                break;
            case 'B':
                cube.b(a);
                break;
            default:
                throw std::invalid_argument("Unrecognized character :" + c);
        }
    }
    std::ofstream output_file(argv[2]);
    cube.write(output_file);
    output_file.close();

    return 0;
}