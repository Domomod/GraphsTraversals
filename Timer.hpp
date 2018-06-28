/*
 Timer.hpp
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

#pragma once
#include <iostream>
#include <chrono>

using namespace std::chrono;

class Timer
{
public:
    
    void StartTimer()
    {
        start = high_resolution_clock::now();
    }
    
    
    void EndTimer()
    {
        end = high_resolution_clock::now();
    }
    
    
    long long GetDelta()
    {
        long delta = (long)duration_cast<microseconds>(end - start).count();
        
        return delta;
        //outcome << "Algorithm took " << delta << " us\n";
    }
    
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
};
