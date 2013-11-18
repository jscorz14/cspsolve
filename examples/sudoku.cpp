#include <cspsolve.hpp>

#include <iostream>
#include <vector>
#include <array>

static const int SIZE = 9;
static const int MAX_SOLUTIONS = 10;

typedef std::array<int, SIZE * SIZE> SudokuArray;
typedef std::vector<int>::iterator EntryIterator;

int getIndex(int row, int col) {
    return row * SIZE + col;
}

bool valid(SudokuArray& instance, const EntryIterator& entry) {

    if (instance[*entry] == 0) return false;

    const int elemRow = *entry / SIZE;
    const int elemCol = *entry % SIZE;

    // check row
    for (int col = 0; col < SIZE; col++) {
        if (col != elemCol && instance[getIndex(elemRow, col)] == instance[*entry])
            return false;
    }

    // check column
    for (int row = 0; row < SIZE; row++) {
        if (row != elemRow && instance[getIndex(row, elemCol)] == instance[*entry])
            return false;
    }

    // check 3x3 block
    const int blockRow = elemRow - elemRow % 3;
    const int blockCol = elemCol - elemCol % 3;
    for (int row = blockRow; row < blockRow + 3; row++) {
        for (int col = blockCol; col < blockCol + 3; col++) {
            if (!(row == elemRow && col == elemCol) && instance[getIndex(row, col)] == instance[*entry])
                return false;
        }
    }

    return true;

}

void firstValue(SudokuArray& instance, const EntryIterator& entry) {
    instance[*entry] = 0;
}

bool nextValue(SudokuArray& instance, const EntryIterator& entry) {
    return ++instance[*entry] <= 9;
}

bool output(const SudokuArray& instance) {
    std::cout << "Solution:" << std::endl;
    for (std::size_t i = 0; i < instance.size(); i++) {
        std::cout << instance[i] << " ";
        if ((i + 1) % 9 == 0) std::cout << std::endl;
    }
    return false; // stop searching for solutions
}

int parseChar(char c) {
    if (c == '.') return 0;
    int intValue = c - '0';
    if (!(intValue >= 1 && intValue <= 9)) intValue = -1;
    return intValue;
}

int main(void) {

    SudokuArray instance;
    std::vector<int> unknownEntries;

    std::cout << "Type the sudoku (use '.' for unknown entries):" << std::endl;

    // Read from stdin
    int counter = 0;
    char c;
    while (counter < SIZE * SIZE && std::cin >> c) {
        int val = parseChar(c);
        if (val > -1) {
            instance[counter] = val;
            if (val == 0) unknownEntries.push_back(counter);
            counter++;
        }
    }

    if (counter != SIZE * SIZE) {
        std::cerr << "Error reading input data" << std::endl;
        exit(-1);
    }

    cspsolve::solve(instance, unknownEntries.begin(), unknownEntries.end(), valid, firstValue, nextValue, output);

    return 0;

}
