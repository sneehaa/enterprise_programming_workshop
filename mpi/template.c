#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int my_rank; // rank of process
    int p;       // number of processes

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    printf("Hello from process %d out of %d processes\n", my_rank, p);

    MPI_Finalize();
    return 0;
}
