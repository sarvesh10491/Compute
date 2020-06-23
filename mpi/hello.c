#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) 
{
    int num_procs, my_id, len;
    char hostname[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);

    /* To get current process ID, total no. of processes started and hostname process is running on. */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Get_processor_name(hostname, &len);

    printf("Hello world! I'm process %i out of %i processes running on %s\n", my_id, num_procs, hostname);
        
    MPI_Finalize();

    return 0;
}