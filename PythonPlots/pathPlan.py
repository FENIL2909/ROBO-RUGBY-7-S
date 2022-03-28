from math import pi,atan2,fabs,asin,tan,sqrt
import matplotlib.pyplot as plt

fig = plt.figure()
ax1 = fig.add_subplot(1, 1, 1)


xPole = [1575,2905,4250,5565,6910]
yPole = [4075,2560,4075,2560,4075]


BotX = 0
BotY = 0

X = []
Y = []

radius = 700
xFence1 = [0,1575+30]
yFence1 = [1575+2500,1575+2500]
xFence2 = [10000,1575+30+1330*4]
yFence2 = [1575+2500,1575+2500]


circle1 = plt.Circle((xPole[0],yPole[0]), radius, color='r')#,fill=False, linestyle=':')
circle2 = plt.Circle((xPole[1],yPole[1]), radius, color='r')#,fill=False, linestyle=':')
circle3 = plt.Circle((xPole[2],yPole[2]), radius, color='r')#,fill=False, linestyle=':')
circle4 = plt.Circle((xPole[3],yPole[3]), radius, color='r')#,fill=False, linestyle=':')
circle5 = plt.Circle((xPole[4],yPole[4]), radius, color='r')#,fill=False, linestyle=':')

plt.ylim(0,13300/2)
plt.xlim(0,10000)

ax1.set_aspect(1)

ax1.scatter(xPole,yPole,label='Poles',color='blue')

ax1.add_artist(circle1)
ax1.add_artist(circle2)
ax1.add_artist(circle3)
ax1.add_artist(circle4)
ax1.add_artist(circle5)

ax1.plot(xFence1, yFence1, label='Fence1', color='blue')
ax1.plot(xFence2, yFence2, label='Fence2', color='blue')

plt.ylim(0,13300/2)#(-5000,13300/2)
plt.xlim(0,10000)

fenceMode = planState = 0
startI = 0
endI = 4
xI = yI = xJ = yJ = lastObj = obCounter = 0
detObjects = [-1,-1,-1,-1,-1]

def collsionCheckGrowingCircle(x1, y1, x2, y2, h, k, r):
    deL = -1
    spCase = 0
    angleSG = atan2(y2-y1,x2-x1)
    angleSC = atan2(k-y1,h-x1)

    if(fabs(angleSG) == pi/2):
        if(x1>h-r and x1<h+r):
            spCase = 1
        c = 0
    else:
        if(angleSG<0):
            angleSG = angleSG + 2*pi
        if(angleSC<0):
            angleSC = angleSC + 2*pi

        m = (y2-y1)/(x2-x1)
        c = y1 - x1*m

        alpha = 1 + m*m
        beta = 2*(h - m*c + m*k)
        gamma = r*r - h*h - k*k - c*c + 2*c*k

        deL = beta*beta + 4*alpha*gamma
        print(deL)
    if(deL >=0 or spCase):
        return 1
    return 0


def avoidGrowingCircle(x1,y1,x2,y2,h,k,r):
    global xI,yI,X,Y,fenceMode
    angleSG = atan2(y2 - y1, x2 - x1)
    angleSC = atan2(k - y1, h - x1)
    dist = sqrt((x1-h)**2+(y1-k)**2)
    theta = asin(r / dist)

    if (angleSG < 0):
        angleSG = angleSG + 2.0 * pi
    if (angleSC < 0):
        angleSC = angleSC + 2.0 * pi

    sign = fabs(fabs(angleSG - angleSC) - pi) / (pi - fabs(angleSG - angleSC));


    if(fenceMode == 0):
        if (angleSG > angleSC):
            angleTan = angleSC + sign * theta
        else:
            angleTan = angleSC - theta

    elif(fenceMode == -1):
        if (y2 > y1):
            angleTan = angleSC - theta
        else:
            angleTan = angleSC + theta
    else:
        if (y1 > y2):
            angleTan = angleSC - theta
        else:
            angleTan = angleSC + theta

    mt = tan(angleTan)
    ct = y1 - mt * x1
    cn = k + h / mt

    xI = ((cn - ct) * mt) / (1 + mt * mt)
    yI = xI * mt + ct

    X.append(xI)
    Y.append(yI)

    return 0


