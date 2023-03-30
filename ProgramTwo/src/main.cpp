/**
 * @file main.cpp
 * @author Andrew Sauerbrei
 *         AJ Bulthuis
 *         Tyrone Wu
 * @brief The main class that parses the input and calls a MST function.
 * 
 */

#include <iostream>
#include "../include/Graph.h"

using namespace std;

// Global counter for number of comparison operators performed.
unsigned long long compares;

int main(int argc, char* argv[]) {
    // Parse in the input
    string line;
    while (getline(cin, line)) {
        cout << line << endl;
    }

    return 0;
}
