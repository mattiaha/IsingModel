# -*- coding: utf-8 -*-
"""
Created on Mon Nov 23 22:13:56 2020

@author: matti
"""

import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("ising_eq1ran.txt", skiprows=2)
M = data[:,1]
length = len(M)
x = np.linspace(0,length,length)

plt.plot(x,M)


plt.xlabel("MC")
plt.ylabel("M")
plt.title("Energy as function of MC-cycles")
plt.show()