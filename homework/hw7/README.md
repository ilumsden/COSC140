# Homework 7: Hash Tables

## Problem 1:

Consider a hash table for which collisions are handled by chaining using single-linked lists. The keys are integers. The table size is 10. The hash function is h(key) = key %10. Determine the contents fo the hash table AFTER the following sequence of integers have been inserted: 12, 44, 13, 67, 23, 90, 11, 25, 21, and 45. List the table index followed by the chain of keys with the newest key listed first. That is:

```
0: 90
1: 11, 21
etc
```

## Problem 2:

Consider a hash table for which collisions are handled by open addressing based on quadratic probing. The hash function is `h(key) = key % 23`. For each integer key in the sequence 12, 44, 13, 67, 23, 90, 11, 25, 21, and 45, list the key and the set of table indices tested until insertion is successful. That is:

```
12: 12
44: 21
13: 13
67: 21, 22
etc
```
