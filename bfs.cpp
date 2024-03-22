// Compilation command: g++ bfs.cpp cube.cpp input_handler.cpp -o bfs.exe -O3 -std=c++20

#include <iostream>
#include <queue>
#include <unordered_set>

#include "cube.h"
#include "input_handler.h"

std::string get_solution(Cube* starting_position);
void add_all(std::queue<std::pair<std::pair<Cube*, std::pair<long long, long long>>, std::string>>& bfs,
             std::unordered_set<long long>& corners, std::unordered_set<long long>& edges,
             const std::pair<std::pair<Cube*, std::pair<long long, long long>>, std::string>& current);

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Command usage: ./bfs <filepath>\n";
        return 1;
    }

    Cube* starting = new Cube(input_handler::get_cube_from_file(argv[1]));


    std::string solution = get_solution(starting);

    


    std::cout << "Solution: " << solution << '\n';

    return 0;
}




std::string get_solution(Cube* starting_position)
{
    std::queue<std::pair<std::pair<Cube*, std::pair<long long, long long>>, std::string>> bfs;
    
    std::unordered_set<long long> corners;
    std::unordered_set<long long> edges;

    long long starting_edges = starting_position->edge_index();
    long long starting_corners = starting_position->corner_index();
    bfs.push( { { starting_position, { starting_edges, starting_corners } } , "" } );

    corners.insert(starting_corners);
    edges.insert(starting_edges);

    int depth = 0;

    while (true)
    {
        std::pair<std::pair<Cube*, std::pair<long, long>>, std::string> current = bfs.front();

        if (current.first.first->is_solved(current.first.second.first, current.first.second.second))
        {
            while (!bfs.empty())
            {
                auto cleanup = bfs.front();
                delete cleanup.first.first;
                bfs.pop();
            }
            return current.second;
        }


        if (current.second.size() > depth)
        {
            depth = current.second.size();
            std::cout << "Depth: " << depth / 2 << '\n';
        }

        add_all(bfs, corners, edges, current);
        delete current.first.first;
        bfs.pop();
    }
}



void add_all(std::queue<std::pair<std::pair<Cube*, std::pair<long long, long long>>, std::string>>& bfs,
             std::unordered_set<long long>& corners, std::unordered_set<long long>& edges,
             const std::pair<std::pair<Cube*, std::pair<long long, long long>>, std::string>& current)
{
    std::string str = current.second;
    Cube* cube = nullptr;
    long long ei, ci;

    cube = current.first.first->rC(1);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('R');
        str.push_back(' ');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;

    cube = current.first.first->rC(2);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('R');
        str.push_back('2');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;
    
    cube = current.first.first->rC(-1);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('R');
        str.push_back('\'');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;

    cube = current.first.first->lC(1);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('L');
        str.push_back(' ');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;

    cube = current.first.first->lC(2);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('L');
        str.push_back('2');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;

    cube = current.first.first->lC(-1);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('L');
        str.push_back('\'');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;
    
    cube = current.first.first->uC(1);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('U');
        str.push_back(' ');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;

    cube = current.first.first->uC(2);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('U');
        str.push_back('2');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;

    cube = current.first.first->uC(-1);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('U');
        str.push_back('\'');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;

    cube = current.first.first->dC(1);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('D');
        str.push_back(' ');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;

    cube = current.first.first->dC(2);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('D');
        str.push_back('2');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;
    
    cube = current.first.first->dC(-1);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('D');
        str.push_back('\'');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;

    cube = current.first.first->fC(1);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('F');
        str.push_back(' ');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;
    
    cube = current.first.first->fC(2);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('F');
        str.push_back('2');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;

    cube = current.first.first->fC(-1);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('F');
        str.push_back('\'');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;

    cube = current.first.first->bC(1);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('B');
        str.push_back(' ');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;

    cube = current.first.first->bC(2);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('B');
        str.push_back('2');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;

    cube = current.first.first->bC(-1);
    ei = cube->edge_index();
    ci = cube->corner_index();
    if (!corners.contains(ci) || !edges.contains(ei))
    {
        corners.insert(ci);
        edges.insert(ei);
        str.push_back('B');
        str.push_back('\'');
        bfs.push( { { cube, { ei, ci } }, std::move(str) } );
        str = current.second;
    }
    else delete cube;
}