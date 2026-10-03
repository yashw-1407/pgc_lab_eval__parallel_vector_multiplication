# Parallel Vector Multiplication using OpenMP

## 🎯 Checkpoint 1: Problem Definition & Design

### Problem Definition
In high-performance computing, mathematical operations on large datasets are often the bottleneck for performance. In this mini-project, we are tasked with performing **Parallel Vector Multiplication**. 

Given two very large arrays (vectors) `A` and `B`, each containing 100 million floating-point numbers, the objective is to multiply them element-by-element to produce a third vector `C`. The mathematical representation is:
```text
C[i] = A[i] * B[i]  (for i = 0 to 100,000,000)
```
This is an $O(N)$ operation. Processing such a massive amount of data sequentially on a single CPU core takes a noticeable amount of time. Our goal is to use parallel computing to speed up this computation.

### Sequential Algorithm
The sequential approach uses a standard `for` loop that iterates through every single element one-by-one on a single CPU core. 
* First, memory is allocated for the three vectors using `malloc`.
* The vectors `A` and `B` are initialized with dummy values (`1.0` and `2.0`).
* A loop runs from `0` to `N-1`, computing `C[i] = A[i] * B[i]`.
* Because there is only one worker (the main thread), the CPU must perform all 100 million multiplications sequentially, one after the other.

### Parallel Design
For the parallel design, we use **OpenMP (Open Multi-Processing)**, which is an API that supports multi-platform shared-memory multiprocessing programming in C.
* We apply the `#pragma omp parallel for` directive just above the main multiplication loop. 
* **What this does:** This directive instructs the compiler to automatically divide the 100 million iterations into equal chunks. 
* Instead of one thread doing 100 million operations, if we use 4 threads, OpenMP will automatically assign 25 million operations to Thread 1, 25 million to Thread 2, and so on.
* Because all threads share the same memory space (Shared Memory Model), they can all read from vectors `A` and `B` and write to vector `C` simultaneously without needing to pass messages over a network.

---

## 👥 Team Members
* [Add Team Member 1]
* [Add Team Member 2]
* [Add Team Member 3]

---

## 🛠️ Prerequisites & Environment Setup
To reproduce this experiment, the following environment was used:
* **Operating System**: Windows 10/11 running **WSL2 (Windows Subsystem for Linux)** with an **Ubuntu** distribution.
* **Compiler**: **GCC (GNU Compiler Collection)**, installed via `sudo apt install build-essential`.
* **Parallel Library**: **OpenMP** (Native support included with GCC).
* **Graphing Tools**: **Python 3** with `pandas` and `matplotlib` libraries to generate the performance plots.

---

## 📂 Project Structure
* `src/` - Contains the raw C source code (`vector_mult_sequential.c` and `vector_mult_openmp.c`).
* `data/` - Contains a text file explaining our in-memory data generation strategy (avoiding file I/O overhead).
* `results/` - Contains our raw execution times stored in a `.csv` file.
* `graphs/` - Python script used to plot data, alongside the generated output images.
* `images/` - Screenshots of our programs executing in the terminal.
* `report/` - PDF version of this report.
* `presentation/` - PowerPoint presentation for the lab evaluation viva.

---

## 🚀 Checkpoint 2: Working Parallel Implementation

### 1. Sequential Baseline (Single Thread)
This program establishes our baseline execution time. We need to know how long the program takes on a single core so we can calculate how much faster the parallel version is.

```bash
# Navigate to the source folder
cd src

# Compile the C code into an executable. 
# The -O2 flag enables standard compiler optimizations for better performance.
gcc -O2 vector_mult_sequential.c -o vector_mult_sequential

# Run the compiled executable program
./vector_mult_sequential
```

**Terminal Output Screenshot:**
![Sequential Output](images/seq_output.png)

### 2. OpenMP Parallel Implementation (Multiple Threads)
This program uses the `#pragma omp parallel for` directive to split the workload. The program is interactive and will prompt the user to input the desired number of threads.

