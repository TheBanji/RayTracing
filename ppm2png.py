import numpy as np
import matplotlib.pyplot as plt
import sys

if(len(sys.argv) == 2):
    try:
        file = open(sys.argv[1], "r")
    except:
        print("Unable to open " + sys.argv[1] + ".")
        sys.exit(1)
    
    file.readline() # Skips the magic keyword for PPM which is P3.
    size = file.readline().split(" ") # Read the "width height" line and put them into a list.
    width, height = int(size[0]), int(size[1]) # Convert width and height to an integer.
    file.readline() # Skips the maximum intensity, it is assumed to be 255.

    img = np.zeros([height, width, 3], dtype = np.uint8)

    i, j = 0, 0
    # Reads the pixel values in the file.
    pixel = file.readline()
    while(pixel != ""):
        pixel     = pixel.split(" ")
        img[j, i, 0] = np.uint8(pixel[0])
        img[j, i, 1] = np.uint8(pixel[1])
        img[j, i, 2] = np.uint8(pixel[2])
        pixel     = file.readline()
        i += 1
        if(i >= width):
            i = 0
            j += 1
    file.close()
    plt.imsave(sys.argv[1][:-3] + "png", img) # Saves the image as a PNG.

else:
    print("PPM image name is missing.")
    sys.exit(1)