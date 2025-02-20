1. Can you think of why we use `fork/execvp` instead of just calling `execvp` directly? What value do you think the `fork` provides?

    > **Answer**:  So we are creating a new forked terminal so that we dont touch or mess with the exisiting one, since we are basically simulating a fake terminal.

2. What happens if the fork() system call fails? How does your implementation handle this scenario?

    > **Answer**:  In the case that it fails I instead call wait pid to handle the closing of the fork and keep track of the success or failure of the waitpid result.

3. How does execvp() find the command to execute? What system environment variable plays a role in this process?

    > **Answer**:  the PATH variable is the key for this, since it checks what commands can be run from there. The same thing happens in your actual terminal, which is why you spend many hours trying to fix issues with commands not being found due to them not being included on the path. It gives back and error if its not on the path like you would commonly see.

4. What is the purpose of calling wait() in the parent process after forking? What would happen if we didn’t call it?

    > **Answer**:  My assumption is that it works like a promise, so you need to wait for it be executed, else you are trying to use the result of a unfinished process and hence will get an error or simply a delayed operation that has no value and would cause issues for the program.

5. In the referenced demo code we used WEXITSTATUS(). What information does this provide, and why is it important?

    > **Answer**:  It gets the exit status from the child process, so we know if it propelry exited or not, and in my case was used to determine if ok was returned or a command exectuion error.

6. Describe how your implementation of build_cmd_buff() handles quoted arguments. Why is this necessary?

    > **Answer**:  So an issue I had is that strtok would break this, so I had to rethink the way I implemented my soltution from the previous week. So instead I iterated over the string so we could properly handle the quoted arguments, and is needed because many commands require quotes for sections of text, like grep for example if there are spaces there. Just a required use case.

7. What changes did you make to your parsing logic compared to the previous assignment? Were there any unexpected challenges in refactoring your old code?

    > **Answer**:  I had to scrap pretty much all of the logic for reading the command, one because our behavior is different now, and two the requirements for handling commands changed. I moved executing commands out of the main loop command, and had to change from splitting the command to a more simple loop for extracting sections of the command due to the quote requirements, but stuff besides that didnt change as much. Was mianly that logic, and caused issues when running tests and realizing that strtok will just tear apart any logic I have for handling quotes for the requirements.

8. For this quesiton, you need to do some research on Linux signals. You can use [this google search](https://www.google.com/search?q=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&oq=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&gs_lcrp=EgZjaHJvbWUyBggAEEUYOdIBBzc2MGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8) to get started.

- What is the purpose of signals in a Linux system, and how do they differ from other forms of interprocess communication (IPC)?

    > **Answer**: They are async processes that allow the system to send requests to to one another, so a local way of handling requests like https where you need to await usually the result, but the signals themselves are a notification system for these async processes.

- Find and describe three commonly used signals (e.g., SIGKILL, SIGTERM, SIGINT). What are their typical use cases?

    > **Answer**:  SIGINT is sent when the user closes the terminal, so control c, SIGTERM is sent when the terminal is terminated completed so it can clean up resources, and SIGKILL is like SIGTERM but it does not clean up and just force shuts down the terminal, so kinda like when you task manager close a stubborn program.

- What happens when a process receives SIGSTOP? Can it be caught or ignored like SIGINT? Why or why not?

    > **Answer**:  SIGSTOP is a heavier hand, meaning that it cannot be ignored. It is ensured by the kernel itself that it goes through, so you could imagine it as a last resort if other ways of shutting down a process dont work, this allows you to bypass that.
