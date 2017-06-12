import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import sys


def update(world):
    neighbor = E @ world @ E - world
    return (neighbor == 3) + world * (neighbor == 2)


def animate(i):
    global world
    plt.cla()
    world = update(world)
    im = plt.imshow(world, interpolation='nearest')


SIZE = 40
E = np.eye(SIZE, k=1) + np.eye(SIZE) + np.eye(SIZE, k=-1)
world = np.random.randint(2, size=(SIZE, SIZE))
# for x in range(200):
#     world = update(world)
#     neighbor = E @ world @ E - world
#     print(np.sum((1 - world) * (neighbor == 3) + world *
#                  (1 - ((neighbor == 2) * (neighbor == 3)))))

fig = plt.figure()
ani = animation.FuncAnimation(fig, animate, interval=50)
plt.show()
