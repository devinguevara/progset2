#include <iostream> 
#include <fstream>


using namespace std;
int** almatrix(int dim); 
void dematrix(int** matrix, int dim);
void addSubtractMatrix(int** A, int** B, int** result, int dim, int sign = 1) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            result[i][j] = A[i][j] + sign * B[i][j];
        }
    }
}
void strassen(int** A, int** B, int** C, int dim) { 

    if (dim == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newDim = dim / 2;
    int** A11 = almatrix(newDim);
    int** A12 = almatrix(newDim);
    int** A21 = almatrix(newDim);
    int** A22 = almatrix(newDim);
    int** B11 = almatrix(newDim);
    int** B12 = almatrix(newDim);
    int** B21 = almatrix(newDim);
    int** B22 = almatrix(newDim);

    for (int i = 0; i < newDim; i++) {
        for (int j = 0; j < newDim; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newDim];
            A21[i][j] = A[i + newDim][j];
            A22[i][j] = A[i + newDim][j + newDim];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newDim];
            B21[i][j] = B[i + newDim][j];
            B22[i][j] = B[i + newDim][j + newDim];
        }
    }

    int** M1 = almatrix(newDim);
    int** M2 = almatrix(newDim);
    int** M3 = almatrix(newDim);
    int** M4 = almatrix(newDim);
    int** M5 = almatrix(newDim);
    int** M6 = almatrix(newDim);
    int** M7 = almatrix(newDim);
    
    int** temp1 = almatrix(newDim);
    int** temp2 = almatrix(newDim);
    
    addSubtractMatrix(A11, A22, temp1, newDim);
    addSubtractMatrix(B11, B22, temp2, newDim);
    strassen(temp1, temp2, M1, newDim);
    
    addSubtractMatrix(A21, A22, temp1, newDim);
    strassen(temp1, B11, M2, newDim);
    
    addSubtractMatrix(B12, B22, temp1, newDim, -1);
    strassen(A11, temp1, M3, newDim);
    
    addSubtractMatrix(B21, B11, temp1, newDim, -1);
    strassen(A22, temp1, M4, newDim);
    
    addSubtractMatrix(A11, A12, temp1, newDim);
    strassen(temp1, B22, M5, newDim);
    
    addSubtractMatrix(A21, A11, temp1, newDim, -1);
    addSubtractMatrix(B11, B12, temp2, newDim);
    strassen(temp1, temp2, M6, newDim);
    
    addSubtractMatrix(A12, A22, temp1, newDim, -1);
    addSubtractMatrix(B21, B22, temp2, newDim);
    strassen(temp1, temp2, M7, newDim);
    
    int** C11 = almatrix(newDim);
    int** C12 = almatrix(newDim);
    int** C21 = almatrix(newDim);
    int** C22 = almatrix(newDim);
    
    addSubtractMatrix(M1, M4, temp1, newDim);
    addSubtractMatrix(temp1, M7, temp2, newDim, -1);
    addSubtractMatrix(temp2, M5, C11, newDim);
    
    addSubtractMatrix(M3, M5, C12, newDim);
    addSubtractMatrix(M2, M4, C21, newDim);
    
    addSubtractMatrix(M1, M3, temp1, newDim);
    addSubtractMatrix(temp1, M6, temp2, newDim, -1);
    addSubtractMatrix(temp2, M2, C22, newDim);
    
    for (int i = 0; i < newDim; i++) {
        for (int j = 0; j < newDim; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newDim] = C12[i][j];
            C[i + newDim][j] = C21[i][j];
            C[i + newDim][j + newDim] = C22[i][j];
        }
    }
    
    dematrix(A11, newDim); dematrix(A12, newDim);
    dematrix(A21, newDim); dematrix(A22, newDim);
    dematrix(B11, newDim);  dematrix(B12, newDim);
    dematrix(B21, newDim);  dematrix(B22, newDim);
    dematrix(C11, newDim); dematrix(C12, newDim);
    dematrix(C21, newDim); dematrix(C22, newDim);
    dematrix(M1, newDim); dematrix(M2, newDim);
    dematrix(M3, newDim); dematrix(M4, newDim);
    dematrix(M5, newDim); dematrix(M6, newDim);
    dematrix(M7, newDim);
    dematrix(temp1, newDim); dematrix(temp2, newDim);
}


void multiply(int** A, int** B, int** C, int dim){ 
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

    if (argc < 4){ 
        cout << "Ur missing an argument hun" << endl; 
        return 1; 

    }

    //first arg is a flag, second, is the dimension x of the square matrix you are multiplying, and last is the ASCII file 
    //int flag = atoi(argv[1]); 
    int dim = atoi(argv[2]);
    string ascii = argv[3]; 

    //read in the matrix values into the matrices using f stream!
    int** A = almatrix(dim); 
    int** B = almatrix(dim);
    int** C = almatrix(dim);

    ifstream inFile(ascii);
    if (!inFile) { 
        cerr << "file didn't open for some reason" << endl; 
        return 1; 
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

    multiply(A, B, C, dim);

    printMatrix(A, dim);
    printMatrix(B, dim);
    printMatrix(C, dim);

    dematrix(A, dim); 
    dematrix(B, dim);
    dematrix(C, dim);

    return 0;

}