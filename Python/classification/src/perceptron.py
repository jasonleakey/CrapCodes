# Perceptron implementation
import util
PRINT = True

class PerceptronClassifier:
  """
  Perceptron classifier.
  
  Note that the variable 'datum' in this code refers to a counter of features
  (not to a raw samples.Datum).
  """
  def __init__( self, legalLabels, max_iterations):
    self.legalLabels = legalLabels
    self.type = "perceptron"
    self.max_iterations = max_iterations
    self.weights = {}
    for label in legalLabels:
      self.weights[label] = util.Counter() # this is the data-structure you should use
      
  def train( self, trainingData, trainingLabels, validationData, validationLabels ):
    """
    The training loop for the perceptron passes through the training data several
    times and updates the weight vector for each label based on classification errors.
    See the project description for details. 
    
    Use the provided self.weights[label] data structure so that 
    the classify method works correctly. Also, recall that a
    datum is a counter from features to values for those features
    (and thus represents a vector a values).
    """
    
    self.features = trainingData[0].keys() # could be useful later
   
    for i in self.legalLabels: #
          self.weights[i]=trainingData[0].copy()#initial the weight table
    for iteration in range(self.max_iterations):
      print "Starting iteration ", iteration, "..."
      for j in range(len(trainingData)):
          label=trainingLabels[j]
          tempCounter=util.Counter()
          for digit in self.legalLabels:
              tempCounter[digit]=self.weights[digit].__mul__(trainingData[j])
          tempy=tempCounter.argMax()
          if tempy!=label:
              self.weights[label] = self.weights[label].__add__(trainingData[j])#adjust weights
              self.weights[tempy] = self.weights[tempy].__sub__(trainingData[j])
        #  "*** YOUR CODE HERE ***"
        #  util.raiseNotDefined()
    
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
    Returns a list of the 100 features with the greatest difference in weights:
                     w_label1 - w_label2

    """
    featuresOdds = []
    tempCounter=self.weights[label1].__sub__(self.weights[label2])
    totalFeaturesOdds=tempCounter.sortedKeys()
    featuresOdds = totalFeaturesOdds[:100]
 #  "*** YOUR CODE HERE ***"
 #   util.raiseNotDefined()

    return featuresOdds

