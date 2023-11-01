import cv2
import sys

def process_image(image_path):
    img = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    if img is None:
        print("Error reading the image", file=sys.stderr)
        sys.exit(1)
    
    # Print width and height as first two lines
    print(img.shape[1])  # width
    print(img.shape[0])  # height

    # Print grayscale values line-by-line
    for row in img:
        print()
        for pixel in row:
            print(pixel, end=" ")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 process_image.py <path_to_image>", file=sys.stderr)
        sys.exit(1)
    process_image(sys.argv[1])
