import serial
import matplotlib.pyplot as plt

# import matplotlib.animation as animation
plt.ion()
fig = plt.figure()

ser = serial.Serial('COM11', 9600)

# ax1 = fig.add_subplot(1, 1, 1)
xs = []
ys = []
x = 0
y = 0
ser.close()
ser.open()
while True:
    while (ser.inWaiting()!=0):
        x = float(ser.readline())
        y = float(ser.readline())
    # xs.append(x.decode())

    # x = x+.01

    # ys.append(y.decode())

    plt.scatter(x, y)
    # plt.plot(x, y)
    plt.show()
    plt.pause(.0001)
