#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100000000L // 100 million elements

int main() {
    int num_threads;
    printf("Enter number of threads: ");
    scanf("%d", &num_threads);

    if (num_threads < 1 || num_threads > 32) {
        printf("Please enter a value between 1 and 32.\n");
        return 1;
    }

    omp_set_num_threads(num_threads);

    double *A, *B, *C;
    A = (double *)malloc(N * sizeof(double));
    B = (double *)malloc(N * sizeof(double));
    C = (double *)malloc(N * sizeof(double));

    if (A == NULL || B == NULL || C == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Initializing vectors of size %ld...\n", N);
    for (long i = 0; i < N; i++) {
        A[i] = 1.0;
        B[i] = 2.0;
        C[i] = 0.0;
    }

    double start_time = omp_get_wtime();

    // Element-wise Vector Multiplication with OpenMP
    #pragma omp parallel for
    for (long i = 0; i < N; i++) {
        C[i] = A[i] * B[i];
    }

    double end_time = omp_get_wtime();

    printf("\nOpenMP Vector Multiplication Completed\n");
    printf("Vector Size = %ld\n", N);
    printf("Number of Threads Used = %d\n", num_threads);
    printf("Execution Time = %f seconds\n", end_time - start_time);
    printf("Verification C[0] = %.2f\n", C[0]);

    free(A);
    free(B);
    free(C);

    return 0;
}
