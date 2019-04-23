import numpy as np 
import matplotlib.pyplot as plt

theta = np.arange(0, 2*np.pi, 0.01)

# Amplitudes
A = 1
B = 1

# angular frequency
a = 3
b = 4

# phase
phase = 0

x = A * np.sin(a * theta + phase)
y = B * np.sin(b * theta)

plt.plot(x, y)
plt.show()