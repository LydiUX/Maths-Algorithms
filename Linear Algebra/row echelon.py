def reduce(matrix):
    try:
        #reduce to row-echelon form using gaussian elimination
        size = len(matrix)
        for i in range(size - 1): 
            for j in range(size - 1, i, -1):
                if matrix[j][i] == 0:
                    continue
                else:
                    try:
                        computationalRatio = matrix[j][i] / matrix[j - 1][i]
                    except ZeroDivisionError:
                        for k in range(size):
                            t = matrix[j][k]
                            matrix[j][k] = matrix[j - 1][k]
                            matrix[j - 1][k] = t
                        continue
                    for l in range(size):
                        matrix[j][l] = matrix[j][l] - computationalRatio * matrix[j - 1][l]
        return matrix
    except:
            raise Exception(f'{matrix} must be square.')

size = int(input('How big (n) is your matrix? '))
print('Input the entries:')
inpMatrix = [[0 for _ in range(size)] for _ in range(size)]
for i in range(len(inpMatrix)):
    for j in range(len(inpMatrix)):
        inpMatrix[i][j] = float(input(f'Row {i+1} Column {j+1}: '))
print(f'The row-echelon form of your matrix is\n{reduce(inpMatrix)}')