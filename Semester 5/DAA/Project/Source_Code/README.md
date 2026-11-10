# DAA Project: Closest Pair of Points and Karatsuba Multiplication

Design and Analysis of Algorithms (CS-2009), Fall 2026.

This project implements two divide and conquer algorithms in C++17:

1. Closest pair of points in 2D, in O(n log n) time (Kleinberg, Section 5.4).
2. Integer multiplication with Karatsuba's algorithm, switching to ordinary (schoolbook) multiplication when the numbers become small.

The project also contains a dataset generator, a command-line benchmark runner, an algorithm test program, and a Qt 6 graphical application that shows both algorithms working.


## 1. Project Structure

```
Project/
|
|-- CMakeLists.txt              Build file for all programs
|-- main.cpp                    Entry point of the Qt application
|-- README.md
|
|-- Algorithms/                 The two algorithms (no GUI code)
|   |-- ClosestPair.h
|   |-- ClosestPair.cpp
|   |-- Karatsuba.h
|   `-- Karatsuba.cpp
|
|-- GUI/                        Qt 6 graphical application
|   |-- MainWindow.h / .cpp             Window, sidebar, dashboard
|   |-- ClosestPairVisualizer.h / .cpp  Closest Pair page
|   |-- KaratsubaVisualizer.h / .cpp    Karatsuba page
|   |-- BenchmarkVisualizer.h / .cpp    Benchmark page
|   `-- DatasetPaths.h                  Finds the datasets folder
|
|-- DatasetGenerator/
|   |-- DatasetGenerator.cpp    Generates all 20 input files
|   `-- seeds.txt               Seed used for each of the 20 files
|
|-- Benchmark/
|   `-- BenchmarkRunner.cpp     Command-line benchmark program
|
|-- tests/
|   `-- AlgorithmTests.cpp      Algorithm test program
|
|-- datasets/
|   |-- closest_pair/           cp01.txt ... cp10.txt
|   `-- integer_multiplication/ im01.txt ... im10.txt
|
`-- results/
    `-- benchmark.csv           Benchmark results
```


## 2. Requirements

- Qt 6 with the MinGW kit (Widgets and Concurrent modules). The project was built with Qt 6.12.0, MinGW 64-bit.
- CMake 3.21 or newer.
- A C++17 compiler (the MinGW compiler that comes with Qt).

`CMakeLists.txt` sets the Qt location with this line:

```
set(CMAKE_PREFIX_PATH "C:/Qt/6.12.0/mingw_64")
```

If Qt is installed somewhere else on your computer, change that path to your own Qt folder (the one that contains `bin`, `lib` and `include`).


## 3. Building

There are two ways to build. Use whichever is easier.

### Option A: Qt Creator (recommended)

1. Open Qt Creator and choose File > Open File or Project.
2. Select `CMakeLists.txt` in the project folder.
3. Choose a Qt 6 MinGW kit and click Configure Project.
4. Select Release in the build type selector (bottom left) if you want accurate timings.
5. Press Ctrl+B to build everything.

### Option B: Command line

Open the Qt terminal from the Start menu (named like "Qt 6.12.0 (MinGW 64-bit)"). It already has the Qt tools and compiler on its PATH. Go to the project folder and run:

