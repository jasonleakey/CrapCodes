package edu.utdallas.nlp.bigram;

import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

/**
 * Bigram Model can do the following things
 * 1. computes the bigrams, 
 * 2. constructs bigram counts
 * 3. bigram probabilities without smoothing, with add-one smoothing, or with
 * Good-Turing smoothing 
 * 4. calculate probability of an input sentence. 
 * 
 * @author Ye-tian Huang
 * 
 */
public class BigramModel
{
    // Simple Good-Turing threshold, that is, c* = c for c > k
    private static final int K = 3;

    // bigram count
    private Map<Bigram, Integer> bigramCount = new HashMap<Bigram, Integer>();

    // word statistics
    private Map<String, Integer> wordCount = new HashMap<>();

    // the path of CORPUS file
    private final static String CORPUS_PATH = "corpus.txt";

    // the corpus content
    private String corpus = null;

    public BigramModel()
    {
        // read the corpus from internal file
        corpus = FileUtils.read_corpus(CORPUS_PATH);
    }

    // count bigram information
    public void train()
    {
        // cannot read file, exit. 
        if (null == corpus)
        {
            System.err.println("corpus file reading error.");
            return;
        }

        // remove new line symbol
        corpus = corpus.replaceAll("\n", " ");
        // lower case and remove heading or trailing space if possible
        corpus = corpus.toLowerCase().trim();
        // split words by multiple-space. 
        String[] words = corpus.split("\\ +");

        for (int i = 0; i < words.length - 1; i++)
        {
            Bigram bigram = new Bigram();
            bigram.setWord1(words[i]);
            bigram.setWord2(words[i + 1]);

            // count bigrams
            if (!bigramCount.containsKey(bigram))
            {
                bigramCount.put(bigram, 1);
            }
            else
            {
                bigramCount.put(bigram, bigramCount.get(bigram) + 1);
            }

            // word statistics
            if (!wordCount.containsKey(words[i]))
            {
                wordCount.put(words[i], 1);
            }
            else
            {
                wordCount.put(words[i], wordCount.get(words[i]) + 1);
            }
        }
    }

    public Map<Bigram, Integer> getBigrams()
    {
        return bigramCount;
    }

    /**
     * get the number of a single word. P(w1)
     * @param word the word 
     * @return the number of word in the corpus.
     */
    public Integer getWordCount(String word)
    {
        return wordCount.get(word);
    }

    /**
     * bigram count table
     * @param input the input sentence
     * @return the bigram count table, with row header and column header.
     */
    public Object[][] count(String input)
    {
        // Preprocess input String
        input = input.trim().toLowerCase();
        // split sentence
        String[] inputs = input.split("\\ +");
        // delete duplicate word
        Set<String> temp = new HashSet<>(Arrays.asList(inputs));
        // final words
        String[] words = new String[temp.size()];
        System.arraycopy(temp.toArray(), 0, words, 0, temp.size());

        Object[][] table = new Object[words.length + 1][words.length + 1];
        // Row Header and Column Header
        for (int i = 0; i < words.length; i++)
        {
            table[0][i + 1] = words[i];
            table[i + 1][0] = words[i];
        }

        // insert column header
        for (int i = 0; i < words.length; i++)
        {
            for (int j = 0; j < words.length; j++)
            {
                Integer count = bigramCount.get(new Bigram(words[i]
                        .toLowerCase(), words[j].toLowerCase()));
                // if there exists no such kind of bigram, just use 0
                table[i + 1][j + 1] = null == count ? 0 : count;
            }
        }

        return table;
    }

    /**
     * get the bigram probability table without smooth of input sentence.
     * @param input the input sentence
     * @return probability table, with column header and row header.
     */
    public Object[][] get_prop_table_without_smooth(String input)
    {
        Object[][] countTable = count(input);
        Object[][] propTable = new Object[countTable.length][countTable[0].length];

        // Row Header and Column Header
        for (int i = 1; i < countTable.length; i++)
        {
            propTable[0][i] = countTable[0][i];
            propTable[i][0] = countTable[i][0];
        }

        for (int i = 1; i < countTable.length; i++)
        {
            for (int j = 1; j < countTable.length; j++)
            {
                Integer wordCnt = getWordCount((String) countTable[i][0]);
                if (null == wordCnt || wordCnt.intValue() == 0)
                {
                    propTable[i][j] = 0.0;
                }
                else
                {
                    // P(w2|w1) = P(w1w2) / P(w1)
                    propTable[i][j] = (Double) ((Integer) countTable[i][j] / (1.0 * wordCnt));
                }
            }
        }

        return propTable;
    }

