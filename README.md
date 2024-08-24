# minitalk
Signal Testing project for local server-client communication.

---

This was a very simple project to introduce signal handling.

The Task:
Create a Server, receiving either SIGUSR1 or SIGUSR2 and create a character out of the signals sent, building a message that a client had converted from a string into signals.

This was achieved by sending either SIGUSR1 or SIGUSR2 for each bit inside of each character and then piecing it back together on the receiving side.

On successfull reception the server would send back an acknowledgment and wait for further input.

Structurally quite simple it nonetheless introduced signal handlers and deepened my understanding of bitshifting using the AND OR and XOR operators.
