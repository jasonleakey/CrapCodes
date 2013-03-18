package edu.utdallas.nlp.bigram;

public class Bigram
{
    private String word1;

    private String word2;
    
    public Bigram()
    {
        
    }

    public Bigram(String word_1, String word_2)
    {
        this.setWord1(word_1);
        this.setWord2(word_2);
    }

    public String getWord1()
    {
        return word1;
    }

    public void setWord1(String word1)
    {
        this.word1 = word1;
    }

    public String getWord2()
    {
        return word2;
    }

    public void setWord2(String word2)
    {
        this.word2 = word2;
    }

    @Override
    public int hashCode()
    {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((word1 == null) ? 0 : word1.hashCode());
        result = prime * result + ((word2 == null) ? 0 : word2.hashCode());
        return result;
    }

    @Override
    public boolean equals(Object obj)
    {
        if (this == obj)
        {
            return true;
        }
        if (obj == null)
        {
            return false;
        }
        if (!(obj instanceof Bigram))
        {
            return false;
        }
        Bigram other = (Bigram) obj;
        if (word1 == null)
        {
            if (other.word1 != null)
            {
                return false;
            }
        }
        else if (!word1.equals(other.word1))
        {
            return false;
        }
        if (word2 == null)
        {
            if (other.word2 != null)
            {
                return false;
            }
        }
        else if (!word2.equals(other.word2))
        {
            return false;
        }
        return true;
    }

    @Override
    public String toString()
    {
        return "Bigram [word1=" + word1 + ", word2=" + word2 + "]";
    }
}
