import csvreader
import graphs
import numpy as np

data = csvreader.readData("counts-problem-4.csv")
graphs.plot(data[0:, 0], data[0:, 1], title = "amount of iterations to reach error 1e-12 over parameter tau", xlabel = "tau", ylabel = "Niter")