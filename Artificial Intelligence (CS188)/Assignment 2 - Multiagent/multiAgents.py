# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        
        ghostDistances =  [manhattanDistance(newPos, ghost) for ghost in successorGameState.getGhostPositions()]
        if min(ghostDistances) < 2:
            return float('-inf')
        
        if successorGameState.getNumFood() < currentGameState.getNumFood():
            return float('inf')
        
        foodDistances = [manhattanDistance(newPos, food) for food in successorGameState.getFood().asList()]
        return -min(foodDistances)

def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        return self.get_max_value_action(gameState, 0, 0)

    def value(self, gameState, agentIndex, dpth):
        agentIndex += 1
        if(agentIndex == gameState.getNumAgents()):
            dpth += 1
            agentIndex = 0
        if gameState.isWin() or gameState.isLose() or dpth == self.depth:
            return self.evaluationFunction(gameState)
        if(agentIndex == 0):
            return self.max_value(gameState, agentIndex, dpth)
        else:
            return self.min_value(gameState, agentIndex, dpth)

    def max_value(self, gameState, agentIndex, dpth):
        v = float('-inf')
        for action in gameState.getLegalActions(agentIndex):
            s = gameState.generateSuccessor(agentIndex, action)
            v = max(v, self.value(s, agentIndex, dpth))
        return v
    
    def min_value(self, gameState, agentIndex, dpth):
        v = float('inf')
        for action in gameState.getLegalActions(agentIndex):
            s = gameState.generateSuccessor(agentIndex, action)
            v = min(v, self.value(s, agentIndex, dpth))
        return v

    def get_max_value_action(self, gameState, agentIndex, dpth):
        v = float('-inf')
        a = None
        for action in gameState.getLegalActions(agentIndex):
            s = gameState.generateSuccessor(agentIndex, action)
            val = self.value(s, agentIndex, dpth)
            v = max(v, val)
            if v == val:
                a = action
        return a
    
class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        return self.get_max_value_action(gameState, 0, 0, float('-inf'), float('inf'))
    
    def value(self, gameState, agentIndex, dpth, alpha, beta):
        agentIndex += 1
        if(agentIndex == gameState.getNumAgents()):
            dpth += 1
            agentIndex = 0
        if gameState.isWin() or gameState.isLose() or dpth == self.depth:
            return self.evaluationFunction(gameState)
        if(agentIndex == 0):
            return self.max_value(gameState, agentIndex, dpth, alpha, beta)
        else:
            return self.min_value(gameState, agentIndex, dpth, alpha, beta)

    def max_value(self, gameState, agentIndex, dpth, alpha, beta):
        v = float('-inf')
        for action in gameState.getLegalActions(agentIndex):
            s = gameState.generateSuccessor(agentIndex, action)
            v = max(v, self.value(s, agentIndex, dpth, alpha, beta))
            if v > beta:
                return v
            alpha = max(alpha, v)
        return v
    
    def min_value(self, gameState, agentIndex, dpth, alpha, beta):
        v = float('inf')
        for action in gameState.getLegalActions(agentIndex):
            s = gameState.generateSuccessor(agentIndex, action)
            v = min(v, self.value(s, agentIndex, dpth, alpha, beta))
            if v < alpha:
                return v
            beta = min(beta, v)
        return v

    def get_max_value_action(self, gameState, agentIndex, dpth, alpha, beta):
        v = float('-inf')
        a = None
        for action in gameState.getLegalActions(agentIndex):
            s = gameState.generateSuccessor(agentIndex, action)
            val = self.value(s, agentIndex, dpth, alpha, beta)
            v = max(v, val)
            if v == val:
                a = action
            if v > beta:
                return a
            alpha = max(alpha, v)
        return a

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        return self.get_max_value_action(gameState, 0, 0)
    
    def value(self, gameState, agentIndex, dpth):
        agentIndex += 1
        if(agentIndex == gameState.getNumAgents()):
            dpth += 1
            agentIndex = 0
        if gameState.isWin() or gameState.isLose() or dpth == self.depth:
            return self.evaluationFunction(gameState)
        if(agentIndex == 0):
            return self.max_value(gameState, agentIndex, dpth)
        else:
            return self.min_value(gameState, agentIndex, dpth)

    def max_value(self, gameState, agentIndex, dpth):
        v = float('-inf')
        for action in gameState.getLegalActions(agentIndex):
            s = gameState.generateSuccessor(agentIndex, action)
            v = max(v, self.value(s, agentIndex, dpth))
        return v
    
    def min_value(self, gameState, agentIndex, dpth):
        sum = float(0)
        num = 0
        for action in gameState.getLegalActions(agentIndex):
            s = gameState.generateSuccessor(agentIndex, action)
            sum += self.value(s, agentIndex, dpth)
            num += 1
        return sum / num

    def get_max_value_action(self, gameState, agentIndex, dpth):
        v = float('-inf')
        a = None
        for action in gameState.getLegalActions(agentIndex):
            s = gameState.generateSuccessor(agentIndex, action)
            val = self.value(s, agentIndex, dpth)
            v = max(v, val)
            if v == val:
                a = action
        return a

def betterEvaluationFunction(currentGameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    if currentGameState.isLose():
        return float('-inf')
    if currentGameState.isWin():
        return float('inf')
    
    pacmanPosition = currentGameState.getPacmanPosition()
    foodDistances = [manhattanDistance(pacmanPosition, food) for food in currentGameState.getFood()]
    capsuleDistances = [manhattanDistance(pacmanPosition, capsule) for capsule in currentGameState.getCapsules()]
    ghostDistances =  [(manhattanDistance(pacmanPosition, ghost.getPosition()), ghost.getPosition()) for ghost in currentGameState.getGhostStates()]
    
    # score is nice so we add score
    eval = 0.5*currentGameState.getScore()
    # more distance from food less we add
    if foodDistances:
        eval += 1.0 / min(foodDistances)
    # more distance from food less we add, but food is more important than capsule
    if capsuleDistances:
        eval += 0.5 / min(capsuleDistances)
    if ghostDistances:
        min_distance_ghost_tuple = min(ghostDistances, key=lambda x: x[0])
        min_distance = min_distance_ghost_tuple[0]
        timer = min_distance_ghost_tuple[1][0]
        if min_distance == 0:
            min_distance = 1
        if timer > 0:
            # less distance from scared ghost more we add
            eval += 15.0 / (min_distance)
        else:
            # less distance from ghost more we substract
            eval -= 10.0 / (min_distance)

    return eval
    

    

# Abbreviation
better = betterEvaluationFunction
