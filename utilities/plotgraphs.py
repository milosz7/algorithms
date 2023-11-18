import matplotlib.pyplot as plt
import glob

text_files = []
for file in glob.glob("*.txt"):
    text_files.append(file)

for file in text_files:
    with open(file, "r") as current_file:
        lines = current_file.read().splitlines()
        xs = []
        ys = []
        for line in lines:
            sort_name = file.split("_")[0]
            x, y = line.split(",")
            xs.append(int(x))
            ys.append(float(y))
        plt.plot(xs, ys, label=sort_name)

plt.title("Sort algorithms speed comparison.")
plt.xlabel("Amount of elements")
plt.ylabel("Elapsed time (s)")
plt.legend()
plt.savefig("speed_comparison.jpg", dpi=400)
plt.show()