def generateWindow(x1, y1, x2, y2):
    global xPole,yPole,startI,endI,BotX,BotY,radius
    index = [-1, -1]
    sign = 1

    if (x1 != x2):
        sign = fabs(x1 - x2) / (x1 - x2)

    for i in range(0,5,1):
        xLine = xPole[i]

        if ((xLine >= x1 + sign *radius and xLine <= x2 - sign * radius) or (xLine <= x1 + sign * radius and xLine >= x2 - sign * radius)):
            if (index[0] == -1):
                index[0] = i
                index[1] = i
            else:
                index[1] = i

    if(index[0] == -1):
        startI = 0
        endI = 0
        return 0

    if sqrt((BotX - xPole[index[0]])**2 + (BotY - yPole[index[0]])**2) < sqrt((BotX - xPole[index[1]])**2 + (BotY - yPole[index[1]])**2):
        startI = index[0]
        endI = index[1]
    else:
        startI = index[1]
        endI = index[0]
    return 1

def planPath(x1,y1,x2,y2):
    global planState,xI,yI,xJ,yJ,fenceMode,obCounter,lastObj,cnt,startI,endI
    global X,Y,detObjects,xPole,yPole,radius


    if planState == 0:
        # checkCollision State
        generateWindow(x1,y1,x2,y2)
        print("Start:",startI,"end:",endI)
        fenceMode = 0

        obCounter = 0
        lastObj = 0

        cnt = 0
        xJ = x1
        yJ = y1

        xI = x2
        yI = y2

        for i in range(0,5,1):
            detObjects[i] = -1

        if endI - startI == 0:
            ranDom = 1
        else:
            ranDom = abs(endI - startI)/(endI - startI)

        for i in range(startI, int(endI+ranDom), int(ranDom)):
            if collsionCheckGrowingCircle(x1, y1, x2, y2, xPole[i], yPole[i], radius):# or collsionCheckGrowingCircle(x1 - radius/2, y1 - radius/2, x2 - radius/2, y2 - radius/2, xPole[i], yPole[i], radius) or collsionCheckGrowingCircle(x1 + radius/2, y1 + radius/2, x2 + radius/2, y2 + radius/2, xPole[i], yPole[i], radius):
                detObjects[obCounter] = i
                obCounter = obCounter + 1
            print(i)


        if obCounter == 0:
            if fabs(x2) > fabs(xPole[4]):
                detObjects[obCounter] = 0
                obCounter = obCounter + 1

            elif fabs(x2) < fabs(xPole[0]):
                detObjects[obCounter] = 0
                obCounter = obCounter + 1


        if obCounter == 0:
            planState = 3
        else:
            planState = 1

        lastObj = obCounter - 1
        obCounter = -1

    elif planState == 1:
        obCounter = obCounter + 1

        cnt = detObjects[obCounter]
        print("Obstacle :",cnt)
        if cnt == 4:
            fenceMode = 1
        elif cnt == 0:
            fenceMode = -1
        else:
            fenceMode = 0

        avoidGrowingCircle(xJ, yJ, x2, y2, xPole[cnt], yPole[cnt], radius)
        avoidGrowingCircle(x2, y2, xJ, yJ, xPole[cnt], yPole[cnt], radius)
        planState = 2

    elif planState == 2:
        if lastObj != obCounter:
            planState = 1
            xJ = xI
            yJ = yI
        else:
            planState = 3
            xI = x2
            yI = y2

    elif planState == 3:
        X.append(x2)
        Y.append(y2)
        return 0
    return 1


BotX = xPole[2]
BotY = 0
goalX = xPole[2] - 1000
goalY = yPole[2] + 1500

X.append(BotX)
Y.append(BotY)

if __name__ == "__main__":
    while planPath(BotX,BotY,goalX,goalY) :
        print("")

    plt.xlabel('X-axis(mm)')
    plt.ylabel('Y-axis(mm)')
    plt.title('Arena')
    #plt.plot(X,Y,label='path chosen',color='g')
    #plt.scatter(BotX, BotY, label='start')
    #plt.scatter(goalX, goalY, label='goal')
    plt.legend()
    plt.show()

