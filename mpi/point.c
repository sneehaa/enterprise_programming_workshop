#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    MPI_Init(&argc, &argv);
    int rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        char msg[] = "Hello Process 1";
        MPI_Send(msg, sizeof(msg), MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    } else if(rank == 1){
        char recv_msg[20];
        MPI_Recv(recv_msg, 20, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received: %s\n", recv_msg);
    }
    MPI_Finalize();
    return 0;
}