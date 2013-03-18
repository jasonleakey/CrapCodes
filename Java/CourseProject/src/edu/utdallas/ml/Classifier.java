package edu.utdallas.ml;

public class Classifier
{
    private double threshold;
    // rflag is true when example with value x > v is classified as positive
    // rflag is false when example with value x > v is classified as negative
    private boolean rflag = true;
    
    public Classifier(double threshold)
    {
        this.threshold = threshold;
    }
    
    // set rflag to minimise the error by training data
    public void train(double[] vals, int[] labels)
    {
        rflag = true;
        int error1 = 0;
        for (int i = 0, len = vals.length; i < len; i++)
        {
            if (classify(vals[i]) != labels[i])
            {
                error1++;
            }
        }
        
        rflag = false;
        int error2 = 0;
        for (int i = 0, len = vals.length; i < len; i++)
        {
            if (classify(vals[i]) != labels[i])
            {
                error2++;
            }
        }
        
        if (error1 < error2)
        {
            rflag = true;
        }
    }
    
    public int classify(double val)
    {
        return (val <= threshold || rflag) && (val > threshold || !rflag) ? 1 : -1;
    }

    public double getThreshold()
    {
        return threshold;
    }
    
    public String toString()
    {
        return rflag ? "I(x>" + threshold + ")" : "I(x<" + threshold + ")";
    }
}
