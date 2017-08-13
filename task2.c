#include "mpi.h" 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(NULL,NULL); 
	int i,no_p, s, rank_p;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank_p);
    MPI_Comm_size(MPI_COMM_WORLD, &no_p);
	s=64;
    int array[s];
	double tmp, start_time, end_time,timer_overhead, communication_time,total_time;
	double iteration[100];
	int recvd, tag = 0;
	for(i=0; i<s; i++)
		{
			array[i] = rand() % 1000 + 1;
		}																																																																	
		int j[s];
		int j_count=0;
		while(j_count<no_p)
		{	
			j[j_count] = j_count;
			j_count++;
		}
	MPI_Status status;
    MPI_Request request;
    for (i=0; i < 100; i++) {
		if (rank_p == 0) {
			tmp = MPI_Wtime();
			start_time = MPI_Wtime();
		}
		MPI_Barrier( MPI_COMM_WORLD ) ;
		MPI_Bcast(&array,s, MPI_INT,rank_p, MPI_COMM_WORLD);
		for(j_count=0;j_count<no_p;j_count++)
		{
			printf("\n processor/node %d sending to processor/node %d", rank_p,j[j_count] );
			MPI_Barrier( MPI_COMM_WORLD ) ;
			printf("\n processor/node %d received from processor/node %d ",j[j_count], rank_p);
			MPI_Barrier( MPI_COMM_WORLD ) ;
		}
		if(rank_p == 0)
		{
			end_time = MPI_Wtime();
			timer_overhead = start_time - tmp;
			total_time = end_time - start_time - timer_overhead;
			iteration[i] = total_time;
		}
	}
	if(rank_p == 0)
	{
		double sum=0.0;
				for (i=0; i<100; i++)
				   {
					 sum = sum + iteration[i];
				   }
		communication_time = (sum / 100.0);
		printf("\n");
		printf("\n Output:");
		printf("\n Number of processor :: %d ",no_p);
		printf("\n Data Size :: %d",s);
		printf("\n Total avg time of 100 iterations :: %lf",communication_time);
	}
    MPI_Finalize();
    return 0;
}