```
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

This builds four programs into the `build` folder:

| Program | What it is |
|---|---|
| `DAA_Project.exe` | The graphical application |
| `DatasetGenerator.exe` | Generates the 20 input files |
| `BenchmarkRunner.exe` | Command-line benchmark |
| `AlgorithmTests.exe` | Algorithm tests |

To build only one of them, add `--target` followed by its name, for example:

```
cmake --build build --target BenchmarkRunner
```

Release mode is recommended. Without it the programs are not optimized and the running times will be much larger.


## 4. Generating the Datasets

Run the generator from the project folder (not from inside `build`):

```
.\build\DatasetGenerator.exe
```

It creates:

- `datasets/closest_pair/cp01.txt` to `cp10.txt`
- `datasets/integer_multiplication/im01.txt` to `im10.txt`
- `DatasetGenerator/seeds.txt` (one seed per file)

It takes about one to two minutes and the output is about 100 MB. Existing files are overwritten. To write the datasets somewhere else, pass a folder name:

```
.\build\DatasetGenerator.exe my_output
```

### What each file contains

Closest pair files:

| File | Points | Content |
|---|---|---|
| cp01 to cp04 | 1,000 / 10,000 / 100,000 / 1,000,000 | Uniform random real coordinates in [0, 1,000,000] |
| cp05 | 1,000,000 | Clustered: points around 10 random centres |
| cp06 | 1,000,000 | Integer coordinates in a small range, so many duplicate points (closest distance 0) |
| cp07 | 100,000 | All points on one vertical line |
| cp08 | 100,000 | Equally spaced 400 x 250 grid (many tied closest pairs) |
| cp09 | 1,000,000 | Closest pair placed across the middle dividing line |
| cp10 | 101 | Small file for showing the algorithm step by step |

Integer multiplication files (each holds two non-negative integers):

| File | Digits per number | Content |
|---|---|---|
| im01 to im04 | 1,000 / 10,000 / 100,000 / 1,000,000 | Random digits, no leading zero |
| im05 | 1,000,000 and 10 | Numbers of very different lengths |
| im06 | 100,000 | One number is all 9s |
| im07 | 99,999 | Odd length, many zeros |
| im08 | 1,000,000 | Both numbers are powers of 10 |
| im09 | 1 and 1,000,000 | One number is 0 |
| im10 | 101 | Small file for showing the algorithm step by step |

### File format

- Closest pair: the first line is the number of points n, followed by n lines of "x y".
- Integer multiplication: two lines, each holding one number in decimal digits.

### Seeds

A seed is the starting value of the random number generator. Using a fixed seed means the generator produces the same files every time, so the large files (which are not submitted) can be regenerated exactly.

Each file has its own seed, listed in `DatasetGenerator/seeds.txt`, for example:

```
cp01 seed: 20261101
im10 seed: 20261210
```

Closest pair file number n uses seed 20261100 + n. Integer multiplication file number n uses seed 20261200 + n. The exact same values are guaranteed when the generator is built with the same compiler and standard library; the structure of every file (sizes, patterns, and the expected answers for cp06 to cp09) is the same on any compiler.


## 5. Running the Benchmark Runner

Run it from the project folder, giving a mode and a dataset file:

```
.\build\BenchmarkRunner.exe closest datasets/closest_pair/cp01.txt
.\build\BenchmarkRunner.exe multiply datasets/integer_multiplication/im01.txt
```

For each run it prints the input size, the result, and the execution time, and it appends one row to `results/benchmark.csv`.

Correctness checks:

- Closest pair is compared against brute force for datasets of up to 5,000 points.
- Multiplication is compared against schoolbook multiplication for numbers of up to 10,000 digits.
- Larger inputs are not checked by this program. The Benchmark page of the graphical application checks every dataset.

The results file has the columns `Algorithm,Dataset,InputSize,TimeMs,Result`.

To run all 20 datasets in PowerShell:

```
1..10 | ForEach-Object { .\build\BenchmarkRunner.exe closest ("datasets/closest_pair/cp{0:D2}.txt" -f $_) }
1..10 | ForEach-Object { .\build\BenchmarkRunner.exe multiply ("datasets/integer_multiplication/im{0:D2}.txt" -f $_) }
```


## 6. Running the Algorithm Tests

```
.\build\AlgorithmTests.exe
```


## 7. Running the Graphical Application

In Qt Creator, select the DAA_Project target and press Ctrl+R. From the command line, run `.\build\DAA_Project.exe` from the Qt terminal.

The datasets are found automatically: the program searches for a `datasets` folder starting from the folder it was launched from and from the folder of the program, going up several levels. Any file can also be chosen with the Browse button.

The sidebar has four pages.

### Dashboard

A summary of the two algorithms and the project.

### Closest Pair

1. Choose a dataset from the list, or click Browse... to pick any input file.
2. Click Load Dataset. The points are drawn on the plot.
3. Click Run Algorithm.

The page shows the number of points, the minimum distance, the execution time, and the closest pair highlighted in red on the plot. For datasets of up to 500 points (for example cp10) it also shows the algorithm step by step: the recursive divisions, the strip comparisons, and the final pair. For larger datasets it shows the final result and the running time. The plot of a large dataset shows a sample of the points to stay fast.

### Karatsuba

1. Choose a dataset from the list, or click Browse... to pick any input file.
2. Click Load Dataset.
3. Click Multiply.

For operands of up to 200 digits (for example im10) the page shows the full recursive working: each split, the values of z0, z1 and z2, and how they are combined, and it checks the result against the Karatsuba implementation. For larger operands it shows the product summary (digit count, first and last digits) and the running time. The step-by-step working switches to ordinary multiplication at 18 digits so that the recursion stays visible; the full-speed implementation works in blocks of 9 digits and switches below 32 blocks (288 digits).

### Benchmark

Choose an algorithm and a dataset and click Run Benchmark. It runs the algorithm, checks the answer independently, shows the time, and keeps a history table and chart. Each result is saved to `results/benchmark.csv`.

Note: the GUI saves `results/benchmark.csv` relative to the folder the program was started from. In Qt Creator the default is the build folder. To keep results in the project's `results` folder, open Projects > Run and set the Working directory to the project folder.


## 8. Running Without Qt Installed (Optional)

A runnable copy of the graphical application can be made with Qt's deployment tool. From the Qt terminal, in the project folder:

```
cmake -S . -B build-release -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build-release --target DAA_Project
mkdir deploy
copy build-release\DAA_Project.exe deploy\
windeployqt --release --no-translations deploy\DAA_Project.exe
```

The `deploy` folder can then be run on a computer without Qt by double-clicking `DAA_Project.exe`. Keep the `datasets` folder beside or above the `deploy` folder, or use the Browse button.


## 9. Algorithm Notes

### Closest pair of points

- The points are sorted by x and by y once.
- Each call splits the points into a left and a right half at the median x, solves both halves, and takes the smaller distance d.
- It then examines the strip of points within distance d of the dividing line, sorted by y, and compares each point with at most the next seven points.
- Subproblems of three points or fewer are solved by brute force.
- Running time: O(n log n). Duplicate points (cp06) give distance 0.

### Karatsuba multiplication

- Numbers are stored as blocks of 9 decimal digits.
- Each number is split into a low and a high half, and the product is built from three recursive multiplications:
  z0 = low(a) x low(b), z2 = high(a) x high(b), and z1 = (low(a) + high(a)) x (low(b) + high(b)) - z0 - z2.
- The result is z2 x B^(2m) + z1 x B^m + z0.
- When either number has 32 blocks or fewer, ordinary schoolbook multiplication is used.
- Running time: O(n^1.585).


## 10. Troubleshooting

| Problem | Fix |
|---|---|
| CMake cannot find Qt | Edit the `CMAKE_PREFIX_PATH` line in `CMakeLists.txt` to your Qt folder. |
| `g++` or `cmake` is not recognized | Use the Qt terminal from the Start menu, or open the project in Qt Creator. |
| The exe says a Qt DLL is missing | Run it from Qt Creator or the Qt terminal, or use the deploy folder from section 8. |
| "Could not open dataset" | Run the dataset generator first, and start the program from the project folder. |
| Times look very slow | Build in Release mode. |
| `results/benchmark.csv` has old rows | Delete the file before a fresh benchmark run; it is recreated automatically. |
