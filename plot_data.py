import pandas as pd 
import matplotlib.pyplot as plt 

data = pd.read_csv("result.csv", sep=";")

x = data["Index"]
pqueue = data["Linked List"]
heap = data["Heap"]

plt.plot(x, pqueue, color="blue")
plt.plot(x, heap, color="red")
plt.show()