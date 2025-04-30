# rowmerge

![Ubuntu](https://img.shields.io/badge/Ubuntu-E95420?style=for-the-badge&logo=ubuntu&logoColor=white) ![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)

```
1 2 4 4 2
1 2 4 6 2           1 2 4 4|6 2
2 2 2 2 2   ----->  2 1|2|3 2 2 2
2 1 2 2 2           1 2 3 4 5
2 3 2 2 2
1 2 3 4 5
```

Please view the [documentation](docs/PROBLEM_STATEMENT.md) for more details about the problem.

## Features

- Automated unit testing to ensure code reliability.
- Four different algorithms, including a multithreading solution for row merging.
- Comprehensive input validation at all steps, with clear error messages for invalid data.
- Automatic executable generation with Github Actions.
- Generator function to create test inputs for easy validation and benchmarking.

## Results

### Time comparison

Time format = `Minute:Second.Millisecond`

| Dataset      | `TrivialAlgorithm` | `MultithreadedAlgorithm` | `OptimizedAlgorithm` | `CompressedTableAlgorithm` |
| ------------ | ------------------ | ------------------------ | -------------------- | -------------------------- |
| mini.csv     | 00:00.000          | -                        | 00:00.000            | 00:00.000                  |
| 90_8.csv     | 00:00.012          | 00:00.023                | 00:00.000            | 00:00.000                  |
| 3k_5.csv     | 00:01.537          | 00:01.981                | 00:00.248            | 00:01.489                  |
| 20k_8.csv    | 02:15.998          | 00:45.969                | 00:00.224            | 01:37.272                  |
| 20k_10.csv   | 01:43.109          | 01:05.649                | 00:00.357            | 00:37.920                  |
| 60k_10.csv   | 18:17.132          | 03:42.275                | 00:01.159            | -                          |
| 100k_100.csv | 02:54.357          | -                        | 00:00.204            | 00:05.003                  |
| 150k_4.csv   |                    | -                        | 00:09.332            | -                          |

### Compression ratio comparison

| Dataset      | `TrivialAlgorithm` | `MultithreadedAlgorithm` | `OptimizedAlgorithm` | `CompressedTableAlgorithm` |
| ------------ | ------------------ | ------------------------ | -------------------- | -------------------------- |
| mini.csv     | 0.375              | -                        | 0.375                | 0.375                      |
| 90_8.csv     | 0.539326           | 0.539326                 | 0.550562             | 0.52809                    |
| 3k_5.csv     | 0.176351           | 0.341081                 | 0.278617             | 0.278617                   |
| 20k_8.csv    | 0.350467           | 0.449692                 | 0.418871             | 0.39302                    |
| 20k_10.csv   | 0.0340276          | 0.542523                 | 0.431225             | 0.440632                   |
| 60k_10.csv   | 0.0381058          | 0.629431                 | 0.436393             | -                          |
| 100k_100.csv | 1                  | -                        | 1                    | 1                          |
| 150k_4.csv   |                    | -                        | 0.436113             | -                          |

> [!TIP]
> Smaller compression ratio = better.

## Conclusion

- `CompressedTableAlgorithm` is similar to OptimizedAlgorithm but performs worse.
- `TrivialAlgorithm` is better if the goal is to minimize compression ratio.
- `OptimizedAlgorithm` is better if the goal is to minimize time of execution while keeping a respectable compression ratio.

## Contributors

- creme332
- shandoescode
- pawanjheelan
- Darshan Narain
- Vib721