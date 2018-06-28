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
    void Euler(int v);
private:
    int n;
    int temp;
    int **tab;
    bool *visited;
    int *sorted;
};
