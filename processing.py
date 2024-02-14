import csvreader
import graphs
import matplotlib.pyplot as plt

csrDense = csvreader.readData("timestamps/csr-dense.csv", 0)
csrSparse = csvreader.readData("timestamps/csr-sparse.csv", 0)
denseDense = csvreader.readData("timestamps/dense-dense.csv", 0)
denseSparse = csvreader.readData("timestamps/dense-sparse.csv", 0)

fig, ax = graphs.basePlot()
plt.title("elapsed time from number of elements")
plt.xlabel("number of elements N (NxN matrix)")
plt.ylabel("time, ms")
ax.plot(csrDense[0:, 0], csrDense[0:, 1], label="csr-dense")
ax.plot(csrSparse[0:, 0], csrSparse[0:, 1], label="csr-sparse")
ax.plot(denseDense[0:, 0], denseDense[0:, 1], label="dense-dense")
ax.plot(denseSparse[0:, 0], denseSparse[0:, 1], label="dense-sparse")
plt.legend()
plt.show()
