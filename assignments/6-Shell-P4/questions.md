1. How does the remote client determine when a command's output is fully received from the server, and what techniques can be used to handle partial reads or ensure complete message transmission?

The remote client knows the output is fully received when it gets the success message back, or if the command has an error, etc. To ensure complete message trasmission we keep reading until we hit the end EOF marker to ensure that it has been fully received.

2. This week's lecture on TCP explains that it is a reliable stream protocol rather than a message-oriented one. Since TCP does not preserve message boundaries, how should a networked shell protocol define and detect the beginning and end of a command sent over a TCP connection? What challenges arise if this is not handled correctly?

So we can ensure it is handled correctly, you would typically use a delimiter to know when the beginning and end of a command come in. If this is not handled correctly you could have a range of issues from like the commands coming in being fragments of what they actually are, or missing parameters ect. But using a delimiter to ensure the full command is processed can cirumvent this issue.

3. Describe the general differences between stateful and stateless protocols.

A stateful protocol has memory, meaning it has a history of what has transpired during the session, while a stateless protocol forgoes this with the idea that it can save processing time and storage while not caring about any more complex situations that a stateful protocol could handle with its memory.

4. Our lecture this week stated that UDP is "unreliable". If that is the case, why would we ever use it?

Because the order and validity or integrity of the data is no guaranteed by UDP, it is seen a messy and quick way to send over data. The reason it would still be used is if you dont care if you lose some data here and there and instead care about speed and lower latency when sending data through your connection.   

5. What interface/abstraction is provided by the operating system to enable applications to use network communications?

The famous and common workplace term, API, and in this case sockets is what enables us to send data over a network connection in paticular for linux. Its the same idea in say my last job where you communicate with a site hosted on a certain ip and can communicate between than and the backend, but in our case we were running 2 different configurations for server and client for our different c files to host it that way using sockets.