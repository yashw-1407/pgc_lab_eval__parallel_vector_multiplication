import pandas as pd
import matplotlib.pyplot as plt

# Load data
df = pd.read_csv('../results/performance.csv')

# Speedup = Sequential Time / Parallel Time
# Assuming first row is sequential (Threads=1)
sequential_time = df.loc[df['Threads'] == 1, 'Execution_Time'].values[0]
df['Speedup'] = sequential_time / df['Execution_Time']
df['Efficiency'] = (df['Speedup'] / df['Threads']) * 100

print("Performance Analysis:")
print(df)

# Plot Execution Time
plt.figure()
plt.plot(df['Threads'], df['Execution_Time'], marker='o')
plt.title('Execution Time vs Number of Threads')
plt.xlabel('Number of Threads')
plt.ylabel('Execution Time (seconds)')
plt.grid(True)
plt.savefig('../graphs/execution_time.png')

# Plot Speedup
plt.figure()
plt.plot(df['Threads'], df['Speedup'], marker='o', color='orange')
plt.title('Speedup vs Number of Threads')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup')
plt.grid(True)
plt.savefig('../graphs/speedup.png')

# Plot Efficiency
plt.figure()
plt.plot(df['Threads'], df['Efficiency'], marker='o', color='green')
plt.title('Efficiency vs Number of Threads')
plt.xlabel('Number of Threads')
plt.ylabel('Efficiency (%)')
plt.grid(True)
plt.savefig('../graphs/efficiency.png')

print("Graphs generated successfully in the 'graphs' folder.")
