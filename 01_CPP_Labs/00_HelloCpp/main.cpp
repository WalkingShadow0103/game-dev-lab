#include <iostream>
#include <string>

int main()
{
    std::string name = "WalkingShadow";
    int level = 1;
    float hp = 100.0f;
    bool isAlive = true;

    std::cout << "=== Hello C++ ===\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Level: " << level << "\n";
    std::cout << "HP: " << hp << "\n";
    std::cout << "Alive: " << isAlive << "\n";

    return 0;
}