#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000L // 100 million elements

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main() {
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

    double start = get_time();

    // Element-wise Vector Multiplication
    for (long i = 0; i < N; i++) {
        C[i] = A[i] * B[i];
    }

    double end = get_time();

    printf("\nSequential Vector Multiplication Completed\n");
    printf("Vector Size = %ld\n", N);
    printf("Execution Time = %f seconds\n", end - start);
    printf("Verification C[0] = %.2f\n", C[0]);

    free(A);
    free(B);
    free(C);

    return 0;
}
