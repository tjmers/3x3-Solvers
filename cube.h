#pragma once

#include <array>
#include <string>
#include <vector>



constexpr unsigned long long operator ""_w(unsigned long long n) {
    return n;
}

constexpr unsigned long long operator ""_g(unsigned long long n) {
    return n + 9;
}

constexpr unsigned long long operator ""_o(unsigned long long n) {
    return n + 18;
}

constexpr unsigned long long operator ""_r(unsigned long long n) {
    return n + 27;
}

constexpr unsigned long long operator ""_y(unsigned long long n) {
    return n + 36;
}

constexpr unsigned long long operator ""_b(unsigned long long n) {
    return n + 45;
}




// stores the cube in a char array such that the first 9 are white, next are green, orange, red, yellow, blue
class Cube
{

public:

    Cube(const std::string& cube);
    Cube(const Cube& other);

    bool isSolved() const;

    void r(int n);
    void l(int n);
    void f(int n);  
    void b(int n);
    void u(int n);
    void d(int n);

    Cube* rC(int n);
    Cube* lC(int n);
    Cube* fC(int n);
    Cube* bC(int n);
    Cube* uC(int n);
    Cube* dC(int n);

    void display() const;
    void write(std::ofstream& ofstream);

    int unique_index() const;

private:

    char cube[54];
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

    void cycle_four(std::array<int, 4> indicies, int n);



    static constexpr std::array<int, 4> r_close_edges = { 1_r, 5_r, 7_r, 3_r };
    static constexpr std::array<int, 4> r_far_edges = { 5_g, 5_w, 3_b, 5_y };
    static constexpr std::array<int, 4> r_close_corners = { 0_r, 2_r, 8_r, 6_r };
    static constexpr std::array<int, 4> r_far_corners_top = { 2_g, 2_w, 6_b, 2_y };
    static constexpr std::array<int, 4> r_far_corners_bottom = { 8_g, 8_w, 0_b, 8_y };

    static constexpr std::array<int, 4> l_close_edges = { 1_o, 5_o, 7_o, 3_o };
    static constexpr std::array<int, 4> l_far_edges = { 3_g, 3_y, 5_b, 3_w };
    static constexpr std::array<int, 4> l_close_corners = { 0_o, 2_o, 8_o, 6_o };
    static constexpr std::array<int, 4> l_far_corners_top = { 0_g, 0_y, 8_b, 0_w };
    static constexpr std::array<int, 4> l_far_corners_bottom = { 6_g, 6_y, 2_b, 6_w };

    static constexpr std::array<int, 4> u_close_edges = { 1_w, 5_w, 7_w, 3_w };
    static constexpr std::array<int, 4> u_far_edges = { 1_g, 1_o, 1_b, 1_r };
    static constexpr std::array<int, 4> u_close_corners = { 0_w, 2_w, 8_w, 6_w };
    static constexpr std::array<int, 4> u_far_corners_left = { 0_g, 0_o, 0_b, 0_r };
    static constexpr std::array<int, 4> u_far_corners_right = { 2_g, 2_o, 2_b, 2_r };

    static constexpr std::array<int, 4> d_close_edges = { 1_y, 5_y, 7_y, 3_y };
    static constexpr std::array<int, 4> d_far_edges = { 7_g, 7_r, 7_b, 7_o };
    static constexpr std::array<int, 4> d_close_corners = { 0_y, 2_y, 8_y, 6_y };
    static constexpr std::array<int, 4> d_far_corners_left = { 6_g, 6_r, 6_b, 6_o };
    static constexpr std::array<int, 4> d_far_corners_right = { 8_g, 8_r, 8_b, 8_o };

    static constexpr std::array<int, 4> f_close_edges = { 1_g, 5_g, 7_g, 3_g };
    static constexpr std::array<int, 4> f_far_edges = { 7_w, 3_r, 1_y, 5_o };
    static constexpr std::array<int, 4> f_close_corners = { 0_g, 2_g, 8_g, 6_g };
    static constexpr std::array<int, 4> f_far_corners_left = { 6_w, 0_r, 2_y, 8_o };
    static constexpr std::array<int, 4> f_far_corners_right = { 8_w, 6_r, 0_y, 2_o };

    static constexpr std::array<int, 4> b_close_edges = { 1_b, 5_b, 7_b, 3_b };
    static constexpr std::array<int, 4> b_far_edges = { 1_w, 3_o, 7_y, 5_r };
    static constexpr std::array<int, 4> b_close_corners = { 0_b, 2_b, 8_b, 6_b };
    static constexpr std::array<int, 4> b_far_corners_left = { 0_w, 6_o, 8_y, 2_r };
    static constexpr std::array<int, 4> b_far_corners_right = { 3_w, 0_o, 6_y, 8_r };
};