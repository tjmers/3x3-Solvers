#include "input_handler.h"

namespace input_handler
{


std::string get_cube_from_file(const std::string& file_path)
    {
        std::ifstream file(file_path);
        
        std::string retval;
        std::getline(file, retval);

        return retval;
   }


}