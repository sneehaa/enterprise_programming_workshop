#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = 8;
    int *arr = NULL;

    if (rank == 0) {
        arr = (int *)malloc(N * sizeof(int));
        int temp[8] = {12, 5, 20, 7, 15, 3, 18, 1};

        for (int i = 0; i < N; i++) {
            arr[i] = temp[i];
        }
    }

    int n_local = N / size;
    int *local_arr = (int *)malloc(n_local * sizeof(int));

    MPI_Scatter(
        arr,
        n_local,
        MPI_INT,
        local_arr,
        n_local,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );

    int local_max = local_arr[0];
    for (int i = 1; i < n_local; i++) {
        if (local_arr[i] > local_max) {
            local_max = local_arr[i];
        }
    }

    int global_max;
    MPI_Reduce(
        &local_max,
        &global_max,
        1,
        MPI_INT,
        MPI_MAX,
        0,
        MPI_COMM_WORLD
    );

    if (rank == 0) {
        printf("Global Maximum: %d\n", global_max);
    }

    free(local_arr);
    if (rank == 0) {
        free(arr);
    }

    MPI_Finalize();
    return 0;
}
