import sys
import numpy as np
import cv2

if __name__ == "__main__":
    output_filename = sys.argv[1]

    pixels = []
    for line in sys.stdin:
        pixels.append(list(map(int, line.strip().split())))

    image = np.array(pixels, dtype=np.uint8).reshape(len(pixels), len(pixels[0]), 1)
    cv2.imwrite(output_filename, image)
