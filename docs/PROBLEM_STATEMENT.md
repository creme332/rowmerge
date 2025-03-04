# Problem Statement

You are given a file with $P$ rows and $K$ columns **where each row of the file is unique**.

For example if $P=6$ and $K=5$, a possible input is:

```
1 2 4 4 2
1 2 4 6 2
2 2 2 2 2
2 1 2 2 2
2 3 2 2 2
1 2 3 4 5
```

We want to compress the file based on the following rules:

1. Merging is performed row-wise.
3. You may merge multiple rows at once.
    
    ```
    1 1 3 2      
    1 1 1 2
    1 1 2 2
    ```

    becomes `1 1 1|2|3 2`.


    ```
    1 1 3 2       
    1 1 1 2
    1 1 2 2
    ```

    becomes
    
    ```
    1 1 1|3 2
    1 1 2 2
    ```
4. You may merge non-consecutive rows.
   
    ```
    1 3 5 5
    2 3 5 5
    1 4 5 5
    2 4 5 5
    ```

    becomes `1|2 3|4 5 5`.

5. Two or more rows can only be merged if they differ by only one column.
    
    An invalid merge is to convert 
    
    ```
    1 1 1 2
    1 3 2 2
    ```

    to `1 1|3 1|2 2` because if we had to un-merge `1 1|3 1|2 2`, invalid rows such as `1 1 3 2` will be created.



One way to compress the original input file is as follows:

1. Merge the first and second rows to yield `1 2 4 4|6 2`.
2. Merge rows 3-5 to yield `2 1|2|3 2 2 2`.

The final compressed result is:

```
1 2 4 4|6 2
2 1|2|3 2 2 2
1 2 3 4 5
```

The goal is to develop a heuristic algorithm compression that minimizes the number of rows.


## Constraints

- $K$ and $P$ are positive integers and can be extremely large, ranging from thousands to millions or more.
- You will be assessed on the execution time of your algorithm and the compression ratio achieved.

## Input

- Your program must read a **CSV** file to get the input data. The file extension should be `.csv`.
- Each row in the file should be unique.
- Each row contains the same number of columns.
- The content of a cell is not important, so it can contain a number, a character, or anything else.


Examples of valid input file:

```
1,1,2,3,1
1,1,2,3,3
3,1,3,1,3
```

```
s,a,a,3,1
e,e,2,s,3
e,f,f,a,3
```

Examples of invalid input file:

```
1,1,2,3,1
1,1,2,3,1
1,1,2,3,1
```

```
1,1,2,3,1
1,1,2,3,1
1,1,2
```

## Output

- You must output your compressed result to a separate CSV file.
- The order of rows in your output does not matter.
- The order of values in a merged cell does not matter. `3|4|5` is same as `4|3|5` and other permutations.