import numpy as np
import matplotlib.pyplot as plt

MPI = np.loadtxt('1.txt').transpose()
J = np.loadtxt('2.txt').transpose()
GS = np.loadtxt('3.txt').transpose()
AGS = np.loadtxt('4.txt').transpose()
SGS = np.loadtxt('5.txt').transpose()
STD = np.loadtxt('6.txt').transpose()
Cheb = np.loadtxt('7.txt').transpose()

plt.plot(MPI[0], MPI[1])
plt.plot(J[0], J[1])
plt.plot(GS[0], GS[1])
plt.plot(AGS[0], AGS[1])
plt.plot(SGS[0], SGS[1])
plt.plot(STD[0], STD[1])
plt.plot(Cheb[0], Cheb[1])

plt.xlabel("Iterations, n")
plt.ylabel("Time, sec")

plt.legend(['Метод простых итераций', 'Метод Якоби', 'Метод Гаусса-Зейделя', 'Ускорение Гаусса-Зейделя',
 'Метод симметризованного Гаусса-Зейделя', 'Метод быстрого спуска', 'Чебышевское ускорение'], loc='lower right',  fontsize="8")
plt.yscale('log')

plt.savefig('graph.png')
plt.show()