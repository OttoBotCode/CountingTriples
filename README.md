# Counting Triples - Benchmarking

The programs in this repository all concern the countTriples function written below (C/C++ implementation):

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

It returns the number of triples in the length $n$ array $arr$, whose elements add up to $sum$.<br>
For example, with arguments $arr = [0, 2, -3, 1, 4, -2]$ and $sum = 0$, the function returns 2.<br>
That's because the array contains two triples which sum to 0, they are $(0, 2, -2)$ and $(2, -3, 1)$.<br>
The algorithm enumerates all triples, so it takes $O(n^3)$ time .

# Benchmarking Programs

This repository contains an implementation of the countTriples function written in 5 popular programming languages - Python, Java, C#, C and C++. <br> The goal of this project is to find out how fast the function runs in practice depending on which language it is written in.

The program for each language takes two command line parameters:
- An input file containing an array
- The number of repetitions

The program reads the array from the file and calls countTriples to find out how many 0-triples (triples with a sum of 0) it contains. <br>
The function is repeatedly called as many times as specified by the second command line argument.
For each call, the program prints the number of 0-triples and how much time the function took to execute. 
When all runs are completed the average time pr. call is printed along with the standard deviation.

Here is an example of running the Python version with input file "ints1k.txt" and 5 repetitions:

    > python TriplesP.py ../ints1k.txt 5
    Benchmarking Python Program...
    Run 1/5, 6742.50 ms, 60709 0-Triples
    Run 2/5, 6817.19 ms, 60709 0-Triples
    Run 3/5, 6808.25 ms, 60709 0-Triples
    Run 4/5, 6797.91 ms, 60709 0-Triples
    Run 5/5, 6816.35 ms, 60709 0-Triples
    6796.44 ms +/- 27.85

To see how to compile and run each version of the program, check out the corresponding section.<br>
There, you can also see which versions of the compilers/interpreters I have used.

# Data Format
The programs read the input array from a text file with the following format:

- The first line specifies the length of the array $n$.
- The remaining $n$ lines specify the array elements in order.

For example, the array $[-2, 3, 0, 4]$ would be represented in a file as:

    4
    -2
    3
    0
    4

The files <em>ints1k.txt</em>, <em>ints2k.txt</em>, <em>ints3k.txt</em>, <em>ints5k.txt</em>, <em>ints10k.txt</em> contain arrays with 1, 2, 3, 5 and 10 thousand elements respecively.<br>
The elements in these arrays are in the range $[-n, n]$ and have been generated uniformly at random.

# Generating Data
You can use the program <em>Generator.cpp</em> to generate random arrays.
Compile it with your favorite C++ compiler and run it with 2 command line arguments:

- The length of the array $n$.
- The maximum element value $max$.

The program will then generate an array with the given length containing elements in the range $[-max, max]$.

# Python
I used Python version 3.11.2 downloaded from Python's official website https://www.python.org/.

    > python --version
    Python 3.11.2

No compilation is needed for the python program, just run it like this:

    python TriplesP.py ints1k.txt 100

# Java
I used Java version 20 downloaded from Oracle's official website https://www.oracle.com/java/technologies/downloads/.

    > javac --version
    javac 20

    > java --version
    java 20 2023-03-21
    Java(TM) SE Runtime Environment (build 20+36-2344)
    Java HotSpot(TM) 64-Bit Server VM (build 20+36-2344, mixed mode, sharing)

Compile and run:

    > javac TriplesJ.java
    > java TriplesJ ints1k.txt 100

### NOTE
When I ran the Java version, the first few calls to countTriples took much longer time than subsequent calls.<br>
Apparently, the JVM only bothers generating optimized code when it feels like it's worth it.<br>
To combat this behaviour, I have included a warmup phase which runs countTriples a number of times before the actual benchmarking. You can specify how many warmup iterations to use by providing a third (optional) argument. 

Run with 10 iterations in the warmup phase:

    > java TriplesJ ints1k.txt 100 10

# C#
I used the C# compiler that came with Visual Studio 2022.

    > csc -version
    4.5.2-3.23171.7 (d17f7415)

I compile and run the program from a Visual Studio 2022 Developer Command Prompt.

    > csc TriplesCS.cs -o
    > TriplesCS ints1k.txt 100

### Note
The -o flag turns on optimization like Visual Studio does for Release builds.

# C
I used Microsoft's C/C++ compiler MSVC.

    > cl
    Microsoft (R) C/C++ Optimizing Compiler Version 19.35.32217.1 for x64
    ...

Compile and run:

    > cl TriplesC.c /O2
    > TriplesC ints1k.txt 100

### Note
The /O2 flag turns on optimization.<br>

# C++
Just like for C, I used Microsoft's C/C++ compiler (MSVC).

    > cl
    Microsoft (R) C/C++ Optimizing Compiler Version 19.35.32217.1 for x64
    ...

Compile and run:

    > cl TriplesCPP.cpp /O2 /EHsc 
    > TriplesCPP ints1k.txt 100

### Note
The compiler does distinguish between C and C++ programs, but in this case it generated identical code for the countTriples function. <br>

# Processor and Operating System
I ran the experiments on a desktop computer.

Processor:
12th Gen Intel(R) Core(TM) i7-12700F, 2100 Mhz, 12 Cores, 20 Logical Processors

RAM:
Corsair Vengeance 16GB DDR4-3600

Operating System:
Microsoft Windows 11 Home (Version 10.0.22621 Build 22621)

# Results
I ran the experiment with three different input files - <em>ints1k.txt</em>, <em>ints5k.txt</em> and <em>ints10k.txt.</em> <br>
The sum argument was set to 0, so the programs are counting triples whose elements add to 0.
In all three experiments each version of the program was run 100 times. <br>

## 1000 element array - ints1k.txt

| Language | Mean Time  | Std. Deviation |
|----------|------------|----------------|
| Python   | 7148.27 ms | ± 206.54 ms  |
| C#       | 63.52 ms   | ± 2.23 ms    |
| Java     | 29.60 ms   | ± 0.33 ms    |
| C++      | 15.72 ms   | ± 0.31 ms    |
| C        | 15.45 ms   | ± 0.55 ms    |

## 5000 element array - ints5k.txt

| Language | Mean Time  | Std. Deviation |
|----------|------------|----------------|
| Python   | Too long   |                |
| C#       | 7434.50 ms | ± 146.00 ms  |
| Java     | 3371.41 ms | ± 30.26 ms   |
| C++      | 1862.04 ms | ± 10.06 ms   |
| C        | 1850.61 ms | ± 35.06 ms   |

## 10,000 element array - ints10k.txt

| Language | Mean Time   | Std. Deviation |
|----------|-------------|----------------|
| Python   | Too long    |                |
| C#       | 58298.82 ms | ± 353.02 ms  |
| Java     | 26599.21 ms | ± 256.51 ms  |
| C++      | 14751.28 ms | ± 192.35 ms  |
| C        | 14670.86 ms | ± 148.54 ms  |

### Note
It's not surprising that the results for C and C++ are so close.<br>
As mentioned earlier, the compiler generated identical code for the countTriples function.<br>
The time difference we observe might be due to natural variability and/or different precision in the timers used for these languages.