#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

const int MAX = 100;

int main()
{
    char greeting [MAX];
    int number_process;
    int rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &number_process);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank != 0) {
        sprintf(greeting, "Greetings from process %d of %d!", rank, number_process);
        MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0,0, MPI_COMM_WORLD);
    } else {
        printf("Greetings from process %d of %d!\n", rank, number_process);
        for (int i = 1; i < number_process; i++) {
            MPI_Recv(greeting, MAX, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Teste %s\n", greeting);
        }
    }

    MPI_Finalize();
    return 0;
}
