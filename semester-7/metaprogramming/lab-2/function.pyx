def build_matrix(elements):
    cdef int triples[10000][3]
    cdef int n = len(elements)
    for i in range(n):
        triples[i][0] = elements[i][0]
        triples[i][1] = elements[i][1]
        triples[i][2] = elements[i][2]
    cdef ResultType matrix_t = generate_matrix(triples, n)
    cdef int rang = find_range(matrix_t) + 1;
    matrix = [[0 for _ in range(rang)] for _ in range(rang)]
    for i in range(rang):
        for j in range(rang):
            matrix[i][j] = matrix_t.arr[i][j]
    return matrix


