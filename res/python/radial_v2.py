import os
import sys
import matplotlib.pyplot as plt
import numpy as np


i = 0
j = 0
k = 0

f = open(os.path.expanduser("~/Arctorus/test/output_threelayer_20180405163445/ccd_images/ccd_one.ppm"))
data = f.read()
f.close()

data.replace('\n', ' ')
p = data.split()
type = p[0]
columns = np.int(p[1])
rows = np.int(p[2])
max_val = np.int(p[3])
use_list = [np.int(i) for i in p[4:]]

pixel = np.zeros((rows, columns, 3))

for i in range(0, rows):
    for j in range(0, columns):
        pixel[i,j] = [use_list[k], use_list[k+1], use_list[k+2]]
        k += 3

# x and y give the location of the image centre.
pix_x = rows/2
pix_y = columns/2

# Find out what the max distance will be by computing the distance to each corner.
distanceToUL = np.sqrt((1-pix_y)**2 + (1-pix_x)**2)
distanceToUR = np.sqrt((1-pix_y)**2 + (columns-pix_x)**2)
distanceToLL = np.sqrt((rows-pix_y)**2 + (1-pix_x)**2)
distanceToLR= np.sqrt((rows-pix_y)**2 + (columns-pix_x)**2)
maxDistance = np.ceil(np.max([distanceToUL, distanceToUR, distanceToLL, distanceToLR]))

# Allocate an array for the profile
profileSums = [[0]*3 for i in range(np.int(maxDistance))]
profileCounts = [[0]*3 for i in range(np.int(maxDistance))]
averageRadialProfile = [[0]*3 for i in range(np.int(maxDistance))]

# Scan the original image getting gray level, and scan image getting distance.
# Then add those values to the profile.
for column in range(1, columns):
    for row in range(1, rows):
        thisDistance = np.int(np.round(np.sqrt((row-pix_y)**2 + (column-pix_x)**2)))
        if thisDistance <= 0:
            continue
        for i in range(len(profileSums[thisDistance])):
            profileSums[thisDistance][i] = profileSums[thisDistance][i] + np.double(pixel[row, column][i])
            profileCounts[thisDistance][i] = profileCounts[thisDistance][i] + 1

#for i in range(len(profileSums)):
#    print('blue sums', profileSums[i][2])

# Divide the sums by the counts at each distance to get the average profile
for i in range(0, len(profileSums)):
    for j in range(0, len(profileSums[i])):
        if profileCounts[i][j] == 0:
            continue
        averageRadialProfile[i][j] = profileSums[i][j] / profileCounts[i][j]

red_list = [averageRadialProfile[i][0] for i in range(len(averageRadialProfile))]
green_list = [averageRadialProfile[i][1] for i in range(len(averageRadialProfile))]
blue_list = [averageRadialProfile[i][2] for i in range(len(averageRadialProfile))]

for i in range(len(red_list)):
    if (red_list[i] != 0.0):
        print('red list entry: ', red_list[i], i)
    if (green_list[i] != 0.0):
        print('green list entry: ', green_list[i], i)
    if (blue_list[i] != 0.0):
        print('blue list entry: ', blue_list[i], i)

total_list = [red_list[i]+green_list[i]+blue_list[i] for i in range(len(averageRadialProfile))]

#print('red list', red_list)

# Plot it.
plt.plot(range(0, len(averageRadialProfile)), red_list, color = 'red', label = 'Red pixel count')
plt.plot(range(0, len(averageRadialProfile)), green_list, color = 'green', label = 'Green pixel count')
plt.plot(range(0, len(averageRadialProfile)), blue_list, color = 'blue', label = 'Blue pixel count')
plt.plot(range(0, len(averageRadialProfile)), total_list, color = 'purple', label = 'Total pixel count')

plt.xlabel('Distance from centre of image (pixels)')
plt.ylabel('Radial average number of pixels')
plt.legend(loc = 'upper right')

plt.show()
