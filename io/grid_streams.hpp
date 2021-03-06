#ifndef IO__GRID_STREAMS_HPP
#define IO__GRID_STREAMS_HPP

#include <ostream>
#include "../core/grid.hpp"

// Allows feeding grids to std::ostreams.
std::ostream& operator<<(std::ostream& os, Picross::Grid const& grid);

#endif//IO__GRID_STREAMS_HPP