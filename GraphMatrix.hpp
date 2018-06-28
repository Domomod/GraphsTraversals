/*
 GraphMatrix.hpp
 Graphs
 
 Copyright � 2018  Dominik Witczak
 
 This program is free software : you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once
#include <iostream>

#include "AdjacencyMatrix.hpp"
#include "AdjacencyList.hpp"

/*
Graph Matrix is a Graph Representation that combines Adjacency Lists with Adjacency Matrix
#Variables:
---------------------------------------------------------------------------------------
matrix (long long int**): 
    matrix itself
n (int):
    number of nodes
visited (int*):
    pointer to a table for DFS traversal, declared as a member variable, because DFS 
    itself is implemented recursively and need this table in every lever of recursion,
        this table contains a map of visited nodes
predecessors (int*):
    pointer to a table for BFS traversal, declared as a member variable,
        each position of the table contains a number of predecessors so far not visited 
sorted (int*):
    pointer to a table containing a traversal (BFS or DFS)
#Methods:
---------------------------------------------------------------------------------------
constructor:
    can create our class from AdjacencyMatrix(passed by copy or pointer), or a pointer
    to table of tables (aka. pointer to a pointer), this table is treated same as
    AdjacencyMatrix), all the constructors use the function initialize 
    (for reusing the same code)
destructor:
    frees memory
DFS:
    a step of recursive DFS traversal computing
sortDFS:
    find a DFS traversal
    WARNING:
        THE CODE DOES NOT CHECK IF OUR GRAPH IS DAG, WE ASSUMED IT IS, BECAUSE WE
        ARE ALWAYS GENERATING DAG GRAPHS.
sortBFS:
    find a BFS traversal
    WARNING:
        THE CODE DOES NOT CHECK IF OUR GRAPH IS DAG, WE ASSUMED IT IS, BECAUSE WE
        ARE ALWAYS GENERATING DAG GRAPHS.
*/

class GraphMatrix {
private:
    long long int * * matrix;
    int n;
    
    int *visited;
    int *predecessors_count;
    
    int *sorted;
    
    void initialize(int ** tab, int _size);
protected:
public:
    GraphMatrix(AdjacencyMatrix source);
    GraphMatrix(AdjacencyMatrix * source);
    ~GraphMatrix();
    
    void DFS(int i, int &idx);
    void sortDFS();
    void sortBFS();
};
