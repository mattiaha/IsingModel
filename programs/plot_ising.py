# -*- coding: utf-8 -*-
"""
Created on Mon Nov 23 20:43:25 2020

@author: matti
"""

import matplotlib.pyplot as plt
import numpy as np

data1 = np.loadtxt("40s_Tl.txt")
T_crit = 2.269
T1 = data1[:,0]
E1 = data1[:,1]
Cv1 = data1[:,2]
sus1 = data1[:,4]
abs_m1 = data1[:,5]

data2 = np.loadtxt("60s_Tl.txt")

T2 = data2[:,0]
E2 = data2[:,1]
Cv2 = data2[:,2]
sus2 = data2[:,4]
abs_m2 = data2[:,5]

data3 = np.loadtxt("80s_Tl.txt")

T3 = data3[:,0]
E3 = data3[:,1]
Cv3 = data3[:,2]
sus3 = data3[:,4]
abs_m3 = data3[:,5]

data4 = np.loadtxt("100s_Tl.txt")

T4 = data4[:,0]
E4 = data4[:,1]
Cv4 = data4[:,2]
sus4 = data4[:,4]
abs_m4 = data4[:,5]

plt.figure(1)
plt.plot(T1,E1, 'r-', label='n=40')
plt.plot(T2,E2, 'b-', label='n=60')
plt.plot(T3,E3, 'k-', label='n=80')
plt.plot(T4,E4, 'g-', label='n=100')
plt.plot(T1,E1, 'rx')
plt.plot(T2,E2, 'bx')
plt.plot(T3,E3, 'kx')
plt.plot(T4,E4, 'gx')
plt.legend()
plt.xlabel("T")
plt.ylabel("<E>/N")
plt.title("Energy as function of T")
plt.show()

plt.figure(2)
plt.plot(T1,Cv1, 'r-', label='n=40')
plt.plot(T2,Cv2, 'b-', label='n=60')
plt.plot(T3,Cv3, 'k-', label='n=80')
plt.plot(T4,Cv4, 'g-', label='n=100')
plt.plot(T1,Cv1, 'rx')
plt.plot(T2,Cv2, 'bx')
plt.plot(T3,Cv3, 'kx')
plt.plot(T4,Cv4, 'gx')
plt.legend()
plt.xlabel("T")
plt.ylabel("$C_{V}/N$")
plt.title("Heat as function of T")
plt.show()
plt.figure(3)
plt.plot(T1,sus1, 'r-', label='n=40')
plt.plot(T2,sus2, 'b-', label='n=60')
plt.plot(T3,sus3, 'k-', label='n=80')
plt.plot(T4,sus4, 'g-', label='n=100')
plt.plot(T1,sus1, 'rx')
plt.plot(T2,sus2, 'bx')
plt.plot(T3,sus3, 'kx')
plt.plot(T4,sus4, 'gx')
plt.legend()
plt.xlabel("T")
plt.ylabel("$\chi /N $")
plt.title("$\chi $ as function of T")
plt.show()
plt.figure(4)
plt.plot(T1,abs_m1, 'r-', label='n=40')
plt.plot(T2,abs_m2, 'b-', label='n=60')
plt.plot(T3,abs_m3, 'k-', label='n=80')
plt.plot(T4,abs_m4, 'g-', label='n=100')
plt.plot(T1,abs_m1, 'rx')
plt.plot(T2,abs_m2, 'bx')
plt.plot(T3,abs_m3, 'kx')
plt.plot(T4,abs_m4, 'gx')
plt.legend()
plt.xlabel("T")
plt.ylabel("<|M|>/N]")
plt.title("Absolute magnitization as function of T")
plt.show()