```bash
# Compile the code with the -fopenmp flag. 
# This flag is absolutely crucial as it enables OpenMP directives and links the OpenMP runtime library.
gcc -O2 -fopenmp vector_mult_openmp.c -o vector_mult_openmp

# Run the compiled program
./vector_mult_openmp
```

**Terminal Output Screenshots:**
![OpenMP Output 1](images/omp_output_1.png)
![OpenMP Output 2](images/omp_output_2.png)

---

## 📊 Checkpoint 3 & 4: Execution Results, Graphs, and Analysis

To thoroughly test our parallel implementation, we ran the OpenMP version multiple times, increasing the number of threads for each execution (1, 2, 4, 6, 8, and 16 threads).

### Mathematical Formulas Used
* **Speedup ($S$)**: Tells us how many times faster the parallel program is compared to the sequential program. 
  * $Speedup = \frac{Sequential\_Execution\_Time}{Parallel\_Execution\_Time}$
* **Efficiency ($E$)**: Tells us how effectively the available threads are contributing to the speedup. 
  * $Efficiency = \frac{Speedup}{Number\_of\_Threads} \times 100\%$

### Results Table
| Threads | Execution Time (seconds) | Speedup (Seq_Time / Par_Time) | Efficiency |
| :---: | :---: | :---: | :---: |
| 1 (Sequential) | 0.692445 | 1.00x | 100.0% |
| 2 | 0.246625 | 2.80x | 140.3% (Hyperthreading anomaly) |
| 4 | 0.126643 | 5.46x | 136.6% |
| 6 | 0.118263 | 5.85x | 97.5% |
| 8 | 0.137638 | 5.03x | 62.8% |
| 16 | 0.133875 | 5.17x | 32.3% |

### Performance Graphs

Here are the visual representations of our performance (generated automatically using Python's `matplotlib` library):

**1. Execution Time vs Threads**  
This graph shows the raw time taken to multiply the 100 million elements. As we add more threads, the execution time drops rapidly, but flattens out after 4 to 6 threads.
![Execution Time](graphs/execution_time.png)

**2. Speedup vs Threads**  
This graph visualizes the speedup multiplier. A perfectly linear speedup would mean 4 threads is exactly 4x faster. Our application scales very well up to 6 threads, reaching a maximum speedup of **~5.85x**.
![Speedup](graphs/speedup.png)

**3. Efficiency vs Threads**  
This graph shows how efficiently the CPU cores are being utilized. As we add more threads (especially beyond 6), the efficiency drops steeply. This indicates that adding more threads eventually leads to diminishing returns.
![Efficiency](graphs/efficiency.png)

---

## 💡 Checkpoint 5: Final Demonstration & Viva Prep

Based on the data collected during our experiment, we can draw several critical conclusions about parallel computing and OpenMP:

1. **Parallelism is Highly Effective:** 
   By simply adding the `#pragma omp parallel for` directive, we were able to distribute the workload across multiple CPU cores, achieving a massive reduction in execution time (from ~0.69 seconds down to ~0.11 seconds).

2. **The Law of Diminishing Returns (Amdahl's Law):** 
   We observed that increasing the thread count from 1 to 4 resulted in massive performance gains. However, increasing the thread count from 8 to 16 provided zero additional benefit, and actually made the program slightly slower in some instances. 

3. **Why doesn't 16 threads give a 16x speedup?** 
   There are two primary reasons for this performance plateau:
   * **Memory Bandwidth Bottleneck:** Vector multiplication (`C[i] = A[i] * B[i]`) is a computationally simple operation, but it requires reading massive amounts of data from the RAM. Very quickly, the CPU cores calculate the math faster than the RAM can physically supply the numbers. At this point, the program becomes *Memory Bound*, meaning no matter how many extra CPU threads you add, they will just sit idle waiting for RAM.
   * **Thread Management Overhead:** OpenMP has to do work behind the scenes to create, schedule, and synchronize threads. When you request 16 threads for a task that finishes in 0.1 seconds, the time it takes the Operating System to manage those 16 threads starts to outweigh the time saved by parallelizing the math.
