#include "cube.h"

#include <algorithm>
#include <cstring>
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

#pragma region CUBE_VALIDATOR


inline bool opposites(char c1, char c2)
{
    switch (c1)
    {
    case 'W':
        return c2 == 'Y';
    case 'Y':
        return c2 == 'W';
    case 'R':
        return c2 == 'O';
    case 'O':
        return c2 == 'R';
    case 'B':
        return c2 == 'G';
    case 'G':
        return c2 == 'B';
    default:
        throw std::invalid_argument("Invalid color passed into opposites");
    }
}

inline bool are_unique_corners(char c1, char c2, char c3, char c4, char c5, char c6)
{
    return c1 != c2 && c1 != c3 && c4 != c5 && c4 != c6 && c2 != c3 && c5 != c6 && 
           !opposites(c1, c2) && !opposites(c1, c3) && !opposites(c2, c3) &&
           !opposites(c4, c5) && !opposites(c4, c6) && !opposites(c5, c6) &&
        !((c1 == c4 || c1 == c5 || c1 == c6) &&
          (c2 == c4 || c2 == c5 || c2 == c6) &&
          (c3 == c4 || c3 == c5 || c3 == c6));
}

inline bool are_unique_edges(char c1, char c2, char c3, char c4)
{
    return c1 != c2 && c3 != c4 &&
          !opposites(c1, c2) && !opposites(c3, c4) &&
        !((c1 == c3 || c1 == c4) &&
          (c2 == c3 || c2 == c4));
}

