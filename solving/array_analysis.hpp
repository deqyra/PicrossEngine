#ifndef SOLVING__ARRAY_ANALYSIS_HPP
#define SOLVING__ARRAY_ANALYSIS_HPP

#include <vector>

#include "../core/cell_t.hpp"
#include "../tools/array_2d.hpp"

namespace Picross
{
namespace ArrayAnalysis
{
    Array2D<bool> matchCellsToHints(std::vector<cell_t> array, std::vector<int> hints);
} // namespace ArrayAnalysis
} // namespace Picross

#endif//SOLVING__ARRAY_ANALYSIS_HPP