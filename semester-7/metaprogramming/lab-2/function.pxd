cdef extern from "function.h":
    ctypedef struct ResultType:
        int size
        int arr[100][100]

    ResultType generate_matrix(int triplets[10000][3], int num)
    
    int find_range(ResultType res)
