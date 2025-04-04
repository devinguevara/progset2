import numpy as np
import sys
import time 

def matrix_mult(A, B):
    """Performs naive matrix multiplication of two square matrices A and B."""
    n = len(A)
    product = np.zeros((n, n), dtype=int)
    for i in range(n):
        for j in range(n):
            for k in range(n):
                product[i, j] += A[i, k] * B[k, j]
    return product

def generate_random_matrix(n):
    """Generates an n x n matrix with entries randomly selected from value_set."""
    return np.random.int(0, 2, size=(n, n))

def add_subtract_matrix(A, B, operation=1):
    """ Adds or subtracts two matrices using NumPy """
    return np.add(A, operation * B)

# def strassen(A, B):
#     dim = A.shape[0]
    
#     #if the dimension is 1 or is under the cutoff then just do naive implementation 
#     if dim == 1:
#         return matrix_mult(A, B)
    
#     newDim = dim // 2
    
#     #split up matrices 
#     a, b, c, d = A[:newDim, :newDim], A[:newDim, newDim:], A[newDim:, :newDim], A[newDim:, newDim:]
#     e, f, g, h = B[:newDim, :newDim], B[:newDim, newDim:], B[newDim:, :newDim], B[newDim:, newDim:]

#     #do 7 multiplications 
#     p1 = matrix_mult(a, add_subtract_matrix(f, h, -1))
#     p2 = matrix_mult(add_subtract_matrix(a, b), h)
#     p3 = matrix_mult(add_subtract_matrix(c, d), e)
#     p4 = matrix_mult(d, add_subtract_matrix(g, e, -1))
#     p5 = matrix_mult(add_subtract_matrix(a, d), add_subtract_matrix(e, h))
#     p6 = matrix_mult(add_subtract_matrix(b, d, -1), add_subtract_matrix(g, h))
#     p7 = matrix_mult(add_subtract_matrix(c, a, -1), add_subtract_matrix(e, f))
    
#     #AE + BG = -p2 + p4 + p5 + p6
#     C11 = add_subtract_matrix(add_subtract_matrix(p4, p2, -1), add_subtract_matrix(p6, p5))

#     #AF + BH = p1 + p2
#     C12 = add_subtract_matrix(p1, p2)

#     #CE + DG = p3 + p4
#     C21 = add_subtract_matrix(p3, p4)

#     #CF + DH = p1 - p3 + p5 + p7
#     C22 = add_subtract_matrix(add_subtract_matrix(p1, p3, -1), add_subtract_matrix(p5, p7))
    
#     #construct result matrix using numpy
#     C = np.block([[C11, C12], [C21, C22]])

    
#     return C

# def next_power_of_2(n):
#     """ Returns the next power of 2 greater than or equal to n """
#     return 2**int(np.ceil(np.log2(n)))

# def strassen_pad(A, B):

#     # Don't padd if its a power of 2 
#     # don't pad to the nearest power of 2 
#     # you should only pad 17 to 18

#     # dim = A.shape[0]
#     # newDim = next_power_of_2(dim)
  
#     # A_padded = np.pad(A, ((0, newDim - dim), (0, newDim - dim)), mode='constant')
#     # B_padded = np.pad(B, ((0, newDim - dim), (0, newDim - dim)), mode='constant')
   
#     # C_padded = strassen(A_padded, B_padded)
    
#     # return C_padded[:dim, :dim]
#     dim = A.shape[0]
   
#     if (dim % 2 == 1): 

#         newDim = next_power_of_2(dim)
    
#         A_padded = np.pad(A, ((0, newDim - dim), (0, newDim - dim)), mode='constant')
#         B_padded = np.pad(B, ((0, newDim - dim), (0, newDim - dim)), mode='constant')
    
#         C_padded = strassen(A_padded, B_padded)
#         return C_padded[:dim, :dim]
#     else: 
#         return strassen(A, B)
    


def pad_matrix(A):
    rows, cols = A.shape
    # Only pad if not even
    if rows % 2 == 1:
        A = np.pad(A, ((0, 1), (0, 0)), mode='constant')
    if cols % 2 == 1:
        A = np.pad(A, ((0, 0), (0, 1)), mode='constant')
    return A

def remove_padding(A, original_shape):
    return A[:original_shape[0], :original_shape[1]]

def strassen(A, B, n_0):
    dim = A.shape[0]
    
    if dim == 1 or dim <= n_0:
        return matrix_mult(A, B)
    
    shape_A = A.shape
    shape_B = B.shape

    A = pad_matrix(A)
    B = pad_matrix(B)
    n = A.shape[0]

    #make sure ur putting the right n in there for example 
    newDim = n // 2
    
    #split up matrices 
    a, b, c, d = A[:newDim, :newDim], A[:newDim, newDim:], A[newDim:, :newDim], A[newDim:, newDim:]
    e, f, g, h = B[:newDim, :newDim], B[:newDim, newDim:], B[newDim:, :newDim], B[newDim:, newDim:]

    #do 7 multiplications 
    p1 = strassen(a, f - h, n_0)
    p2 = strassen(a + b, h, n_0)
    p3 = strassen(c + d, e, n_0)
    p4 = strassen(d, g - e, n_0)
    p5 = strassen(a + d, e + h, n_0)
    p6 = strassen(b - d, g + h, n_0)
    p7 = strassen(a - c, e + f, n_0)

    #AE + BG = -p2 + p4 + p5 + p6
    C11 = p4 + p5 + p6 - p2

    #AF + BH = p1 + p2
    C12 = p1 + p2

    #CE + DG = p3 + p4
    C21 = p3 + p4

    #CF + DH = p1 - p3 + p5 + p7
    C22 = p1 + p5 + p7 - p3
    
    #construct result matrix using numpy
    C = np.block([[C11, C12], [C21, C22]])

    Z = remove_padding(C, (shape_A[0], shape_B[1]))
    return Z

def main():
    if len(sys.argv) < 4: 
        print("Incorrect Number of Arguments")

    flag = int(sys.argv[1])
    d = int(sys.argv[2])
    filename = sys.argv[3]

    #reconstruct the matrices 
    with open(filename, 'r') as file:
        data = list(map(int, file.read().splitlines()))

    A = np.array(data[:d**2]).reshape(d, d)
    B = np.array(data[d**2:]).reshape(d, d)

    #multiply them
    C = strassen(A, B, 2)

    #return result 
    for i in range(d): 
        print(C[i][i])


if __name__ == "__main__":
    main()