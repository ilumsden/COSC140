# Homework 8: Big-O

## Problem 1:

Determine the Big-O expression for each of the following T(N) functions:

    a) T(N) = 2N + N(N+3)
    b) T(N) = 5
    c) T(N) = N + log(N^2)
    d) T(N) = N(2 + log(N))

## Problem 2:

Given an array list, determine the following Big-O costs:

    a) Worst case cost associated with finding the ith element.
    b) Average cost for checking if a specific data value is present. All locations are equally likely.

## Problem 3:

Given a linked list, determine the following Big-O costs:

    a) Worst case cost associated with finding the ith element.
    b) Average cost for checking if a specific data value is present. All locations are equally likely.

## Problem 4:

The Big-O cost for executing the for-loop shown below is O(sqrt(N)) = O(N^(1/2)). Give simple mathematical explanations why this is quadratically faster than O(N), but exponentially slower than O(log(N)).

```
bool isprime(int N) {
    if (N <= 1) {
        return false;
    }
    for (int i = 2; i*i <= N; i++) {
        if (N % i == 0) {
            return false;
        }
    }
    return true;
}
```
