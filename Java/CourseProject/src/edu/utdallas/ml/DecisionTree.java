package edu.utdallas.ml;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class DecisionTree
{
    // the total number of instances.
    private int numInstances;

    // the number of features, including target attribute.
    private int numFeatures;

    // The feature matrix for dataset.
    private int[][] dataset;

    // Partition declaration
    private class Partition
    {
        // partition id
        public String id;

        // the elements in this partition.
        public List<Integer> elements;
    }

    // the partition array.
    private List<Partition> partitions = new ArrayList<Partition>();

    private class Result
    {
        // parent partition to be split
        public String parentId;

        // child partitions
        public List<String> childId;

        // the feature index used
        public int featureId;
    }

    // the result
    private Result result = new Result();

    /**
     * read dataset file.
     * 
     * @return true if read process succeeds, otherwise false.
     */
    public boolean readDataset(String filename)
    {
        // Open Dataset File
        FileInputStream in = null;
        BufferedReader reader = null;

        try
        {
            in = new FileInputStream(filename);
            reader = new BufferedReader(new InputStreamReader(in));

            String line = null;
            // Read the number of instances
            // Read the number of features
            line = reader.readLine();
            String[] str = line.split(" +");
            if (str.length != 2)
            {
                System.err
                        .println("Illegal arguments in dataset file. "
                                + "The number of instances and the number of features not recognized!");
                return false;
            }
            numInstances = Integer.parseInt(str[0]);
            numFeatures = Integer.parseInt(str[1]);
            dataset = new int[numInstances][numFeatures];

            // For each line, read features and the
            // target attribute
            for (int i = 0; i < numInstances; i++)
            {
                line = reader.readLine();
                str = line.split(" +");
                if (str.length != numFeatures)
                {
                    System.err
                            .println("Illegal arguments in dataset file. Only "
                                    + numFeatures + " features are allowed.");
                    return false;
                }

                // Check the validity of data.
                for (int j = 0; j < numFeatures; j++)
                {
                    int feature = Integer.parseInt(str[j]);
                    if ((j < numFeatures - 1 && feature >= 0 && feature <= 2)
                            || (j == numFeatures - 1 && feature >= 0 && feature <= 1))
                    {
                        // save dataset.
                        dataset[i][j] = Integer.parseInt(str[j]);
                    }
                    else
                    {
                        System.err
                                .println("Illegal arguments in dataset file. feature value should be within 0 - 2, and target class within 0 - 1.");
                    }
                }
            }
        }
        catch (IOException e)
        {
            System.err.println("Could not open dataset file. ");
            return false;
        }
        catch (NumberFormatException e)
        {
            System.err.println("Illegal arguments in dataset file.");
            return false;
        }
        finally
        {
            if (null != reader)
                ;
            {
                try
                {
                    reader.close();
                }
                catch (IOException e2)
                {
                    System.err.println("error when close dataset file.");
                }
            }
            // Close file.
            if (null != in)
            {
                try
                {
                    in.close();
                }
                catch (IOException e2)
                {
                    System.err.println("error when close dataset file.");
                }
            }
        }
        return true;
    }

    /**
     * read one partition file.
     * 
     * @return true if the read process succeeds, otherwise false.
     */
    public boolean readPartition(String filename)
    {
        FileInputStream in = null;
        BufferedReader reader = null;

        try
        {
            // Open one partition file as input.
            in = new FileInputStream(filename);
            reader = new BufferedReader(new InputStreamReader(in));

            String line = null;
            // For each line, read features and the target attribute
            while (null != (line = reader.readLine()))
            {

                // For each line, read the first string as the partition id.
                String[] str = line.split(" +");
                // illegal format.
                if (str.length <= 1)
                {
                    System.err.println("Illegal partition file.");
                    return false;
                }

                // read partition id
                Partition partition = new Partition();
                partition.id = str[0];
                // read elements in each partition.
                partition.elements = new ArrayList<Integer>();
                for (int j = 1; j < str.length; j++)
                {
                    partition.elements.add(Integer.parseInt(str[j]));
                }
                partitions.add(partition);
            }
        }
        catch (IOException e)
        {
            System.err.println("Could not open dataset file. ");
            return false;
        }
        catch (NumberFormatException e)
        {
            System.err.println("Illegal arguments in dataset file.");
            return false;
        }
        finally
        {
            // Close file.
            if (null != reader)
            {
                try
                {
                    reader.close();
                }
                catch (IOException e2)
                {
                    System.err.println("error when close partition file.");
                }
            }
            if (null != in)
            {
                try
                {
                    in.close();
                }
                catch (IOException e2)
                {
                    System.err.println("error when close partition file.");
                }
            }
        }
        return true;
    }

    /**
     * generate a new partition file.
     */
    public boolean writePartition(String filename)
    {
        // Open a new file as the output partition.
        FileOutputStream out = null;
        BufferedWriter writer = null;
        try
        {
            out = new FileOutputStream(filename);
            writer = new BufferedWriter(new OutputStreamWriter(out));

            // For each partition,
            // output the partition id number
            // output all elements in this partition
            for (Partition part : partitions)
            {
                StringBuilder sb = new StringBuilder();
                sb.append(part.id);
                for (Integer element : part.elements)
                {
                    sb.append(" " + element.toString());
                }
                writer.write(sb.toString());
                writer.newLine();
            }
        }
        catch (IOException e)
        {
            System.err.println("Could not open dataset file. ");
            return false;
        }
        catch (NumberFormatException e)
        {
            System.err.println("Illegal arguments in dataset file.");
            return false;
        }
        finally
        {
            if (null != writer)
            {
                try
                {
                    writer.close();
                }
                catch (IOException e2)
                {
                    System.err.println("error when close partition file.");
                }
            }
            // Close file.
            if (null != out)
            {
                try
                {
                    out.close();
                }
                catch (IOException e2)
                {
                    System.err.println("error when close partition file.");
                }
            }
        }
        return true;
    }

    /**
     * calculate which partition to split next and according to what attribute.
     */
    public void splitPartition()
    {
        // the maximum of F
        double maxF = 0.0;
        // each partition has an attribute with max gain, so record it.
        Map<String, Integer> maxGainFeature = new HashMap<String, Integer>();
        for (Partition part : partitions)
        {
            // compute its entropy, Entropy(Si)
            double entropySi = 0.0;
            double[] targetProbs = new double[2];
            for (Integer element : part.elements)
            {
                targetProbs[dataset[element - 1][numFeatures - 1]]++;
            }
            entropySi = calcEntropy(Arrays.asList(targetProbs[0]
                    / (targetProbs[0] + targetProbs[1]), targetProbs[1]
                    / (targetProbs[0] + targetProbs[1])));

            // compute the information gain for each attribute
            double maxGain = 0.0;
            for (int i = 0; i < numFeatures - 1; i++)
            {
                // In this matrix
                // the first column refers to the number of target attribute to
                // be 0 when Ai equals 0, 1 or 2
                // the second column refers to the number of target attribute to
                // be 1 when Ai equals 0, 1 or 2
                // the third column refers to the number of elements attribute
                // Ai
                // to be 0, 1 or 2.
                double[][] count = new double[3][3];
                for (Integer element : part.elements)
                {
                    // the count of attribute Ai plus one
                    count[dataset[element - 1][i]][2]++;
                    // the conditional probability of target attribute plus one.
                    count[dataset[element - 1][i]][dataset[element - 1][numFeatures - 1]]++;
                }

                // initially the gain equals the entropySi
                // then subtract the conditional entropy
                double gain = entropySi;
                //
                double[] probfeature = new double[3];
                for (int k = 0; k < 3; k++)
                {
                    probfeature[k] = count[k][2]
                            / (count[0][2] + count[1][2] + count[2][2]);
                    // if the probability of feature i to be k is zero,
                    // then the information gain will not be changed.
                    if (probfeature[k] != 0)
                    {
                        gain -= probfeature[k]
                                * calcEntropy(Arrays.asList(count[k][0]
                                        / (count[k][0] + count[k][1]),
                                        count[k][1]
                                                / (count[k][0] + count[k][1])));
                    }
                }

                if (gain > maxGain)
                {
                    maxGain = gain;
                    // the i-th feature has the maximum information gain in this
                    // partition.
                    maxGainFeature.put(part.id, i);
                }
            }

            // compute the entropy contribution
            double F = part.elements.size() * 1.0 / numInstances * maxGain;
            // choose the partition with max F
            if (F > maxF)
            {
                maxF = F;
                result.parentId = part.id;
                result.featureId = maxGainFeature.get(part.id) + 1;
            }
        }

        // split the partition according to the result above
        Partition[] childParts = new Partition[3];
        // search parent partition
        for (Partition part : partitions)
        {
            // found the parent partition
            if (part.id.equals(result.parentId))
            {
                // generate child partitions from parent partition
                for (Integer elem : part.elements)
                {
                    int targetNo = dataset[elem - 1][numFeatures - 1];
                    if (null == childParts[targetNo])
                    {
                        childParts[targetNo] = new Partition();
                    }
                    if (null == childParts[targetNo].elements)
                    {
                        childParts[targetNo].elements = new ArrayList<Integer>();
                    }
                    childParts[targetNo].elements.add(elem);
                }
                // remove parent partition.
                partitions.remove(part);
                break;
            }
        }
        // create partition id for each child partition
        result.childId = new ArrayList<String>();
        int childCnt = 0;
        for (Partition part : childParts)
        {
            if (null != part && !part.elements.isEmpty())
            {
                // child partition id is named as parent partition id appended
                // with '_1' or something.
                part.id = result.parentId + '_' + (++childCnt);
                // add the child partition into the partition array.
                partitions.add(part);
                // update result
                result.childId.add(part.id);
            }
        }

    }

    /**
     * Calculate the entropy of a probability vector
     */
    private final double calcEntropy(List<Double> probVector)
    {
        double entropy = 0;
        for (Double prob : probVector)
        {
            if (0 == prob)
            {
                continue;
            }
            // Log base 2
            entropy += -prob * (Math.log(prob) / Math.log(2));
        }
        return entropy;
    }

    /**
     * print the message that the partition split is done.
     */
    public void printResult()
    {
        System.out.print("Partition " + result.parentId
                + " was replaced with partitions ");
        System.out.print(result.childId.get(0));
        for (int k = 1; k < result.childId.size(); k++)
        {
            System.out.print("," + result.childId.get(k));
        }
        System.out.println(" using Feature " + result.featureId);
    }

    public static void main(String[] args)
    {
        // Prompt user to input three filenames: dataset, input-partition,
        // output-partition
        System.out
                .println("Enter names of the files dataset input-partition output-partition");

        // check the number of arguments the user inputs.
        Scanner scanner = new Scanner(System.in);
        String files = scanner.nextLine();
        scanner.close();
        // the three files are separated by SPACE
        String[] filenames = files.split(" +");

        // illegal input.
        if (filenames.length != 3)
        {
            System.err
                    .println("Illegal Input. You should enter three file names.");
            return;
        }

        DecisionTree dt = new DecisionTree();
        // Read and analyse the first two files.
        if (!dt.readDataset(filenames[0]))
        {
            System.err.println("Application exit");
            return;
        }
        if (!dt.readPartition(filenames[1]))
        {
            System.err.println("Application exit");
            return;
        }

        // Compute which partition to split according to what attribute next.
        dt.splitPartition();

        // Save result in output file.
        if (!dt.writePartition(filenames[2]))
        {
            System.err.println("Application exit");
            return;
        }

        // print result
        dt.printResult();

        // exit successfully.
        return;
    }
}
