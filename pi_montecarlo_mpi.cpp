#include <iostream>
#include <mpi/mpi.h>
#include <time.h>
#include <math.h>
#include <iomanip>

void get_in(int argc, char *argv[], int mRank, long *total);
long toss (long numToss, int mRank);

using namespace std;

int main(int argc, char *argv[])
{
    int mRank, numProcess;
    long totalTosses, numProcessTosses, processNumCircle, totalNumCircle;
    double start, finish, locElapsed, elapsed, piEstimate;
    double myPI = 3.141592653589793238462643;

    MPI_Init(&argc, &argv); //Initializes MPI environment
    MPI_Comm_size(MPI_COMM_WORLD, &numProcess); // returns the size of group associated with communicator
    MPI_Comm_rank(MPI_COMM_WORLD, &mRank); // Determines the rank of the calling process in the communicator
                                           // Determines the amount of concurrency available for a specific library or program
    get_in(argc, argv, mRank, &totalTosses);

    powerOfTwo

    cout << "numProcess: " << numProcess << endl;

    numProcessTosses = totalTosses / numProcess;

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();
    processNumCircle = toss(numProcessTosses, mRank);
    finish = MPI_Wtime();
    elapsed = finish - start;
    // Reduces all values on all processes within a group
    MPI_Reduce(&locElapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&processNumCircle, &totalNumCircle, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (mRank == 0) {
        piEstimate = (4*totalNumCircle) / (double)totalTosses;
        cout << "Elapsed time: " << elapsed << endl;
        cout << "Pi approximated: " << fixed << setprecision(16) << piEstimate << ". Error: " << fabs(piEstimate - myPI) << endl;
    }

    MPI_Finalize();

    return 0;
}

void get_in(int argc, char *argv[], int mRank, long *total) {
    if (mRank == 0) {
        if (argc != 2) {
            cout << "Erro! Usage: mpirun -np <N> " << argv[0] << " <number of tosses> \n";
            *total = 0;
        }
        else *total = atoi(argv[1]);
    }
    // Broadcasts value of total to each process
    MPI_Bcast(total, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    if (*total == 0) {
        MPI_Finalize();
        exit(-1);
    }
}

long toss (long procTosses, int mRank) {
    long toss, numberCircle = 0;
    double x, y;
    unsigned int seed = (unsigned) time(NULL);
    srand(seed + mRank);
    for (toss = 0; toss < procTosses; toss++) {
        x = rand_r(&seed) / (double)RAND_MAX;
        y = rand_r(&seed) / (double)RAND_MAX;
        if ((x*x+y*y) <= 1.0) numberCircle++;
    }
    return numberCircle;
}
