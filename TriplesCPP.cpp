#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>

int countTriples(int* arr, int n, int sum) {
	int count = 0;

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			for (int k = j + 1; k < n; k++) {
				if (arr[i] + arr[j] + arr[k] == sum) {
					count++;
				}
			}
		}
	}

	return count;
}

struct Data {
	int n;
	int* arr;
};

Data readInput(const char* fileName) {
	std::ifstream is(fileName);

	int n;
	is >> n;

	int* arr = new int[n];

	for (int i = 0; i < n; i++) {
		is >> arr[i];
	}

	return Data{n, arr};
}

int main(int argc, const char* argv[]) {
	if (argc != 3) {
        std::cout << "Please provide two arguments\n";
        std::cout << "1) An input file\n";
        std::cout << "2) Number of repetitions\n";
        return -1;
    }

	const char* fileName = argv[1];
    int reps = atoi(argv[2]);
    Data data = readInput(fileName);
	int n = data.n;
    int* arr = data.arr;
    double timeSum = 0;
	double timeSqSum = 0;

	using namespace std::chrono;
	std::cout << std::setprecision(2) << std::fixed;
	puts("Benchmarking C++ Program...");

	for (int i = 0; i < reps; i++) {
		auto before = high_resolution_clock::now();
		int triples = countTriples(arr, n, 0);
		double time = duration_cast<nanoseconds>(high_resolution_clock::now() - before).count() / 1e6;
		timeSum += time;
		timeSqSum += (time * time);
		std::cout << "Run " << (i+1) << "/" << reps << ", " << time << " ms, " << triples << " 0-Triples\n";
	}

	double mean = timeSum / reps;
	double stdDev = sqrt((timeSqSum - reps * mean * mean) / reps);
	std::cout << mean << " ms +/- " << stdDev << '\n';
	delete[] arr;
	return 0;
}