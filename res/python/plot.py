#   == IMPORTS ==
import matplotlib.pyplot as plt
import numpy as np
import sys

#   == DEFINES ==
#   -- Plotting --
col = ['r.', 'g.', 'b.', 'k.', 'y.', 'c.', 'm.']


#   == FUNCTIONS ==
#   -- Reading --
#
#   Read data in from a csv file, skipping the first row w.
#
def read_datafile(t_fileName):
    data = np.genfromtxt(t_fileName, delimiter=',', comments='#')
    return data


#   == MAIN ==
#
#   Plot a csv file.
#
for j in range(1, len(sys.argv)):
    print(sys.argv[j])
    data = read_datafile(sys.argv[j])
    # Plot data.
    for i in range(1, len(data[0])):
        plt.plot(data[:, 0], data[:, i], col[j - 1])

# x = np.arange(0, 0.001, 1E-5)
# y = np.exp(-x * 10000) * 9518763.0
# x = np.arange(0, 1.0, 1E-5)
# y = np.exp(-x * 100) * 6.1707E+01
# plt.plot(x, y)


# Plot axis.
plt.axis()

# Show plot.
plt.show()
