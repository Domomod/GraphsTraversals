/*
 AdjacencyMatrix.cpp
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
 
 This part was written by Krzysztof Sychla (expect destructor),
  documented by Dominik Witczak
 */

#include "AdjacencyMatrix.hpp"
#include <iostream>
#include <queue>

AdjacencyMatrix::AdjacencyMatrix(int ile){
    n = ile;
    temp = n-1;
    tab = new int *[n];
    visited = new bool [n];
    sorted = new int [n];
    for(int i = 0;i < n;i++)
        tab[i] = new int [n];
}

AdjacencyMatrix::~AdjacencyMatrix(){
    if(tab != nullptr){
        for( int idx = 0; idx < n; idx++)
            delete [] tab[idx];
    }
    if(tab != nullptr)
        delete [] tab;
    if(visited != nullptr)
        delete [] visited;
    if(sorted != nullptr)
        delete [] sorted;
}

void AdjacencyMatrix::fill(int array[]) {
    int *ptr = array;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < j) {
                tab[i][j] = *ptr;
                ptr++;
            }
            else {
                tab[i][j] = 0;
            }
        }
    }
    
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            printf("%d ", tab[i][j]);
//        }
//        printf("\n");
//    }
    
}

void AdjacencyMatrix::printTab(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            std::cout<<tab[i][j];
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

void AdjacencyMatrix::printSorted(){
    for(int i=0;i<n;i++){
        std::cout<<sorted[i];
    }
    std::cout<<"\n";
}

void AdjacencyMatrix::DFS(int v){
    visited[v] = true;
    //    std::cout<<v<<" ";
    for(int i=0;i<n;i++)
        if(tab[v][i] && !visited[i])
            DFS(i);
    sorted[temp--] = v;
}

void AdjacencyMatrix::SortDFS(){
    for(int i=0;i<n;i++)
        if(!visited[i])
            DFS(i);
}


void AdjacencyMatrix::SortBFS(){
    int *b_count= new int [n];
    int temp = n;
    for(int i=0;i<n;i++)
        b_count[i] = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(tab[i][j] == 1)
                b_count[j] += 1;
        }
    }
    while(temp){
        for(int i=0;i<n;i++){
            if(b_count[i]==-1)
                continue;
            if(b_count[i]==0){
                b_count[i] = -1;
                for(int j=0;j<n;j++)
                    if(tab[i][j]==1)
                        b_count[j]--;
                //                std::cout<<i<<" ";
                temp--;
            }
        }
    }
    //    std::cout<<"\n";
    delete b_count;
}

void AdjacencyMatrix::Euler(int v){
    for(int i=0;i>n;i++){
        if(tab[v][i]){
            tab[v][i]--;
            tab[i][v]--;
            Euler(i);
        }
    }
    std::cout<<v<<" ";
}


