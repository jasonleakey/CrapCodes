package edu.utdallas.ml;

import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;

public class BinBoostClassifier
{
    // Alphas
    private List<Double> weights = new ArrayList<>();
    // h(x)
    private List<Classifier> classifiers = new ArrayList<>();
    
    private final static DecimalFormat FORMATER = new DecimalFormat("###.#####");
    
    public BinBoostClassifier()
    {
    }
    
    public BinBoostClassifier(double[] weights, Classifier[] classifiers)
    {
        for (int i = 0, len = weights.length; i < len; i++)
        {
            this.weights.add(weights[i]);
            this.classifiers.add(classifiers[i]);
        }
    }
    
    public BinBoostClassifier(List<Double> weights, List<Classifier> classifiers)
    {
        this.weights = weights;
        this.classifiers = classifiers;
    }
    
    public void addClassifier(double weight, Classifier classifier)
    {
        this.weights.add(weight);
        this.classifiers.add(classifier);
    }
    
    public int classify(double val)
    {
        double result = 0.0;
        for (int i = 0, len = weights.size(); i < len; i++)
        {
            result += (weights.get(i) * classifiers.get(i).classify(val));
        }
        
        return (result >= 0) ? 1 : -1;
    }
    
    /**
     * output the boosted classifier in a form of polynomial 
     */
    public String toString()
    {
        StringBuffer buf = new StringBuffer();
        for (int i = 0, len = weights.size(); i < len; i++)
        {
            buf.append("+" + FORMATER.format(weights.get(i)) + "*" + classifiers.get(i));
        }
        // remove the first "+" character
        buf.deleteCharAt(0);
        
        return buf.toString();
    }
}
