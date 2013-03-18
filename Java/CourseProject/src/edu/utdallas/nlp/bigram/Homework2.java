package edu.utdallas.nlp.bigram;

public class Homework2
{
    // S1 string
    public static final String S1 = "The company chairman said he will increase the profit next year .";

    // S2 string
    public static final String S2 = "The president said he believes the last year profit were good .";

    private BigramModel model;

    public void print_count(String input)
    {
        Object[][] countTable = model.count(input);

        System.out.println("=====================================");
        System.out.println("BIGRAM COUNTS");
        print_table(countTable);
    }

    public void print_prop_without_smooth(String input)
    {
        Object[][] propTable = model.get_prop_table_without_smooth(input);

        System.out.println("=====================================");
        System.out.println("a) WITHOUT SMOOTHING");
        print_table(propTable);

        System.out.println("\nTotal probability: "
                + model.get_total_prop(propTable,
                        input.toLowerCase().split("\\ +")) + '\n');
    }

    public void print_prop_with_addone_smooth(String input)
    {
        Object[][] propTable = model.get_prop_table_addone_smooth(input);

        System.out.println("=====================================");
        System.out.println("b) ADD-ONE SMOOTHING");
        print_table(propTable);

        System.out.println("\nTotal probability: "
                + model.get_total_prop(propTable,
                        input.toLowerCase().split("\\ +")) + '\n');
    }

    public void print_prop_with_goodturing_smooth(String input)
    {
        Object[][] propTable = model.get_prop_table_goodturing_smooth(input);

        System.out.println("=====================================");
        System.out.println("c) GOOD-TURING SMOOTHING");
        print_table(propTable);

        System.out.println("\nTotal probability: "
                + model.get_total_prop(propTable,
                        input.toLowerCase().split("\\ +")) + '\n');
    }

    private void print_table(Object[][] table)
    {
        for (Object[] row : table)
        {
            for (Object elem : row)
            {
                if (null == elem)
                {
                    System.out.printf("%10s", "");
                    continue;
                }

                if (elem instanceof String)
                {
                    System.out.printf("%10s", elem);
                }
                if (elem instanceof Integer)
                {
                    System.out.printf("%10d", elem);
                }
                if (elem instanceof Double)
                {
                    if (((Double) elem).doubleValue() == 0.0)
                    {
                        System.out.printf("%10s", '0');
                    }
                    else
                    {
                        System.out.printf("%10f", elem);
                    }
                }
            }
            System.out.println();
        }
    }

    public void setModel(BigramModel model)
    {
        this.model = model;
    }

    public static void main(String[] args)
    {
        if (args.length != 1)
        {
            System.out
                    .print("Usage: nlp2 [-S1] \n   or: nlp2 [-S2] \n   or: nlp2 ANY_SENTENCE\nensure enbraced with \" \"\n");
            return;
        }

        String targetStr = "";
        if (args[0].equals("-S1"))
        {
            targetStr = S1;
        }
        else if (args[0].equals("-S2"))
        {
            targetStr = S2;
        }
        else if (1 == args[0].split("\\ +").length)
        {
            System.err.println("Bigram only! Please input a sentence.");
            return;
        }
        else
        {
            targetStr = args[0];
        }

        BigramModel model = new BigramModel();
        model.train();

        Homework2 hw = new Homework2();
        hw.setModel(model);
        hw.print_count(targetStr);
        hw.print_prop_without_smooth(targetStr);
        hw.print_prop_with_addone_smooth(targetStr);
        hw.print_prop_with_goodturing_smooth(targetStr);

        if (!FileUtils.isFileExisted("bigram"))
        {
            FileUtils.write_file("bigram", model.toString());
        }
    }
}
