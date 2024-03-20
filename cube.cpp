#include "cube.h"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

Cube::Cube(const std::string& cube) 
{
    if (validate_state(cube))
    {
        for (int i = 0; i < 54; ++i)
            (this->cube)[i] = cube[i];
    }
    else
    {
        throw std::invalid_argument("Invalid cube starting position");
    }
}

Cube::Cube(const Cube& other)
{
    std::memcpy(cube, other.cube, 54 * sizeof(char));
}



#pragma region CUBE_VALIDATION



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
    int positions[12] = { 1_w, 3_w, 5_w, 7_w, 1_y, 3_y, 5_y, 7_y, 3_g, 5_g, 3_b, 5_b };
    int off_positions[12] = { 1_b, 1_o, 1_r, 1_g, 7_g, 7_o, 7_r, 7_b, 5_o, 3_r, 5_r, 3_o };

    for (int i = 0; i < 12; ++i)
    {
        if (cube[positions[i]] == 'W' || cube[positions[i]] == 'Y' ||
                (cube[off_positions[i]] != 'W' && cube[off_positions[i]] != 'Y' &&
                (cube[positions[i] == 'G' || cube[positions[i] == 'B']])))
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

        while (third_corner == first_corner || third_corner == second_corner || corners[third_corner] == third_corner)
            ++third_corner;

        int temp = corners[first_corner];
        corners[first_corner] = corners[third_corner];
        corners[third_corner] = corners[second_corner];
        corners[second_corner] = temp; 

        solved_corners += (corners[first_corner] == first_corner) + (corners[second_corner] == second_corner) + (corners[third_corner] == third_corner);
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

    if ((c1 == 'G' || c2 == 'G') && (c1 == 'O' || c2 == 'O'))
        return 8;

    if ((c1 == 'G' || c2 == 'G') && (c1 == 'R' || c2 == 'R'))
        return 9;
    
    if ((c1 == 'B' || c2 == 'B') && (c1 == 'R' || c2 == 'R'))
        return 10;

    if ((c1 == 'B' || c2 == 'B') && (c1 == 'O' || c2 == 'O'))
        return 11;

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
    case 8:
        return { cube[3_g], cube[5_o] };
    case 9:
        return { cube[5_g], cube[3_r] };
    case 10:
        return { cube[3_b], cube[5_r] };
    case 11:
        return { cube[5_b], cube[3_o] };
    default:
        throw std::invalid_argument("Invalid edge index to be converted to a color");
    }
}

bool edge_parity(const std::string& cube)
{

    int edges[12];

    for (int i = 0; i < 12; ++i)
    {
        std::pair<char, char> current_edge = get_edge_colors(cube, i);
        edges[i] = get_edge_index(current_edge.first, current_edge.second);
        // std::cout << current_edge.first << current_edge.second << edges[i] << '\n';
    }

    int solved_edges = 0;

    for (int i = 0; i < 12; ++i)
    {
        if (edges[i] == i)
            ++solved_edges;
    }

    // std::cout << "Solved Edges: " << solved_edges << '\n';

    while (solved_edges < 10)
    {
        int first_edge = 0;
        while (edges[first_edge] == first_edge)
            ++first_edge; // find the first edge that isn't solved

        int second_edge = edges[first_edge];

        int third_edge = edges[second_edge];

        while (third_edge == first_edge || third_edge == second_edge || third_edge == edges[third_edge])
            ++third_edge;

        int temp = edges[first_edge];
        edges[first_edge] = edges[third_edge];
        edges[third_edge] = edges[second_edge];
        edges[second_edge] = temp;

        solved_edges += (edges[first_edge] == first_edge) + (edges[second_edge] == second_edge) + (edges[third_edge] == third_edge);
    }

    return solved_edges != 12;


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
        if (cube[i] != solved_cube[i])
            return false;

    return true;
}


#pragma region MOVE_COLORS

void Cube::cycle_four(std::array<int, 4> indicies, int n)
{
    switch (n)
    {
    case 1:
    {
        int temp = cube[indicies[0]];
        cube[indicies[0]] = cube[indicies[3]];
        cube[indicies[3]] = cube[indicies[2]];
        cube[indicies[2]] = cube[indicies[1]];
        cube[indicies[1]] = temp;
    }
        break;
    case 2:
    {
        int temp = cube[indicies[0]];
        cube[indicies[0]] = cube[indicies[2]];
        cube[indicies[2]] = temp;
        temp = cube[indicies[1]];
        cube[indicies[1]] = cube[indicies[3]];
        cube[indicies[3]] = temp;
    }
        break;
    case -1:
    {
        int temp = cube[indicies[0]];
        cube[indicies[0]] = cube[indicies[1]];
        cube[indicies[1]] = cube[indicies[2]];
        cube[indicies[2]] = cube[indicies[3]];
        cube[indicies[3]] = temp;
    }
        break;
    default:
        throw std::invalid_argument("n must be -1, 1, or 2");
    }
}

