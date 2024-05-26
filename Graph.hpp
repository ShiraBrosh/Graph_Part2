//ID - 211821137
//GMAIL - shira1d2631@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <stdexcept>
#include <initializer_list>

namespace ariel {

class Graph {
private:
    std::size_t numVertices;
    std::size_t edgeCount;
    bool isWeighted;
    std::vector<std::vector<int>> adjacencyMatrix;


public:
    Graph(); // Default constructor
    Graph(const std::vector<std::vector<int>>& matrix); // Constructor to accept adjacency matrix
    Graph(const std::initializer_list<std::initializer_list<int>>& list); // Constructor to accept an initializer list
    Graph(const Graph& other); // Copy constructor
    Graph& operator=(const Graph& other); // Assignment operator

    void loadGraph(const std::vector<std::vector<int>>& matrix);


    void printGraph() const;
    int getnumvertices() const;
    int getedgecount() const;
    int getadjacencymatrix(std::size_t i, std::size_t j) const;

    // Arithmetic operators
    Graph operator+(const Graph& other) const; // Add two graphs
    Graph& operator+=(const Graph& other); // Add two graphs and assign the result to the first graph
    Graph operator+(const int scalar) const; // Add a scalar to the graph
    Graph& operator+=(const int scalar); // Add a scalar to the graph and assign the result
    Graph operator-(const Graph& other) const; // Subtract two graphs
    Graph& operator-=(const Graph& other); // Subtract two graphs and assign the result to the first graph
    Graph operator-(const int scalar) const; // Subtract a scalar from the graph
    Graph& operator-=(const int scalar); // Subtract a scalar from the graph and assign the result
    Graph& operator/=(int scalar); // Divide the graph by a scalar
    Graph& operator*=(int scalar);// Multiply the graph by a scalar
    Graph operator*(const Graph& other) const; // Multiply two graphs

    // Unary plus operator
    Graph operator+() const; // Unary plus operator

    // Negation operator
    Graph operator-() const; // Negate the graph

    // Increment/Decrement operators
    Graph& operator++(); // Pre-increment
    Graph operator++(int); // Post-increment
    Graph& operator--(); // Pre-decrement
    Graph operator--(int); // Post-decrement

    // Comparison operators
    bool operator==(const Graph& other) const;
    bool operator!=(const Graph& other) const;
    bool operator<(const Graph& other) const;
    bool operator<=(const Graph& other) const;
    bool operator>(const Graph& other) const;
    bool operator>=(const Graph& other) const;

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
};

} // namespace ariel

#endif // GRAPH_HPP
