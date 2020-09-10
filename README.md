# Content

1. [Project description](https://github.com/shikarukitake/lem-in#lem-in)
2. [How to run](https://github.com/shikarukitake/lem-in#how-to-run)
3. [Marks](https://github.com/shikarukitake/lem-in#marks)
4. [Bonus](https://github.com/shikarukitake/lem-in#bonus)
5. [Resources](https://github.com/shikarukitake/lem-in#resources)

# Lem-in
The goal of this project is to find the quickest way to get n ants across the farm. To achieve the best efficiency Bellman-Ford and Suurballe's algorithms were used for finding the shortest disjoint paths in a graph. The graph is represented by an adjacency list in order to get a low time and memory complexity. Number of needed paths depends on the amount of ants.

# How to run
You can compile whole project with
```
make
```
Or you can open project with CLion and load CMake Project

Then you can run program like this:
```
./lem-in < map_file
```
# Map file
Structure of map looks like this:
```
number_of_ants
the_rooms
the_links
```
Example:
```
20
##start
A 0 1
##end
H 1 0
B 0 0
C 1 1
D 2 2
E 3 3
F 4 4
G 5 5
A-B
B-C
C-D
D-H
A-E
E-D
E-F
D-F
F-G
G-H
```
Comments "##start" and "##end" are provided to show the start and end room information.

# Marks
```
**in progress**
```

# Bonus
```
-l -- flag to print count of solution's lines
-p -- flag to print finded paths
-h -- flag to read the manual of flags
```

# Resources
[Macfreek](http://www.macfreek.nl/memory/Disjoint_Path_Finding#Suurballe)

