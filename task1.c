#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
	MPI_Init(NULL, NULL);
    int no_p, rank_p, n_length,i ;
	double tmp, start_time, end_time,overhead,total,avg_time;
    MPI_Comm_size(MPI_COMM_WORLD, &no_p);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank_p);
	char p_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Get_processor_name(p_name, &n_length);
    printf("Processor %s, rank %d out of %d Processors\n",p_name, rank_p, no_p);
    int S=64;
    int array[S];
    if(rank_p==0)
    {
        for(i = 0; i < S; ++i)
        {
			array[i] = rand() % 1000 + 1;
        }
    }
    int iteration=100;
    tmp = MPI_Wtime();
	start_time = MPI_Wtime();
    for(i=0;i<iteration;i++)
    {
        if(rank_p==0)
        {
			MPI_Send(&array, S, MPI_INT, (rank_p+1)%no_p, i, MPI_COMM_WORLD) ;
			MPI_Recv(&array, S, MPI_INT,  (rank_p-1)%no_p, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE) ;
        }
        else
        {
           MPI_Recv(&array, S, MPI_INT,  (rank_p-1)%no_p, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE) ;
           MPI_Send(&array, S, MPI_INT, (rank_p+1)%no_p, i, MPI_COMM_WORLD) ;
        }
    }
    if(rank_p==0)
    {
        end_time = MPI_Wtime();
        overhead = start_time - tmp;
        total = end_time - start_time - overhead;
        avg_time = total / iteration;
        printf("\n\nAverage time for 1 iteration out of %d iterations = %lf",iteration, avg_time);
    }
    MPI_Finalize();
}