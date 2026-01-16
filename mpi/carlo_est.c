#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = 100000;
    int local_count = 0;

    srand(time(NULL) + rank);

    for (int i = 0; i < N; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        if (x * x + y * y <= 1.0) {
            local_count++;
        }
    }

    int global_count;
    MPI_Reduce(
        &local_count,
        &global_count,
        1,
        MPI_INT,
        MPI_SUM,
        0,
        MPI_COMM_WORLD
    );

    if (rank == 0) {
        double pi_est = (double)global_count / (N * size) * 4;
        printf("Estimated Pi = %f\n", pi_est);
    }

    MPI_Finalize();
    return 0;
}
