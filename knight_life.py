import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import sys


class LifeGame(object):
    """
    """

    def __init__(self, size=20):
        self.size = size
        self.E = np.eye(size, k=1) + np.eye(size) + np.eye(size, k=-1)
        self.A = np.eye(size, k=1) + np.eye(size, k=-1)
        self.B = np.eye(size, k=2) + np.eye(size, k=-2)
        self.world = np.random.randint(2, size=(size, size))
        pass

    def countNeighbor(self):
        # self.E @ self.world @ self.E - self.world
        return self.A @ self.world @ self.B + self.B @ self.world @ self.A

    def update(self):
        neighbor = self.countNeighbor()
        self.world = (neighbor == 3) + self.world * (neighbor == 2)
        pass

    def animate(self, i):
        plt.cla()
        self.update()
        im = plt.imshow(self.world, interpolation='nearest')

if __name__ == '__main__':
    lg = LifeGame(40)
    fig = plt.figure()
    ani = animation.FuncAnimation(fig, lg.animate, interval=50)
    plt.show()
