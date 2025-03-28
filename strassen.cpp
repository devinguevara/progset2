#include <iostream> 
#include <fstream>


using namespace std;

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

int** almatrix(int dim){ 
    int** matrix = new int*[dim];
    
    for (int i = 0; i < dim; i++){ 

        matrix[i] = new int[dim];
    }
    
    return matrix;
}

void dematrix(int** matrix, int dim){ 
    for (int i = 0; i < dim; i++){ 

        delete[] matrix[i];
    }
    delete[] matrix;
}

void printMatrix(int** matrix, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
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

    return 0;

}