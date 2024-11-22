# Family Tree Management System

A C program designed to manage and explore family trees. It allows users to add individuals, define relationships (marriage, parent-child), view family hierarchies, track generations, calculate cousin relationships, and simulate the passage of time.

## Features
- **Add individuals**: Create new family members with names and ages.
- **Marriage relationships**: Define and validate marriages between individuals.
- **Parent-child connections**: Link children to their parents and vice versa.
- **Family tree visualization**: Print family structures from the top down.
- **Cousin detection**: Identify cousins up to a specified degree.
- **Simulation**: Advance time to age all individuals.
- **Data management**: Sort names, reset flags, and clean memory.

## How to Use
1. Compile the program using any standard C compiler:
   gcc family_tree.c -o family_tree
   
Follow the on-screen menu to interact with the system:
1: Add a new family member (head).
2: Marry two people.
3: Add a child to a couple.
4: Print a family tree top-down.
5: Simulate the passage of years.
6: Count the total number of individuals.
7: Print cousins of a specific degree.

## Menu Options
Choose an option:
0. Exit
1. Add a head
2. Marry two people
3. New offspring
4. Print family top-down
5. Years pass
6. Count people
7. Print cousins

## File Overview
family_tree.c: The main source file containing all logic for managing the family tree.
Structures:
Humanbeing: Represents an individual with details like name, age, parents, partner, and children.
Node: Represents a linked list node for managing family members.
Allhumans: Container for the entire family tree.

##Future Improvements
Add functionality for saving/loading family tree data to/from a file.
Expand relationship calculations to include aunts, uncles, and grandparents.
Enhance error handling for invalid inputs.
