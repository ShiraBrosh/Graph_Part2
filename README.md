# Graph Project

This project implements a `Graph` class for representing and manipulating graphs using an adjacency matrix. The class supports various arithmetic operations, comparison operators, increment/decrement operators, and scalar multiplication on graphs.

## Files

1. `Graph.hpp`: Header file containing the declaration of the `Graph` class.
2. `Graph.cpp`: Implementation file for the `Graph` class.
3. `test.cpp`: Test file containing unit tests for the `Graph` class.

## Graph Class

The `Graph` class provides the following functionality:

### Constructors

- Default constructor: Creates an empty graph.
- Constructor from adjacency matrix: Creates a graph from a given adjacency matrix.
- Copy constructor: Creates a deep copy of an existing graph.

### Member Functions

- `loadGraph(const std::vector<std::vector<int>>& matrix)`: Loads a graph from an adjacency matrix.
- `printGraph()`: Prints the graph information (number of vertices and edges).
- `getnumvertices()`: Returns the number of vertices in the graph.
- `getedgecount()`: Returns the number of edges in the graph.
- `getadjacencymatrix(std::size_t i, std::size_t j)`: Returns the value of the adjacency matrix at the given indices.

### Arithmetic Operators

- `operator+`, `operator+=`: Addition and compound addition of graphs.
- `operator-`, `operator-=`: Subtraction and compound subtraction of graphs.
- `operator*`, `operator*=`: Multiplication and compound multiplication of graphs by a scalar.
- `operator/=`: Division of a graph by a scalar.
- `operator*`: Multiplication of two graphs (matrix multiplication).
- `operator+()`: Unary plus operator.
- `operator-()`: Negation operator.

### Comparison Operators

- `operator==`, `operator!=`: Equality and inequality operators for graphs.
- `operator<`, `operator<=`, `operator>`, `operator>=`: Relational operators for comparing graphs based on size and edge count.

### Increment/Decrement Operators

- `operator++`, `operator--`: Pre-increment and pre-decrement operators for graphs.
- `operator++`, `operator--`: Post-increment and post-decrement operators for graphs.

### Output Operator

- `operator<<`: Overloaded output stream operator for printing graph information.

## Usage

To use the `Graph` class, include the `Graph.hpp` header file in your project. You can create, manipulate, and perform operations on graphs using the provided member functions and overloaded operators.

## Contributors

- [Your Name] - [Your Student ID] - [Your Email]

Please note that the actual implementation details of the `Graph` class and the test cases are not included in this README file. You should refer to the respective source files (`Graph.cpp` and `test.cpp`) for the complete implementation.
