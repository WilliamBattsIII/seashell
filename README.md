# seashell is a C shell

There's no special steps to use this project -- you just compile the program and run it.


The shell doesn't use the PATH environment variable, or the *which* command, or anything -- it can't find commands on its own, you'll have to type the full path, like */bin/ls*.
There are *some* builtins, however. You can use *exit* to quit the shell. A way to change the working directory is coming soon-ish.