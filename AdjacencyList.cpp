/*
 AdjacencyList.cpp
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
 
 This part was written by Dominik Witczak, documented by Dominik Witczak
 */

#include"AdjacencyList.hpp"

AdjacencyList::AdjacencyList(AdjacencyMatrix source, int which)
{
    initialize(source.tab, source.n, which);
}

AdjacencyList::AdjacencyList(AdjacencyMatrix *source, int which)
{
    initialize(source->tab, source->n, which);
}

AdjacencyList::AdjacencyList(int **tab, int _size, int which)
{
    initialize(tab, _size, which);
}

void AdjacencyList::initialize(int **tab, int _size, int which)
{
    size = _size;
    type = which;
    lists.reserve(size); //that's faster
    //declare a table
    
    for (int i = 0; i < size; i++) {
        lists.push_back(std::list<int>());
        for (int j = 0; j < size; j++) {
            if ((tab[i][j] == 1 && type == NEXT) || (tab[i][j] == 0 && tab[j][i] == 0 && type == NOINCIDENCY)) {
                lists[i].push_back(j);
            }
            else if (tab[j][i] == 1 && type == PREV) {
                lists[i].push_back(j);
            }
        }
    }
}

AdjacencyList::~AdjacencyList()
{
    if(!lists.empty()){
        for (int i = 0; i < size; i++){
            lists[i].clear();
        }
        lists.clear();
    }
}

void AdjacencyList::DFS(int i, int &idx)
{
    if (visited == NULL)
        return;
    visited[i] = 1;

    //for every succesor
    for (auto element : lists[i]) {
        //Deep First Search if unvisited
        if(!visited[element])
            DFS(element, idx);
    }
    //fill the answer
    sorted[--idx] = i;
}

void AdjacencyList::sortDFS()
{
    if (type != NEXT) {
        return;
    }
    
    //initialize data
    visited = new int[size];
    for (int i = 0; i < size; i++) {
        visited[i] = 0;
    }
    sorted = new int[size];
    
    //Deep First Search every unvisited node
    int idx = size;
    for (int i = 0; i < size; i++) {
        if (!visited[i])
            DFS(i, idx);
    }
    
    //free memory
    delete [] visited;
    delete [] sorted;
}


void AdjacencyList::sortBFS()
{
    //check for error
    if (type != NEXT) {
        return;
    }
    //initialize arrays
    predecessors = new int[size];
    for (int i = 0; i < size; i++)
        predecessors[i] = 0;
    sorted = new int[size];
    
    //fill the ancestors list
    for (int i = 0; i < size; i++) {
        for (auto elem : lists[i]) {
            predecessors[elem]++;
        }
    }
    
    //sort
    for (int idx = 0; idx < size;) {
        //find an elem with no ancestors;
        int k = 0;
        while (predecessors[k] != 0 && k < size - 1)
            k++;
        
        //Indicate as sorted
        sorted[idx++] = k;
        predecessors[k]--;
        
        //for every succesor of k, decrement it predecessors count
        for (auto elem : lists[k]) {
            predecessors[elem]--;
        }
    }
    
    //free memory
    delete [] predecessors;
    delete [] sorted;
}
