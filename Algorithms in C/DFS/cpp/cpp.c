#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <list>

using std::vector;
using std::map;
using std::list;
using std::ifstream;
using std::cout;
using std::endl;

// Constants
//-------------------------------
const char FILENAME[] = "test.txt";

// Prototypes
//-------------------------------
long get_node_count(const char filename[]);
vector< vector<long> > parse_file(const char filename[]);
map< long, vector<long> > compute_scc(vector< vector<long> > &graph);
vector< vector<long> > reverse_graph(const vector< vector<long> > &graph);
void dfs_loop(const vector< vector<long> > &graph, vector<long> &finishTime, vector<long> &leader);
long dfs(const vector< vector<long> > &graph, long nodeIndex, vector<bool> &expanded, vector<long> &finishTime, long t, vector<long> &leader, long s);
list<unsigned long> get_largest_components(const map< long, vector<long> > scc, long size);


/**
 * Main
 */
int main() {
    // Get the sequential graph representation from the file
    vector< vector<long> > graph = parse_file(FILENAME);

    // Compute the strongly-connected components
    map< long, vector<long> > scc = compute_scc(graph);

    // Compute the largest 5 components and print them out
    list<unsigned long> largestComponents = get_largest_components(scc, 5);

    list<unsigned long>::iterator it;
    for (it = largestComponents.begin(); it != largestComponents.end(); it++) {
        cout << *it << ' ';
    }
    cout << endl;

    return 0;
}


/**
 * Parse an input file as a graph, and return the graph.
 */
vector< vector<long> > parse_file(const char filename[]) {
    // Get the node count and prepare the graph
    long nodeCount = get_node_count(filename);
    vector< vector<long> > graph(nodeCount);

    // Open file and extract the data
    ifstream graphFile(filename);

    long nodeIndex;
    long outIndex;

    while (graphFile) {
        graphFile >> nodeIndex;
        graphFile >> outIndex;

        // Add the new outgoing edge to the node
        graph[nodeIndex - 1].push_back(outIndex - 1);
    }

    return graph;
}


/**
 * Get the count of nodes from a graph file representation
 */
long get_node_count(const char filename[]) {
    // Open file and keep track of how many times the value changes
    ifstream graphFile(filename);

    long maxNodeIndex = 0;
    long nodeIndex = 0;

    while (graphFile) {
        // Check the node index
        graphFile >> nodeIndex;

        if (nodeIndex > maxNodeIndex) {
            maxNodeIndex = nodeIndex;
        }

        // Check the outgoing edge
        graphFile >> nodeIndex;

        if (nodeIndex > maxNodeIndex) {
            maxNodeIndex = nodeIndex;
        }
    }

    return maxNodeIndex;
}


/**
 * Compute all of the strongly-connected components of a graph
 * using depth-first search, Kosaraju's 2-pass method
 */
map< long, vector<long> > compute_scc(vector< vector<long> > &graph) {
    // Create finishing time and leader vectors to record the data
    // from the search
    vector<long> finishTime(graph.size(), 0);
    vector<long> leader(graph.size(), 0);

    // Initialize the finish time initially to be the numbers of the graph
    vector<long>::iterator it;
    long index = 0;
    for (it = finishTime.begin(); it != finishTime.end(); it++) {
        *it = index;
        index++;
    }

    // Reverse the graph, to compute the 'magic' finishing times
    vector< vector<long> > reversed = reverse_graph(graph);
    dfs_loop(reversed, finishTime, leader);

    // Compute the SCC leaders using the finishing times
    dfs_loop(graph, finishTime, leader);

    // Distribute nodes to SCCs
    map< long, vector<long> > scc;
    vector<long>::iterator lit;

    for (lit = leader.begin(); lit != leader.end(); lit++) {
        long nodeIndex = lit - leader.begin();

        // Append node to SCC
        scc[*lit].push_back(nodeIndex);
    }

    return scc;
}


/**
 * Reverse a directed graph by looping through each node/edge pair
 * and recording the reverse
 */
vector< vector<long> > reverse_graph(const vector< vector<long> > &graph) {
    // Create new graph
    vector< vector<long> > reversed(graph.size());

    // Loop through all elements and fill new graph with reversed endpoints
    vector< vector<long> >::const_iterator it;
    for (it = graph.begin(); it != graph.end(); it++) {
        long nodeIndex = it - graph.begin();

        // Loop through all outgoing edges, and reverse them in new graph
        vector<long>::const_iterator eit;
        for (eit = graph[nodeIndex].begin(); eit != graph[nodeIndex].end(); eit++) {
            reversed[*eit].push_back(nodeIndex);
        }
    }

    return reversed;
}


/**
 * Compute a depth-first search through all nodes of a graph
 */
void dfs_loop(const vector< vector<long> > &graph, vector<long> &finishTime, vector<long> &leader) {
    // Create expanded tracker and copied finishing time tracker
    vector<bool> expanded(graph.size(), 0);
    vector<long> loopFinishTime = finishTime;

    long t = 0;
    vector<long>::reverse_iterator it;

    // Outer loop through all nodes in order to cover disconnected
    // sections of the graph
    for (it = loopFinishTime.rbegin(); it != loopFinishTime.rend(); it++) {
        // Compute a depth-first search if the node hasn't
        // been expanded yet
        if (!expanded[*it]) {
            t = dfs(graph, *it, expanded, finishTime, t, leader, *it);
        }
    }
}


/**
 * Search through a directed graph recursively, beginning at node 'nodeIndex',
 * until no more node can be searched, recording the finishing times and the 
 * leaders
 */
long dfs(
    const vector< vector<long> > &graph,
    long nodeIndex,
    vector<bool> &expanded,
    vector<long> &finishTime,
    long t,
    vector<long> &leader,
    long s
) {
    // Mark the current node as explored
    expanded[nodeIndex] = true;

    // Set the leader to the given leader
    leader[nodeIndex] = s;

    // Loop through outgoing edges
    vector<long>::const_iterator it;
    for (it = graph[nodeIndex].begin(); it != graph[nodeIndex].end(); it++) {
        // Recursively call DFS if not explored
        if (!expanded[*it]) {
            t = dfs(graph, *it, expanded, finishTime, t, leader, s);
        }
    }

    // Update the finishing time
    finishTime[t] = nodeIndex;
    t++;

    return t;
}


/**
 * Computes the largest 'n' of a strongly-connected component list
 * and return them
 */
list<unsigned long> get_largest_components(const map< long, vector<long> > scc, long size) {
    // Create vector to hold the largest components
    list<unsigned long> largest(size, 0);

    // Iterate through map and keep track of largest components
    map< long, vector<long> >::const_iterator it;
    for (it = scc.begin(); it != scc.end(); it++) {
        // Search through the current largest list to see if there exists
        // an SCC with less elements than the current one
        list<unsigned long>::iterator lit;
        for (lit = largest.begin(); lit != largest.end(); lit++) {
            // Compare size and change largest if needed, inserting
            // the new one at the proper position, and popping off the old
            if (*lit < it->second.size()) {
                largest.insert(lit, it->second.size());
                largest.pop_back();
                break;
            }
        }
    }

    return largest;
}