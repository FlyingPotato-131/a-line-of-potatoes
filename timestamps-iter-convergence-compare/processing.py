import sys
sys.path.append("../")
import csvreader
import graphs
from matplotlib import pyplot as plt

end = 50 #error doesn't visibly change after this value

data = csvreader.readData("data.csv")

fig, ax = graphs.basePlot();
plt.title("discrepancy over iterations")
plt.xlabel("iterations")
plt.ylabel("length of discrepancy vector / length of free terms vector")
ax.plot(data[0:end, 0], data[0:end, 2], label = "simple iter method")
ax.plot(data[0:end, 0], data[0:end, 4], label = "jakobi method")
ax.plot(data[0:end, 0], data[0:end, 6], label = "gauss seidel method")
plt.legend()
plt.show()

fig, ax = graphs.basePlot();
plt.title("discrepancy over time")
plt.xlabel("time, us")
plt.ylabel("length of discrepancy vector / length of free terms vector")
ax.plot(data[0:end, 1], data[0:end, 2], label = "simple iter method")
ax.plot(data[0:end, 3], data[0:end, 4], label = "jakobi method")
ax.plot(data[0:end, 5], data[0:end, 6], label = "gauss seidel method")
plt.legend()
plt.show()
