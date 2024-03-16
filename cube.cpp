#include "cube.h"

#include <iostream>
#include <stdexcept>

Cube::Cube(const std::string& cube) 
{
    if (validate_state(cube))
    {
        for (int i = 0; i < 54; ++i)
            state[i] = cube[i];
    }
    else
    {
        throw std::invalid_argument("Invalid cube starting position");
    }
}

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

inline bool are_unique_corners(char c1, char c2, char c3, char c4, char c5, char c6)
{
    return c1 != c2 && c1 != c3 && c4 != c5 && c4 != c6 && 
        !((c1 == c4 || c1 == c5 || c1 == c6) &&
          (c2 == c4 || c2 == c5 || c2 == c6) &&
          (c3 == c4 || c3 == c5 || c3 == c6));
}

inline bool are_unique_edges(char c1, char c2, char c3, char c4)
{
    return c1 != c2 && c3 != c4 &&
        !((c1 == c3 || c1 == c4) &&
          (c2 == c3 || c2 == c4));
}

bool validate_edges(const std::string& cube)
{

    int nGoodEdges = 0;
    int positions[8] = { 1_w, 3_w, 5_w, 7_w, 1_y, 3_y, 5_y, 7_y };
    int off_positions[8] = { 2_b, 2_o, 2_r, 2_g, 7_g, 7_o, 7_r, 7_b };

    for (int i : positions)
    {
        if (cube[i] == 'W' || cube[i] == 'Y')
            ++nGoodEdges;
    }

    if (nGoodEdges % 2 != 0)
    {
        std::cout << "Good edges test fail\n";
        return false;
    }

    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < 8; ++i)
    {
        edges.push_back({ cube[positions[i]], cube[off_positions[i]] });
    }

    while (edges.size() > 1)
    {
        int n = edges.size() - 1;
        for (int i = 0; i < n; ++i)
        {
            if (!are_unique_edges(edges[n].first, edges[n].second,
                                  edges[i].first, edges[i].second))
            {
                std::cout << "Unique edges test fail\n";
                return false;
            }
        }
        edges.pop_back();
    }

    return true;
}

bool validate_corners(const std::string& cube)
{

    constexpr int corner_indicies[] = { 0_w, 0_o, 2_b, 2_w, 0_b, 2_r,
                                        6_w, 0_g, 2_o, 8_w, 0_r, 2_g,
                                        0_y, 8_o, 6_g, 2_y, 8_g, 6_r,
                                        6_y, 8_b, 6_o, 8_y, 8_r, 6_b };

    int total_corner_orientations = 0;

    for (int i = 0; i < 24; ++i)
    {
        int cur_color = cube[corner_indicies[i]];
        if (cur_color == 'Y' || cur_color == 'W')
            total_corner_orientations += i % 3;
    }

    if (total_corner_orientations % 3 != 0)
        return false;

    std::vector<std::tuple<char, char, char>> corners;
    for (int i = 0; i < 24; i += 3)
    {
        corners.push_back({cube[corner_indicies[i]], cube[corner_indicies[i + 1]], cube[corner_indicies[i + 2]]});
    }

    while (corners.size() > 1)
    {
        int n = corners.size() - 1;
        for (int i = 0; i < n; ++i)
        {
            if (!are_unique_corners(std::get<0>(corners[n]), std::get<1>(corners[n]), std::get<2>(corners[n]),
                                  std::get<0>(corners[i]), std::get<1>(corners[i]), std::get<2>(corners[i])))
                return false;
        }
        corners.pop_back();
    }

    return true;
}

bool Cube::validate_state(const std::string& cube)
{
    if (cube.size() != 54)
    {
        std::cout << cube << '\n';
        std::cout << "Size fails\n";
        return false;
    }



    if (cube[4_w] != 'W' || cube[4_g] != 'G' || cube[4_o] != 'O' || cube[4_r] != 'R' || cube[4_y] != 'Y' || cube[4_b] != 'B')
    {
        std::cout << "Centers Fail\n";
        return false;
    }

    if (!validate_edges(cube))
    {
        std::cout << "Edges fail\n";
        return false;
    }
    
    if (!validate_corners(cube))
    {
        std::cout << "Corners fail\n";
        return false;
    }

    

    return true;
}

bool Cube::isSolved() const
{
    for (int i = 0; i < 54; ++i)
        if (state[i] != solved_cube[i])
            return false;

    return true;
}

void Cube::move_indicies(std::array<int, 8> indicies, int n)
{

}


// void Cube::r(int n)
// {
//     // move edges
//     std::array<int, 8> indicies = { 27, 28, 29, 30, 32, 33, 34, 35 };

//     move_indicies(indicies, n);
// }