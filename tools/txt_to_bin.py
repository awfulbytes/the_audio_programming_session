import numpy as np

# Read float values from the txt file
with open('sound.txt', 'r') as f:  # Change to np.float64 if needed
    floats = np.array([float(x) for x in f.read().split()], dtype=np.float64)

# Write the floats to a binary file
floats.tofile('input.bin')
