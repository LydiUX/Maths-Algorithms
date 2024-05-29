import matplotlib.pyplot as plt
import numpy as np

if __name__ == "__main__":
    with open("logistic.txt", "r") as coordinates:
        total = [float(line.strip()) for line in coordinates]
    plt.figure(facecolor = 'black')
    plt.axes().set_facecolor('black')
    x_coord = total[:len(total) // 2]
    y_coord = total[len(total) // 2:]
    x = np.array(x_coord)
    y = np.array(y_coord)
    plt.scatter(x, y, s = 0.00008, c = 'pink')
    # plt.savefig("out.png", format = "png", dpi = 1200)
    plt.show()