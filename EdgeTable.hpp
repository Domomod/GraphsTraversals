/*
 EdgeTable.hpp
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
    a 2 x n dynamic table to store edges
n (int):
    number of edges
elem (int):
    number of nodes
temp1 (int):
    a counter used in DFS and BFS, it represtents index of table sorted to which those functions
    write nodes, when temp1 = 0, calculation is over and traversal is found
visited (int*):
    pointer to a table for DFS traversal, declared as a member variable, because DFS 
    itself is implemented recursively and need this table in every lever of recursion,
        this table contains a map of visited nodes
sorted (int*):
    pointer to a table containing a traversal (BFS or DFS)
#Methods:
---------------------------------------------------------------------------------------
constructor:
    dynamically create a table, visited, and sorted table
destructor:
    frees memory
getters:
    there are getters for:
        :GetVisited(x): - visited[x] (x given as param, unsafe does not check if x is valid)
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

class EdgeTable{
public:
    void SortBFS();
    void SortDFS();
    void DFS(int v);
    void PrintTab();
    bool GetVisited(int v){return visited[v];}
    void PrintSorted();
    EdgeTable(int p, int** const arr);
    ~EdgeTable();
private:
    int n;
    int elem;
    int temp1;
    int **tab;
    bool *visited;
    int *sorted;
};
