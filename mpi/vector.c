#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = 8;
    int *A = NULL, *B = NULL, *C = NULL;
    if(rank == 0){
        A = (int*)malloc(N*sizeof(int));
        B = (int*)malloc(N*sizeof(int));
        C = (int*)malloc(N*sizeof(int));
        for(int i=0;i<N;i++){ A[i]=i; B[i]=i*2; }
    }

    int n_local = N/size;
    int *local_A = (int*)malloc(n_local*sizeof(int));
    int *local_B = (int*)malloc(n_local*sizeof(int));
    int *local_C = (int*)malloc(n_local*sizeof(int));

    MPI_Scatter(A, n_local, MPI_INT, local_A, n_local, MPI_INT, 0,
        MPI_COMM_WORLD);
    MPI_Scatter(B, n_local, MPI_INT, local_B, n_local, MPI_INT, 0,
        MPI_COMM_WORLD);

    for(int i=0;i<n_local;i++) local_C[i] = local_A[i] + local_B[i];

    MPI_Gather(local_C, n_local, MPI_INT, C, n_local, MPI_INT, 0,
        MPI_COMM_WORLD);
        
    if(rank==0){
        printf("Result C: ");
        for(int i=0;i<N;i++) printf("%d ", C[i]);
        printf("\n");
    }
    
    free(local_A); free(local_B); free(local_C);
    if(rank==0){ free(A); free(B); free(C); }
    
    MPI_Finalize();
    return 0;
}