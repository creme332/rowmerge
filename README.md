# rowmerge

A heuristic algorithm for merging rows efficiently. Please view the [problem statement](docs/PROBLEM_STATEMENT.md) for more details.


```
1 2 4 4 2
1 2 4 6 2           1 2 4 4|6 2
2 2 2 2 2   ----->  2 1|2|3 2 2 2
2 1 2 2 2           1 2 3 4 5
2 3 2 2 2
1 2 3 4 5
```


Download links:


[![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
](https://github.com/creme332/rowmerge/releases/latest/download/rowmerge-windows-amd-64) [![Ubuntu](https://img.shields.io/badge/Ubuntu-E95420?style=for-the-badge&logo=ubuntu&logoColor=white)](https://github.com/creme332/rowmerge/releases/latest/download/rowmerge-linux-amd-64
)[![macOS](https://img.shields.io/badge/mac%20os-000000?style=for-the-badge&logo=macos&logoColor=F0F0F0)](https://github.com/creme332/rowmerge/releases/latest/download/rowmerge-macos-amd-64
)

## Features

- Four different algorithms, including a multithreading solution for row merging.
- Generator function to create test inputs for easy validation and benchmarking.
- Validator program for CSV file and output file.
- Automated unit testing to ensure code reliability.
- Comprehensive input validation at all steps, with clear error messages for invalid data.
- Automatic executable generation for different platforms with Github Actions.

## Installation

To download the source code and compile the program locally, see the [installation guide](docs/INSTALLATION_GUIDE.md). If you only want to run the program, use the download buttons above.

## Results

### Time comparison

> [!NOTE]  
> Time format = `Minute:Second.Millisecond`. Smaller time =  better.

| Dataset     | `TrivialAlgorithm` | `MultithreadedAlgorithm` | `OptimizedAlgorithm` | `CompressedTableAlgorithm` |
| ----------- | ------------------ | ------------------------ | -------------------- | -------------------------- |
| mini.csv    | 00:00.000          | 00:00.001                | 00:00.000            | 00:00.000                  |
| 90_8.csv    | 00:00.012          | 00:00.023                | 00:00.000            | 00:00.000                  |
| 3k_5.csv    | 00:01.537          | 00:01.981                | 00:00.248            | 00:01.489                  |
| 10k_100.csv | 02:54.357          | 00:40.897                | 00:00.204            | 00:05.003                  |
| 20k_8.csv   | 02:15.998          | 00:45.969                | 00:00.224            | 01:37.272                  |
| 20k_10.csv  | 01:43.109          | 01:05.649                | 00:00.357            | 00:37.920                  |
| 60k_10.csv  | 18:17.132          | 03:42.275                | 00:01.159            | -                          |
| 150k_4.csv  | -                  | -                        | 00:09.332            | -                          |
| 5m_10.csv   | -                  | -                        | 002:41.641           | -                          |

### Compression ratio comparison

> [!NOTE]
> Compression ratio = Final Line Count ÷ Initial Line Count. Smaller compression ratio = better.

| Dataset     | `TrivialAlgorithm` | `MultithreadedAlgorithm` | `OptimizedAlgorithm` | `CompressedTableAlgorithm` |
| ----------- | ------------------ | ------------------------ | -------------------- | -------------------------- |
| mini.csv    | 0.375              | 0.375                    | 0.375                | 0.375                      |
| 90_8.csv    | 0.539326           | 0.539326                 | 0.550562             | 0.52809                    |
| 3k_5.csv    | 0.176351           | 0.341081                 | 0.278617             | 0.278617                   |
| 10k_100.csv | 1                  | 1                        | 1                    | 1                          |
| 20k_8.csv   | 0.350467           | 0.449692                 | 0.418871             | 0.39302                    |
| 20k_10.csv  | 0.0340276          | 0.542523                 | 0.431225             | 0.440632                   |
| 60k_10.csv  | 0.0381058          | 0.629431                 | 0.436393             | -                          |
| 150k_4.csv  | -                  | -                        | 0.436113             | -                          |
| 5m_10.csv   | -                  | -                        | 0.389667             | -                          |

## Conclusion

- Choose `TrivialAlgorithm` if the goal is to minimize compression ratio.
- Choose `OptimizedAlgorithm` if the goal is to minimize time of execution while keeping a respectable compression ratio.

## Contributors

- creme332
- shandoescode
- pawanjheelan
- Darshan Narain
- Vib721