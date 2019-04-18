import numpy as np 
import matplotlib.pyplot as plt 

m = 1.0   # 重さ
k = 1.0   # バネ定数
c = 1.0   # ダンパ定数
x = 1.0   # 初期位置
v = 0     # 初期速度
dt = 0.1  # 時間刻み
record = []
time = np.arange(0, 10, dt)
for t in time:
    F = -k * x  -c * v 
    a = F / m
    v += a * dt
    x += v * dt  
    record.append(x)

plt.plot(time, record)
plt.show()