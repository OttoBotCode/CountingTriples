import time
import sys
import math

def count_triples(arr, _sum):
    n = len(arr)
    count = 0

    for i in range(n):
        for j in range(i+1, n):
            for k in range(j+1, n):
                if arr[i] + arr[j] + arr[k] == _sum:
                    count += 1
    
    return count

def read_input(file_name):
    arr = None

    with open(file_name) as f:
        n = int(f.readline())
        arr = [None] * n

        for i in range(n):
            arr[i] = int(f.readline())
    
    return arr

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Please provide two arguments")
        print("1) An input file")
        print("2) Number of repetitions")
        exit()

    file_name = sys.argv[1]
    reps = int(sys.argv[2])
    arr = read_input(file_name)
    time_sum = 0
    sq_time_sum = 0

    print("Benchmarking Python Program...")

    for i in range(reps):
        before = time.time()
        triples = count_triples(arr, 0)
        t = 1000 * (time.time() - before)
        time_sum += t
        sq_time_sum += t * t
        print(f"Run {i+1}/{reps}, {t:.2f} ms, {triples} 0-Triples")

    mean = time_sum / reps
    std_dev = math.sqrt((sq_time_sum - reps * mean * mean) / reps)
    print(f"{mean:.2f} ms +/- {std_dev:.2f}")