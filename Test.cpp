//ID - 211821137
//GMAIL - shira1d2631@gmail.com

#include "Graph.hpp"
#include <iostream>
#include "doctest.h"
#include <sstream> 

using namespace std;

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    ariel::Graph expected(expectedGraph);
    CHECK(g3 == expected);
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    ariel::Graph expected(expectedGraph);
    CHECK(g4 == expected);
}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1},
        {1, 1, 1, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}

// Operator tests

TEST_CASE("Test Graph Operators") {
    SUBCASE("Addition Operator (+)") {
        ariel::Graph g1 = {
            {0, 1, 2},
            {1, 0, 0},
            {2, 0, 0}
        };

        ariel::Graph g2 = {
            {0, 0, 1},
            {0, 0, 2},
            {1, 2, 0}
        };

        ariel::Graph g3 = g1 + g2;
        ariel::Graph expected = {
            {0, 1, 3},
            {1, 0, 2},
            {3, 2, 0}
        };

        CHECK(g3 == expected);

        g1 += g2;
        CHECK(g1 == expected);
    }

    SUBCASE("Scalar Addition Operator (+)") {
        ariel::Graph g = {
            {0, 1, 2},
            {1, 0, 0},
            {2, 0, 0}
        };

        ariel::Graph g_plus_2 = g + 2;
        ariel::Graph expected = {
            {2, 3, 4},
            {3, 2, 2},
            {4, 2, 2}
        };

        CHECK(g_plus_2 == expected);
    }

    SUBCASE("Negation Operator (-)") {
        ariel::Graph g = {
            {0, 1, 2},
            {1, 0, 0},
            {2, 0, 0}
        };

        ariel::Graph neg_g = -g;
        ariel::Graph expected = {
            {0, -1, -2},
            {-1, 0, 0},
            {-2, 0, 0}
        };

        CHECK(neg_g == expected);
    }

    SUBCASE("Subtraction Operator (-)") {
        ariel::Graph g1 = {
            {0, 1, 2},
            {1, 0, 0},
            {2, 0, 0}
        };

        ariel::Graph g2 = {
            {0, 0, 1},
            {0, 0, 2},
            {1, 2, 0}
        };

        ariel::Graph g3 = g1 - g2;
        ariel::Graph expected = {
            {0, 1, 1},
            {1, 0, -2},
            {1, -2, 0}
        };

        CHECK(g3 == expected);

        g1 -= g2;
        CHECK(g1 == expected);
    }

    SUBCASE("Scalar Subtraction Operator (-)") {
        ariel::Graph g = {
            {0, 1, 2},
            {1, 0, 0},
            {2, 0, 0}
        };

        ariel::Graph g_minus_2 = g - 2;
        ariel::Graph expected = {
            {-2, -1, 0},
            {-1, -2, -2},
            {0, -2, -2}
        };

        CHECK(g_minus_2 == expected);
    }

    SUBCASE("Multiplication Operator (*)") {
        ariel::Graph g1 = {
            {0, 1, 2},
            {1, 0, 0},
            {2, 0, 0}
        };

        ariel::Graph g2 = {
            {0, 0, 1},
            {0, 0, 2},
            {1, 2, 0}
        };

        ariel::Graph g3 = g1 * g2;
        ariel::Graph expected = {
            {2, 4, 2},
            {0, 0, 1},
            {0, 0, 2}
        };

        CHECK(g3 == expected);
    }

    SUBCASE("Scalar Multiplication Operator (*)") {
        ariel::Graph g = {
            {0, 1, 2},
            {1, 0, 0},
            {2, 0, 0}
        };

        ariel::Graph g_times_2 = g *= 2;
        ariel::Graph expected = {
            {0, 2, 4},
            {2, 0, 0},
            {4, 0, 0}
        };

        CHECK(g_times_2 == expected);
    }

    SUBCASE("Comparison Operators (==, !=, <, <=, >, >=)") {
        ariel::Graph g1 = {
            {0, 1, 2},
            {1, 0, 0},
            {2, 0, 0}
        };

        ariel::Graph g2 = {
            {0, 1, 2},
            {1, 0, 0},
            {2, 0, 0}
        };

        ariel::Graph g3 = {
            {0, 0, 1},
            {0, 0, 2},
            {1, 2, 0}
        };

        CHECK(g1 == g2);
        CHECK(!(g1 != g2));
        CHECK(g1 <= g2);
        CHECK(g1 >= g2);
        CHECK(!(g1 < g2));
        CHECK(!(g1 > g2));

        CHECK(g1 != g3);
        CHECK(!(g1 == g3));
        CHECK(g1 >= g3);
        CHECK(!(g1 <= g3));
        CHECK(g1 > g3);
        CHECK(!(g1 < g3));
    }
}

    TEST_CASE("Test Graph Increment/Decrement Operators") {
    SUBCASE("Post-Increment Operator (g++)") {
        ariel::Graph g = {
            {0, 1, 2},
            {1, 0, 0},
            {2, 0, 0}
        };

        ariel::Graph original = g;
        ariel::Graph expected = {
            {0, 2, 3},
            {2, 0, 0},
            {3, 0, 0}
        };

        ariel::Graph result = g++;
        CHECK(result == original);
        CHECK(g == expected);
    }

    SUBCASE("Post-Decrement Operator (g--)") {
        ariel::Graph g = {
            {0, 1, 2},
            {1, 0, 0},
            {2, 0, 0}
        };

        ariel::Graph original = g;
        ariel::Graph expected = {
            {0, 0, 1},
            {0, 0, 0},
            {1, 0, 0}
        };

        ariel::Graph result = g--;
        CHECK(result == original);
        CHECK(g == expected);
    }
}

