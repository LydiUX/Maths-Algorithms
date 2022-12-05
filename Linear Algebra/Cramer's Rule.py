def systemSolution(coefficientMatrix, solutionVector, whichSolution):
    
    #Duplicates the coefficientMatrix as any matrix with matrix1 = matrix2 will share the same memory
    startingCoefMatrix = [[0]*len(coefficientMatrix) for _ in range(len(coefficientMatrix))]
    for i in range(len(coefficientMatrix)):
        for j in range(len(coefficientMatrix)):
            startingCoefMatrix[i][j] = coefficientMatrix[i][j]
    
    def det(matrix):
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
            #the product of diagnols of a row-echelon matrix is the determinant
            determinant = 1
            for i in range(size):
                for j in range(size):
                    if i == j:
                        determinant *= matrix[i][j]
            return determinant
        except:
            raise Exception(f'{matrix} must be square.')
    
    def newSolutionMatrix(matrix, solution, index):
        for _ in range(len(matrix)):
            for x in range(len(solution)):
                matrix[x][index] = solution[x]
        return matrix

    if whichSolution >= 1:
        try:
            return f'Solution x_{whichSolution}: {det(newSolutionMatrix(coefficientMatrix, solutionVector, whichSolution - 1)) / det(startingCoefMatrix)}'
        except ZeroDivisionError:
            return f'This system may have infinitely many solutions, or no solutions.'
        except:
            return f'Solution x_{whichSolution} is out of range!'
    else:
        return f'Solution x_{whichSolution} is out of range!'

#User interaction
try:
    print('This calculator solves linear systems of equations in the form of\na_0x_1 + a_1x_2 + ... + a_mx_n = s_1\nb_0x_1 + b_1x_2 + ... + b_mx_n = s_2\netc...')
    size = int(input('How many variables does your system have? '))
    print('Enter the coefficients of your equations:')
    coefMatrix = [[0 for _ in range(size)] for _ in range(size)]
    for i in range(len(coefMatrix)):
        for j in range(len(coefMatrix)):
            coefMatrix[i][j] = float(input(f'Coefficient of equation {i+1} variable {j+1}: '))
    print(f'Your system of equations should have {size} solutions.\nEnter the solutions of your equations:')
    solution = [1 for _ in range(size)]
    for i in range(size):
        solution[i] = float(input(f'Solution corresponding to equation {i+1}: '))
    sol = int(input('Which solution would you like to see? '))
    print(systemSolution(coefMatrix, solution, sol))
except:
    print('Please provide number answers to the questions.')
