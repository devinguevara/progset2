import numpy as np
import time

def matrix_mult(A, B):
    """Naive matrix multiplication"""
    n = len(A)
    return np.dot(A, B)  # Using numpy's dot for better performance

def strassen(A, B, n_0=64):
    """Strassen's algorithm with crossover to naive"""
    if A.shape[0] <= n_0:
        return matrix_mult(A, B)
    
    # Pad matrices to make them even-sized
    n = A.shape[0]
    if n % 2 != 0:
        A = np.pad(A, ((0, 1), (0, 0)), mode='constant')
        B = np.pad(B, ((0, 1), (0, 0)), mode='constant')
    
    m = A.shape[0] // 2
    
    # Split matrices
    a, b = A[:m, :m], A[:m, m:]
    c, d = A[m:, :m], A[m:, m:]
    e, f = B[:m, :m], B[:m, m:]
    g, h = B[m:, :m], B[m:, m:]

    # Strassen's 7 multiplications
    p1 = strassen(a, f - h)
    p2 = strassen(a + b, h)
    p3 = strassen(c + d, e)
    p4 = strassen(d, g - e)
    p5 = strassen(a + d, e + h)
    p6 = strassen(b - d, g + h)
    p7 = strassen(a - c, e + f)

    # Combine results
    C11 = p5 + p4 - p2 + p6
    C12 = p1 + p2
    C21 = p3 + p4
    C22 = p1 + p5 - p3 - p7
    
    # Assemble result and remove padding if needed
    C = np.vstack((np.hstack((C11, C12)), np.hstack((C21, C22))))
    return C[:n, :n]

def generate_random_graph(n, p):
    """Generate random undirected graph"""
    adj = (np.random.rand(n, n) < p).astype(int)
    np.fill_diagonal(adj, 0)  # No self-loops
    return np.triu(adj) + np.triu(adj, 1).T  # Symmetric

def count_triangles(adj):
    """Count triangles using Strassen's matrix multiplication"""
    A_sq = strassen(adj, adj)
    A_cubed = strassen(A_sq, adj)
    return np.trace(A_cubed) // 6

def expected_triangles(n, p):
    """Calculate expected number of triangles"""
    return (n * (n-1) * (n-2) // 6) * p**3

def run_fast_experiment():
    n = 1024
    probabilities = [0.01, 0.02, 0.03, 0.04, 0.05]
    num_trials = 5
    
    print(f"{'p':<6} | {'Trial 1':<8} | {'Trial 2':<8} | {'Trial 3':<8} | {'Trial 4':<8} | {'Trial 5':<8} | {'Avg':<8} | {'Expected':<8}")
    print("-" * 95)
    
    for p in probabilities:
        trials = []
        for _ in range(num_trials):
            adj = generate_random_graph(n, p)
            triangles = count_triangles(adj)
            trials.append(triangles)
        
        avg = np.mean(trials)
        expected = expected_triangles(n, p)
        
        print(f"{p:.2f}  | {trials[0]:<8} | {trials[1]:<8} | {trials[2]:<8} | {trials[3]:<8} | {trials[4]:<8} | {avg:<8.1f} | {expected:<8.1f}")

if __name__ == "__main__":
    start_time = time.time()
    run_fast_experiment()
    print(f"\nTotal runtime: {time.time() - start_time:.2f} seconds")