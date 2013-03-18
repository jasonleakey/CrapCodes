package edu.utdallas.ml;

import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;

public class RealBoostClassifier
{
    private class GClassifier
    {
        public double cplus;

        public double cminus;

        public Classifier classifier;

        public GClassifier(double cplus, double cminus, Classifier classifier)
        {
            this.cplus = cplus;
            this.cminus = cminus;
            this.classifier = classifier;
        }
    }

    private List<GClassifier> g = new ArrayList<>();
    
    private final static DecimalFormat FORMATER = new DecimalFormat("###.#####");

    public RealBoostClassifier()
    {
    }

    public void
            addClassifier(double cplus, double cminus, Classifier classifier)
    {
        g.add(new GClassifier(cplus, cminus, classifier));
    }

    public int classify(double val)
    {
        return (Double.valueOf(valueOf(val)) >= 0) ? 1 : -1;
    }

    /**
     * COMPUTE the f(x) value
     * @param val the value of training data.
     * @return the f(x) value in String form.
     */
    public String valueOf(double val)
    {
        double result = 0.0;
        for (int t = 0, len = g.size(); t < len; t++)
        {
            if (1 == g.get(t).classifier.classify(val))
            {
                result += g.get(t).cplus;
            }
            else
            {
                result += g.get(t).cminus;
            }
        }
        
        return FORMATER.format(result);
    }
}
