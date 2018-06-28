/*
 GraphMatrix.cpp
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

#include "GraphMatrix.hpp"


GraphMatrix::GraphMatrix(AdjacencyMatrix source)
{
    initialize(source.tab, source.n);
}

GraphMatrix::GraphMatrix(AdjacencyMatrix *source)
{
    initialize(source->tab, source->n);
    
}

void GraphMatrix::initialize(int **tab, int _size)
{
    n = _size;
    //intiazlize Adjacency Lists
    AdjacencyList    *succesors = new AdjacencyList(tab, _size, AdjacencyList::NEXT),
    *predecessors = new AdjacencyList(tab, _size, AdjacencyList::PREV),
    *noincidences = new AdjacencyList(tab, _size, AdjacencyList::NOINCIDENCY);
    //initialzie the container (matrix)
    matrix = new long long int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new long long int[n + 3];
    }
    
    //initialize Succesors, Predecessors and NoIncidences columns
    for (int i = 0; i < n; i++) {
        //Succesors
        if (succesors->lists[i].empty())
            matrix[i][0] = 0;
        else
            matrix[i][0] = succesors->lists[i].front() + 1;
        //Predecessors
        if (predecessors->lists[i].empty())
            matrix[i][1] = 0;
        else
            matrix[i][1] = predecessors->lists[i].front() + 1;
        //NoIncidences
        if (noincidences->lists[i].empty())
            matrix[i][2] = 0;
        else
            matrix[i][2] = noincidences->lists[i].front() + 1;
    }
    
    for (int i = 0; i < n; i++) {
        //fill the succesors of i-th element <1, n>
        for (std::list<int>::const_iterator iter = succesors->lists[i].begin(), end = succesors->lists[i].end(); iter != end; ++iter) {
            //for (auto iter : succesors.lists[i]){
            std::list<int>::const_iterator next = iter;
            next++;
            if (next != succesors->lists[i].end()) {
                //assign the value of next succesor
                matrix[i][*iter + 3] = *next + 1;
            }
            else {
                //assign the value of itself
                matrix[i][*iter + 3] = *iter + 1;
            }
        }
        
        //fill the predecessors of i-th element <-n, -1>
        for (std::list<int>::const_iterator iter = predecessors->lists[i].begin(), end = predecessors->lists[i].end(); iter != end; ++iter) {
            //for (auto iter : succesors.lists[i]){
            std::list<int>::const_iterator next = iter;
            next++;
            if (next != predecessors->lists[i].end()) {
                //assign the value of next succesor
                matrix[i][*iter + 3] = -*next - 1;
                iter;
            }
            else {
                //assign the value of itself
                matrix[i][*iter + 3] = -*iter - 1;
            }
        }
        
        //fill elem with no incidences to i-th element <n+1, 2n>
        for (std::list<int>::const_iterator iter = noincidences->lists[i].begin(), end = noincidences->lists[i].end(); iter != end; ++iter) {
            //for (auto iter : succesors.lists[i]){
            std::list<int>::const_iterator next = iter;
            next++;
            if (next != noincidences->lists[i].end()) {
                //assign the value of next succesor
                matrix[i][*iter + 3] = n + *next + 1;
                iter;
            }
            else {
                //assign the value of itself
                matrix[i][*iter + 3] = n + *iter + 1;
            }
        }
    }

    // free memory
    delete succesors;
    delete predecessors;
    delete noincidences;
}

GraphMatrix::~GraphMatrix()
{
    if(matrix != nullptr){
        for( int idx = 0; idx < n; idx++)
            delete [] matrix[idx];
    }
    if(matrix != nullptr)
        delete [] matrix;
}


void GraphMatrix::DFS(int i, int &idx)
{
    //NOTE : this function and all the helping structures is indexing from 0, but Graph Matrix Requires to index from 1,
    //this means I had to manipulate the indexes on the run.
    if (visited == NULL)
        return; //

    visited[i] = 1;
    long long int iter = matrix[i][0];
    
    //for every succesor
    int twice = 0;//do one more step because we want to include the ending node
    while (twice != 2 && iter != 0) {
        //Deep First Search if unvisited
        if (!visited[iter - 1])
            DFS(iter - 1, idx);
        //check next on the list
        iter = matrix[i][2 + iter];
        //check if node is the last or one before the last 
        if (iter == matrix[i][2 + iter])
            twice++;
    }

    sorted[--idx] = i;
}

void GraphMatrix::sortDFS()
{
    //initialize data
    visited = new int[n];
    for (int i = 0; i < n; i++) 
        visited[i] = 0;
    sorted = new int[n];
    
    //Deep First Search every unvisited node
    int idx = n;
    for (int i = 0; i < n; i++) {
        if (!visited[i])
            DFS(i, idx);
    }
    
    //free memory
    delete [] visited;
    delete [] sorted;
}



void GraphMatrix::sortBFS()
{
    //initialize arrays
    predecessors_count = new int[n];
    for (int i = 0; i < n; i++)
        predecessors_count[i] = 0;
    sorted = new int[n];
    
    //fill the ancestors list
    for (int i = 0; i < n; i++) {
        long long int iter = matrix[i][0];
        int twice = 0;
        bool first_iteration = true;
        
        while (twice != 2 && iter != 0) {
            predecessors_count[iter-1]++;
            iter = matrix[i][2 + iter];
            //so the last element is handled
            if (iter == matrix[i][2 + iter])
                twice++;
            //if the list is one-element, dont write it twice
            if (iter == matrix[i][2 + iter] && first_iteration)
                twice = 2;
            first_iteration = false;
        }
    }
    
    
    //sort
    for (int idx = 0; idx < n;) {
        //find an elem with no ancestors;
        int k = 0;
        while (predecessors_count[k] != 0 && k < n - 1)
            k++;
        
        //Indicate as sorted
        sorted[idx++] = k;
        predecessors_count[k]--; // indicate as -1, so you ingore it later
        
        //for every succesor of k, decrement it predecessors count
        int iter = matrix[k][0];
        int twice = 0;
        bool first_iteration = true;
        while (twice != 2 && iter != 0) {
            predecessors_count[iter-1]--;
            iter = matrix[k][2 + iter];
            //so the last element is handled
            if (iter == matrix[k][2 + iter])
                twice++;
            //if the list is one-element, dont write it twice
            if (iter == matrix[k][2 + iter] && first_iteration)
                twice = 2;
            first_iteration = false;
        }
    }

    //free memory
    delete [] predecessors_count;
    delete [] sorted;
}
