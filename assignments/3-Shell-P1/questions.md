1. In this assignment I suggested you use `fgets()` to get user input in the main while loop. Why is `fgets()` a good choice for this application?

    > **Answer**:  It is a clean way to get string from the input buffer rather than read from stdin yourself which can be annoying and lead to more issues. So it basically handles all of the annoying stuff with dealing directly with stdin, error handling, etc.

2. You needed to use `malloc()` to allocte memory for `cmd_buff` in `dsh_cli.c`. Can you explain why you needed to do that, instead of allocating a fixed-size array?

    > **Answer**:  In my case I got it to work without malloc first, but went back and changed it. It does work with just using a static sized array, but in the case we need to work with the buffer in a different way than I did it, or a situation where we need to mutate the buff, malloc gives us more flexibility in that area.


3. In `dshlib.c`, the function `build_cmd_list(`)` must trim leading and trailing spaces from each command before storing it. Why is this necessary? If we didn't trim spaces, what kind of issues might arise when executing commands in our shell?

    > **Answer**: So the way I handled it is to split by | if possible, then split by " ", which basically trims off any trailing spaces and whatnot when getting the exe and the args. But if you didn't do it this way, it would consider a space as part of the command so " dragon" for example would not be a valid command since it would count the space as part of the command. But in my case " dragon" would first try to be split by "|", then split by " " for that "|" split, so giving us just dragon since it essentially removes spaces and gives us the list of split strings, which would just be "dragon".

4. For this question you need to do some research on STDIN, STDOUT, and STDERR in Linux. We've learned this week that shells are "robust brokers of input and output". Google _"linux shell stdin stdout stderr explained"_ to get started.

- One topic you should have found information on is "redirection". Please provide at least 3 redirection examples that we should implement in our custom shell, and explain what challenges we might have implementing them.

    > **Answer**:  A few examples that are common in shells are > for overwriting and creating a new file with stdout, >> which does the same with the output to a file specified on the right but appends to it or creates it, so not overrite, and a slightly more unusual one I had to lookup, 2> which handles errors in the case there is one from stderr and isntead of putting it in the terminal, puts it in the file specified.

    So for the challenges, for implementing all of these would be differentiating between commands and these functions, as the current system is based on splitting on |, so then we need to split on multiple different keys, detect that it is split on that, then handle logic accoringly, which adds complexity.

- You should have also learned about "pipes". Redirection and piping both involve controlling input and output in the shell, but they serve different purposes. Explain the key differences between redirection and piping.

    > **Answer**:  So a pipe is the symbol we use for working with outputs of commands, then sending that output as the input to a command to the right of the pipe, while the redirection I showed is about taking output of a command and sending it to a file, whether it be stdout or stderror. So pipes are used for chains of commands while redirection is just sending of output to a location.

- STDERR is often used for error messages, while STDOUT is for regular output. Why is it important to keep these separate in a shell?

    > **Answer**:  Well like the 2> example I provided, in the case that stdout had values before reaching an error, stderror is a way to differentiate them and append only the error message to the file in the case that there is an issue. Its basically just logging fundamentals, keep errors seperate from the same channel, so it is easier to read and debug from as well.

- How should our custom shell handle errors from commands that fail? Consider cases where a command outputs both STDOUT and STDERR. Should we provide a way to merge them, and if so, how?

    > **Answer**:  When we eventually fully implement commands, in the case where a command being processed is OK but the command itself has an error when being run, we would use both stdout and stderror. In this case, we could have a unified log/output for both. In linux terminal, by using 2>&1 this actually combines stdout and stderror into a single output, so we could also implement something similar to this.