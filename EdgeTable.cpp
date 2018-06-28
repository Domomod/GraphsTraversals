/*
 EdgeTable.cpp
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

#include "EdgeTable.hpp"
#include <iostream>

EdgeTable::EdgeTable(int p,int** const arr){
    n = 0;
    for(int i=0;i<p;i++)
        for(int j=0;j<p;j++)
            if(arr[i][j])
                n++;
    tab = new int *[2];
    for(int i=0;i<2;i++)
        tab[i] = new int [n];
    int k=0;
    for(int i=0;i<p;i++)
        for(int j=0;j<p;j++)
            if(arr[i][j]){
                tab[0][k] = i;
                tab[1][k] = j;
                k++;
            }
    elem = p;
    temp1 = elem-1;
    visited = new bool [elem];
    sorted = new int [elem];
}

EdgeTable::~EdgeTable(){
    if(tab!= nullptr)
        for(int i=0;i<2;i++)
           delete[] tab[i];
    if(tab!= nullptr)
        delete[] tab;
    if(visited!= nullptr)
        delete[] visited;
    if(sorted!= nullptr)
        delete[] sorted;
}

void EdgeTable::PrintTab(){
    for(int i=0;i<n;i++)
        std::cout<<tab[0][i]<<" "<<tab[1][i]<<"\n";
}

void EdgeTable::SortBFS(){
    int *b_count = new int [elem];
    int temp = elem;
    for(int i=0;i<elem;i++)
        b_count[i] = 0;
    for(int i=0;i<n;i++)
        b_count[tab[1][i]]++;
    for(int i=0;i<elem;i++);
//        std::cout<<b_count[i]<<" ";
//    std::cout<<"\n";
    while(temp){
        for(int i=0;i<elem;i++){
            if(b_count[i]==-1)
                continue;
            if(b_count[i]==0){
                b_count[i] = -1;
                for(int j=0;j<n;j++)
                    if(tab[0][j]==i)
                        b_count[tab[1][j]]--;
//                std::cout<<i<<" ";
                temp--;
            }
        }
    }
//    std::cout<<"\n";
    delete[] b_count;
}

void EdgeTable::SortDFS(){
    for(int i=0;i<elem;i++)
        if(!visited[i])
            DFS(i);
}

void EdgeTable::DFS(int v){
    visited[v] = true;
//    std::cout<<v<<" ";
    for(int i=0;i<n;i++)
        if(tab[0][i]==v && !visited[tab[1][i]])
            DFS(tab[1][i]);
    sorted[temp1--] = v;
}

void EdgeTable::PrintSorted(){
    for(int i=0;i<elem;i++){
        std::cout<<sorted[i]<<" ";
    }
    std::cout<<"\n";
}

