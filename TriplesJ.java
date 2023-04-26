import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class TriplesJ {

    private static int countTriples(int[] arr, int sum) {
        int n = arr.length;
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

    private static int[] readInput(String fileName) {
        int[] arr = null;

        try (Scanner scanner = new Scanner(new File(fileName))) {
            int n = scanner.nextInt();
            arr = new int[n];
        
            for (int i = 0; i < n; i++) {
                arr[i] = scanner.nextInt();
            }
        }
        catch(FileNotFoundException e) {
            System.out.println("File not found");
            System.exit(-1);
        }
        
        return arr;
    }

    private static int warmup(int[] arr, int sum, int reps) {
        int dummy = 0;

        for (int i = 0; i < reps; i++) {
            dummy += countTriples(arr, sum);
        }

        return dummy;
    }

    public static void main(String[] args) {
        if (args.length < 2 || args.length > 3) {
            System.out.println("Please provide two/three arguments");
            System.out.println("1) An input file");
            System.out.println("2) Number of repetitions");
            System.out.println("3) Warmup iterations (Default value: 0)");
            return;
        }

        String fileName = args[0];
        int reps = Integer.parseInt(args[1]);
        int[] arr = readInput(fileName);

        if (args.length == 3) {
            int warmupReps = Integer.parseInt(args[2]);
            System.out.println("Warming up...");
            warmup(arr, 0, warmupReps);
        }

        System.out.println("Benchmarking Java Program...");
        double timeSum = 0;
        double timeSqSum = 0;

        for (int i = 0; i < reps; i++)
        {
            long before = System.nanoTime();
            int triples = countTriples(arr, 0);
            double time = (System.nanoTime() - before) / 1e6;
            timeSum += time;
            timeSqSum += time * time;
            System.out.printf("Run %d/%d, %.2f ms, %d 0-Triples\n", i+1, reps, time, triples);
        }

        double mean = timeSum / reps;
        double stdDev = Math.sqrt((timeSqSum - reps * mean * mean) / reps);
        System.out.printf("%.2f ms +/- %.2f\n", mean, stdDev);
    }
}