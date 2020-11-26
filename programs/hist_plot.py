# -*- coding: utf-8 -*-
"""
Created on Wed Nov 25 19:07:21 2020

@author: matti
"""
import numpy as np
import matplotlib.pyplot as plt
data = np.loadtxt("T24P.txt")
E = data[:,0]

weights = np.ones_like(E)/float(len(E))
binwidth = 1
plt.hist(E,weights=weights,bins=np.arange(min(E), max(E) + binwidth, binwidth))
plt.xlabel('E')
plt.ylabel('P(E)')
"""plt.axis([-800,-775,0.0,1.0])"""
plt.title('Probability of energies for T=2.4')
plt.show()