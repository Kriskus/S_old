#include "cellvisibilitygenerator.h"

#include <chrono>
#include <random>
#include <algorithm>

CellVisibilityGenerator::CellVisibilityGenerator()
    : generator_(std::chrono::high_resolution_clock::now().time_since_epoch().count())
{

}

QVector<std::pair<int, int>> CellVisibilityGenerator::drawCellVisibility(int numberOfCell)
{
    std::pair<int,int> pair{};
    while(cellSettings_.size() < numberOfCell) {
        if(cellSettings_.size() > 0) {
            pair = generateNumbers();
            for(const auto& el: cellSettings_) {
                if( el == pair) {
                    break;
                }
            }
            cellSettings_.push_back(pair);
        } else {
            cellSettings_.push_back(pair);
        }
    }
    std::sort(cellSettings_.begin(), cellSettings_.end());
    return cellSettings_;
}

std::pair<int, int> CellVisibilityGenerator::generateNumbers()
{
    std::uniform_int_distribution<int> distribution(0, 8);
    return {distribution(generator_), distribution(generator_)};
}
