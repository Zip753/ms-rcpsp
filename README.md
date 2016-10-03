# MS-RCPSP
This repository contains a suboptimal solution (and its visualizations) of MS-RCPSP problem using simple genetic algorithm as a part of bachelor thesis.

## About MS-RCPSP problem
MS-RCPSP stands for Multi-Skill Resource Constrained Project Scheduling Problem, it is and NP-complete scheduling problem. Given a set of workers (a.k.a. *resources*), each possessing certain skills at certain levels, and a set of tasks, each with its own duration, (one) skill requirement and possible dependencies on other tasks, one has to find the sequence of tasks along with workers assignments that minimizes the total time of execution of all tasks. The conditions are as follows:
* every task can only be completed by one person and cannot be pre-empted
* no task can be started until all its dependencies (tasks) are finished
* workers can only execute one task at a time
* worker must possess the required skill at (not smaller than) required level in order to complete the task

## About solution
The solution implements a simple GA (genetic algorithm) using this interpretation:
* specimen are schedules
* genes are task assignments (assigned workers)

GA uses tournament selection and simple mutation and crossover operators. LAX crossover operator from [this paper](http://imopse.ii.pwr.edu.pl/files/Pages_57_62_Mendel2013_PRESS.pdf) has also been implemented as an experimental option.

When it comes to schedule building strategy, the solution in `simple` branch uses a so-called *schedule-builder* procedure, which generates a non-conflicting starting times for all tasks using worker assignments encoded in the genotype. Meanwhile the solution in `master` branch also encodes *task priority* in gene (along with worker assignment), so that when the worker is able to execute several tasks at some point, he always executes the task with the highest priority first. The simple solution is generally faster, but also greedier and performs worse on tasks with many dependencies. However, in simpler cases it proves to be a fast and viable solution.

## About test data
The solutions have been tested and validated on benchmarking corpus of iMOPSE project. The dataset and validation tool can be found [here](http://imopse.ii.pwr.edu.pl/download.html).

Also, the original input is first parsed using Ruby script into a simpler structured format, which is later given to the GA solution as an input.

## About visualizations
In order to comprehend the problem the solutions better, I have implemented the visualization tool for showing the business of each worker throughout the project execution. The tool takes a solution file and generates an HTML page with Google Timeline chart based on the solution data. An example of such chart is shown below:

![](img/d3_res.png)

As you can see, each worker is busy throughout the whole project, therefore it is easy to state that the following solution is optimal for the given input. On contrary, the next image isn't that trivial and contains gaps due to the numerous task dependencies:

![](img/d6_res.png)