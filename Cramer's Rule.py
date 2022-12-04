def systemSolution(coefficientMatrix, solutionVector, whichSolution):
    
    #Duplicates the coefficientMatrix as any matrix with matrix1 = matrix2 will share the same memory
    startingCoefMatrix = [[0]*len(coefficientMatrix) for i in range(len(coefficientMatrix))]
    for i in range(len(coefficientMatrix)):
        for j in range(len(coefficientMatrix)):
            startingCoefMatrix[i][j] = coefficientMatrix[i][j]
    
    def det(matrix):
        try:
            #reduce to row-echelon form
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
            #the sum of products of a row-echelon matrix is the determinant
            determinant = 1
            for i in range(size):
                for j in range(size):
                    if i == j:
                        determinant *= matrix[i][j]
            return determinant
        except:
            return Exception(f'{matrix} must be square.')
    
    def newSolutionMatrix(matrix, solution, index):
        lenSolution = len(solution)
        lenCoef = len(matrix)
        for i in range(lenCoef):
            for x in range(lenSolution):
                matrix[x][index] = solution[x]
        return matrix

    if whichSolution >= 1:
        try:
            return f'Solution x{whichSolution}: {det(newSolutionMatrix(coefficientMatrix, solutionVector, whichSolution - 1)) / det(startingCoefMatrix)}'
        except ZeroDivisionError:
            return f'This system may have infinitely many solutions, or no solutions.'
        except:
            return f'Solution x{whichSolution} is out of range!'
    else:
        return f'Solution x{whichSolution} is out of range!'
    
A = [[1,2,3],[3,4,6],[5,6,7]]
B = [5,6,7]
print(systemSolution(A, B, 3))