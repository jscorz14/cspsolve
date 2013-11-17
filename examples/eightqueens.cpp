#include <cspsolve.hpp>

#include <iostream>
#include <array>
#include <cmath>

static const int DIMENSION = 8;

typedef std::array<int, DIMENSION> QueenArray;

bool valid(const QueenArray& instance, int queen) {
    
    // check columns and diagonals
    for (int prevQueen = 0; prevQueen < queen; prevQueen++) {
        const int dist = queen - prevQueen;
        if (instance[prevQueen] == instance[queen] ||
                std::abs(instance[queen] - instance[prevQueen]) == dist) {
            return false;
        }
    }

    return true;

}

void firstValue(QueenArray& instance, int queen) {
    instance[queen] = 0;
}

bool nextValue(QueenArray& instance, int queen) {
    return ++instance[queen] < DIMENSION;
}

int main(void) {

    QueenArray instance;
    std::fill(instance.begin(), instance.end(), 0);
    
    int solutions = 0;
    const auto output = [&solutions](const QueenArray& instance) -> bool {
        solutions++;
        for (int queen = 0; queen < DIMENSION; queen++) {
            for (int col = 0; col < DIMENSION; col++) {
                if (col == instance[queen]) std::cout << "Q";
                else std::cout << "-";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        return true; // find the next solution
    };
    
    cspsolve::solve(instance, 0, DIMENSION, valid, firstValue, nextValue, output);
    
    std::cout << "Number of solutions: " << solutions << std::endl;

    return 0;

}
