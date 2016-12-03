import matplotlib.pyplot as plt
import sys

filename = sys.argv[1]

with open(filename) as f:
  lines = f.readlines()
  t = list(range(len(lines)))
  s = [int(line.split(' ')[0]) for line in lines]
  plt.plot(t, s)

plt.xlabel('# of generation')
plt.ylabel('best cost function')
plt.title(filename)
plt.grid(True)
plt.show()
