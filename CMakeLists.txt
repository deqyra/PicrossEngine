# CMake configuration
    cmake_minimum_required( VERSION 3.8...3.15 )

    if( ${CMAKE_VERSION} VERSION_LESS 3.12 )
        cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} )
    endif(  )

    set( CMAKE_CXX_COMPILER_WORKS 1 )   # Skips the compiler test, which is platform-dependent

# Toggles
    option( BUILD_STATIC_LIBS "Build libraries as static libraries" OFF )

    if( WIN32 )
        message( "Windows detected, forcing static libs." )
        set( BUILD_STATIC_LIBS ON )
    endif(  )

    if( ${BUILD_STATIC_LIBS} )
        set( STATIC_OR_SHARED "STATIC" )
    else(  )
        set( STATIC_OR_SHARED "SHARED" )
    endif(  )

# Project general info
    set( PROJECT_MAINTAINER_NAME "François Brachais" )
    set( PROJECT_MAINTAINER_EMAIL "deqyra@gmail.com" )

# Project target structure
    set( PROJECT_TARGET_NAME "PicrossEngine" )
    set( TOOLS_LIB_NAME "Tools" )
    set( CORE_LIB_NAME "${PROJECT_TARGET_NAME}.Core" )
    set( SOLVER_LIB_NAME "${PROJECT_TARGET_NAME}.Solvers" )
    set( IO_LIB_NAME "${PROJECT_TARGET_NAME}.IO" )
    set( CLI_LIB_NAME "${PROJECT_TARGET_NAME}.CLI" )
    set( SHELL_LIB_NAME "${PROJECT_TARGET_NAME}.Shell" )
    set( EXECUTABLE_NAME ${PROJECT_TARGET_NAME} )
    set( TEST_TARGET_NAME "tests" )
    set( COPY_RESOURCES_TARGET_NAME "copy_resources" )

# Copy resource folder
    add_custom_target( ${COPY_RESOURCES_TARGET_NAME} )
    add_custom_command( TARGET ${COPY_RESOURCES_TARGET_NAME}
                        COMMENT "Copying resource folder"
                        POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ./resources )

# Header configuration variables
    set( PROJECT_VERSION "1.1" )
    set( PROJECT_NAME "PICROSS ENGINE" )

    # Copyright notice generation
        set( PROJECT_START_YEAR "2019" )
        string(TIMESTAMP CURRENT_YEAR "%Y" )
        # "(C) 2019"
        set( PROJECT_COPYRIGHT "(C) ${PROJECT_START_YEAR}" )
        if( NOT CURRENT_YEAR EQUAL PROJECT_START_YEAR )
            # "(C) 2019-2020"
            set( PROJECT_COPYRIGHT "${PROJECT_COPYRIGHT}-${CURRENT_YEAR}" )
        endif( )
        # "(C) 2019[-2020] deqyra <deqyra@gmail.com>"
        set( PROJECT_COPYRIGHT "${PROJECT_COPYRIGHT} ${PROJECT_MAINTAINER_NAME} <${PROJECT_MAINTAINER_EMAIL}>" )

# Header configuration
    configure_file( "cmake_defines.config.hpp" "${CMAKE_SOURCE_DIR}/cmake_defines.hpp" )

# Project definition
    project( ${PROJECT_TARGET_NAME} VERSION ${PROJECT_VERSION}
                                    DESCRIPTION "A Picross grid solver"
                                    LANGUAGES CXX)
    
# C++ standard version
    # C++17 requires at least gcc 7 to be compiled
    set( CMAKE_CXX_STANDARD 17 )

# Build tinyxml2
    set( TINYXML2_NAME "tinyxml2" )
    add_library( ${TINYXML2_NAME} ${STATIC_OR_SHARED}
                lib/tinyxml2/tinyxml2.cpp   lib/tinyxml2/tinyxml2.hpp)

