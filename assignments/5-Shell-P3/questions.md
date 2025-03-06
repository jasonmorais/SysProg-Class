1. Your shell forks multiple child processes when executing piped commands. How does your implementation ensure that all child processes complete before the shell continues accepting user input? What would happen if you forgot to call waitpid() on all child processes?

Because we are calling waitpid on all child proccesses we obviously avoid this, but in a world where we didnt, the shell would not correctly process our commands, where we would have old child processes that never finished. But in my implementation we loop through the child processes at the very end and make sure to waitpid all of them, and error if an issue arrises.

2. The dup2() function is used to redirect input and output file descriptors. Explain why it is necessary to close unused pipe ends after calling dup2(). What could go wrong if you leave pipes open?

The purpose of closing the unused pipe the child processes that depend on the data to the next part of the pipe, creating issues further along, so you may have more dead child processes waiting for that pipe to fully close before it can proceed even if the process in the original pipe has already finished, leading to issues.

3. Your shell recognizes built-in commands (cd, exit, dragon). Unlike external commands, built-in commands do not require execvp(). Why is cd implemented as a built-in rather than an external command? What challenges would arise if cd were implemented as an external process?

Because of the issue with creating child processes, and is actually something I ran into. I one, didnt implement it at all first, forgot it from the previous, so when testing cd i quickly realized the issue, it couldnt find where it was because it was stuck in a child process which created issues. So you would need to create some reference while calling that fruther down, or some other solution, but is overall MUCH  easier to implement as an internal command than through exec.

4. Currently, your shell supports a fixed number of piped commands (CMD_MAX). How would you modify your implementation to allow an arbitrary number of piped commands while still handling memory allocation efficiently? What trade-offs would you need to consider?

I would need to reallocate memory whenever we hit the threshhold, which would force me to use malloc instead of memset, so I could later readjust the memory. Beyond that, you need some set limit or you allow your terminalt to be flooded and create issues with timeout and things beyond your control, so I think in my opinion I would always keep it set, but maybe to a slightly higher amount to allow some larger pipelines. Overall would require a lot more handling of memory on the fly using malloc and realloc.
