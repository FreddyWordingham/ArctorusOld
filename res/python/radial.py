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
radius = 2.0
red_middle = []
green_middle = []
blue_middle = []

f = open(os.path.expanduser("~/Arctorus/test/above.txt"))
data = f.read()
f.close()

data.replace('\n', ' ')
p = data.split()
type = p[0]
columns = np.int(p[1])
rows = np.int(p[2])
max_val = np.int(p[3])
use_list = [np.int(i) for i in p[4:]]

for i in range(0, len(use_list)-1, 3):
    red_list.append([use_list[i]])
    green_list.append([use_list[i+1]])
    blue_list.append([use_list[i+2]])

red_array = np.array(red_list).reshape(rows, columns)
green_array = np.array(green_list).reshape(rows, columns)
blue_array = np.array(blue_list).reshape(rows, columns)

# x and y give the location of the image centre.
red_x = rows/2
red_y = columns/2
green_x = rows/2
green_y = columns/2
blue_x = rows/2
blue_y = columns/2

# Find out what the max distance will be by computing the distance to each corner.
red_distanceToUL = np.sqrt((1-red_y)**2 + (1-red_x)**2)
red_distanceToUR = np.sqrt((1-red_y)**2 + (columns-red_x)**2)
red_distanceToLL = np.sqrt((rows-red_y)**2 + (1-red_x)**2)
red_distanceToLR= np.sqrt((rows-red_y)**2 + (columns-red_x)**2)
red_maxDistance = np.ceil(np.max([red_distanceToUL, red_distanceToUR, red_distanceToLL, red_distanceToLR]))
green_distanceToUL = np.sqrt((1-green_y)**2 + (1-green_x)**2)
green_distanceToUR = np.sqrt((1-green_y)**2 + (columns-green_x)**2)
green_distanceToLL = np.sqrt((rows-green_y)**2 + (1-green_x)**2)
green_distanceToLR= np.sqrt((rows-green_y)**2 + (columns-green_x)**2)
green_maxDistance = np.ceil(np.max([green_distanceToUL, green_distanceToUR, green_distanceToLL, green_distanceToLR]))
blue_distanceToUL = np.sqrt((1-blue_y)**2 + (1-blue_x)**2)
blue_distanceToUR = np.sqrt((1-blue_y)**2 + (columns-blue_x)**2)
blue_distanceToLL = np.sqrt((rows-blue_y)**2 + (1-blue_x)**2)
blue_distanceToLR= np.sqrt((rows-blue_y)**2 + (columns-blue_x)**2)
blue_maxDistance = np.ceil(np.max([blue_distanceToUL, blue_distanceToUR, blue_distanceToLL, blue_distanceToLR]))

# Allocate an array for the profile
redtemp_profileSums = np.zeros((1, red_maxDistance))
greentemp_profileSums = np.zeros((1, green_maxDistance))
bluetemp_profileSums = np.zeros((1, blue_maxDistance))
redtemp_profileCounts = np.zeros((1, red_maxDistance))
greentemp_profileCounts = np.zeros((1, green_maxDistance))
bluetemp_profileCounts = np.zeros((1, blue_maxDistance))

red_profileSums = [x for y in redtemp_profileSums for x in y]
green_profileSums = [x for y in greentemp_profileSums for x in y]
blue_profileSums = [x for y in bluetemp_profileSums for x in y]
red_profileCounts = [x for y in redtemp_profileCounts for x in y]
green_profileCounts = [x for y in greentemp_profileCounts for x in y]
blue_profileCounts = [x for y in bluetemp_profileCounts for x in y]

red_averageRadialProfile = red_profileSums
green_averageRadialProfile = green_profileSums
blue_averageRadialProfile = blue_profileSums

# Scan the original image getting gray level, and scan image getting distance.
# Then add those values to the profile.
for column in range(1, columns):
    for row in range(1, rows):
        red_thisDistance = np.int(np.round(np.sqrt((row-red_y)**2 + (column-red_x)**2)))
        green_thisDistance = np.int(np.round(np.sqrt((row-green_y)**2 + (column-green_x)**2)))
        blue_thisDistance = np.int(np.round(np.sqrt((row-blue_y)**2 + (column-blue_x)**2)))
        if red_thisDistance <= 0 and green_thisDistance <= 0 and blue_thisDistance <= 0:
            continue
        red_profileSums[red_thisDistance] = red_profileSums[red_thisDistance] + np.double(red_array[row, column])
        red_profileCounts[red_thisDistance] = red_profileCounts[red_thisDistance] + 1
        green_profileSums[green_thisDistance] = green_profileSums[green_thisDistance] + np.double(green_array[row, column])
        green_profileCounts[green_thisDistance] = green_profileCounts[green_thisDistance] + 1
        blue_profileSums[blue_thisDistance] = blue_profileSums[blue_thisDistance] + np.double(blue_array[row, column])
        blue_profileCounts[blue_thisDistance] = blue_profileCounts[blue_thisDistance] + 1

# Divide the sums by the counts at each distance to get the average profile
for i in range(0, len(red_profileSums)-1):
    if red_profileCounts[i] == 0:
        continue
    red_averageRadialProfile[i] = red_profileSums[i] / red_profileCounts[i]
    if green_profileCounts[i] == 0:
        continue
    green_averageRadialProfile[i] = green_profileSums[i] / green_profileCounts[i]
    if blue_profileCounts[i] == 0:
        continue
    blue_averageRadialProfile[i] = blue_profileSums[i] / blue_profileCounts[i]

    if red_averageRadialProfile[i] != 0 and green_averageRadialProfile != 0 and blue_averageRadialProfile[i] != 0:
        print('Profile sums', red_profileSums[i], green_profileSums[i], blue_profileSums[i])
        print('Profile counts', red_profileCounts[i], green_profileCounts[i], blue_profileCounts[i])
        print('Average', red_averageRadialProfile[i], green_averageRadialProfile[i], blue_averageRadialProfile[i])
    #print('Averages:    ', red_averageRadialProfile[i], green_averageRadialProfile[i], blue_averageRadialProfile[i])

#Debugging
#for i in range(0, len(red_list)):
#    if red_list[i][0] != 0:
#        print('red list greater than 0 :    ', i, red_list[i])
#    if green_list[i][0] != 0:
#        print('green list greater than 0:   ', i, green_list[i])
#    if blue_list[i][0] != 0:
#        print('blue list greater than 0:    ', i, blue_list[i])

# Plot it.
fig, (ax1, ax2, ax3) = plt.subplots(nrows = 3, ncols = 1)
ax1.plot(range(0, len(red_averageRadialProfile)), red_averageRadialProfile, color = 'red')
ax2.plot(range(0, len(green_averageRadialProfile)), green_averageRadialProfile, color = 'green')
ax3.plot(range(0, len(blue_averageRadialProfile)), blue_averageRadialProfile, color = 'blue')
#plt.plot(range(0, len(red_averageRadialProfile)), red_averageRadialProfile, color = 'red')
#plt.plot(range(0, len(green_averageRadialProfile)), green_averageRadialProfile, color = 'green')
#plt.plot(range(0, len(blue_averageRadialProfile)), blue_averageRadialProfile, color = 'blue')
plt.show()
