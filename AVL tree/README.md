# Self-Balancing Binary Search Tree or AVL Tree
- This program implements an [AVL Tree](https://en.wikipedia.org/wiki/AVL_tree) in C which is a version of a [BST (Binary search tree)](https://en.wikipedia.org/wiki/Binary_search_tree).  
- This Tree balances itself after each operation (removal and insertion of keys).
- At the end of execution, the expected output shows the resulting keys and their respective layers.  
- The program reads from stdin.  
- Run "make" to compile.

## Program input
```i x``` - inserts x into the tree  
```r y``` - removes y from the tree  
```q```   - ends program and shows resulting tree  
```EOF``` - ends program and shows resulting tree

Reading from file:
```
./myavl < teste.in
```

Example Input:
```
i 4
i 6
i 1
i 2
i 7
i 3
i 5
i 8
r 8
```

Expected Output:
```
1,2
2,1
3,2
4,0
5,2
6,1
7,2
```

This example tree looks like this:
```
     4
   /   \
  2     6
 / \   / \
1   3 5   7
```
