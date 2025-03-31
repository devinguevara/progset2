#include <iostream> 
#include <fstream>

#include <vector>
#include <cstdlib>
#include <ctime>


using namespace std;

//crossover point for strassen's algorithm
const int CUTOFF = 2;

//matrix multiplication function
void multiply(int** A, int** B, int** C, int dim){ 

    //multiply the matrices and save output in c 
    // iterate through every position in c and then like add the product that belongs there
    // you iterate up to dim again but either keep the column or the row constant bbgirl

    for (int i = 0; i < dim; i++){ 
        for (int j = 0; j < dim; j++){ 
            
            C[i][j] = 0; 

            for (int y = 0; y < dim; y++){ 
                C[i][j] += A[i][y] * B[y][j] ;// column of A corresponds to column of B
            }
        }
    }
}

//allocate memory for the matrix
int** almatrix(int dim){ 
    int** matrix = new int*[dim];
    
    for (int i = 0; i < dim; i++){ 

        matrix[i] = new int[dim];
    }
    
    return matrix;
}

//frees allocated memory
void dematrix(int** matrix, int dim){ 
    for (int i = 0; i < dim; i++){ 

        delete[] matrix[i];
    }
    delete[] matrix;
}

//prints matrix
void printMatrix(int** matrix, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

//adding two matrices
void add(int** A, int** B, int** C, int dim){ 
    for (int i = 0; i < dim; i++){ 
        for (int j = 0; j < dim; j++){ 
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

//subtracting two matrices
void subtract(int** A, int** B, int** C, int dim){ 
    for (int i = 0; i < dim; i++){ 
        for (int j = 0; j < dim; j++){ 
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

//strassen's algorithm to be implemented

//triangles in random graphs
//1024 vertices in graph
const int N  = 1024;
//edge inclusion probabilities
const std::vector<double> p_values = {0.01, 0.02, 0.03, 0.04, 0.05};
//matrix type
typedef std::vector<std::vector<int>> Matrix;

//generate random graph
Matrix generateRandomGraph(double p) {
    //intiailize matrix
    Matrix A(N, std::vector<int>(N, 0));
    srand(time(0));
    
    //loop over upper triangle and include edge with probability p
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if ((double)rand() / RAND_MAX < p) {
                A[i][j] = A[j][i] = 1;
            }
        }
    }
    return A;
}


//computing A^3
Matrix matrixPower3(const Matrix &A) {
    Matrix A2 = strassen(A, A); //strassen algo needs to be implemented
    return strassen(A2, A);
}

//counting triangles from A^3
int countTriangles(const Matrix &A3) {
    //trace = sum of diagonal of matrix
    int trace = 0;
    //summing diagonal to calculate trace
    for (int i = 0; i < N; ++i) {
        trace += A3[i][i];
    }
    //returning trace divided by 6 since we count each triangle 6 times
    return trace / 6;
}

int main(int argc, char* argv[]) {

    cout << "Hello, World!" << endl;

    if (argc != 4){ 
        cout << "Ur missing an argument hun" << endl; 

    }

    //first arg is a flag, second, is the dimension x of the square matrix you are multiplying, and last is the ASCII file 
    //int flag = atoi(argv[1]); 
    int dim = atoi(argv[2]);
    string ascii = argv[3]; 

    //read in the matrix values into the matrices using f stream!
    int** A = almatrix(dim); 
    int** B = almatrix(dim);
    //int** C = almatrix(dim);

    ifstream inFile(ascii);
    if (!inFile) { 
        cerr << "file didn't open for some reason" << endl; 
    }

    for (int i = 0; i < dim; i++){ 
        for (int j = 0; j < dim; j++){ 

            inFile >> A[i][j]; 

        }
    }

    for (int i = 0; i < dim; i++){ 
        for (int j = 0; j < dim; j++){ 

            inFile >> B[i][j]; 

        }
    }

    inFile.close();

    //multiply(A, B, C, dim);
    printMatrix(A, dim);
    dematrix(A, dim); 
    dematrix(B, dim);
    //dematrix(C, dim);

    //table for observed and expected triangles
    std::cout << "p, Observed Triangles, Expected Triangles" << std::endl;
    
    for (double p : p_values) {
        Matrix A = generateRandomGraph(p);
        Matrix A3 = matrixPower3(A);
        int observed = countTriangles(A3);
        double expected = pow(N, 3) * pow(p, 3);
        
        //output results
        std::cout << p << ", " << observed << ", " << expected << std::endl;
    }
    return 0;

}