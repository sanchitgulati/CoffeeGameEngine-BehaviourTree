#pragma once

#include <iostream>
#include <random>

namespace Coffee
{
    class Random
    {
    public:
        Random() : rd(), gen(rd()), dis(0.0, 1.0)
        {
            // Seed the random number generator
        }
        
        float rand()
        {
            // Generate a random number between 0 and 1
            return (float)dis(gen);
        }

    private:
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<double> dis;
    };
}
