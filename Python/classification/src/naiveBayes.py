#from gdata.tlslite import mathtls
import util
import classificationMethod
import math

class NaiveBayesClassifier(classificationMethod.ClassificationMethod):
  """
  See the project description for the specifications of the Naive Bayes classifier.
  
  Note that the variable 'datum' in this code refers to a counter of features
  (not to a raw samples.Datum).
  """
  def __init__(self, legalLabels):
    self.legalLabels = legalLabels
    self.type = "naivebayes"
    self.k = 1 # this is the smoothing parameter, ** use it in your train method **
    self.automaticTuning = False # Look at this flag to decide whether to choose k automatically ** use this in your train method **

  def setSmoothing(self, k):
    """
    This is used by the main method to change the smoothing parameter before training.
    Do not modify this method.
    """
    self.k = k

  def train(self, trainingData, trainingLabels, validationData, validationLabels):
    """
    Outside shell to call your method. Do not modify this method.
    """

    self.features = trainingData[0].keys() # this could be useful for your code later...

    if (self.automaticTuning):
        kgrid = [0.001, 0.01, 0.05, 0.1, 0.5, 1, 5, 10, 20, 50]
    else:
        kgrid = [self.k]

    self.trainAndTune(trainingData, trainingLabels, validationData, validationLabels, kgrid)

  def trainAndTune(self, trainingData, trainingLabels, validationData, validationLabels, kgrid):
    """
    Trains the classifier by collecting counts over the training data, and
    stores the Laplace smoothed estimates so that they can be used to classify.
    Evaluate each value of k in kgrid to choose the smoothing parameter 
    that gives the best accuracy on the held-out validationData.
    
    trainingData and validationData are lists of feature Counters.  The corresponding
    label lists contain the correct label for each datum.
    
    To get the list of all possible features or labels, use self.features and 
    self.legalLabels.
    """

    "*** YOUR CODE HERE ***"
    counter = util.Counter()
    counter.incrementAll(trainingLabels, 1)
    trainNum = len(trainingLabels)

    self.prior = util.Counter()
    cnt_fi_y = util.Counter()
    for y in self.legalLabels:
        self.prior[y] = float(counter[y]) / trainNum
        clsIdx = [i for i in range(trainNum) if trainingLabels[i] == y]
        for i in self.features:
            cnt = 0
            for j in clsIdx:
                if trainingData[j][i] == 1:
                    cnt += 1
            cnt_fi_y[(y, i)] = cnt

    maxCorrectCnt = 0
    minK = 1000
    self.CondProb = util.Counter()
    for k in kgrid:
        CondProb = util.Counter()
        for y in self.legalLabels:
            for i in self.features:
                CondProb[(y, i)] = float(cnt_fi_y[(y, i)] + k) / (counter[y] + 2 * k)

        correctCnt = 0
        for s, datum in enumerate(validationData):
            posterior = util.Counter()
            for y in self.legalLabels:
                condsum = 0.0
                for i in self.features:
                    if datum[i] == 1:
                        condsum += (math.log(CondProb[(y, i)]))
                    else:
                        condsum += (math.log(1 - CondProb[(y, i)]))
                posterior[y] = math.log(self.prior[y]) + condsum
            guess = posterior.argMax()
            if guess == validationLabels[s]:
                correctCnt += 1
        if correctCnt > maxCorrectCnt or (correctCnt == maxCorrectCnt and k < minK):
            minK = k
            maxCorrectCnt = correctCnt
            self.setSmoothing(k)
            self.CondProb = CondProb.copy()


  def classify(self, testData):
    """
    Classify the data based on the posterior distribution over labels.
    
    You shouldn't modify this method.
    """
    guesses = []
    self.posteriors = [] # Log posteriors are stored for later data analysis (autograder).
    for datum in testData:
      posterior = self.calculateLogJointProbabilities(datum)
      guesses.append(posterior.argMax())
      self.posteriors.append(posterior)
    return guesses

  def calculateLogJointProbabilities(self, datum):
    """
    Returns the log-joint distribution over legal labels and the datum.
    Each log-probability should be stored in the log-joint counter, e.g.    
    logJoint[3] = <Estimate of log( P(Label = 3, datum) )>
    """
    logJoint = util.Counter()

    "*** YOUR CODE HERE ***"
    for y in self.legalLabels:
        condsum = 0.0
        for i in self.features:
            if datum[i] == 1:
                condsum += (math.log(self.CondProb[(y, i)]))
            else:
                condsum += (math.log(1 - self.CondProb[(y, i)]))
        logJoint[y] = math.log(self.prior[y]) + condsum
    return logJoint

  def findHighOddsFeatures(self, label1, label2):
    """
    Returns the 100 best features for the odds ratio:
            P(feature=1 | label1)/P(feature=1 | label2) 
    """
    featuresOdds = []

    proCounter = util.Counter()
    tempCounter = self.CondProb.copy()
    for key in self.features:
        proCounter[key] = (tempCounter[(label1, key)]) / (self.CondProb[(label2, key)])
    featuresOdds = proCounter.sortedKeys()
    featuresOdds = featuresOdds[:100]
    # "*** YOUR CODE HERE ***"
    return featuresOdds
