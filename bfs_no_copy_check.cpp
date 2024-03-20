// Compilation Command: g++ bfs_no_copy_check.cpp cube.cpp input_handler.cpp -o bfs_no_copy_check.exe -O3 -std=c++20

#include <iostream>
#include <queue>

#include "cube.h"
#include "input_handler.h"

std::string get_solution(Cube* starting_position);

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Command ussage: ./bfs_no_copy_check <filepath>\n";
        return 1;
    }


    Cube* c1 = new Cube(input_handler::get_cube_from_file(argv[1]));

    // c1->display();

    std::string solution = get_solution(c1);

    std::cout << "Solution: " << solution << '\n';




    return 0;
}



std::string get_solution(Cube* starting_position)
{
    std::queue<std::pair<Cube*, std::string>> bfs;
    bfs.push({ starting_position, "" });

    int length = 0;

    while (true)
    {
        std::pair<Cube*, std::string> current = bfs.front();
        if (current.first->isSolved())
            return current.second;


        std::string next = current.second;

        if (next.size() > length)
        {
            length = next.size();
            std::cout << "Depth: " << length / 2 << '\n';
        }
        next.push_back('R');
        next.push_back(' ');
        bfs.push({ current.first->rC(1), next });

        next = current.second;
        next.push_back('R');
        next.push_back('\'');
        bfs.push({ current.first->rC(-1), next });

        next = current.second;
        next.push_back('R');
        next.push_back('2');
        bfs.push({ current.first->rC(2), next});

        next = current.second;
        next.push_back('L');
        next.push_back(' ');
        bfs.push({ current.first->lC(1), next });

        next = current.second;
        next.push_back('L');
        next.push_back('\'');
        bfs.push({ current.first->lC(-1), next });

        next = current.second;
        next.push_back('L');
        next.push_back('2');
        bfs.push({ current.first->lC(2), next});
        
        next = current.second;
        next.push_back('U');
        next.push_back(' ');
        bfs.push({ current.first->uC(1), next });

        next = current.second;
        next.push_back('U');
        next.push_back('\'');
        bfs.push({ current.first->uC(-1), next });

        next = current.second;
        next.push_back('U');
        next.push_back('2');
        bfs.push({ current.first->uC(2), next});

        next = current.second;
        next.push_back('D');
        next.push_back(' ');
        bfs.push({ current.first->dC(1), next });

        next = current.second;
        next.push_back('D');
        next.push_back('\'');
        bfs.push({ current.first->dC(-1), next });

        next = current.second;
        next.push_back('D');
        next.push_back('2');
        bfs.push({ current.first->dC(2), next});

        next = current.second;
        next.push_back('F');
        next.push_back(' ');
        bfs.push({ current.first->fC(1), next });

        next = current.second;
        next.push_back('F');
        next.push_back('\'');
        bfs.push({ current.first->fC(-1), next });

        next = current.second;
        next.push_back('F');
        next.push_back('2');
        bfs.push({ current.first->fC(2), next});

        next = current.second;
        next.push_back('B');
        next.push_back(' ');
        bfs.push({ current.first->bC(1), next });

        next = current.second;
        next.push_back('B');
        next.push_back('\'');
        bfs.push({ current.first->bC(-1), next });

        next = current.second;
        next.push_back('B');
        next.push_back('2');
        bfs.push({ current.first->bC(2), next});

        bfs.pop();
        delete current.first;
    }
}
