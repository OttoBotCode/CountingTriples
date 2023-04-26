using System.Diagnostics;
using System;
using System.IO;

public class TriplesCS
{
    private static int CountTriples(int[] arr, int sum)
    {
        int n = arr.Length;
        int count = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                for (int k = j + 1; k < n; k++)
                {
                    if (arr[i] + arr[j] + arr[k] == sum)
                    {
                        count++;
                    }
                }
            }
        }

        return count;
    }

    private static int[] ReadInput(string fileName) {
        string[] lines = File.ReadAllLines(fileName);
        int n =  int.Parse(lines[0]);
        int[] arr = new int[n];

        for (int i = 0; i < n; i++)
        {
            arr[i] = int.Parse(lines[i+1]);
        }
        
        return arr;
    }

    public static void Main(string[] args)
    {
        if (args.Length != 2) {
            Console.WriteLine("Please provide two arguments");
            Console.WriteLine("1) An input file");
            Console.WriteLine("2) Number of repetitions");
            return;
        }

        string fileName = args[0];
        int reps = int.Parse(args[1]);
        int[] arr = ReadInput(fileName);
        double timeSum = 0;
        double timeSqSum = 0;

        Console.WriteLine("Benchmarking C# Program...");

        for (int i = 0; i < reps; i++)
        {
            Stopwatch sw = new Stopwatch();
            sw.Start();
            int triples = CountTriples(arr, 0);
            double time = sw.Elapsed.TotalMilliseconds;
            timeSum += time;
            timeSqSum += (time * time);
            Console.WriteLine($"Run {i+1}/{reps}, {time:F2} ms, {triples} 0-Triples");
        }

        double mean = timeSum / reps;
        double stdDev = Math.Sqrt((timeSqSum - reps * mean * mean) / reps);
        Console.WriteLine($"{mean:F2} ms +/- {stdDev:F2}");
    }
}