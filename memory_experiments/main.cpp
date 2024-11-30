#include "experiments.hpp"
#include <iostream>

int main() {
    std::cout << "Message passing: " << messagePassing() / 100000 << "%\n";
    std::cout << "Store buffering: " << storeBuffering() / 100000 << "%\n";
    std::cout << "Load buffering: " << loadBuffering() / 100000 << "%\n";
    return 0;
}
