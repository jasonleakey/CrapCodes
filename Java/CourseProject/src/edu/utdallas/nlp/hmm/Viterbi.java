package edu.utdallas.nlp.hmm;

import java.util.HashMap;
import java.util.InputMismatchException;
import java.util.Map;
import java.util.Scanner;

public class Viterbi
{
    // start probability
    // HOT: 0.8; COLD: 0.2
    private final static double[] PI = { 0.8, 0.2 };

    // transition probability matrix
    //
    // ----HOT COLD
    // HOT 0.7 0.3
    // COLD 0.4 0.6
    private final static double[][] A = { { 0.7, 0.3 }, { 0.4, 0.6 } };

    // State observation likelihood
    // ----1---2---3
    // HOT 0.2 0.4 0.4
    // COLD 0.5 0.4 0.1
    private final static double[][] B = { { 0.2, 0.4, 0.4 }, { 0.5, 0.4, 0.1 } };

    // the number of states N
    private final static int N = 2;

    // State number and state name mapping
    private final static Map<Integer, String> WEATHER_STATE = new HashMap<Integer, String>()
    {
        private static final long serialVersionUID = -3412166173565248028L;

        {
            put(0, "HOT");
            put(1, "COLD");
        }
    };

    // observation sequence
    private int[] O;

    public Viterbi(int[] obs)
    {
        this.O = obs;
    }

    public Viterbi(Object[] obs)
    {
        this.O = new int[obs.length];
        for (int i = 0; i < obs.length; i++)
        {
            this.O[i] = (Integer) obs[i];
        }
    }

    public void run()
    {
        // print out observation sequence
        print_array(O);

        // create ancillary array
        double[][] viterbi = new double[N][O.length];
        int[][] path = new int[N][O.length];

        // Initialisation step
        for (int state = 0; state < N; state++)
        {
            viterbi[state][0] = PI[state] * B[state][map_obs(O[0])];
            path[state][0] = -1;
        }

        // Recursion
        for (int obs = 1; obs < O.length; obs++)
        {
            for (int state = 0; state < N; state++)
            {
                for (int preState = 0; preState < N; preState++)
                {
                    double tempV = viterbi[preState][obs - 1]
                            * A[preState][state] * B[state][map_obs(O[obs])];
                    if (tempV > viterbi[state][obs])
                    {
                        viterbi[state][obs] = tempV;
                        path[state][obs] = preState;
                    }
                }
            }
        }

        StringBuffer result = new StringBuffer();
        // choose the larger probability, and its state
        int finalState = viterbi[0][O.length - 1] > viterbi[1][O.length - 1] ? 0
                : 1;
        // Backtrace from the end to the start
        for (int state = finalState, t = O.length - 1; state != -1; state = path[state][t--])
        {
            result.insert(0, WEATHER_STATE.get(state) + "  ");
        }

        System.out.println("Result: " + result);
    }

    final int map_obs(int obs)
    {
        return obs - 1;
    }

    final void print_array(int[] arr)
    {
        for (int a : arr)
        {
            System.out.print(a + "    ");
        }
        System.out.println();
    }

    public static void main(String[] args)
    {
        int[] observ1 = { 3, 1, 2, 3, 1, 2, 3, 1, 2 };
        int[] observ2 = { 3, 1, 1, 2, 3, 3, 1, 1, 2 };
        new Viterbi(observ1).run();
        System.out.println("====================================");
        new Viterbi(observ2).run();
        System.out.println("====================================");

        System.out.print("Or input your observation sequence:");
        Scanner scan = new Scanner(System.in);
        try
        {
            String[] nums = scan.nextLine().trim().split("\\ +");
            int[] observ3 = new int[nums.length];
            for (int i = 0; i < nums.length; i++)
            {
                observ3[i] = Integer.parseInt(nums[i]);
                if (observ3[i] >= 4 || observ3[i] <= 0)
                {
                    System.err.println("Illegal Input!");
                    return;
                }
            }
            new Viterbi(observ3).run();
        }
        catch (InputMismatchException e)
        {
            e.printStackTrace();
        }
        finally
        {
            scan.close();
        }
    }
}
