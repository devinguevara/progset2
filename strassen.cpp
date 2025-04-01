#include <iostream> 
#include <fstream>


using namespace std;
int** almatrix(int dim); 
void dematrix(int** matrix, int dim);
void printMatrix(int** matrix, int dim);
void multiply(int** A, int** B, int** C, int dim); 

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

    //construct 8 submatrices 
    int newDim = dim / 2;
    int** a = almatrix(newDim); //a
    int** b = almatrix(newDim); //b
    int** c = almatrix(newDim); //c
    int** d = almatrix(newDim); //d
    int** e = almatrix(newDim); //e
    int** f = almatrix(newDim); //f 
    int** g = almatrix(newDim); //g 
    int** h = almatrix(newDim); //h 

    for (int i = 0; i < newDim; i++) {
        for (int j = 0; j < newDim; j++) {
            a[i][j] = A[i][j];
            b[i][j] = A[i][j + newDim];
            c[i][j] = A[i + newDim][j];
            d[i][j] = A[i + newDim][j + newDim];
            e[i][j] = B[i][j];
            f[i][j] = B[i][j + newDim];
            g[i][j] = B[i + newDim][j];
            h[i][j] = B[i + newDim][j + newDim];
        }
    }


    /* THE SEVEN MULTIPLICATIONS */
    int** p1 = almatrix(newDim);
    int** p2 = almatrix(newDim);
    int** p3 = almatrix(newDim);
    int** p4 = almatrix(newDim);
    int** p5 = almatrix(newDim);
    int** p6 = almatrix(newDim);
    int** p7 = almatrix(newDim);
    
    int** temp1 = almatrix(newDim);
    int** temp2 = almatrix(newDim);

    // for p1 = A(F-H), subtract h from f and store in temp 1
    addSubtractMatrix(f, h, temp1, newDim, -1);  
    strassen(A, temp1, p1, newDim); 

    //for p2 (A +b)h, add a and b and store in temp1
    addSubtractMatrix(a, b, temp1, newDim);
    strassen(temp1, h, p2, newDim);

    //for p3 = (c + d)e, add c and d and store in temp1
    addSubtractMatrix(c, d, temp1, newDim); 
    strassen(temp1, e, p3, newDim); 

    //for p4 = d(g - e), add c and e and store in temp1
    addSubtractMatrix(g, e, temp1, newDim, -1); 
    strassen(d, temp1, p4, newDim); 

    //for p5 (a + d)(e + h), store sums in temp1 and temp2
    addSubtractMatrix(a, d, temp1, newDim); 
    addSubtractMatrix(e, h, temp2, newDim);
    strassen(temp1, temp2, p5, newDim); 

    //for p6= (b - d)(g + h)
    addSubtractMatrix(b, d, temp1, newDim, -1); 
    addSubtractMatrix(g, h, temp2, newDim);
    strassen(temp1, temp2, p6, newDim); 

    //for p7 = (c - a)(e + f)
    addSubtractMatrix(c, a, temp1, newDim, -1); 
    addSubtractMatrix(e, f, temp2, newDim);
    strassen(temp1, temp2, p6, newDim); 
    

    /*CALCULATING THE RESULTING MATRIX*/
    int** C11 = almatrix(newDim);
    int** C12 = almatrix(newDim);
    int** C21 = almatrix(newDim);
    int** C22 = almatrix(newDim);

    // AE + BG = -p2 + p4 + p5 + p6
    addSubtractMatrix(p4, p2, temp1, newDim, -1);
    addSubtractMatrix(p5, p6, temp2, newDim); 
    addSubtractMatrix(temp1, temp2, C11, newDim); 

    // AF + BH = p1 + p2
    addSubtractMatrix(p1, p2, C12, newDim); 

    // CE + DG = p3 + p4
    addSubtractMatrix(p3, p4, C21, newDim); 

    // CF + DH = p1 - p3 + p5 + p7
    addSubtractMatrix(p1, p3, temp1, newDim, -1);
    addSubtractMatrix(p5, p7, temp2, newDim); 
    addSubtractMatrix(temp1, temp2, C22, newDim); 

    
    for (int i = 0; i < newDim; i++) {
        for (int j = 0; j < newDim; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newDim] = C12[i][j];
            C[i + newDim][j] = C21[i][j];
            C[i + newDim][j + newDim] = C22[i][j];
        }
    }
    
    dematrix(a, newDim); dematrix(b, newDim);
    dematrix(c, newDim); dematrix(d, newDim);
    dematrix(e, newDim);  dematrix(f, newDim);
    dematrix(g, newDim);  dematrix(h, newDim);
    dematrix(C11, newDim); dematrix(C12, newDim);
    dematrix(C21, newDim); dematrix(C22, newDim);
    dematrix(p1, newDim); dematrix(p2, newDim);
    dematrix(p3, newDim); dematrix(p4, newDim);
    dematrix(p5, newDim); dematrix(p6, newDim);
    dematrix(p7, newDim);
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

    strassen(A, B, C, dim);

    for (int i = 0; i < dim; i++){ 
        cout << C[i][i] << endl;
    }
  
    dematrix(A, dim); 
    dematrix(B, dim);
    dematrix(C, dim);

    return 0;

}