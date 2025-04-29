# Problem Statement

- [Problem Statement](#problem-statement)
  - [Instructions](#instructions)
    - [Merging Rules](#merging-rules)
    - [Constraints](#constraints)
    - [Input Format](#input-format)
    - [Output Format](#output-format)
  - [Task 1](#task-1)
  - [Task 2](#task-2)
  - [Task 3](#task-3)

## Instructions

You are given a matrix with $P$ rows and $K$ columns **where each row is unique**.

For example if $P=6$ and $K=5$, a possible input is:

```
1 2 4 4 2
1 2 4 6 2
2 2 2 2 2
2 1 2 2 2
2 3 2 2 2
1 2 3 4 5
```

The goal is to develop a heuristic compression algorithm that minimizes the number of rows based on certain rules.

### Merging Rules

1. Merging is performed row-wise.
3. You may merge multiple rows at once.
    
   **Example 1:**

    ```
    1 1 3 2      
    1 1 1 2   -->  1 1 1|2|3 2
    1 1 2 2
    ```

    **Example 2:**

    ```
    1 1 3 2       
    1 1 1 2   -->  1 1 1|3 2
    1 1 2 2        1 1 2 2
    ```

4. You may merge non-consecutive rows.
   
    ```
    1 3 5 5
    2 3 5 5
    1 4 5 5   -->  1|2 3|4 5 5
    2 4 5 5
    ```

    Another possible sub-optimal result after merging is:

    ```
    1 3|4 5 5
    2 3|4 5 5
    ```

5. The merging operation should be reversible: We should be able to obtain the original input from the compressed result, ignoring order of rows.
6. Two rows can be merged if they differ by exactly one column.
    
    An invalid merge is to convert 
    
    ```
    1 1 1 2
    1 3 2 2   -->  1 1|3 1|2 2  [WRONG]
    ```

   because if we had to unmerge/uncompress `1 1|3 1|2 2`, invalid rows such as `1 1 3 2` will be created.


One way to compress the original input is as follows:

1. Merge the first and second rows to yield `1 2 4 4|6 2`.
2. Merge rows 3-5 to yield `2 1|2|3 2 2 2`.

The final compressed result is:

```
1 2 4 4|6 2
2 1|2|3 2 2 2
1 2 3 4 5
```

### Constraints

- $K$ and $P$ are positive integers and can be extremely large, ranging from thousands to millions or more.
- You will be assessed on the **execution time** of your algorithm and the **compression ratio** achieved.

### Input Format

- Your program must read a **CSV** file to get the input data. The file extension should be `.csv`.
- Each row in the file should be unique.
- Each row has the same number of columns.
- The content of a cell may contain a number, a character, or a **non-empty** string. However, will not contain the following symbols: `|`, `,`.


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

### Output Format

- You must save your output to a separate CSV file.
- The order of rows in your output does not matter.
- The order of values in a merged cell does not matter. `3|4|5` is same as `4|3|5` and other permutations.


## Task 1

Write a function that performs clustering of rows given the following parameters:
- The input in array/string format
- Number of columns to be considered for clustering.
- The direction (forward or backward) of clustering. For a forward pass, process columns from left to right. For backward pass, process columns from right to left.

## Task 2

Extend the function in Task 1 to add a new parameter:

- The index of the column where clustering will start.

Create a **new** function that takes as parameter:

- The tolerance level (1, 2, or 3) for merging rows. A tolerance of 1 means that rows must differ by exactly 1 column to be mergeable. A tolerance of 2 means that rows must differ by 1 or 2 columns can be merged. 

> [!NOTE]
> When the tolerance is not equal to 1, you do **not** have to specify a value for the other parameters.

For example, when tolerance = 2:

```
1 2 3
3 3 3   --> 1|3 2|3 3
9 9 9       9 9 9
```

## Task 3

Create a **new** function that performs row clustering but **allows row duplication of any row in the original input any number of times**. An indicator (`^`) is then placed in a merged cell to indicate that a value comes from a duplicate row.

The goal of this task is to **minimize the number of duplicate rows created** while minimizing the number of rows in the output.

```
1,2,3,6
1,3,3,6        1 3,4 3 6
1,4,3,6   -->  1^|7 2 3 6
7,2,3,6        1 2 3^|4 6    
1,2,4,6
```