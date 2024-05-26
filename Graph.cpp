//ID - 211821137
//GMAIL - shira1d2631@gmail.com

#include "Graph.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace ariel {

    Graph::Graph() : numVertices(0), edgeCount(0),isWeighted(false) {} // Default constructor

    Graph::Graph(const std::vector<std::vector<int>>& matrix) { // New constructor to accept adjacency matrix
        loadGraph(matrix); // Load the graph using the given adjacency matrix
    }
    
    Graph::Graph(const std::initializer_list<std::initializer_list<int>>& list) {// Constructor to accept an initializer list
    std::vector<std::vector<int>> matrix(list.size());
    std::size_t i = 0;
    for (const auto& row : list) {
        matrix[i] = std::vector<int>(row);
        i++;
    }
    loadGraph(matrix);
} 

    Graph::Graph(const Graph& other) // Copy constructor
        : numVertices(other.numVertices), edgeCount(other.edgeCount), isWeighted(other.isWeighted), adjacencyMatrix(other.numVertices, std::vector<int>(other.numVertices, 0)) {
      for (std::size_t i = 0; i < numVertices; i++) { // Copy the adjacency matrix
        for (std::size_t j = 0; j < numVertices; j++) { 
          adjacencyMatrix[i][j] = other.adjacencyMatrix[i][j];
        }
      }
    }


    Graph& Graph::operator=(const Graph& other) { // Assignment operator
      if (this != &other) { // Check for self-assignment
        numVertices = other.numVertices; // Copy the number of vertices
        edgeCount = other.edgeCount; // Copy the number of edges
        isWeighted = other.isWeighted;// Copy the number of edges
        adjacencyMatrix = std::vector<std::vector<int>>(other.numVertices, std::vector<int>(other.numVertices, 0)); // Copy the adjacency matrix
        for (std::size_t i = 0; i < numVertices; i++) { //deep copy
          for (std::size_t j = 0; j < numVertices; j++) {
            adjacencyMatrix[i][j] = other.adjacencyMatrix[i][j]; // Copy the adjacency matrix
          }
        }
      }
      return *this;
    }

  void Graph::loadGraph(const std::vector<std::vector<int>>& matrix) {
    // Check if the matrix is square
    int size = matrix.size();
    for (std::size_t i = 0; i < size; i++) {
        if (matrix[i].size() != size) {
            throw std::invalid_argument("Invalid graph: The matrix is not square.");
        }
    }

    bool isWeightedCheck = false; // Check if the graph is weighted
    isWeighted = isWeightedCheck;

    adjacencyMatrix = matrix;
    numVertices = size;

    // Initialize adjacencyMatrix with all zeroes
    adjacencyMatrix = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));

    // Copy values from the input matrix, setting the diagonal to zero
    for (std::size_t i = 0; i < size; i++) {
        for (std::size_t j = 0; j < size; j++) {
            if (i != j) {
                adjacencyMatrix[i][j] = matrix[i][j];
            }
        }
    }

    edgeCount = 0;
    for (const auto & i : matrix) { // Count the number of edges
        for (int j : i) { // Count the number of edges
            if (j != 0) { //if the matrix not zero so we have weight
                edgeCount++;
            }
        }
    }
}

    void Graph::printGraph() const {
        std::cout << "Graph with " << numVertices << " vertices and " << edgeCount << " edges." << std::endl;
    }

    int Graph::getnumvertices() const {
        return numVertices;
    }

    int Graph::getedgecount() const {
        return edgeCount;
    }

    int Graph::getadjacencymatrix(std::size_t i, std::size_t j) const {
      return adjacencyMatrix[i][j];
    }

    Graph Graph::operator+(const Graph& other) const { // Add two graphs
      if (numVertices != other.numVertices) { // Check if the graphs have the same number of vertices
        throw std::invalid_argument("Cannot add graphs of different sizes.");
      }

      std::vector<std::vector<int>> newMatrix(numVertices, std::vector<int>(numVertices, 0));// Create a new matrix to store the result
      for (std::size_t i = 0; i < numVertices; i++) { // Add the corresponding elements of the two matrices
        for (std::size_t j = 0; j < numVertices; j++) {
          newMatrix[i][j] = adjacencyMatrix[i][j] + other.adjacencyMatrix[i][j];
        }
      }

      return Graph(newMatrix);
    }

        Graph Graph::operator+() const {
        return *this;
    }

    Graph& Graph::operator+=(const Graph& other) { // Add two graphs and assign the result to the first graph
      *this = *this + other; 
      return *this;
    }

    Graph Graph::operator+(const int scalar) const {
      std::vector<std::vector<int>> newMatrix(numVertices, std::vector<int>(numVertices));
      for (std::size_t i = 0; i < numVertices; i++) { 
        for (std::size_t j = 0; j < numVertices; j++) {
          newMatrix[i][j] = adjacencyMatrix[i][j] + scalar; 
        }
      }

      return Graph(newMatrix);
    }


    Graph Graph::operator-() const { // Negate the graph
      std::vector<std::vector<int>> newMatrix(numVertices, std::vector<int>(numVertices));
      for (std::size_t i = 0; i < numVertices; i++) {
        for (std::size_t j = 0; j < numVertices; j++) {
          newMatrix[i][j] = -adjacencyMatrix[i][j];
        }
      }

      return Graph(newMatrix);
    }

    Graph Graph::operator-(const Graph& other) const {
      if (numVertices != other.numVertices) {  // Check if the graphs have the same number of vertices
        throw std::invalid_argument("Cannot subtract graphs of different sizes.");
      }

      std::vector<std::vector<int>> newMatrix(numVertices, std::vector<int>(numVertices)); // Create a new matrix to store the result
      for (std::size_t i = 0; i < numVertices; i++) {
        for (std::size_t j = 0; j < numVertices; j++) {
          newMatrix[i][j] = adjacencyMatrix[i][j] - other.adjacencyMatrix[i][j]; // Subtract the corresponding elements of the two matrices
        }
      }

      return Graph(newMatrix);
    }

    Graph& Graph::operator-=(const Graph& other) {
      *this = *this - other;
      return *this;
    }

    Graph Graph::operator-(const int scalar) const { // Subtract a scalar from the graph
      std::vector<std::vector<int>> newMatrix(numVertices, std::vector<int>(numVertices)); 
      for (std::size_t i = 0; i < numVertices; i++) {
        for (std::size_t j = 0; j < numVertices; j++) {
          newMatrix[i][j] = adjacencyMatrix[i][j] - scalar;
        }
      }

      return Graph(newMatrix);
    }

    Graph& Graph::operator-=(const int scalar) {
      *this = *this - scalar;
      return *this;
    }

  Graph& Graph::operator/=(int scalar){
    Graph& non_const_this = const_cast<Graph&>(*this);
    for (std::size_t i = 0; i < non_const_this.numVertices; i++) {
        for (std::size_t j = 0; j < non_const_this.numVertices; j++) {
            non_const_this.adjacencyMatrix[i][j] /= scalar;
        }
    }
    return non_const_this;
}

  Graph& Graph::operator*=(int scalar) {
    Graph& non_const_this = const_cast<Graph&>(*this);
    for (std::size_t i = 0; i < non_const_this.numVertices; i++) {
        for (std::size_t j = 0; j < non_const_this.numVertices; j++) {
            non_const_this.adjacencyMatrix[i][j] *= scalar;
        }
    }
    return non_const_this;
}

    Graph Graph::operator*(const Graph& other) const {
      if (numVertices != other.numVertices) { // Check if the multiplication is possible
        throw std::invalid_argument("Cannot multiply graphs of different sizes.");
      }

      std::vector<std::vector<int>> newMatrix(numVertices, std::vector<int>(numVertices, 0));
      for (std::size_t i = 0; i < numVertices; i++) { 
        for (std::size_t j = 0; j < numVertices; j++) {
          for (std::size_t k = 0; k < numVertices; k++) {
            newMatrix[i][j] += adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j]; //Multiply the matrix like we learned in linear algebra
          }
        }
      }

      return Graph(newMatrix);
    }

    // Comparison operators
    bool Graph::operator==(const Graph& other) const {
      if (numVertices != other.numVertices) { // Check if the graphs have the same number of vertices, if not they are not equal  
        return false;
      }

      for (std::size_t i = 0; i < numVertices; i++) { 
        for (std::size_t j = 0; j < numVertices; j++) {
          if (adjacencyMatrix[i][j] != other.adjacencyMatrix[i][j]) { //check if the edges are equal, if not they are not equal
            return false;
          }
        }
      }

      return true;
    }
    bool Graph::operator!=(const Graph& other) const { 
      return !(*this == other); //use the == operator to check if the graphs are not equal
    }
   
    //Inclusion - is to check that every vertex and every edge that is in the graph g1 is also in the graph g2 but they are not equal
    //Order of magnitude - this is the number of rows or columns of the matrix (if a matrix of different neighborhoods has the same number of vertices, it means that they have the same order of magnitude)

  bool Graph::operator<(const Graph& other) const {
    if (numVertices < other.numVertices) { // Check if the number of vertices is less than the other graph
return true;
}
        if (numVertices > other.numVertices) { // Check if the number of vertices is greater than the other graph
            return false;
    }
  //if we got here it means that the number of vertices is equal
  //so we will check the number of edges
    std::size_t thisEdgeCount = 0;
    std::size_t otherEdgeCount = 0;
    for (std::size_t i = 0; i < numVertices; i++) {
        for (std::size_t j = 0; j < numVertices; j++) {
              if (adjacencyMatrix[i][j] != 0) { //if the matrix not zero so we have edge
                  thisEdgeCount++;
    }
      if (other.adjacencyMatrix[i][j] != 0) {
          otherEdgeCount++;
      }
    }
  }
      return thisEdgeCount < otherEdgeCount;
  }
  

    bool Graph::operator<=(const Graph& other) const {
      return (*this < other) || (*this == other);
    }

    bool Graph::operator>(const Graph& other) const {
      return !(*this <= other);
    }

    bool Graph::operator>=(const Graph& other) const {
      return !(*this < other);
    }

    // Increment/Decrement operators
    Graph& Graph::operator++() { // Pre-increment
      for (auto& row : adjacencyMatrix) {
        for (int& value : row) {
          if (value != 0) {
            value++;
          }
        }
      }
      return *this;
    }

    Graph Graph::operator++(int) { // Post-increment
      Graph temp(*this);
      ++(*this);
      return temp; //return the value before the increment
    }

    Graph& Graph::operator--() { // Pre-decrement
      for (auto& row : adjacencyMatrix) {
        for (int& value : row) {
          if (value != 0) {
            value--;
          }
        }
      }
      return *this;
    }

    Graph Graph::operator--(int) { // Post-decrement
      Graph temp(*this);
      --(*this);
      return temp;
    }

    std::ostream& operator<<(std::ostream& os, const Graph& graph) { //print the graph
      os << "Graph with " << graph.numVertices << " vertices and " << graph.edgeCount << " edges:" << std::endl;
      for (const auto& row : graph.adjacencyMatrix) {
        for (int value : row) {
          os << value << " ";
        }
        os << std::endl;
      }
      return os;
    }


}