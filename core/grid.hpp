#ifndef CORE__GRID_HPP
#define CORE__GRID_HPP

#include <vector>
#include <string>
#include <functional>

#include "cell_t.hpp"
#include "../tools/array_2d.hpp"

namespace Picross
{
	inline static const int GRID_MAX_SIZE = 100;
	inline static const int MERGING_POLICY_THROW_ON_CONFLICTS = 0;
	inline static const int MERGING_POLICY_OVERWRITE = 1;
	inline static const int MERGING_POLICY_PRESERVE = 2;
	
	class Grid
	{
		private:	// Attributes
			Array2D<cell_t> _innerGrid;
			int _width;
			int _height;
			std::vector<std::vector<int>> _rowHints;
			std::vector<std::vector<int>> _colHints;

			static const std::function<bool(const cell_t&)> _throwingCellChecker;

		public:		// Public methods
			Grid(int width, int height);
			Grid(int width, int height, std::vector<std::vector<int>> horizontalHints, std::vector<std::vector<int>> verticalHints);

			int getWidth() const;
			int getHeight() const;

		// These return COPIES only. Modifications to the grid content and hints to be made through the appropriate methods.
			std::vector<cell_t> getRow(int row) const;
			std::vector<cell_t> getCol(int col) const;

			std::vector<std::vector<int>> getAllRowHints() const;
			std::vector<int> getRowHints(int row) const;
			std::vector<std::vector<int>> getAllColHints() const;
			std::vector<int> getColHints(int col) const;

		// Cell modification methods.
			cell_t getCell(int row, int col) const;
			void setCell(int row, int col, cell_t val);
			void setCellRange(int i0, int in, int j0, int jn, cell_t val);
			void setRow(int row, std::vector<cell_t> array);
			void setCol(int col, std::vector<cell_t> array);
			void checkCell(int row, int col);
			void crossCell(int row, int col);
			void clearCell(int row, int col);

			void merge(const Grid& other, int mergingPolicy = MERGING_POLICY_THROW_ON_CONFLICTS);

		// Hint modification methods.
			void setRowHints(int row, std::vector<int> hints);
			void setColHints(int col, std::vector<int> hints);
			void setAllRowHints(std::vector<std::vector<int>> hints);
			void setAllColHints(std::vector<std::vector<int>> hints);
			void setHintsFromState();
			void clearRowHints();
			void clearColHints();
			void clearAllHints();

		// Useful checks.
			bool isValidRow(int row, bool throwOnFail = false) const;
			bool isValidCol(int col, bool throwOnFail = false) const;
			bool isValidCell(int row, int col, bool throwOnFail = false) const;
			bool hintsAreConsistent() const;
			bool isSolved() const;
			int rowHintSum() const;
			int colHintSum() const;
		
		// Return the cell value which is most present within a grid.
			cell_t mostPresentState() const;

		// Useful hint-related checks and functions.
			bool areValidRowHints(const std::vector<int>& hints, bool throwOnFail = false) const;
			bool areValidColHints(const std::vector<int>& hints, bool throwOnFail = false) const;

			friend bool operator==(const Grid& lhs, const Grid& rhs);
			friend bool operator!=(const Grid& lhs, const Grid& rhs);
	};
} // namespace Picross

// Allows feeding grids to std::ostreams.
std::ostream& operator<<(std::ostream& os, Picross::Grid const& grid);

#endif//CORE__GRID_HPP