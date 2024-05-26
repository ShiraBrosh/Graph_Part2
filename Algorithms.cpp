//ID - 211821137
//GMAIL - shira1d2631@gmail.com

#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <limits>
#include <algorithm>
#include "Algorithms.hpp"
#include "Graph.hpp"

namespace ariel {

void dfs(const Graph& graph, std::size_t start, std::unordered_set<int>& visited, std::stack<std::size_t>& st) {
    visited.insert(static_cast<int>(start)); 

    for (std::size_t i = 0; i < graph.getnumvertices(); i++) { //itrate over all vertices
        if (graph.getadjacencymatrix(start, i) != 0) { //if there is an edge between the vertices
            if (visited.count(static_cast<int>(i)) == 0) { //if the vertex is not visited
                dfs(graph, i, visited, st); 
            }
        }
    }

    st.push(start); 
}

bool Algorithms::isConnected(const Graph& graph) {
    int num_vertices = graph.getnumvertices();//get the number of vertices
    if (num_vertices < 0) {
        throw std::runtime_error("Number of vertices cannot be negative.");//if the number of vertices is negative
    }

    std::size_t n = static_cast<std::size_t>(num_vertices); //convert the number of vertices to size_t
    std::unordered_set<int> visited; //create a set of visited vertices
    std::stack<std::size_t> st; //create a stack of vertices

    dfs(graph, 0, visited, st);//run the dfs algorithm

    std::vector<std::vector<int>> reversed_graph(n, std::vector<int>(n, 0));
    for (std::size_t i = 0; i < n; i++) { //create a reversed graph
        for (std::size_t j = 0; j < n; j++) { //itrate over all vertices
            if (graph.getadjacencymatrix(i, j) != 0) { //if there is an edge between the vertices
                reversed_graph[j][i] = graph.getadjacencymatrix(i, j);//add the edge to the reversed graph
            }
        }
    }

    visited.clear();

    while (!st.empty()) {
        auto current_vertex = st.top(); //get the top vertex
        st.pop();//pop the top vertex

        if (visited.count(static_cast<int>(current_vertex)) == 0) {//if the vertex is not visited
            std::unordered_set<int> dfs_reversed;//create a set of visited vertices
            std::stack<std::size_t> dfs_reversed_stack;
            Graph reversed_graph_obj(reversed_graph);
            dfs(reversed_graph_obj, current_vertex, dfs_reversed, dfs_reversed_stack);

            if (dfs_reversed.size() != n) { //if the size of the set is not equal to the number of vertices
                return false;
            }

            for (int v : dfs_reversed) {
                visited.insert(v);
            }
        }
    }

    return true;
}

std::pair<std::vector<int>, std::vector<std::size_t>> bellmanFord(const Graph& graph, std::size_t start, bool returnParent = false) {
    int num_vertices = graph.getnumvertices(); //get the number of vertices
    if (num_vertices < 0) {
        throw std::runtime_error("Number of vertices cannot be negative."); //if the number of vertices is negative
    }

    std::size_t n = static_cast<std::size_t>(num_vertices); //convert the number of vertices to size_t
    std::vector<int> dist(n, std::numeric_limits<int>::max()); 
    std::vector<std::size_t> parent(n, n); // Initialize parent vector with n (invalid index)
    dist[start] = 0;
    parent[start] = start; // Set parent of start vertex to itself

    for (std::size_t i = 0; i < n - 1; i++) { //itrate over all vertices
        for (std::size_t u = 0; u < n; u++) { 
            for (std::size_t v = 0; v < n; v++) { 
                if (graph.getadjacencymatrix(u, v) != 0) { // if there is an edge between the vertices
                    if (dist[u] != std::numeric_limits<int>::max() &&
                        dist[v] > dist[u] + graph.getadjacencymatrix(u, v)) { //if the distance is not equal to the maximum value and the distance is greater than the distance between the vertices
                        dist[v] = dist[u] + graph.getadjacencymatrix(u, v); // Set distance of v to u + weight of edge u-v
                        parent[v] = u; // Set parent of v to u
                    }
                }
            }
        }
    }

    if (returnParent) { //if returnParent is true
        return std::make_pair(dist, parent); //return the distance and the parent
    }

    return std::make_pair(dist, std::vector<std::size_t>());
}

bool Algorithms::hasNegativeCycle(const Graph& graph) { //  Bellman-Ford algorithm
    int num_vertices = graph.getnumvertices();
    if (num_vertices < 0) { //if the number of vertices is negative
        throw std::runtime_error("Number of vertices cannot be negative.");
    }

    std::size_t n = static_cast<std::size_t>(num_vertices); // convert the number of vertices to size_t

    for (std::size_t start = 0; start < n; start++) {
        std::pair<std::vector<int>, std::vector<std::size_t>> bellmanFordResult = bellmanFord(graph, start, false);
        std::vector<int> dist = bellmanFordResult.first;

        for (std::size_t u = 0; u < n; u++) { //itrate over all vertices
            for (std::size_t v = 0; v < n; v++) { //itrate over all vertices
                if (graph.getadjacencymatrix(u, v) != 0) { 
                    if (dist[u] != std::numeric_limits<int>::max() && dist[u] + graph.getadjacencymatrix(u, v) < dist[v]) { 
                        return true;
                    }
                }
            }
        }
    }

    return false;
}


std::string Algorithms::shortestPath(const Graph& g, std::size_t start, std::size_t end) {
    if (Algorithms::hasNegativeCycle(g)) { //if there is a negative cycle
        return "-1"; 
    }

    int num_vertices = g.getnumvertices();
    if (num_vertices < 0) {
        throw std::runtime_error("Number of vertices cannot be negative.");
    }

    std::size_t n = static_cast<std::size_t>(num_vertices);//convert the number of vertices to size_t
    std::pair<std::vector<int>, std::vector<std::size_t>> bellmanFordResult = bellmanFord(g, start, false); //run the bellmanFord algorithm
    std::vector<int> dist = bellmanFordResult.first; //get the distance
    std::vector<std::size_t> parent = bellmanFord(g, start, true).second; //get the parent

    if (dist[end] == std::numeric_limits<int>::max()) { // if the distance is equal to the maximum value
        return "-1";
    }


    std::vector<int> path; //create a vector of the path
    std::size_t current_vertex = end; //set the current vertex to the end
    if (current_vertex < 0) { //if the current vertex is negative
        throw std::runtime_error("Vertex index cannot be negative.");
    }

    while (current_vertex != start) { //while the current vertex is not equal to the start
        if (current_vertex >= n) { //if the current vertex is greater than or equal to the number of vertices
            throw std::runtime_error("Vertex index is out of range.");
        }
        path.push_back(static_cast<int>(current_vertex));//add the current vertex to the path
        current_vertex = parent[current_vertex];//set the current vertex to the parent of the current vertex
    }
    path.push_back(static_cast<int>(start));//add the start vertex to the path
    std::reverse(path.begin(), path.end());//reverse the path

    std::ostringstream oss; //create an output string stream
    for (std::size_t i = 0; i < path.size(); i++) { //itrate over all vertices
        if (i > 0) { //if i is greater than 0
            oss << "->"; //add an arrow to the output string stream
        }
        oss << path[i];//add the vertex to the output string stream
    }

    return oss.str();//return the output string stream
}

std::string Algorithms::detectCycleDFS(const Graph& graphObj, std::size_t currNode, std::vector<int>& nodeColors, std::vector<std::size_t>& cycleStack) {
    nodeColors[currNode] = 1;
    cycleStack.push_back(currNode); // Add current node to cycle stack

    for (std::size_t i = 0; i < graphObj.getnumvertices(); i++) {//itrate over all vertices
        if (graphObj.getadjacencymatrix(currNode, i) != 0 && currNode != i){ //if there is an edge between the vertices and the vertices are not equal
            if (nodeColors[i] == 0) {//if the vertex is not visited
                
                std::string cyclePath = detectCycleDFS(graphObj, i, nodeColors, cycleStack);
                if (cyclePath != "0") { //if the cyclePath is not equal to "0"
                    return cyclePath;
                }
            }
            else if (nodeColors[i] == 1) {
                std::string route = "";//create a string of the route
                for (std::size_t j = 0; j < cycleStack.size() ; j++) { // itrate over all vertices
                    if (cycleStack[j] == i || route != "") {//if the vertex is equal to i or the route is not empty
                        route += std::to_string(cycleStack[j]) + "->"  ; //add the vertex to the route
                    }
                }
                return route + std::to_string(i);//return the route
            }
        }
    }
    nodeColors[currNode] = 2; // Mark node as visited
    cycleStack.pop_back(); // Remove current node from cycle stack
    return "0";
}

std::string Algorithms::isContainsCycle(const Graph& graphObj) {
    int vertex_count = graphObj.getnumvertices(); //get the number of vertices
    if (vertex_count < 0) { //if the number of vertices is negative
        throw std::runtime_error("Number of vertices cannot be negative.");
    }

    std::size_t numNodes = static_cast<std::size_t>(vertex_count); //convert the number of vertices to size_t
    std::vector<int> nodeColors(numNodes, 0);//create a vector of the colors of the vertices
    std::vector<std::size_t> cycleStack;//create a vector of the cycle stack
    for (std::size_t i = 0; i < numNodes; i++) {
        if (nodeColors[i] == 0) {//if the vertex is not visited
            std::string cyclePath = detectCycleDFS(graphObj, i, nodeColors, cycleStack);
            if (cyclePath != "0") {//if the cyclePath is not equal to "0"
                return cyclePath;
            }
            // Reset nodeColors and clear cycleStack
            std::fill(nodeColors.begin(), nodeColors.end(), 0);
            cycleStack.clear();
        }
    }

    return "0";
}

std::string Algorithms::isBipartite(const Graph& graph) {
   int num_vertices = graph.getnumvertices();//get the number of vertices
    if (num_vertices < 0) {//if the number of vertices is negative
        throw std::runtime_error("Number of vertices cannot be negative.");
    }

    std::size_t numNodes = static_cast<std::size_t>(num_vertices); //convert the number of vertices to size_t


    std::vector<std::vector<int>> undirectedGraph(numNodes, std::vector<int>(numNodes, 0));
    for (std::size_t u = 0; u < numNodes; u++) {//itrate over all vertices
        for (std::size_t v = 0; v < numNodes; v++) { 
            if (graph.getadjacencymatrix(u, v) != 0 || graph.getadjacencymatrix(v, u) != 0) { //if there is an edge between the vertices
                undirectedGraph[u][v] = 1; 
                undirectedGraph[v][u] = 1;
            }
        }
        
    }

    std::vector<int> partitionA;
    std::vector<int> partitionB;
    std::vector<int> nodeColors(numNodes, -1); 

    for (std::size_t startNode = 0; startNode < numNodes; startNode++) { //itrate over all vertices
        if (nodeColors[startNode] == -1) { //if the vertex is not visited
            if (!bipartiteDFS(undirectedGraph, startNode, nodeColors, partitionA, partitionB, 0)) {
                return "0";
            }
        }
    }

    std::ostringstream outputStream;//create an output string stream
    outputStream << "The graph is bipartite: A={";
    for (std::size_t idx = 0; idx < partitionA.size(); idx++) { 
        outputStream << partitionA[idx];//add the vertex to the output string stream
        if (idx < partitionA.size() - 1) {//if the index is less than the size of the partition - 1
            outputStream << ", ";
        }
    }

    outputStream << "}, B={";
    for (std::size_t idx = 0; idx < partitionB.size(); idx++) {
        outputStream << partitionB[idx];//add the vertex to the output string stream
        if (idx < partitionB.size() - 1) {//if the index is less than the size of the partition - 1
            outputStream << ", "; //add a comma to the output string stream
        }
    }

    outputStream << "}";

    return outputStream.str();
}

bool Algorithms::bipartiteDFS(const std::vector<std::vector<int>>& graph, std::size_t currNode, std::vector<int>& nodeColors,
                  std::vector<int>& partitionA, std::vector<int>& partitionB, int currColor) { // 0 - white, 1 - black
    nodeColors[currNode] = currColor; // Mark node as visited

    if (currColor == 0) { //if the color is white
        partitionA.push_back(currNode);//add the vertex to partition A
    } else {
        partitionB.push_back(currNode);
    }
    for (std::size_t neighbor = 0; neighbor < graph.size(); neighbor++) { //itrate over all vertices
        if (graph[currNode][neighbor] != 0) { //if there is an edge between the vertices
            if (nodeColors[neighbor] == -1) {//if the vertex is not visited
                return bipartiteDFS(graph, neighbor, nodeColors, partitionA, partitionB, 1 - currColor);
            } else if (nodeColors[neighbor] == currColor) { //if the color is equal to the current color
                return false;
            } 
            
        }
    }

    

    return true;
}

}