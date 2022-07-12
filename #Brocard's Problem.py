#Brocard's Problem
#TODO: use decimal module instead of default float module as it cannot parse floats with more than 16 sig figs.
#Find pairs (m, n) that satisfy n!+1=m^2
#m(n)=sqrt(n!+1)
import math
returnm = lambda n: math.sqrt(math.factorial(n)+1)
checkInt = lambda parse: parse.is_integer()
run = True
i = 0
while run == True:
    try:
        if checkInt(returnm(i)) == True: 
            print(f'The working values are ({int(returnm(i))}, {i})')
            i = i + 1
        elif checkInt(returnm(i)) == False: 
            i = i + 1
    except:
        print('Integer too large')
        run = False
print('End Script')