*This project has been created as part of the 42 curriculum by andcardo.*

# Philosophers: I Never Thought Philosophy Would Be So Deadly

## Description
The **Philosophers** project is an introduction to the basics of concurrent programming and process threading. It is a 42 School adaptation of Edsger Dijkstra's classic "Dining Philosophers" problem. 

The goal of this project is to successfully manage shared resources across multiple threads running simultaneously without causing data races, memory leaks, or deadlocks. In this simulation, philosophers sit around a round table doing three things: eating, sleeping, and thinking. To eat, a philosopher must safely acquire two forks (one on their left and one on their right) without starving to death. 

Through this project, I learned how to create and join POSIX threads, implement mutexes for memory protection, and design robust architectures to handle edge cases in highly parallel environments.

## Instructions

### Compilation
To compile the project, clone the repository and run the `make` command at the root of the directory. This will compile the source files using `cc` with the required flags (`-Wall -Wextra -Werror -pthread`) and generate the `philo` executable.

## Execution
Run the program with the following arguments:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
 	•	⁠number_of_philosophers: The number of philosophers sitting at the table (and the number of forks). 	•	⁠time_to_die: Time in milliseconds. If a philosopher doesn't start eating within this time after the start of their last meal, they die. 	•	⁠time_to_eat: Time in milliseconds it takes for a philosopher to eat (requires holding two forks). 	•	⁠time_to_sleep: Time in milliseconds a philosopher spends sleeping. 	•	⁠number_of_times_each_philosopher_must_eat: (Optional) The simulation stops if all philosophers have eaten at least this many times. If left blank, the simulation runs until someone dies.
Usage Examples
Example 1: Infinite Survival
Five philosophers, plenty of time to eat and sleep. The simulation will run forever.
 ./philo 5 800 200 200
 Example 2: Inevitable Death
Four philosophers, tight timings. A philosopher will eventually starve.
 ./philo 4 310 200 100
 Example 3: Meal Target Reached
Five philosophers will eat exactly 7 times each, after which the program will exit cleanly.
 ./philo 5 800 200 200 7
 Technical Choices
	•	Deadlock Prevention: Implemented the "Asymmetric Solution" (Resource Hierarchy). Even-numbered philosophers reach for their left fork then right, while odd-numbered philosophers reach for their right fork then left. This breaks circular waiting patterns. 	•	The Monitor Thread: A dedicated "Grim Reaper" thread runs entirely outside the philosopher routines to constantly monitor starvation times. This ensures a death is announced within the strict 10ms tolerance, even if a philosopher is blocked by a mutex or ⁠usleep. 	•	Custom Sleep: Implemented a micro-chunking ⁠ft_usleep function to combat the natural time drift of standard C ⁠usleep, ensuring high-precision scheduling.
Resources
	•	Documentation: POSIX Threads Programming (LLNL) 	•	Theory: Edsger Dijkstra's original papers on the Dining Philosophers Problem and Resource Hierarchy Solutions. 	•	AI Usage: Artificial Intelligence (LLM) was utilized throughout this project specifically for:
	▪	Research: Understanding the theoretical concepts of concurrency, data races, deadlocks, and the differences between threads and processes. 	▪	Debugging: Tracing complex segmentation faults related to thread-joining orders, diagnosing out-of-bounds array access, and resolving obscure data races caught by ThreadSanitizer. 	▪	Refactoring: Restructuring functions to adhere strictly to the 42 Norm (v4.1), keeping functions under 25 lines, and improving overall code readability and modularity.
