#ifndef CLI_MENU_HPP
#define CLI_MENU_HPP

#include <string>
#include <vector>

#include "cli_command.hpp"
#include "cli_state.hpp"

namespace Picross
{
    class CLIMenu
    {
        private:
            std::vector<CLICommand*> _commands;
            CLIState& _state;
            std::string _tooltip;
            std::string _exitName;
            CLICommand* _exitCommand;
            
            void showOption(int n, std::string tooltip);
            void showOptions();

        public:
            CLIMenu(CLIState& state, std::vector<CLICommand*> commands, std::string tooltip, std::string exitName, CLICommand* exitCommand = nullptr);
            virtual ~CLIMenu();
            virtual std::string getTooltip();
            virtual void show();
    };
}

#endif//CLI_MENU_HPP