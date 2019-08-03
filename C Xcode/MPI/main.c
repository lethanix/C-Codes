//
//  main.c
//  MPI
//
//  Created by Louis Murguia on 8/2/19.
//  Copyright © 2019 Louis Murguia. All rights reserved.
//

#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
	int rank;
	int world;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world);
	printf("Hello: rank %d, world: %d\n",rank, world);
	MPI_Finalize();
}