    public Object[][] get_prop_table_addone_smooth(String input)
    {
        Object[][] countTable = count(input);
        Object[][] propTable = new Object[countTable.length][countTable[0].length];

        // Row Header and Column Header
        for (int i = 1; i < countTable.length; i++)
        {
            propTable[0][i] = countTable[0][i];
            propTable[i][0] = countTable[i][0];
        }

        // Vocabulary V
        Integer V = wordCount.keySet().size();
        for (int i = 1; i < countTable.length; i++)
        {
            for (int j = 1; j < countTable.length; j++)
            {
                Integer wordCnt = getWordCount((String) countTable[i][0]);
                if (null == wordCnt || wordCnt.intValue() == 0)
                {
                    propTable[i][j] = 0.0;
                }
                else
                {
                    // Laplace add-one smooth formula
                    // C* = (c + 1) N / (N + V)
                    propTable[i][j] = ((Integer) countTable[i][j] + 1)
                            / (1.0 * (getWordCount((String) countTable[i][0]) + V));
                }
            }
        }

        return propTable;
    }

    public Object[][] get_prop_table_goodturing_smooth(String input)
    {
        Object[][] countTable = count(input);
        Object[][] propTable = new Object[countTable.length][countTable[0].length];

        // Row Header and Column Header
        for (int i = 1; i < countTable.length; i++)
        {
            propTable[0][i] = countTable[0][i];
            propTable[i][0] = countTable[i][0];
        }

        // total frequency N
        Integer totalFreq = 0;
        Integer maxFreq = 0;
        for (Integer freq : bigramCount.values())
        {
            totalFreq += freq;
            if (freq > maxFreq)
            {
                maxFreq = freq;
            }
        }

        // Nc List, the number of bigrams that occur c times;
        int N[] = new int[maxFreq + 1];
        for (Integer freq : bigramCount.values())
        {
            N[freq] += 1;
        }

        for (int i = 1; i < countTable.length; i++)
        {
            for (int j = 1; j < countTable.length; j++)
            {
                Integer c = (Integer) countTable[i][j];

                // use N1 for unseen bigrams N0
                if (c.intValue() == 0)
                {
                    propTable[i][j] = 1.0 * N[1] / totalFreq;
                }
                else if (c > K)
                {
                    // keep the old count to avoid N[c + 1] == 0
                    propTable[i][j] = c / (1.0 * totalFreq);
                }
                else
                {
                    propTable[i][j] = 1.0 * ((Integer) countTable[i][j] + 1)
                            * N[c + 1] / N[c] / totalFreq;
                }
            }
        }

        return propTable;
    }

    public Double get_total_prop(Object[][] table, String[] words)
    {
        Double totalProp = 1.0;
        for (int i = 0; i < words.length - 1; i++)
        {
            // find the row
            int j = 1;
            while (j < table.length && !((String) table[j][0]).equals(words[i]))
            {
                j++;
            }

            if (j >= table.length)
            {
                System.err.println("invalid sentence!");
                return null;
            }

            // find the column
            int k = 1;
            while (k < table.length
                    && !((String) table[0][k]).equals(words[i + 1]))
            {
                k++;
            }

            if (k >= table.length)
            {
                System.err.println("invalid sentence!");
                return null;
            }

            // get the bigram probability and product all of them. 
            totalProp *= ((Double) table[j][k]);
        }

        return totalProp;
    }

    @Override
    public String toString()
    {
        // output bigram in a descendant order by frequency.
        StringBuffer buf = new StringBuffer();
        ValueComparator comp = new ValueComparator(bigramCount);
        TreeMap<Bigram, Integer> sortedBiCount = new TreeMap<Bigram, Integer>(
                comp);
        sortedBiCount.putAll(bigramCount);
        for (Bigram bigram : sortedBiCount.keySet())
        {
            buf.append("[" + bigram.getWord1() + ", " + bigram.getWord2()
                    + "]: " + bigramCount.get(bigram) + '\n');
        }
        return buf.toString();
    }

    private class ValueComparator implements Comparator<Bigram>
    {

        Map<Bigram, Integer> base;

        public ValueComparator(Map<Bigram, Integer> base)
        {
            this.base = base;
        }

        // Note: this comparator imposes orderings that are inconsistent with
        // equals.
        public int compare(Bigram a, Bigram b)
        {
            if (base.get(a) >= base.get(b))
            {
                return -1;
            }
            else
            {
                return 1;
            } // returning 0 would merge keys
        }
    }
}
