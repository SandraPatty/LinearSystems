import numpy as np
import matplotlib.pyplot as plt

MPI = np.loadtxt('1.txt').transpose()
J = np.loadtxt('2.txt').transpose()
GS = np.loadtxt('3.txt').transpose()
Cheb = np.loadtxt('4.txt').transpose()

plt.plot(MPI[0], MPI[1])
plt.plot(J[0], J[1])
plt.plot(GS[0], GS[1])
plt.plot(Cheb[0], Cheb[1])

plt.legend(['Метод простых итераций', 'Метод Якоби', 'Метод Гаусса-Зейделя', 'Чебышевское ускорение'])
plt.yscale('log')

plt.savefig('graph.png')
plt.show()