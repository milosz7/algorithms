import matplotlib.pyplot as plt
import glob
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
import numpy as np

def construct_label(coefs, sort_name):
    c, b, a = coefs
    return f"{sort_name} approximation: {a}x^2 + {b}x + {c}"
    
plt.figure(figsize=(14,8))

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

        xs = np.array(xs).reshape(-1, 1)
        ys = np.array(ys)
        poly = PolynomialFeatures(degree=2)
        X_poly = poly.fit_transform(xs)
        regressor = LinearRegression(fit_intercept=False)
        regressor.fit(X_poly, ys)

        plt.plot(xs, regressor.predict(X_poly), label=construct_label(regressor.coef_, sort_name))
        plt.scatter(xs, ys, label=sort_name)

plt.title("Sort algorithms speed comparison.")
plt.xlabel("Amount of elements")
plt.ylabel("Elapsed time (s)")
plt.legend()
plt.savefig("speed_comparison.jpg", dpi=400)
plt.show()
