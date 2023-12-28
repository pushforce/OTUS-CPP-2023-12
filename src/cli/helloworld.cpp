#include <iostream>
#include "version.hpp"

int main()
{
    std::cout << "Build: " << version() << std::endl;
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
