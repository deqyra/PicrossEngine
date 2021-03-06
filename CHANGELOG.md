# [PicrossEngine v0.1](https://github.com/deqyra/PicrossEngine/releases/tag/v0.1)

Functional groundwork to build upon in future releases.

**Main additions:**

- Fully featured representation of a game state
- Flexible CLI menu/command architecture to easily build apps around
- XML serialization
  
Includes an **interactive CLI app** capable of the following:  

- Create a new grid
- Load a grid from an XML file
- Save a grid to an XML file

**Planned for next release:**

- Print grid on screen
- Modify grid through CLI app
- Tests (and maybe CI)
- Windows support (it currently builds but doesn't run)

# [PicrossEngine v1.0](https://github.com/deqyra/PicrossEngine/releases/tag/v1.0)

Fully working Picross simulator. Lacks solvers.  

**Main additions:**

- Modular buildsystem
- CLI menu/command became a new library kind of thing, in order to make it reusable in any kind of project
- Newly added shell also became a library in that fashion
- General restructuration of the project following these changes
- Nice test suite
- CI is live!
  
Includes an **interactive CLI app** capable of the following:  

- Create a new grid
- Load a grid from an XML file
- Save a grid to an XML file
- **Modify a loaded grid**
This is done through displaying a shell to the user, who can then input commands to modify the grid. Documentation is to be available in the wiki of the repo.

**Planned for next release:**

- Windows console support: UTF8 characters display gibberish for now. If you are using Windows, please consider installing WSL and using the project from there.
- Iterative solver

# [PicrossEngine v1.1](https://github.com/deqyra/PicrossEngine/releases/tag/v1.1)

Some bug fixes as well as a whole lot of general code enhancement.  

**Main additions:**

- Upgraded `hints` shell command: grid hints can now be reset and otherwise manipulated in a bunch of ways
- More tests and comments
  
**Bug fixes:**

- XML deserializer now accepts XML grids with no content
- Text formatter now properly renders grids with no vertical or horizontal hints
- Text formatter now properly renders grids with hints of any character width
- Failproof exception handling
- Tests don't fail to compile anymore with MinGW
- Windows console now prints all characters properly

**Planned for next release:**

- Iterative solver
- Ease-of-life improvements to the CLI menus and grid modification shell
