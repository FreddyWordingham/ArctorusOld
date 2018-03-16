import os
import sys
import matplotlib.pyplot as plt
import numpy as np


i = 0
j = 0
red_list = []
green_list = []
blue_list = []
red_centre = []
green_centre = []
blue_centre = []
red_temp = []
green_temp = []
blue_temp = []
red_average = []
green_average = []
blue_average = []
red_tot = 0
green_tot = 0
blue_tot = 0

f = open(os.path.expanduser("~/Arctorus/test/output_threelayer_20180308135612/ccd_images/ccd_one.ppm"))
data = f.read()
f.close()

data.replace('\n', ' ')
p = data.split()
type = p[0]
columns = int(p[1])
rows = int(p[2])
max_val = np.int(p[3])
use_list = [np.int(i) for i in p[4:]]

for i in range(0, len(use_list)-1, 3):
    red_list.append([use_list[i]])
    green_list.append([use_list[i+1]])
    blue_list.append([use_list[i+2]])

for i in range(0, len(red_list)-1):
    if ((i % (rows/2)) == 0 and (i/100) % 2 != 0 ):
        red_centre.append(red_list[i])
        green_centre.append(green_list[i])
        blue_centre.append(blue_list[i])

for i in range(0, rows):
    red_temp.append(red_list[i*rows:(i+1)*rows])
    green_temp.append(green_list[i*rows:(i+1)*rows])
    blue_temp.append(blue_list[i*rows:(i+1)*rows])

for i in range(0, len(red_temp)):
    for j in range(0, len(red_temp[i])):
        red_tot = red_tot + red_temp[i][j][0]
        green_tot = green_tot + green_temp[i][j][0]
        blue_tot = blue_tot + blue_temp[i][j][0]
    red_average.append(red_tot/len(red_temp))
    green_average.append(green_tot/len(green_temp))
    blue_average.append(blue_tot/len(blue_temp))
    red_tot = 0
    green_tot = 0
    blue_tot = 0

fig, (ax1, ax2, ax3) = plt.subplots(nrows = 3, ncols = 1)
ax1.plot(range(0, len(red_average)), red_average, color = 'red')
ax2.plot(range(0, len(green_average)), green_average, color = 'green')
ax3.plot(range(0, len(blue_average)), blue_average, color = 'blue')


#plt.plot(range(0, len(red_average)), red_average, color = 'red')
#plt.plot(range(0, len(green_average)), green_average, color = 'green')
#plt.plot(range(0, len(blue_average)), blue_average, color = 'blue')
#plt.show()

plt.show()
