#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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

struct Data readInput(char* fileName) {
    FILE* file = fopen(fileName, "r");
    char buffer[10];
    fgets(buffer, 10, file);
    int n = atoi(buffer);

    int* arr = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        fgets(buffer, 10, file);
        arr[i] = atoi(buffer);
    }

    fclose(file);

    struct Data data = { n, arr };
    return data;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        puts("Please provide two arguments");
        puts("1) An input file");
        puts("2) Number of repetitions");
        return -1;
    }

    char* fileName = argv[1];
    int reps = atoi(argv[2]);
    struct Data data = readInput(fileName);
    int n = data.n;
    int* arr = data.arr;
    double timeSum = 0;
    double timeSqSum = 0;

    puts("Benchmarking C Program...");

    for (int i = 0; i < reps; i++)
    {
        clock_t before = clock();
        int triples = countTriples(arr, n, 0);
        double time = 1000 * (clock() - before) / (double) CLOCKS_PER_SEC;
        timeSum += time;
        timeSqSum += time * time;
        printf("Run %d/%d, %.2f ms, %d 0-Triples\n", i+1, reps, time, triples);
    }

    double mean = timeSum / reps;
    double stdDev = sqrt((timeSqSum - reps * mean * mean) / reps);
    printf("%.2f ms +/- %.2f\n", timeSum / reps, stdDev);
    free(arr);
    return 0;
}