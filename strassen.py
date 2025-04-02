import numpy as np

def matrix_mult(A, B):
    """Performs naive matrix multiplication of two square matrices A and B."""
    n = len(A)
    product = np.zeros((n, n), dtype=int)
    for i in range(n):
        for j in range(n):
            for k in range(n):
                product[i, j] += A[i, k] * B[k, j]
    return product

def strassen(A, B, n0):
    """Performs Strassen's matrix multiplication with a crossover point n0."""
    n = len(A)
    if n <= n0:
        return matrix_mult(A, B)
    
    # Ensure n is even by padding if necessary
    padded = False
    if n % 2 != 0:
        A = np.pad(A, ((0, 1), (0, 1)), mode='constant')
        B = np.pad(B, ((0, 1), (0, 1)), mode='constant')
        n += 1
        padded = True
    
    mid = n // 2
    A11, A12, A21, A22 = A[:mid, :mid], A[:mid, mid:], A[mid:, :mid], A[mid:, mid:]
    B11, B12, B21, B22 = B[:mid, :mid], B[:mid, mid:], B[mid:, :mid], B[mid:, mid:]
    
    P1 = strassen(A11, B12 - B22, n0)
    P2 = strassen(A11 + A12, B22, n0)
    P3 = strassen(A21 + A22, B11, n0)
    P4 = strassen(A22, B21 - B11, n0)
    P5 = strassen(A11 + A22, B11 + B22, n0)
    P6 = strassen(A12 - A22, B21 + B22, n0)
    P7 = strassen(A21 - A11, B11 + B12, n0)
    
    C11 = P5 + P4 - P2 + P6
    C12 = P1 + P2
    C21 = P3 + P4
    C22 = P5 + P1 - P3 - P7
    
    C = np.vstack((np.hstack((C11, C12)), np.hstack((C21, C22))))
    return C[:len(A) - (1 if padded else 0), :len(A) - (1 if padded else 0)]

def generate_random_matrix(n, value_set):
    """Generates an n x n matrix with entries randomly selected from value_set."""
    return np.random.choice(value_set, size=(n, n))

def main():
    n = 3  # Example size, can be modified
    mode = 1  # Change to 0 for values {0,1,2}, or 1 for values {0,1,-1}
    n0 = 2  # Crossover point for Strassen's algorithm
    
    value_sets = [[0, 1, 2], [0, 1, -1]]
    A = generate_random_matrix(n, value_sets[mode])
    B = generate_random_matrix(n, value_sets[mode])
    
    print("Matrix A:")
    print(A)
    print("Matrix B:")
    print(B)
    
    C_strassen = strassen(A, B, n0)
    C_naive = matrix_mult(A, B)
    
    print("Strassen Result:")
    print(C_strassen)
    print("Naive Result:")
    print(C_naive)
    
    if np.array_equal(C_strassen, C_naive):
        print("Test Passed: Strassen's and Naive results match.")
    else:
        print("Test Failed: Strassen's result differs from Naive result.")

if __name__ == "__main__":
    main()