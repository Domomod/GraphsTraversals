//
//  main.cpp
//  Graphs
//
//  Created by Krzysztof Sychla & Dominik Witczak on 18.04.2018.
//  Copyright © 2018 Krzysztof Sychla & Dominik Witczak. All rights reserved.
//  Documentation by Dominik Witczak
//  Source by Krzysztof Sychla

/*
 main.cpp
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

#include <iostream>
#include <fstream>
#include "AdjacencyMatrix.hpp"
#include "EdgeTable.hpp"
#include "Timer.hpp"
#include "AdjacencyList.hpp"
#include "GraphMatrix.hpp"

int main(int argc, const char * argv[]) {
    
// Initialization
//---------------------------------------------------------------
    int sizes[] = {500,1000,1500,2000,2500,3000,3500,4000,4500,5000};
    //declare instantion sizes (they are not specified in the input)
    int size_sizes = sizeof(sizes)/sizeof(*sizes); 
    //quantity of diffrent instatnion sizes
    Timer timer;
    //timer for measure period of time (in microseconds)
    std::fstream input_data;
    std::fstream output_BFS;
    std::fstream output_DFS;
    input_data.open("input_data.txt",std::ios_base::in);
    output_BFS.open("BFS.txt",std::ios_base::out);
    output_DFS.open("DFS.txt",std::ios_base::out);
    //files to read from and write to, all opened at the same time

// Main Loop for computing Breadth First Traversal/Search (BFS)
//---------------------------------------------------------------
    for(int i=0;i<size_sizes;i++){
        std::cout << "Instatnion size = " << sizes[i] << "\n";

        //Loading data
        int *n_tab = new int[(sizes[i]*(sizes[i]-1))/2];
        for(int j=0;j<(sizes[i]*(sizes[i]-1))/2;j++){
            input_data >> n_tab[j];
        }

        //Creating graph representations
        AdjacencyMatrix *adjMatrix = new AdjacencyMatrix(sizes[i]);
        adjMatrix->fill(n_tab);
        EdgeTable *edgTab = new EdgeTable(sizes[i],adjMatrix->GetTab());
        AdjacencyList *adjLis = new AdjacencyList(adjMatrix,0);
        GraphMatrix *graMat = new GraphMatrix(adjMatrix);

        //Compute Traversal using Adjacency Matrix representation
        std::cout<<sizes[i]<<" - Adjacency Matrix\n";
        timer.StartTimer();
        adjMatrix->SortBFS();
        timer.EndTimer();
        output_BFS<<timer.GetDelta();

        //Compute Traversal using Edge Table representation
        std::cout<<sizes[i]<<" - Edge Table\n";
        timer.StartTimer();
        edgTab->SortBFS();
        timer.EndTimer();
        output_BFS<<" "<<timer.GetDelta();

        //Compute Traversal using Adjacency List representation
        std::cout<<sizes[i]<<" - Adjacency List\n";
        timer.StartTimer();
        adjLis->sortBFS();
        timer.EndTimer();
        output_BFS<<" "<<timer.GetDelta();

        //Compute Traversal using Graph Matrix representation
        std::cout<<sizes[i]<<" - Graph Matrix\n";
        timer.StartTimer();
        graMat->sortBFS();
        timer.EndTimer();
        output_BFS<<" "<<timer.GetDelta()<<"\n";

        //Free memory
        delete adjMatrix;
        delete edgTab;
        delete adjLis;
        delete graMat;
        delete [] n_tab;
    }

// Reload data
//---------------------------------------------------------------
    input_data.close();
    input_data.open("input_data.txt",std::ios_base::in);

// Main Loop for computing Depth First Traversal/Search (DFS)
//---------------------------------------------------------------
    for(int i=0;i<size_sizes;i++){
        std::cout << "Instatnion size = " << sizes[i] << "\n";


        //Loading data
        int *n_tab = new int[(sizes[i]*(sizes[i]-1))/2];
        for(int j=0;j<(sizes[i]*(sizes[i]-1))/2;j++){
            input_data >> n_tab[j];
        }

        // //Creating graph representations
        AdjacencyMatrix *adjMatrix = new AdjacencyMatrix(sizes[i]);
        adjMatrix->fill(n_tab);
        EdgeTable *edgTab = new EdgeTable(sizes[i],adjMatrix->GetTab());
        AdjacencyList *adjLis = new AdjacencyList(adjMatrix,0);
        GraphMatrix *graMat = new GraphMatrix(adjMatrix);

        //Compute Traversal using Adjacency Matrix representation
        std::cout<<sizes[i]<<" - Adjacency Matrix\n";
        timer.StartTimer();
        adjMatrix->SortDFS();
        timer.EndTimer();
        output_DFS<<timer.GetDelta();

        //Compute Traversal using Edge Table representation
        std::cout<<sizes[i]<<" - Edge Table\n";
        timer.StartTimer();
        edgTab->SortDFS();
        timer.EndTimer();
        output_DFS<<" "<<timer.GetDelta();

        //Compute Traversal using Adjacency List representation
        std::cout<<sizes[i]<<" - Adjacency List\n";
        timer.StartTimer();
        adjLis->sortDFS();
        timer.EndTimer();
        output_DFS<<" "<<timer.GetDelta();

        //Compute Traversal using Graph Matrix representation
        std::cout<<sizes[i]<<" - Graph Matrix\n";
        timer.StartTimer();
        graMat->sortDFS();
        timer.EndTimer();
        output_DFS<<" "<<timer.GetDelta()<<"\n";

        //Free memory
        delete adjMatrix;
        delete edgTab;
        delete adjLis;
        delete graMat;
        delete[] n_tab;
    }


// Close Files, Exit the program
//---------------------------------------------------------------
    input_data.close();
    output_BFS.close();
    output_DFS.close();

    return 0;
}