bool validate_edges(const std::string& cube)
{

    int nGoodEdges = 0;
    int positions[8] = { 1_w, 3_w, 5_w, 7_w, 1_y, 3_y, 5_y, 7_y };
    int off_positions[8] = { 1_b, 1_o, 1_r, 1_g, 7_g, 7_o, 7_r, 7_b };

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

    std::vector<std::pair<char, char>> edges;
    for (int i = 0; i < 8; ++i)
    {
        // std::cout << cube[positions[i]] << cube[off_positions[i]] << '\n';
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
                std::cout << '(' << i << ", " << n << ")\n";
                std::cout << '(' << edges[n].first << ", " << edges[n].second << "), (" << edges[i].first << ", " << edges[i].second << ")\n";
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

    // for (auto a : corners)
    // {
    //     std::cout << '(' << std::get<0>(a) << ", " << std::get<1>(a) << ", " << std::get<2>(a) << ") " ;
    // }
    // std::cout << '\n';

    while (corners.size() > 1)
    {
        int n = corners.size() - 1;
        for (int i = 0; i < n; ++i)
        {
            if (!are_unique_corners(std::get<0>(corners[n]), std::get<1>(corners[n]), std::get<2>(corners[n]),
                                  std::get<0>(corners[i]), std::get<1>(corners[i]), std::get<2>(corners[i])))
                {
                    std::cout << "Unique corner test fails\n";
                    std::cout << "(" << std::get<0>(corners[n]) << ", " << std::get<1>(corners[n]) << ", " << std::get<2>(corners[n]) << "), (" << std::get<0>(corners[i]) << ", " << std::get<1>(corners[i]) << ", " << std::get<2>(corners[i]) << ")\n";
                    return false;
                }
        }
        corners.pop_back();
    }

    return true;
}

int get_corner_index(char c1, char c2, char c3)
{
    if ((c1 == 'W' || c2 == 'W' || c3 == 'W') &&
        (c1 == 'O' || c2 == 'O' || c3 == 'O') &&
        (c1 == 'B' || c2 == 'B' || c3 == 'B'))
        return 0;

    if ((c1 == 'W' || c2 == 'W' || c3 == 'W') &&
        (c1 == 'R' || c2 == 'R' || c3 == 'R') &&
        (c1 == 'B' || c2 == 'B' || c3 == 'B'))
        return 1;
    
    if ((c1 == 'W' || c2 == 'W' || c3 == 'W') &&
        (c1 == 'O' || c2 == 'O' || c3 == 'O') &&
        (c1 == 'G' || c2 == 'G' || c3 == 'G'))
        return 2;

    if ((c1 == 'W' || c2 == 'W' || c3 == 'W') &&
        (c1 == 'R' || c2 == 'R' || c3 == 'R') &&
        (c1 == 'G' || c2 == 'G' || c3 == 'G'))
        return 3;

    if ((c1 == 'Y' || c2 == 'Y' || c3 == 'Y') &&
        (c1 == 'G' || c2 == 'G' || c3 == 'G') &&
        (c1 == 'O' || c2 == 'O' || c3 == 'O'))
        return 4;

    if ((c1 == 'Y' || c2 == 'Y' || c3 == 'Y') &&
        (c1 == 'G' || c2 == 'G' || c3 == 'G') &&
        (c1 == 'R' || c2 == 'R' || c3 == 'R'))
        return 5;

    if ((c1 == 'Y' || c2 == 'Y' || c3 == 'Y') &&
        (c1 == 'B' || c2 == 'B' || c3 == 'B') &&
        (c1 == 'O' || c2 == 'O' || c3 == 'O'))
        return 6;

    if ((c1 == 'Y' || c2 == 'Y' || c3 == 'Y') &&
        (c1 == 'B' || c2 == 'B' || c3 == 'B') &&
        (c1 == 'R' || c2 == 'R' || c3 == 'R'))
        return 7;

    return -1;
}


std::tuple<char, char, char> get_corner_colors(const std::string& cube, int i)
{
    switch (i)
    {
    case 0:
        return { cube[0_w], cube[0_o], cube[2_b] };
    case 1:
        return { cube[2_w], cube[2_r], cube[0_b] };
    case 2:
        return { cube[6_w], cube[2_o], cube[0_g] };
    case 3:
        return { cube[8_w], cube[0_r], cube[2_g] };
    case 4:
        return { cube[0_y], cube[6_g], cube[8_o] };
    case 5:
        return { cube[2_y], cube[8_g], cube[6_r] };
    case 6:
        return { cube[6_y], cube[8_b], cube[6_o] };
    case 7:
        return { cube[8_y], cube[6_b], cube[8_r] };
    default:
        throw std::invalid_argument("Invalid corner index");
    }
}

bool corner_parity(const std::string& cube)
{
    int corners[8];

    for (int i = 0; i < 8; ++i)
    {
        std::tuple<char, char, char> current_corners = get_corner_colors(cube, i);
        corners[i] = get_corner_index(std::get<0>(current_corners), std::get<1>(current_corners), std::get<2>(current_corners));
        // std::cout << corners[i] << '\n';
    }

    int solved_corners = 0;

    for (int i = 0; i < 8; ++i)
    {
        if (corners[i] == i)
            ++solved_corners;
    }

    // std::cout << "Solved Corners: " << solved_corners << '\n';

    while (solved_corners < 6)
    {
        int first_corner = 0;
        while (corners[first_corner] == first_corner)
            ++first_corner; // find the first corner that isn't solved

        int second_corner = corners[first_corner];

        int third_corner = corners[second_corner];

        int temp = corners[first_corner];
        corners[first_corner] = corners[third_corner];
        corners[third_corner] = corners[second_corner];
        corners[second_corner] = temp; 
    }

    return solved_corners != 8;
}

int get_edge_index(char c1, char c2)
{
    if ((c1 == 'W' || c2 == 'W') && (c1 == 'B' || c2 == 'B'))
        return 0;

    if ((c1 == 'W' || c2 == 'W') && (c1 == 'O' || c2 == 'O'))
        return 1;

    if ((c1 == 'W' || c2 == 'W') && (c1 == 'R' || c2 == 'R'))
        return 2;

    if ((c1 == 'W' || c2 == 'W') && (c1 == 'G' || c2 == 'G'))
        return 3;

    if ((c1 == 'Y' || c2 == 'Y') && (c1 == 'G' || c2 == 'G'))
        return 4;

    if ((c1 == 'Y' || c2 == 'Y') && (c1 == 'O' || c2 == 'O'))
        return 5;

    if ((c1 == 'Y' || c2 == 'Y') && (c1 == 'R' || c2 == 'R'))
        return 6;

    if ((c1 == 'Y' || c2 == 'Y') && (c1 == 'B' || c2 == 'B'))
        return 7;

    return -1;
}

std::pair<char, char> get_edge_colors(const std::string& cube, int i)
{
    switch (i)
    {
    case 0:
        return { cube[1_w], cube[1_b] };
    case 1:
        return { cube[3_w], cube[1_o] };
    case 2:
        return { cube[5_w], cube[1_r] };
    case 3:
        return { cube[7_w], cube[1_g] };
    case 4:
        return { cube[1_y], cube[7_g] };
    case 5:
        return { cube[3_y], cube[7_o] };
    case 6:
        return { cube[5_y], cube[7_r] };
    case 7:
        return { cube[7_y], cube[7_b] };
    default:
        throw std::invalid_argument("Invalid edge index to be converted to a color");
    }
}

bool edge_parity(const std::string& cube)
{

    int edges[8];

    for (int i = 0; i < 8; ++i)
    {
        std::pair<char, char> current_edge = get_edge_colors(cube, i);
        edges[i] = get_edge_index(current_edge.first, current_edge.second);
        // std::cout << current_edge.first << current_edge.second << edges[i] << '\n';
    }

    int solved_edges = 0;

    for (int i = 0; i < 8; ++i)
    {
        if (edges[i] == i)
            ++solved_edges;
    }

    // std::cout << "Solved Edges: " << solved_edges << '\n';

    while (solved_edges < 6)
    {
        int first_edge = 0;
        while (edges[first_edge] == first_edge)
            ++first_edge; // find the first edge that isn't solved

        int second_edge = edges[first_edge];

        int third_edge = edges[second_edge];

        int temp = edges[first_edge];
        edges[first_edge] = edges[third_edge];
        edges[third_edge] = edges[second_edge];
        edges[second_edge] = temp; 
    }

    return solved_edges != 8;


}

bool validate_parity(const std::string& cube)
{
    return corner_parity(cube) == edge_parity(cube);
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

    if (!validate_parity(cube))
    {
        std::cout << "Parity failed\n";
        return false;
    }
    

    return true;
}

#pragma endregion

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