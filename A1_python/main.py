import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("../A1/cmake-build-debug/results.csv") # Загружаем данные

# Изменение приближенной площади
plt.figure(figsize=(10, 6))
plt.plot(data["N"], data["EstimatedArea"], label="Estimated Area", color="green")
plt.xlabel("Number of Points (N)")
plt.ylabel("Estimated Area")
plt.title("Estimated Area Change")
plt.legend()
plt.grid()
plt.savefig("estimated_area_graph.png")
plt.show()

# Изменение относительного отклонения
plt.figure(figsize=(10, 6))
plt.plot(data["N"], data["RelativeError"], label="Relative Error", color="orange")
plt.xlabel("Number of Points (N)")
plt.ylabel("Relative Error(%)")
plt.title("Relative Error Change")
plt.legend()
plt.grid()
plt.savefig("relative_error_graph.png")
plt.show()
