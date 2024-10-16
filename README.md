# **🧠💀 42 Paris - Philosophers: I never thought philosophy would be so deadly ⚔️🍝**

![Project Status](https://img.shields.io/badge/Philosophy-Deadly-red)
## Project overview

This project simulates the classic "Dining Philosophers" problem, where some philosophers sit at a table with a bowl of spaghetti. They alternate between eating, thinking, and sleeping, but they need two forks to eat, and only one fork is available between each pair of philosophers.

The challenge is to manage threads and mutexes to ensure that no philosopher starves and that the simulation adheres to strict timing constraints.

## Key concepts

Threading and Mutexes: Each philosopher is represented by a thread, and forks are shared resources, protected by mutexes to avoid race conditions.

Philosopher Actions: Philosophers can eat, think, or sleep. They need to take two forks (mutexes) to eat. After eating, they return the forks and go to sleep. If a philosopher doesn’t eat in time, he dies, and the simulation ends.

Simulation Rules:
- Number of philosophers = number of forks.
- A philosopher can only eat when both their left and right forks are available.
- The simulation ends when a philosopher dies or when all have eaten a specified number of times.
- Logging: The program logs events with precise timestamps, such as when a philosopher takes a fork, starts eating, starts sleeping, or dies.

Project Requirements:
- Written in **C** with a Makefile to compile the project.
- No global variables.
- Must handle proper memory management : `make debug` to run with fsanitize
- Use standard C library functions such as `malloc`, `free`, `pthread_create`, `pthread_mutex_lock`, etc.
- No data races allowed.

The program accepts the following arguments:

- `number_of_philosophers`: The number of philosophers and forks.
- `time_to_die` (in ms): Time (in milliseconds) before a philosopher dies if they haven’t eaten.
- `time_to_eat` (in ms): Time (in milliseconds) a philosopher spends eating.
- `time_to_sleep` (in ms): Time (in milliseconds) a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): The number of times each philosopher needs to eat before the simulation ends. If not specified, the simulation runs until a philosopher dies.



## Demo

<div align="center">

![Demo of philosophers project](philo/demo/demo.gif)

</div>