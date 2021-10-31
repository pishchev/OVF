import numpy as np
import matplotlib.pyplot as plt

from scipy.fft import fft, ifft

def windowDefault(N):
    return lambda x: 1 if abs(x) < N else 0

def windowHanna(N):
    return lambda x: 0.5 * (1 - np.cos( 2*np.pi * x / (N - 1)))

def sin(x):
    return np.sin(x)

def mult(f1, f2):
    return lambda x: f1(x) * f2(x)


rng = np.linspace(-10, 10, 1000)
N = 10


defaultWindow = np.vectorize(mult(windowDefault(N),sin))
sinDefaultWindow = defaultWindow(rng)
sinDefaultWindowFFT = fft(sinDefaultWindow)

plt.title("RectWindow")
plt.plot(rng, np.abs(sinDefaultWindowFFT))
#plt.show()

HannaWindow = np.vectorize(mult(windowHanna(N),sin))
sinHannaWindow = HannaWindow(rng)
sinHannaWindowFFT = fft(sinHannaWindow)

plt.title("HannaWindow")
plt.plot(rng, np.abs(sinHannaWindowFFT))
plt.show()