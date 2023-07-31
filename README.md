# Tixt
Tixt is a new file editor and directory manager focusing on the user's comfort rather than its own power. 

# Keybindings
`$` is the prefix or `ctrl` key.
`#` is the enter key.
Note that movement can also be done with arrow keys.

### Inside the Editor
`ESC` -> clear all warnings
`$q#` -> exit tixt
`$j`  -> go down one line
`$k`  -> go up one line
`$h`  -> go left once
`$l`  -> go right once

### Inside the File Manager
`ESC` -> clear all warnings
`$q#` -> exit tixt
`$j`  -> go down one line
`$k`  -> go up one line
`$h`  -> go left once
`$l`  -> go right once
`$nf` -> create a new file
`$nd` -> create a new directory


# Behavior and features
If tixt is called with no arguments, you can view all the files and directories in `$PWD`. You can select one by pressing enter or you can create a new file by pressing `$nf` (see Keybindings for more details).
Tixt automatically detects if you want to open a directory or a file.
If you open a file and it's in an executable format, tixt will give you details about that file.
