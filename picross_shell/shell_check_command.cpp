#include "../tools/micro_shell/micro_shell_command.hpp"
#include "../tools/micro_shell/micro_shell_codes.hpp"
#include "../tools/cli/cli_input.hpp"
#include "../tools/cli/cli_streams.hpp"
#include "shell_check_command.hpp"
#include "picross_shell_state.hpp"

#include <vector>
#include <string>
#include "cell_manip_for_commands.hpp"
#include "../tools/string_tools.hpp"
#include "../io/text_grid_formatter.hpp"
#include "../tools/exceptions/range_bounds_exceeded_error.hpp"

namespace Picross
{
    ShellCheckCommand::ShellCheckCommand() :
        MicroShellCommand<PicrossShellState>()
    {

    }

    ShellCheckCommand::~ShellCheckCommand()
    {

    }

    int ShellCheckCommand::processInput(const std::string& command, PicrossShellState& state, CLIStreams& streams)
    {
        // Expected syntax: see docstring in help().

        // Parse arguments.
        std::vector<std::string> tokens = StringTools::tokenizeString(command, ' ', true);

        if (tokens.size() < 3)          // Too few arguments.
        {
            streams.out() << "check: too few arguments." << std::endl;
            return SHELL_COMMAND_BAD_ARGUMENTS;
        }
        else if (tokens.size() > 3)     // Too many arguments.
        {
            streams.out() << "check: too many arguments." << std::endl;
            return SHELL_COMMAND_BAD_ARGUMENTS;
        }
        else // if (tokens.size() == 3)
        {
            return handleCellManipForCommand(tokens, CELL_CHECKED, "check", state, streams);
        }
    }

    std::string ShellCheckCommand::name()
    {
        return "check";
    }

    std::string ShellCheckCommand::description()
    {
        return "Check cell or range of cells";
    }

    std::string ShellCheckCommand::help()
    {
        std::string s;
        s += "check - check cells in the working grid.\n";
        s += "Syntax: check <i|i0:in> <j|j0:jn>\n";
        s += " - `i`: row coordinate of the cells to check.\n";
        s += " - `i0:in`: row coordinate range of the cells to check (e.g: `3:6`).\n";
        s += " - `j`: column coordinate of the cells to check.\n";
        s += " - `j0:jn`: column coordinate range of the cells to check (e.g: `8:9`).\n";
        s += "Omitting x0 or xn will automatically expand the range respectively to its lower bound or higher bound.\n";
        s += "E.g: `:3` will expand to `0:3`, `3:` will expand to `3:9` if 9 is the max value.\n";
        s += "`:` will expand to the whole range (continuing the above example, `0:9`).\n";
        return s;
    }

}
