/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
using namespace std;

/* Function: buildPath
 * 
 * Builds the shortest path. Firstly it's
 * reversed but then function reverses it.
 */
Vector<Loc> buildPath(Loc start, Loc end,
					  Vector<Vector<pair<double, Loc> > > &weightParent){
	Vector<Loc> path;
	Stack<Loc> reversedPath;

	Loc curr = end;
	while(curr != start){
		reversedPath.push(curr);
		curr = weightParent[curr.row][curr.col].second;
	}

	path.push_back(start);
	while(!reversedPath.isEmpty()){
		path.push_back(reversedPath.pop());
	}

    return path;
}

/* Function: checkNeighbor
 * 
 * checks neighbor. Calculates new weight/length and if
 * it's shorter than prevous, reduces its weight/length
 * or puts in queue. Makes it color yellow in the world.
 */
void checkNeighbor(int i, int j, double weight, Loc curr, Loc end,
				   Vector<Vector<pair<double, Loc> > > &weightParent,
				   TrailblazerPQueue<Loc> &pq, Grid<double>& world,
				   double costFn(Loc from, Loc to, Grid<double>& world),
				   double heuristic(Loc start, Loc end, Grid<double>& world)){
	Loc neighbor = makeLoc(i, j);
	double neighborWeight = costFn(curr, neighbor, world) + weight;
	double heuristicWeight = heuristic(neighbor, end, world);
	if(neighborWeight >= weightParent[i][j].first) return;
	if(weightParent[i][j].first == INT_MAX)
		pq.enqueue(neighbor, neighborWeight + heuristicWeight);
	else
		pq.decreaseKey(neighbor, neighborWeight + heuristicWeight);
	weightParent[i][j].first = neighborWeight;
	weightParent[i][j].second = curr;
	colorCell(world, neighbor, YELLOW);
}

/* Function: enqueueingNeighbors
 * 
 * Searchs 8 neighbors and checks each of them.
 */
void enqueueingNeighbors(int row, int col, Loc curr, Loc end, double weight,
						Vector<Vector<pair<double, Loc> > > &weightParent,
						TrailblazerPQueue<Loc> &pq, Grid<double>& world,
						double costFn(Loc from, Loc to, Grid<double>& world),
						double heuristic(Loc start, Loc end, Grid<double>& world)){
	for(int i = row - 1; i <= row + 1; i++){
		for(int j = col - 1; j <= col + 1; j++){
			if(!(i == row && j == col) && world.inBounds(i, j))
				checkNeighbor(i, j, weight, curr, end, weightParent, pq, world, costFn, heuristic);
		}
	}
}

/* Function: dequeueingMin
 * 
 * Dequeues first element from queue and makes it curr. Searchs
 * it's weigth/length to use it in next steps. And colors it
 * green in the world, becouse its weight is the shortest path
 * already.
 */
void dequeueingMin(Loc &curr, double &weight, TrailblazerPQueue<Loc> &pq,
			   Vector<Vector<pair<double, Loc> > > &weightParent,
			   Grid<double>& world){
    curr = pq.dequeueMin();
	weight = weightParent[curr.row][curr.col].first;
	colorCell(world, curr, GREEN);
}

/* Function: putFirstElementInPQ
 * 
 * Making algorithm and first element ready. Starting point
 * weight should be 0. Becouse of it doesn't have parent it
 * is parent of its self. Making start yellow color in the
 * world and adding in queue with priority 0.
 */
void putFirstElementInPQ(Loc start, Loc end,
						 Vector<Vector<pair<double, Loc> > > &weightParent,
						 TrailblazerPQueue<Loc> &pq, Grid<double>& world,
						 double heuristic(Loc start, Loc end, Grid<double>& world)){
	pair<double, Loc> startPair;
	startPair.first = 0;
	startPair.second = start;
	weightParent[start.row][start.col] = startPair;
	colorCell(world, start, YELLOW);
	pq.enqueue(start, heuristic(start, end, world));
}

/* Function: algorithm
 * 
 * This is the main algorithm, works with priority queue and
 * searchs the shortest paths with minimal element in queue.
 * Also fills vector with parents, where we came from, to
 * build path later.
 */