# Build project
    # Build tools lib
        add_library( ${TOOLS_LIB_NAME} ${STATIC_OR_SHARED}
                    tools/string_tools.cpp                              tools/string_tools.hpp
                                                                        tools/lambda_maker.hpp
                                                                        tools/iterable_tools.hpp
                                                                        tools/micro_shell/micro_shell.hpp
                                                                        tools/micro_shell/micro_shell_codes.hpp
                                                                        tools/micro_shell/micro_shell_command.hpp
                                                                        tools/make_basic_exception.hpp
                    tools/exceptions/index_out_of_bounds_error.cpp      tools/exceptions/index_out_of_bounds_error.hpp
                    tools/exceptions/file_not_found_error.cpp           tools/exceptions/file_not_found_error.hpp 
                    tools/exceptions/range_bounds_exceeded_error.cpp    tools/exceptions/range_bounds_exceeded_error.hpp 
                    tools/cli/cli_input.hpp                             tools/cli/cli_input.cpp
                    tools/cli/cli_streams.cpp                           tools/cli/cli_streams.hpp
                                                                        tools/cli/cli_command.hpp
                                                                        tools/cli/cli_menu.hpp
                                                                        tools/cli/menu_command.hpp
                                                                        tools/cli/command_sequence.hpp )

    # Build core lib
        add_library( ${CORE_LIB_NAME} ${STATIC_OR_SHARED}
                    core/cell_t.cpp                                             core/cell_t.hpp
                    core/grid.cpp                                               core/grid.hpp
                    core/utility.cpp                                            core/utility.hpp
                    core/exceptions/invalid_cell_value_error.cpp                core/exceptions/invalid_cell_value_error.hpp
                    core/exceptions/invalid_grid_hints_error.cpp                core/exceptions/invalid_grid_hints_error.hpp
                    core/exceptions/unrecognized_cell_value_error.cpp           core/exceptions/unrecognized_cell_value_error.hpp )
                    target_link_libraries( ${CORE_LIB_NAME} PUBLIC ${TOOLS_LIB_NAME} )

    # Build solver lib
        add_library( ${SOLVER_LIB_NAME} ${STATIC_OR_SHARED}
                    solving/solver.cpp                      solving/solver.hpp
                    solving/utility.cpp                     solving/utility.hpp)
        target_link_libraries( ${SOLVER_LIB_NAME} PUBLIC ${CORE_LIB_NAME} )

    # Build IO lib
        add_library( ${IO_LIB_NAME} ${STATIC_OR_SHARED}
                    io/xml_grid_serializer.cpp                  io/xml_grid_serializer.hpp
                    io/text_grid_formatter.cpp                  io/text_grid_formatter.hpp
                    io/exceptions/invalid_xml_grid_error.cpp    io/exceptions/invalid_xml_grid_error.hpp
                    io/exceptions/tinyxml2_error.cpp            io/exceptions/tinyxml2_error.hpp )
        target_link_libraries( ${IO_LIB_NAME} PUBLIC ${CORE_LIB_NAME} ${TINYXML2_NAME} )

    # Build CLI lib
        add_library( ${CLI_LIB_NAME} ${STATIC_OR_SHARED}
                    picross_cli/picross_cli_state.cpp           picross_cli/picross_cli_state.hpp
                    picross_cli/cli_create_grid_command.cpp     picross_cli/cli_create_grid_command.hpp
                    picross_cli/cli_load_grid_command.cpp       picross_cli/cli_load_grid_command.hpp
                    picross_cli/cli_save_grid_command.cpp       picross_cli/cli_save_grid_command.hpp
                    picross_cli/cli_modify_grid_command.cpp     picross_cli/cli_modify_grid_command.hpp
                    picross_cli/cli_solve_grid_command.cpp      picross_cli/cli_solve_grid_command.hpp )
        target_link_libraries( ${CLI_LIB_NAME} PUBLIC
                                ${TOOLS_LIB_NAME}
                                ${CORE_LIB_NAME}
                                ${SOLVER_LIB_NAME}
                                ${IO_LIB_NAME}
                                ${SHELL_LIB_NAME} )
    
    # Build shell lib
        add_library( ${SHELL_LIB_NAME} ${STATIC_OR_SHARED}
                    picross_shell/shell_commit_command.cpp      picross_shell/shell_commit_command.hpp
                    picross_shell/shell_display_command.cpp     picross_shell/shell_display_command.hpp
                    picross_shell/shell_exit_command.cpp        picross_shell/shell_exit_command.hpp
                    picross_shell/shell_hints_command.cpp       picross_shell/shell_hints_command.hpp
                    picross_shell/shell_rollback_command.cpp    picross_shell/shell_rollback_command.hpp
                    picross_shell/shell_check_command.cpp       picross_shell/shell_check_command.hpp
                    picross_shell/shell_cross_command.cpp       picross_shell/shell_cross_command.hpp
                    picross_shell/shell_clear_command.cpp       picross_shell/shell_clear_command.hpp
                    picross_shell/picross_shell_state.cpp       picross_shell/picross_shell_state.hpp
                    picross_shell/cell_manip_for_commands.cpp   picross_shell/cell_manip_for_commands.hpp )
        target_link_libraries( ${SHELL_LIB_NAME} PUBLIC ${TOOLS_LIB_NAME} ${IO_LIB_NAME} )

    # Build executable
        add_executable( ${EXECUTABLE_NAME}
                        main.cpp
                        cmake_defines.config.hpp     cmake_defines.hpp )        
        target_link_libraries( ${EXECUTABLE_NAME} PUBLIC
                                ${CLI_LIB_NAME} 
                                ${TOOLS_LIB_NAME}
                                ${CORE_LIB_NAME}
                                ${SOLVER_LIB_NAME}
                                ${IO_LIB_NAME}
                                ${SHELL_LIB_NAME} )
        add_dependencies( ${EXECUTABLE_NAME} ${COPY_RESOURCES_TARGET_NAME} )

