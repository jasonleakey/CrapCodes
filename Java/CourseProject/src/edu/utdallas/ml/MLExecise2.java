package edu.utdallas.ml;

import java.util.Random;

public class MLExecise2
{
    public int exactSteepDesc2()
    {
        // the beta values.
        double[] betas = { 0.1, 0.3, 0.5, 0.7, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4,
                1.5, 1.6, 1.7, 1.8, 1.9 };

        for (double beta : betas)
        {
            double c = 0.001;
            double x = 1;
            double y = c;
            // the number of iteration
            int k = 0;
            while (Math.abs(x) > 1e-6 || Math.abs(y) > 1e-6)
            {
                // double m = y / x;
                // double a = (Math.pow(c, 2) + Math.pow(m, 2))
                // / (Math.pow(c, 3) + Math.pow(m, 2));
                x = (1 - beta * c) * x;
                y = (1 - beta) * y;
                k++;
            }
            System.out.println("for epsilon=" + beta + ", k=" + k);
        }
        return 0;
    }

    public int exactSteepDesc3()
    {
        for (int i = 0; i < 3; i++)
        {
            Random rand = new Random();
            double avgBeta = 0.0;

            double c = 0.001;
            double x = 1;
            double y = c;

            // the number of iteration
            int k = 0;
            while (Math.abs(x) > 1e-6 || Math.abs(y) > 1e-6)
            {
                double m = y / x;
                double a = (Math.pow(c, 2) + Math.pow(m, 2))
                        / (Math.pow(c, 3) + Math.pow(m, 2));
                // beta is randomly generated within [0, 1]
                double beta = rand.nextDouble();
                x = (1 - beta * a * c) * x;
                y = (1 - beta * a) * y;

                avgBeta += beta;
                k++;
            }
            avgBeta /= k;

            System.out.printf("for beta=%.6f in average, k=%d\n", avgBeta, k);
        }
        return 0;
    }

    public int epsilonSteepDesc()
    {
        Random rand = new Random();

        double c = 0.001;
        double x = 1;
        double y = c;

        double avg_epsilon = 0.0;
        // the number of iteration
        int k = 0;
        while (Math.abs(x) > 1e-6 || Math.abs(y) > 1e-6)
        {
             double epsilon = 2 * rand.nextDouble();
//            double epsilon = 1.97;
            x = (1 - epsilon * c) * x;
            y = (1 - epsilon) * y;

            avg_epsilon += epsilon;
            k++;
        }

        avg_epsilon /= k;
        System.out.printf("for avg_epsilon=%.6f, k=%d\n", avg_epsilon, k);
        return 0;
    }
    
    public void train()
    {
        double w1 = 0;
        double w2 = 1;
        double w0 = -0.5;
        final double BETA = 1;
        final double epsilon = 2;
        int[][] samples = {{1, 0, 1}, {1, 1, 1}, {2, 0, 0}, {2, 1, 0}};
        
        boolean isTerminated = false;
        while (!isTerminated)
        {
            isTerminated = true;
            for (int i = 0; i < samples.length; i++)
            {
                double x1 = samples[i][0];
                double x2 = samples[i][1];
                double y = samples[i][2];
                double h = w0 + w1 * x1 + w2 * x2;
                double g = sigmoid(h, BETA);
                double delta = 2 * BETA * g * (1 - g) * (y - g);
                w0 += epsilon * delta;
                w1 += epsilon * delta * x1;
                w2 += epsilon * delta * x2;
                System.out.println("w0=" + w0 + ", w1=" + w1 + ", w2=" + w2);
                if (Math.abs(h - y) > 0.2)
                {
                    isTerminated = false;
                }
            }
        }
        
        System.out.println("w0" + w0 + ", w1=" + w1 + ", w2=" + w2);
    }
    
    private double sigmoid(double h, double beta)
    {
        return 1.0 / (1 + Math.exp(-2 * beta * h));
    }

    public static void main(String[] args)
    {
//         new MLExecise2().exactSteepDesc2();
//        new MLExecise2().epsilonSteepDesc();
        new MLExecise2().train();
    }
}
