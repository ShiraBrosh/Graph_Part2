//ID - 211821137
//GMAIL - shira1d2631@gmail.com

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <string>
#include <vector>
#include "Graph.hpp"
#include <deque>


namespace ariel {

class Algorithms {
public:
    //delicaration of the funcations
    static bool isConnected(const Graph& graph);
    static std::string shortestPath(const Graph& graph, std::size_t start, std::size_t end);
    static bool hasNegativeCycle(const Graph& graph);

    static std::string isContainsCycle(const Graph& graph);
    static std::string isBipartite(const Graph& graph);
    static bool bipartiteDFS(const std::vector<std::vector<int>>& graph, std::size_t currNode, std::vector<int>& nodeColors,
                  std::vector<int>& partitionA, std::vector<int>& partitionB, int currColor);
    
    static std::string detectCycleDFS(
        const Graph& graphObj,
        std::size_t currNode,
        std::vector<int>& nodeColors,
        std::vector<std::size_t>& cycleStack
    );

};

} // namespace ariel

#endif // ALGORITHMS_HPP