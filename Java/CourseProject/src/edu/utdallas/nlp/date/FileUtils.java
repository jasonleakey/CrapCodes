package edu.utdallas.nlp.date;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Properties;

/**
 * File read functions.
 * @author jasonleakey
 *
 */
public class FileUtils
{
    protected final static String rulePath = "rules.prop";

    /*
     * read the shorthand file. 
     */
    protected static Properties readRules()
    {
        Properties prop = new Properties();
        InputStream in = null;
        try
        {
            in = FileUtils.class.getResourceAsStream(rulePath);

            prop.load(in);
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        finally
        {
            if (null != in)
            {
                try
                {
                    in.close();
                    in = null;
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
            }
        }

        return prop;
    }

    /**
     * read the content of file by given name
     * 
     * @param filename the filename you want to read 
     * @return the content of file as a string.
     */
    protected static String readArticle(String filename)
    {
        InputStream in = null;
        BufferedReader reader = null;
        String result = null;
        try
        {
            in = new FileInputStream(filename);
            reader = new BufferedReader(new InputStreamReader(in));
            
            StringBuffer buf = new StringBuffer();
            String line = null;
            while (null != (line = reader.readLine()))
            {
                buf.append(line + '\n');
            }

            result = buf.toString();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
        finally
        {
            if (null != reader)
            {
                try
                {
                    reader.close();
                    reader = null;
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
            }
            if (null != in)
            {
                try
                {
                    in.close();
                    in = null;
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
            }
        }

        return result;
    }
}
