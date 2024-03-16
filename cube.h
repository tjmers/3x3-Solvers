#pragma once

#include <array>
#include <string>
#include <vector>


// stores the cube in a char array such that the first 9 are white, next are green, orange, red, yellow, blue
class Cube
{

public:

    Cube(const std::string& cube);

    bool isSolved() const;

    // void r(int n);
    // void l(int n);
    // void f(int n);  
    // void b(int n);
    // void u(int n);
    // void d(int n);

    // Cube rC(int n);
    // Cube lC(int n);
    // Cube fC(int n);
    // Cube bC(int n);
    // Cube uC(int n);
    // Cube dC(int n);

private:

    char state[54];
    static constexpr char solved_cube[54] =
    {
        'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W',
        'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G',
        'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',
        'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y',
        'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B',

    };
    
    static bool validate_state(const std::string& cube);

    void move_indicies(std::array<int, 8> indicies, int n);

};