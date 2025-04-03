# Insights

A number of observations have been made while working on the problem. 

## Choice of rows for grouping matters

Input:

```
1 3 y
1 3 x
1 4 x
2 3 x
2 4 x
```

One way to merge the rows is as follows:

1. Merge rows 1 and 2 to get `1 3 x|y`.
2. Merge rows 4 and 5 to get `2 3|4 x`.

The final result becomes:

```
1 3 x|y
1 4 x
2 3|4 x
```

A better way to compress the input is as follows:
1. Merge rows 2 and 4 to get `1|2 3 x`.
2. Merge rows 3 and 5 to get `1|2 4 x`.

This gives:

```
1 3 y
1|2 3 x
1|2 4 x
```

where a final grouping can be applied on rows 2 and 3 to get:

```
1 3 y
1|2 3|4 x
```

## Keep the merged column sorted

The problem statement does not require you to sort a merged column. For example, `1|2|3 1 1` can also be written as `2|1|3 1 1`, `2|3|1 1 1`, or other permutations. However, sorting the merged column (e.g., `1|2|3`) can increase the number of groupings.

Consider the following input:

```
2 3 2 1
1 2 2 1
2 2 2 1
1 3 2 1
```

which can be compressed as follows:

1. Merge rows 1 and 4 to yield `2|1 3 2 1`.
2. Merge rows 2 and 3 to yield `1|2 2 2 1`.

The final result becomes:

```
2|1 3 2 1
1|2 2 2 1
```

and cannot be merged further despite `2|1` and `1|2` being equivalent.

Sorting the merged column will prevent such a problem. To insert a new number into a merged column, binary search can be utilized. 
