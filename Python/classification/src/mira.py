# Mira implementation
import util
PRINT = True

class MiraClassifier:
  """
  Mira classifier.
  
  Note that the variable 'datum' in this code refers to a counter of features
  (not to a raw samples.Datum).
  """
  def __init__( self, legalLabels, max_iterations):
    self.legalLabels = legalLabels
    self.type = "mira"
    self.automaticTuning = False 
    self.C = 0.001
    self.legalLabels = legalLabels
    self.max_iterations = max_iterations
    self.initializeWeightsToZero()

  def initializeWeightsToZero(self):
    "Resets the weights of each label to zero vectors" 
    self.weights = {}
    for label in self.legalLabels:
      self.weights[label] = util.Counter() # this is the data-structure you should use
  
  def train(self, trainingData, trainingLabels, validationData, validationLabels):
    "Outside shell to call your method. Do not modify this method."  
      
    self.features = trainingData[0].keys() # this could be useful for your code later...
    
    if (self.automaticTuning):
        Cgrid = [0.002, 0.004, 0.008]
    else:
        Cgrid = [self.C]
        
    return self.trainAndTune(trainingData, trainingLabels, validationData, validationLabels, Cgrid)

  def trainAndTune(self, trainingData, trainingLabels, validationData, validationLabels, Cgrid):
    """
    This method sets self.weights using MIRA.  Train the classifier for each value of C in Cgrid, 
    then store the weights that give the best accuracy on the validationData.
    
    Use the provided self.weights[label] data structure so that 
    the classify method works correctly. Also, recall that a
    datum is a counter from features to values for those features
    representing a vector of values.
    """
    "*** YOUR CODE HERE ***"
    #util.raiseNotDefined()
    maxCorrect = 0
    minC = 1000.0
    Pi = 1.0
    for C in Cgrid:
        weights=self.weights.copy()
        for i in self.legalLabels: #
            weights[i]=trainingData[0].copy()#initial the weight table
        for iteration in range(self.max_iterations):
            print "Starting iteration ", iteration, "..."
            for j in range(len(trainingData)):
                label=trainingLabels[j]
                f=trainingData[j].copy()
                tempCounter=util.Counter()
                for digit in self.legalLabels:
                    tempCounter[digit]=weights[digit] * f
                tempy=tempCounter.argMax()
                if tempy!=label:
                    Pi=float((weights[tempy] - weights[label])* f + 1)/(2 * (f * f))
                    Pi=min(C,Pi)
                    f.divideAll(1.0/Pi) # tao * f
                    tf=f
                    weights[label] = weights[label] + tf #adjust weights
                    weights[tempy] = weights[tempy] - tf
                  
        guesses = []#validation
        for datum in validationData:
            vectors = util.Counter()
            for l in self.legalLabels:
                vectors[l] = weights[l] * datum
            guesses.append(vectors.argMax())
        correct = [guesses[i] == validationLabels[i] for i in range(len(validationLabels))].count(True)    
        print str('C='),C,str(correct), ("correct out of " + str(len(validationLabels)) + " (%.1f%%).") % (100.0 * correct / len(validationLabels))
        if correct > maxCorrect:
            minC = C
            self.C = minC
            maxCorrect=correct
            self.weights=weights.copy()    
  def classify(self, data ):
    """
    Classifies each datum as the label that most closely matches the prototype vector
    for that label.  See the project description for details.
    
    Recall that a datum is a util.counter... 
    """
    guesses = []
    for datum in data:
      vectors = util.Counter()
      for l in self.legalLabels:
        vectors[l] = self.weights[l] * datum
      guesses.append(vectors.argMax())
    return guesses

  
  def findHighOddsFeatures(self, label1, label2):
    """
    Returns a list of the 100 features with the greatest difference in feature values
                     w_label1 - w_label2

    """
    featuresOdds = []
    tempCounter=self.weights[label1]-(self.weights[label2])
    totalFeaturesOdds=tempCounter.sortedKeys()
    featuresOdds = totalFeaturesOdds[:100]
    "*** YOUR CODE HERE ***"

    return featuresOdds

