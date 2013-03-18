package edu.utdallas.nlp.date;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Properties;
import java.util.Set;


public class DateRecognition
{
    // The state-transition table for fsa.
    // each column represents the class of words:
    // month, day_cipher, day_suffix, holiday, of
    private Integer[][] transTable = { { 1, null, 2, 4, null },
            { null, 4, 4, null, null }, { null, null, null, null, 3 },
            { 4, null, null, null, null }, { null, null, null, null, null } };

    // each column includes all formats of class of words.
    // e.g. column 0 is the collection of month expressions, March, Mar., MAR.
    Set<String>[] columns = new HashSet[5];

    // enumeration of shorthands
    private enum ShortHand
    {
        MONTH, // Column 0
        DAY_CIPHER, // Column 1
        DAY_SUFFIX, // Column 2 
        HOLIDAY, // Column 3
        OF // Column 4
    }

    // start state number 
    private static final int START_STATE = 0;
    // final state number
    private static final int FINAL_STATE = 4;

    // recognise the dates from the article.
    public void recognize(String article, Integer[][] stateTable)
    {
        // remove all punctuation symbols to avoid its interference to date
        // words.
        article = article.replaceAll("[,.!;]", "");
        // insert a space before and after the '\n' new line character to avoid the
        // adhesion with adjacent words.
        article = article.replaceAll("\n", " \n ");
        // divide article into words, remove redundant space. 
        String[] words = article.split("\\ +");

        // current state initialised to 0
        int curState = START_STATE;
        // Row number
        int row = 1;
        // DATE PHRASE COUNT
        int totalCount = 0;
        // result output 
        StringBuffer result = new StringBuffer();
        // save possible date phrase in a temporary list
        List<String> tempPhrase = new ArrayList<String>();
        // loop the whole article.
        for (int index = 0; index < words.length; index++)
        {
            // jump over '\n' character and row number add one. 
            if (words[index].equals("\n"))
            {
                row++;
                continue;
            }

            if (curState != FINAL_STATE)
            {
                // see which column in the state-transition table the current
                // word belongs.
                Integer column = getWordColumn(words[index]);
                // if the current word is not date involved or the next state is
                // empty.
                // then jump to next word, and clean the temporary space.
                if (null == column
                        || null == stateTable[curState][column.intValue()])
                {
                    tempPhrase.clear();
                    curState = START_STATE;
                }
                else
                {
                    // found a keyword, save it. 
                    if (curState == START_STATE)
                    {
                        tempPhrase.add("Row " + row + ": ");
                    }
                    tempPhrase.add(words[index]);
                    curState = stateTable[curState][column.intValue()];
                }
            }
            else
            {
                // a date expression is found, so append this expression to the result.
                for (String str : tempPhrase)
                {
                    result.append(str + " ");
                }
                result.append('\n');
                // add a record. 
                totalCount++;
                // clear the temporary list after found a date phrase. 
                tempPhrase.clear();
                // initialize the state back to START_STATE
                curState = START_STATE;
            }
        }
        
        // print out the result. 
        if (0 == totalCount)
        {
            result = new StringBuffer("No date expression is found!");
        }
        else
        {
            result.insert(0, totalCount + " date expressions are found:\n");
        }
        
        System.out.println(result);
    }

    // in the state-transition table, determine to which column current word 
    // belongs. 
    final private Integer getWordColumn(String str)
    {
        for (int i = 0; i < columns.length; i++)
        {
            // ignored cases 
            if (columns[i].contains(str.toUpperCase()))
            {
                return i;
            }
        }
        return null;
    }

    public void run(String filename)
    {
        Properties prop = FileUtils.readRules();
        String article = FileUtils.readArticle(filename);

        columns[ShortHand.MONTH.ordinal()] = new HashSet<String>(
                Arrays.asList(prop.getProperty("month").split(",")));
        columns[ShortHand.DAY_CIPHER.ordinal()] = new HashSet<String>(
                Arrays.asList(prop.getProperty("day_cipher").split(",")));
        columns[ShortHand.DAY_SUFFIX.ordinal()] = new HashSet<String>(
                Arrays.asList(prop.getProperty("day_suffix").split(",")));
        columns[ShortHand.HOLIDAY.ordinal()] = new HashSet<String>(
                Arrays.asList(prop.getProperty("holiday").split(",")));
        columns[ShortHand.OF.ordinal()] = new HashSet<String>(
                Arrays.asList(prop.getProperty("of").split(",")));

        // start date phrase recognition
        recognize(article, transTable);
    }

    public static void main(String[] args)
    {
        // Need an argument of input file name. 
        if (args.length != 1)
        {
            System.out.println(args.length);
            System.out.println("Please specifiy the input file.");
            System.out.println("USAGE: DateRecognition input_file");
            return;
        }

        new DateRecognition().run(args[0]);
    }
}
