import matplotlib.pyplot as plt
import numpy as np

if __name__ == "__main__":
    with open("output.txt", "r") as coordinates:
        total = [float(line.strip()) for line in coordinates]
    x_coord = total[:len(total) // 2]
    y_coord = total[len(total) // 2:]
    x = np.array(x_coord)
    y = np.array(y_coord)
    plt.scatter(x, y, s = 1)
    plt.show()