import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint as ode
def odeSystem(vars, init_conditions):
    x, y, z = vars
    return σ * (y - x), x * (ρ - z) - y, x * y - β * z
initconditions = []
interval = np.arange(0.0, 40.0, 0.01)
gatherValues = True
while gatherValues == True:
    print('Default ρ, σ, and β values are 28, 10, and 2.6666...\n')
    try:
        ρ = float(input('Enter the ρ value: '))
        σ = float(input('Enter the σ value: '))
        β = float(input('Enter the β value: '))
        gatherValues_2 = True
        while gatherValues_2 == True:
            try:
                for i in range(3): initconditions.append(float(input('Enter the initial conditions of the ODE (x(0),y(0),z(0)): ')))
                gatherValues_2 = False
            except: 
                print('Please enter valid initial conditions.\n')
                continue      
        gatherValues = False
    except:
        print('Please enter valid ρ, σ, and β values.\n')
        continue
solvedSystem = ode(odeSystem, initconditions, interval)
fig = plt.figure()
solved = fig.add_subplot(projection='3d')
solved.plot(solvedSystem[:, 0], solvedSystem[:, 1], solvedSystem[:, 2])
plt.draw()
plt.show() 