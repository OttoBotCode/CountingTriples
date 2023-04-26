#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Please provide two arguments:\n";
        std::cout << "1) Integer Count\n";
        std::cout << "2) Maximum Integer\n";
    }

    int n = atoi(argv[1]);
    int max = atoi(argv[2]);

    if (max > RAND_MAX) {
        std::cout << "Max Value > RAND_MAX\n";
        return 0;
    }

    std::cout << n;
    srand(time(0));

    for (int i = 0; i < n; i++) {
        int x = -max + rand() % (2 * max);
        std::cout << '\n' << x;
    }

    return 0;
}