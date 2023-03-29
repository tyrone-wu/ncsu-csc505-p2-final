# Final project for team ...

## Teammates

* Andrew Sauerbrei, amsauerb
* AJ Bulthuis, ajbulthu
* Tyrone Wu, tkwu

## Project Description

We plan to do an implementaiton with the focus our project being parallel algorithms for identifying connected components. The comparitive analysis will be on the following algorithms:
  - Parallel Breadth-First Search (BFS): This algorithm was convered in class, however, we plan on parallelizing the processes at each "level" when a node is adding their neighbors. 
  - Parallel Label Propagation: This is an algorithm that we have not covered in class, so it is something our team will have learn and implement. Label Propogation can also be parallelized, based on our research so far. 

We plan on implementing them with C++ and OpenMP for our parallel framework.  
The objective is to compare the runtimes of identifying the connected components against:
  - the overall size of the graphs
  - the number of connected components in the graph
  - the sparsity/density of the graph