void algorithm(Loc start, Loc end, TrailblazerPQueue<Loc> &pq,
			   Vector<Vector<pair<double, Loc> > > &weightParent,
			   double costFn(Loc from, Loc to, Grid<double>& world),
			   double heuristic(Loc start, Loc end, Grid<double>& world),
			   Grid<double>& world){
	Loc curr = start;
	double weight;

	putFirstElementInPQ(start, end, weightParent, pq, world, heuristic);
	while(curr != end){
		dequeueingMin(curr, weight, pq, weightParent, world);
		if(curr == end) break;
		enqueueingNeighbors(curr.row, curr.col, curr, end, weight, weightParent, pq, world, costFn, heuristic);
	}
}

/* Function: resizeVector
 * 
 * Resizes vector to world size. On each (x, y)
 * is pair of it's weight/length and Loc of its
 * parent, from where we get there.
 */
void resizeVector (int row, int col, Loc start,
				   Vector<Vector<pair<double, Loc> > > &weightParent){
	for(int i = 0; i < row; i++){
		Vector<pair<double, Loc> > temp;
		for(int j = 0; j < col; j++){
			pair<double, Loc > newPair;
			Loc parent = start;
			newPair.first = INT_MAX;
			newPair.second = parent;
			temp.push_back(newPair);
			}
		weightParent.push_back(temp);
	}
}

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc>
shortestPath(Loc start, Loc end, Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
			 double heuristic(Loc start, Loc end, Grid<double>& world)) {
	Vector<Vector<pair<double, Loc> > > weightParent;
	TrailblazerPQueue<Loc> pq;

	resizeVector(world.numRows(), world.numCols(), start, weightParent);
	algorithm(start, end, pq, weightParent, costFn, heuristic, world);
    return buildPath(start, end, weightParent);
}

pair<int, int> findParent(pair<int, int> v,
						  Vector<Vector<pair<int, int> > > &dsu){
	if(dsu[v.first][v.second] == v) return v;
	return dsu[v.first][v.second] = findParent(dsu[v.first][v.second], dsu);
}

/* Function: buildMST
 * 
 * Finds shortest edge and checks parents/colors.
 */
Set<Edge> buildMST(TrailblazerPQueue<Edge> &pq,
				   Vector<Vector<pair<int, int> > > &dsu){
	Set<Edge> maze;
	while(!pq.isEmpty()){
		Edge newEdge = pq.dequeueMin();
		pair<int, int> v1;
		v1.first = newEdge.start.row;
		v1.second = newEdge.start.col;
		pair<int, int> v2;
		v2.first = newEdge.end.row;
		v2.second = newEdge.end.col;
		pair<int, int> v1Parent = findParent(v1, dsu);
		pair<int, int> v2Parent = findParent(v2, dsu);
		if(v1Parent != v2Parent){
			maze.add(newEdge);
			dsu[v1Parent.first][v1Parent.second] = v2Parent;
		}
	}
	return maze;
}
/* Function: generateEdges
 * 
 * Generates horizontal and vertical edges
 * and fills queue with random weights.
 */
void generateEdges(int row, int col, TrailblazerPQueue<Edge> &pq){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			Loc curr = makeLoc(i, j);
			if(j+1 < col){
				Loc neighbor = makeLoc(i, j+1);
				Edge newEdge = makeEdge(curr, neighbor);
				double weight = randomReal(0,1);
				pq.enqueue(newEdge, weight);
			}
			if(i+1 < row){
				Loc neighbor = makeLoc(i+1, j);
				Edge newEdge = makeEdge(curr, neighbor);
				double weight = randomReal(0,1);
				pq.enqueue(newEdge, weight);
			}
		}
	}
}
/* Function: fillDsu
 * 
 * Fills vector with parents/colors. In the
 * begining every point is parent of itself.
 */
void fillDsu(Vector<Vector<pair<int, int> > > &dsu, int row, int col){
	for(int i = 0; i < row; i++){
		Vector<pair<int, int> > temp;
		for(int j = 0; j < col; j++){
			pair<int, int> newPair;
			newPair.first = i;
			newPair.second = j;
			temp.push_back(newPair);
		}
		dsu.push_back(temp);
	}
}
/* Function: createMaze
 * 
 * Creates a maze of the specified dimensions using a randomized version of
 * Kruskal's algorithm, then returns a set of all of the edges in the maze.
 *
 * As specified in the assignment handout, the edges you should return here
 * represent the connections between locations in the graph that are passable.
 * Our provided starter code will then use these edges to build up a Grid
 * representation of the maze.
 */
Set<Edge> createMaze(int numRows, int numCols) {
	Vector<Vector<pair<int, int> > > dsu;
	TrailblazerPQueue<Edge> pq;
	fillDsu(dsu, numRows,numCols);
	generateEdges(numRows, numCols, pq);
    return buildMST(pq, dsu);
}
