package edu.utdallas.ml;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

/**
 * File read functions.
 * @author jasonleakey
 *
 */
public class FileUtils
{
    /**
     * read the content of file by given name
     * 
     * @param filename the filename you want to read 
     * @return the content of file as a string.
     */
    protected static String read_corpus(String filename)
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
    /**
     * write the content of file by given name
     * 
     * @param filename the filename you want to write 
     * @return true if succeed, otherwise false
     */
    protected static boolean write_file(String filename, String content)
    {
        FileOutputStream out = null;
        BufferedWriter writer = null;
        try
        {
            out = new FileOutputStream(filename);
//            in = FileUtils.class.getClassLoader().getResourceAsStream(filename);
            writer = new BufferedWriter(new OutputStreamWriter(out));
            
            writer.write(content);
        }
        catch (IOException e)
        {
            e.printStackTrace();
            return false;
        }
        finally
        {
            if (null != writer)
            {
                try
                {
                    writer.close();
                    writer = null;
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
            }
            if (null != out)
            {
                try
                {
                    out.close();
                    out = null;
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
            }
        }

        return true;
    }
    
    public static boolean isFileExisted(String path)
    {
        File file = new File(path);
        return file.exists();
    }
}

