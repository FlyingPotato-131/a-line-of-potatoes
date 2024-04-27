import sys
sys.path.append("../")
import csvreader
import graphs
from matplotlib import pyplot as plt
import numpy as np

resdata = csvreader.readData("data.csv")

fig, ax = graphs.basePlot()
plt.xlabel("lambda min")
plt.ylabel("lambda max")
plt.title("Шаги итерационных методов")

ax.plot(resdata[:, 1], resdata[:, 2], label = "GD")
ax.plot(resdata[:, 3], resdata[:, 4], label = "GD, tau opt")
ax.plot(resdata[:, 5], resdata[:, 6], label = "SGD")
ax.plot(resdata[:, 7], resdata[:, 8], label = "GD, CA")
ax.plot(resdata[:, 9], resdata[:, 10], label = "CG")
plt.legend()
plt.show()
