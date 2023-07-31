# Tixt
Tixt is a new file editor and directory manager focusing on the user's comfort rather than its own power. 

## This is an expermintal product! Please report bugs.

# Keybindings
`$` is the prefix or `ctrl` key.

`#` is the enter key.

Note that movement can also be done with arrow keys.

### Inside the Editor
`ESC` -> clear all warnings

`$q#` -> exit tixt

`$j`  -> go down one line (you can use arrow keys too)

`$k`  -> go up one line   (you can use arrow keys too)

`$w$w`-> go to the top of the screen

`$s$s`-> go to the bottom of the screen

### Inside the File Manager
Not Implemented yet.


# Behavior and features
If tixt is called with no arguments, you can view all the files and directories in `$PWD`. You can select one by pressing enter or you can create a new file by pressing `$nf` (see Keybindings for more details).
Tixt automatically detects if you want to open a directory or a file.
If you open a file and it's in an executable format, tixt will give you details about that file. [Not Implemented]
