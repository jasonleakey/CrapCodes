package edu.utdallas.ml;

import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

public class AdaBoost
{
    // the number of iterations.
    private int T;

    // the number of training data
    private int n;

    // smoothing 
    private double epsilon;

    // values of training data.
    private double[] x;

    // classes of training data.
    private int[] y;

    // initial probability.
    private double[] init_p;

    // Output format
    private final static DecimalFormat FORMATER = new DecimalFormat("###.#####");

    public AdaBoost()
    {
    }

    public AdaBoost(String input)
    {
        analyze_input(input);
    }

    // read parameters.
    public void analyze_input(String input)
    {
        assert (null != input);

        Scanner scan = new Scanner(input);
        T = scan.nextInt();
        n = scan.nextInt();
        epsilon = scan.nextDouble();

        x = new double[n];
        for (int i = 0; i < n; i++)
        {
            x[i] = scan.nextDouble();
        }

        y = new int[n];
        for (int i = 0; i < n; i++)
        {
            y[i] = scan.nextInt();
            if (y[i] != -1 && y[i] != 1)
            {
                throw new InputMismatchException();
            }
        }

        init_p = new double[n];
        for (int i = 0; i < n; i++)
        {
            init_p[i] = scan.nextDouble();
        }
        
        scan.close();
    }

    /**
     *  Binary AdaBoosting
     */
    public void binary_adaboost()
    {
        // find thresholds from the training data.
        double[] thresholds = find_thresholds();
        // all training data are all positive or all negative. 
        // then no necessary to train. 
        if (0 == thresholds.length)
        {
            System.err
                    .println("Cannot find a threshold. Maybe All training data have the same label. Give more training data.");
            return;
        }

        // binary boosted classifier composed of weak classifiers.
        BinBoostClassifier f = new BinBoostClassifier();
        // max upper bound that could be reached.
        double bound = 1.0;
        double[] p = init_p.clone();
        
        // run iteration
        for (int t = 0; t < T; t++)
        {
            // /////
            System.out.println("Iteration " + (t + 1) + ":");
            // /////

            // the minimum epsilon (error) that can be reach in this iteration.
            double minEpsilon = 1.0;
            // the best weak classifier choosed in this iteration.
            Classifier bestClassifier = null;
            // for each hypothesis
            for (int j = 0, len = thresholds.length; j < len; j++)
            {
                // create a weak classifier with this hypothesis.
                Classifier classifier = new Classifier(thresholds[j]);
                // train the classifier over the training data
                classifier.train(x, y);
                
                // the error for this weak classifier.
                double sumEpsilon = 0.0;
                for (int i = 0; i < n; i++)
                {
                    if (classifier.classify(x[i]) != y[i])
                    {
                        sumEpsilon += p[i];
                    }
                }

                // If epsilon_t ≥ 0.5 go back to the iteration step. This
                // shouldn’t happen too often.
                if (sumEpsilon > 0.5)
                {
                    continue;
                }

                // strong classifier case.
                if (0 == sumEpsilon)
                {
                    System.err.println("The classifier with x>" + thresholds[j]
                            + " or x<" + thresholds[j] + " is not weak.");
                    return;
                }

                // better classifier ?
                if (sumEpsilon < minEpsilon)
                {
                    minEpsilon = sumEpsilon;
                    bestClassifier = classifier;
                }
            }
            // /////
            System.out.println("The selected weak classifier: "
                    + bestClassifier);
            System.out
                    .println("The error of h: " + FORMATER.format(minEpsilon));
            // ////

            // COMPUTE alpha, the "goodness" weight of hypothesis.
            double alpha = 0.5 * Math.log((1 - minEpsilon) / minEpsilon);

            // /////
            System.out.println("The weight of h: " + FORMATER.format(alpha));
            // ////

            // the error bound Zt
            double z = 0.0;
            double[] q = new double[n];
            // UPDATE the probabilities
            for (int i = 0; i < n; i++)
            {
                if (bestClassifier.classify(x[i]) != y[i])
                {
                    q[i] = Math.exp(alpha);
                }
                else
                {
                    q[i] = Math.exp(-alpha);
                }

                z += p[i] * q[i];
            }

            // ////
            System.out.println("The probabilities normalization factor Zt: "
                    + FORMATER.format(z));
            // ////
            System.out.print("The probabilities after normalization: pi=[");
            p[0] = (p[0] * q[0]) / z;
            System.out.print(FORMATER.format(p[0]));
            // ////
            for (int i = 1; i < n; i++)
            {
                // normalise probabilities
                p[i] = (p[i] * q[i]) / z;
                System.out.print(", " + FORMATER.format(p[i]));
            }
            System.out.println("]");
            // /////

            // UPDATE boosted classifier.
            f.addClassifier(alpha, bestClassifier);
            // UPDATE bound after this iteration.
            // bound = Z1 * Z2 * Z3 * ...
            bound *= z;

            // ////
            System.out.println("The boosted classifier ft: " + f);
            // ////

            // COMPUTE the error of boosted classifier Et
            double e = 0.0;
            for (int i = 0; i < n; i++)
            {
                if (f.classify(x[i]) != y[i])
                {
                    e = e + 1;
                }
            }
            e /= n;

            // ////
            System.out.println("The error of the boosted classifier Et: "
                    + FORMATER.format(e));
            // ////

            // ////
            System.out.println("The bound on Et: " + FORMATER.format(bound));
            // ////

            System.out.println();
        }
    }

