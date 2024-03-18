# 3A-LilTrieAdventure analysis

Unlike programming projects, this repo does not have any `tests` infrastructure.

## To Compile/Run
1.  You will need to copy your 3P-Trie header and source file file into this tree.  
    The build expects them to be named `trie.h` and `trie.cpp`.  Make sure you can
    build `main-lta` with your 3P-Trie code before making changes for this project.
2. `cmake . -B build` (on Windows native, use `cmake . -B build -G "MinGW Makefiles"`)
3. `cd build`
4. `make` (on Windows native, use `mingw32-make`) 
5. `./run-main`