# Build and run tests
    enable_testing( )
    add_executable( ${TEST_TARGET_NAME} tests/main.cpp                                  tests/catch2_custom_generators.hpp
                                        tests/catch2_custom_string_makers.cpp           tests/catch2_custom_string_makers.hpp
                                        tests/debugging_tools.cpp                       tests/debugging_tools.hpp
                                        tests/core/test_cell_t.cpp
                                        tests/core/test_utility.cpp
                                        tests/core/test_grid.cpp
                                        tests/picross_cli/test_picross_cli_state.cpp
                                        tests/picross_cli/test_create_grid_command.cpp
                                        tests/picross_cli/test_load_grid_command.cpp
                                        tests/picross_cli/test_save_grid_command.cpp
                                        tests/picross_cli/test_modify_grid_command.cpp
                                        tests/picross_shell/test_commit_command.cpp
                                        tests/picross_shell/test_display_command.cpp
                                        tests/picross_shell/test_rollback_command.cpp
                                        tests/picross_shell/test_hints_command.cpp
                                        tests/picross_shell/test_check_command.cpp
                                        tests/picross_shell/test_cross_command.cpp
                                        tests/picross_shell/test_clear_command.cpp
                                        tests/picross_shell/test_exit_command.cpp
                                        tests/tools/cli/test_cli_input.cpp
                                        tests/tools/cli/test_cli_streams.cpp
                                        tests/tools/cli/cli_test_classes.cpp            tests/tools/cli/cli_test_classes.hpp
                                        tests/tools/cli/test_cli_menu.cpp
                                        tests/tools/cli/test_cli_menu_command.cpp
                                        tests/tools/cli/test_cli_command_sequence.cpp
                                        tests/tools/test_string_tools.cpp
                                        tests/tools/test_iterable_tools.cpp
                                        tests/generate_static_grids.cpp                 tests/generate_static_grids.hpp
                                        tests/io/test_xml_grid_serializer.cpp
                                        tests/io/test_text_grid_formatter.cpp )
    target_link_libraries( ${TEST_TARGET_NAME} PUBLIC ${CORE_LIB_NAME} ${CLI_LIB_NAME} ${IO_LIB_NAME} ${TOOLS_LIB_NAME} )
    add_dependencies( ${TEST_TARGET_NAME} ${COPY_RESOURCES_TARGET_NAME} )

    add_test( NAME "tests" COMMAND ${TEST_TARGET_NAME} )
    add_custom_command( TARGET ${TEST_TARGET_NAME}
                        COMMENT "Running tests"
                        POST_BUILD
                        COMMAND "./tests" )