    /**
     * REAL ADABOOSTING
     */
    public void real_adaboost()
    {
        double[] thresholds = find_thresholds();
        if (0 == thresholds.length)
        {
            System.err
                    .println("Cannot find a threshold. Maybe All training data have the same label. Give more training data.");
            return;
        }

        // Real boosted classifier
        RealBoostClassifier f = new RealBoostClassifier();
        double bound = 1.0;
        double[] p = init_p.clone();
        // for each iteration
        for (int t = 0; t < T; t++)
        {
            // /////
            System.out.println("Iteration " + (t + 1) + ":");
            // /////

            double minG = 100; // initialise G to an unreachable value.
            // best classifier chosen in this iteration.
            Classifier bestClassifier = null;
            // error probabilities under the best classifier in this iteration.
            double bestPRP = 0.0; // probability of h(x) = 1, y = 1
            double bestPRM = 0.0; // probability of h(x) = -1, y = -1
            double bestPWP = 0.0; // probability of h(x) = -1, y = 1
            double bestPWM = 0.0; // probability of h(x) = 1, y = -1
            // for each hypothesis
            for (int j = 0, len = thresholds.length; j < len; j++)
            {
                // G(j)
                double sumG = 0.0;
                // Right Plus
                double prp = 0.0;
                // Right Minus
                double prm = 0.0;
                // Wrong Plus
                double pwp = 0.0;
                // Wrong Minus
                double pwm = 0.0;
                Classifier classifier = new Classifier(thresholds[j]);
                classifier.train(x, y);

                // COMPUTE the probabilities
                for (int i = 0; i < n; i++)
                {
                    if (1 == classifier.classify(x[i]) && 1 == y[i])
                    {
                        prp += p[i];
                    }
                    else if (-1 == classifier.classify(x[i]) && -1 == y[i])
                    {
                        prm += p[i];
                    }
                    else if (-1 == classifier.classify(x[i]) && 1 == y[i])
                    {
                        pwp += p[i];
                    }
                    else if (1 == classifier.classify(x[i]) && -1 == y[i])
                    {
                        pwm += p[i];
                    }
                }

                // If epsilon_t ≥ 0.5 go back to the iteration step. This
                // shouldn’t happen too often.
                if (sumG > 0.5)
                {
                    continue;
                }

                // COMPUTE G(j)
                sumG = Math.sqrt(prp * pwm) + Math.sqrt(pwp * prm);

                // smaller G(j) ?
                if (sumG < minG)
                {
                    minG = sumG;
                    bestClassifier = classifier;
                    bestPRP = prp;
                    bestPRM = prm;
                    bestPWP = pwp;
                    bestPWM = pwm;
                }
            }
            // /////
            System.out.println("The selected weak classifier: "
                    + bestClassifier);
            System.out.println("The G error of h: " + FORMATER.format(minG));
            // ////

            // COMPUTE c+, c-
            double cplus = 0.5 * Math.log((bestPRP + epsilon)
                    / (bestPWM + epsilon));
            double cminus = 0.5 * Math.log((bestPWP + epsilon)
                    / (bestPRM + epsilon));

            // /////
            System.out.println("The weight of c+, c-: c+ = "
                    + FORMATER.format(cplus) + ", c- = "
                    + FORMATER.format(cminus));
            // ////

            // normalisation factor Zt
            double z = 0.0;
            double[] q = new double[n];
            // UPDATE the probabilities
            for (int i = 0; i < n; i++)
            {
                if (1 == bestClassifier.classify(x[i]))
                {
                    q[i] = Math.exp(-1 * y[i] * cplus);
                }
                else
                {
                    q[i] = Math.exp(-1 * y[i] * cminus);
                }

                z += p[i] * q[i];
            }

            // ////
            System.out.println("The probabilities normalization factor Zt: "
                    + FORMATER.format(z));
            // ////
            System.out.print("The probabilities after normalization: pi=[");
            p[0] = (p[0] * q[0]) / z;
            System.out.print(FORMATER.format(p[0]));
            // ////
            for (int i = 1; i < n; i++)
            {
                // normalize
                p[i] = (p[i] * q[i]) / z;
                System.out.print(", " + FORMATER.format(p[i]));
            }
            System.out.println("]");
            // /////

            // integrate current classifier to boosted classifier.
            f.addClassifier(cplus, cminus, bestClassifier);
            // UPDATE error bound
            // bound = Z1 * Z2 * Z3 * ...
            bound *= z;

            // ////
            StringBuffer buf = new StringBuffer();
            buf.append("The values ft(x) for each one of the examples: [");
            for (double val : x)
            {
                // COMPUTE the value f(x) for each example.
                buf.append(f.valueOf(val) + ", ");
            }
            buf.delete(buf.length() - 2, buf.length() - 1);
            buf.append("]");
            System.out.println(buf.toString());
            // ////

            // COMPUTE the error of boosted classifier Et
            double e = 0.0;
            for (int i = 0; i < n; i++)
            {
                if (f.classify(x[i]) != y[i])
                {
                    e = e + 1;
                }
            }
            e /= n;

            // ////
            System.out.println("The error of the boosted classifier Et: "
                    + FORMATER.format(e));
            // ////

            // ////
            System.out.println("The bound on Et: " + FORMATER.format(bound));
            // ////

            System.out.println();
        }
    }

