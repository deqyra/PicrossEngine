#ifndef CLI__SOLVE_COMMAND_HPP
#define CLI__SOLVE_COMMAND_HPP

#include "../tools/cli/cli_command.hpp"
#include "../tools/cli/cli_streams.hpp"
#include "../tools/cli/cli_input.hpp"
#include "picross_cli_state.hpp"

#include <string>
#include <vector>
#include <memory>

#include "../solving/solver.hpp"

namespace Picross
{
    class SolveCommand : public CLICommand<PicrossCLIState>
    {
        using SolverPtr = std::shared_ptr<Solver>;

        public:     // Public methods
            SolveCommand();
            virtual ~SolveCommand();

            virtual std::string getTooltip();
            virtual int run(PicrossCLIState& state, CLIStreams& streams = CLIInput::defaultStreams);

        private:    // Private methods
            // Print available solvers in a numbered list.
            void showSolvers(std::vector<SolverPtr>& solvers, CLIStreams& streams);
            // Solve the grid using a solver.
            bool handleSolving(SolverPtr solver, PicrossCLIState& state, CLIStreams& streams);
    };
}

#endif//CLI__SOLVE_COMMAND_HPP