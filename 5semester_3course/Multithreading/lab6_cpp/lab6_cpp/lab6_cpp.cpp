// C:\Users\roman\Media\Roman\IKNI\PP-34\Multithreading\lab6_cpp\x64\Debug\lab6_cpp.exe
#include <mpi.h>
#include <iostream>
#include <vector>
#include <random>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int ROWS = 80;
    const int COLS = 120;
    const int block_rows = 40;
    const int block_cols = 30;

    // Local block of the matrix
    std::vector<double> A_block(block_rows * block_cols);
    std::vector<double> x_block(block_cols);
    std::vector<double> y_block(block_rows, 0.0);

    // setup random
    std::random_device rd;  // for generating a "seed"
    std::mt19937 gen(rd()); // Mersenne Twister generator
    std::uniform_int_distribution<> dist(0, 10); // numbers from 0 to 10

    // Initialization
    for (int i = 0; i < block_rows * block_cols; i++)
        A_block[i] = dist(gen);
    for (int i = 0; i < block_cols; i++)
        x_block[i] = dist(gen);

    // Multiply the local block by the subvector
    for (int i = 0; i < block_rows; i++) {
        for (int j = 0; j < block_cols; j++) {
            y_block[i] += A_block[i * block_cols + j] * x_block[j];
        }
    }

    // Gather results on process 0
    std::vector<double> y;
    if (rank == 0) y.resize(ROWS, 0.0);

    MPI_Reduce(y_block.data(), y.data(), block_rows, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::cout << "Result vector y: ";
        for (double val : y)
            if (val) {
                std::cout << val << " ";
            }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}
