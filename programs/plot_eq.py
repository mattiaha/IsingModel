# -*- coding: utf-8 -*-
"""
Created on Mon Nov 23 20:06:02 2020

@author: matti
"""

import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("ising_eq_2.txt")
E_m = data[:,0]
length = len(E_m)
x = np.linspace(0,length,length)
plt.figure(1)
plt.plot(x,E_m)


plt.xlabel("MC")
plt.ylabel("E [J]")
plt.title("Mean energy,random state,T=2.4 [J/$k_b$]")
plt.show()

M = data[:,1]
plt.figure(2)

plt.plot(x,M)


plt.xlabel("MC")
plt.ylabel("M [$\hbar $]")
plt.title("Absolute magnetization, random state, T=2.4 [J/$k_b$]")
plt.show()