    /**
     * find thresholds to separate training data
     * e.g. a list of training data with classes [1 1 -1 -1 -1 1 1 1]
     * then the thresholds could be between 2nd element and 3rd element,
     * or between 5th element and 6th element. 
     * And all possible thresholds will be returned. 
     * 
     * @return an array of thresholds
     */
    private double[] find_thresholds()
    {
        List<Double> thresholdList = new ArrayList<>();
        for (int i = 0, j = i + 1, len = y.length; j < len; i++, j++)
        {
            if (y[i] != y[j])
            {
                // compare the labels of adjacent two training data.
                thresholdList.add((x[i] + x[j]) / 2);
            }
        }

        double[] thresholds = new double[thresholdList.size()];
        for (int i = 0, len = thresholdList.size(); i < len; i++)
        {
            thresholds[i] = thresholdList.get(i);
        }

        return thresholds;
    }

    public static void main(String[] args)
    {
        if (args.length != 1)
        {
            System.err
                    .println("Filename needed. \nUSAGE: adaboost input_file_name");
            return;
        }

        String inputfile = FileUtils.read_corpus(args[0]);
        AdaBoost ada = new AdaBoost();
        try
        {
            ada.analyze_input(inputfile);
        }
        catch (InputMismatchException e)
        {
            e.printStackTrace();
            System.err.println("Oops! Something wrong in the input file.");
            return;
        }
        catch (Exception e)
        {
            e.printStackTrace();
            return;
        }

        // ///
        System.out.println("****************************************");
        System.out.println("Binary AdaBoosting");
        System.out.println("****************************************");
        // ////
        ada.binary_adaboost();
        // ////
        System.out.println();
        System.out.println("****************************************");
        System.out.println("Real AdaBoosting");
        System.out.println("****************************************");
        ada.real_adaboost();

    }
}
