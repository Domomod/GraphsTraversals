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