void Cube::r(int n)
{
    cycle_four(r_close_edges, n);
    cycle_four(r_far_edges, n);
    cycle_four(r_close_corners, n);
    cycle_four(r_far_corners_top, n);
    cycle_four(r_far_corners_bottom, n);
}


Cube* Cube::rC(int n)
{
    Cube* new_cube = new Cube(*this);
    new_cube->cycle_four(r_close_edges, n);
    new_cube->cycle_four(r_far_edges, n);
    new_cube->cycle_four(r_close_corners, n);
    new_cube->cycle_four(r_far_corners_top, n);
    new_cube->cycle_four(r_far_corners_bottom, n);
    return new_cube;
}

void Cube::l(int n)
{
    cycle_four(l_close_edges, n);
    cycle_four(l_far_edges, n);
    cycle_four(l_close_corners, n);
    cycle_four(l_far_corners_top, n);
    cycle_four(l_far_corners_bottom, n);
}


Cube* Cube::lC(int n)
{
    Cube* new_cube = new Cube(*this);
    new_cube->cycle_four(l_close_edges, n);
    new_cube->cycle_four(l_far_edges, n);
    new_cube->cycle_four(l_close_corners, n);
    new_cube->cycle_four(l_far_corners_top, n);
    new_cube->cycle_four(l_far_corners_bottom, n);
    return new_cube;
}


void Cube::u(int n)
{
    cycle_four(u_close_edges, n);
    cycle_four(u_far_edges, n);
    cycle_four(u_close_corners, n);
    cycle_four(u_far_corners_left, n);
    cycle_four(u_far_corners_right, n);
}


Cube* Cube::uC(int n)
{
    Cube* new_cube = new Cube(*this);
    new_cube->cycle_four(u_close_edges, n);
    new_cube->cycle_four(u_far_edges, n);
    new_cube->cycle_four(u_close_corners, n);
    new_cube->cycle_four(u_far_corners_left, n);
    new_cube->cycle_four(u_far_corners_right, n);
    return new_cube;
}


void Cube::d(int n)
{
    cycle_four(d_close_edges, n);
    cycle_four(d_far_edges, n);
    cycle_four(d_close_corners, n);
    cycle_four(d_far_corners_left, n);
    cycle_four(d_far_corners_right, n);
}


Cube* Cube::dC(int n)
{
    Cube* new_cube = new Cube(*this);
    new_cube->cycle_four(d_close_edges, n);
    new_cube->cycle_four(d_far_edges, n);
    new_cube->cycle_four(d_close_corners, n);
    new_cube->cycle_four(d_far_corners_left, n);
    new_cube->cycle_four(d_far_corners_right, n);
    return new_cube;
}


void Cube::f(int n)
{
    cycle_four(f_close_edges, n);
    cycle_four(f_far_edges, n);
    cycle_four(f_close_corners, n);
    cycle_four(f_far_corners_left, n);
    cycle_four(f_far_corners_right, n);
}

Cube* Cube::fC(int n)
{
    Cube* new_cube = new Cube(*this);
    new_cube->cycle_four(f_close_edges, n);
    new_cube->cycle_four(f_far_edges, n);
    new_cube->cycle_four(f_close_corners, n);
    new_cube->cycle_four(f_far_corners_left, n);
    new_cube->cycle_four(f_far_corners_right, n);
    return new_cube;
}

void Cube::b(int n)
{
    cycle_four(b_close_edges, n);
    cycle_four(b_far_edges, n);
    cycle_four(b_close_corners, n);
    cycle_four(b_far_corners_left, n);
    cycle_four(b_far_corners_right, n);
}

Cube* Cube::bC(int n)
{
    Cube* new_cube = new Cube(*this);
    new_cube->cycle_four(b_close_edges, n);
    new_cube->cycle_four(b_far_edges, n);
    new_cube->cycle_four(b_close_corners, n);
    new_cube->cycle_four(b_far_corners_left, n);
    new_cube->cycle_four(b_far_corners_right, n);
    return new_cube;
}


#pragma endregion


void Cube::display() const
{
    for (int i = 0; i < 9; i += 3)
        std::cout << "        " << cube[i] << ' '
                                << cube[i + 1] << ' ' 
                                << cube[i + 2] << '\n';

    std::cout << '\n';
    for (int i = 0; i < 9; i += 3)
    {
    std::cout << cube[0_o + i] << ' ' << cube[1_o + i] << ' ' << cube[2_o + i] << "   "
              << cube[0_g + i] << ' ' << cube[1_g + i] << ' ' << cube[2_g + i] << "   "
              << cube[0_r + i] << ' ' << cube[1_r + i] << ' ' << cube[2_r + i] << "   "
              << cube[0_b + i] << ' ' << cube[1_b + i] << ' ' << cube[2_b + i] << '\n';

    }
    
    std::cout << '\n';
    for (int i = 0_y; i < 0_y + 9; i += 3)
        std::cout << "        " << cube[i] << ' '
                                << cube[i + 1] << ' '
                                << cube[i + 2] << '\n';

}

void Cube::write(std::ofstream& ofstream)
{
    ofstream << cube;
}


int Cube::unique_index() const
{
    return 0;
}