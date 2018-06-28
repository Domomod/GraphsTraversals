/*
 AdjacencyMatrix.hpp
 Graphs
 
 Copyright � 2018  Dominik Witczak & Krzysztof Sychla
 
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
 
 This part was written by Krzysztof Sychla, documented by Dominik Witczak
 */

#pragma once
#include <stdio.h>

/*
Adjacency Matrix is a Graph Representation more at: https://en.wikipedia.org/wiki/Adjacency_matrix
#Variables:
---------------------------------------------------------------------------------------
tab (long long int**): 
    a dynamically alocated matrix to store data
n (int):
    number of nodes
temp (int):
    a counter used in DFS and BFS, it represtents index of table sorted to which those functions
    write nodes, when temp = 0, calculation is over and traversal is found
visited (int*):
    pointer to a table for DFS traversal, declared as a member variable, because DFS 
    itself is implemented recursively and need this table in every lever of recursion,
        this table contains a map of visited nodes
sorted (int*):
    pointer to a table containing a traversal (BFS or DFS)
#Methods:
---------------------------------------------------------------------------------------
constructor:
    dynamically create a matrix, visited, and sorted table
fill:
    fill the matrix with data
destructor:
    frees memory
getters:
    there are getters for:
        :GetN(void):    - n 
        :GetVisited(x): - visited[x] (x given as param, unsafe does not check if x is valid)
        :GetTab(void):  - tab (return int**)
printers:
    there are printers for:
        :printTab(void):    - prints the matrix
        :orintSorted(void): - prints the sorted, use only after sortDFS or sortBFS, otherwise it
        will print gibberish
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

class AdjacencyMatrix{
    friend class AdjacencyList;
    friend class GraphMatrix;
public:
    void fill(int tab[]);
    void DFS(int v);
    void SortBFS();
    void SortDFS();
    int GetN(){return n;}
    bool GetVisited(int v){return visited[v];}
    int** GetTab(){return tab;}
    void printTab();
    void printSorted();
    AdjacencyMatrix(int ile);
    ~AdjacencyMatrix();
private:
    int n;
    int temp;
    int **tab;
    bool *visited;
    int *sorted;
};
