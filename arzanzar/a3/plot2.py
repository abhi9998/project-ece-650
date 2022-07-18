from cProfile import label
import sys;
import matplotlib.pyplot as plt

pointsx =[]
pointsy =[]
i=0;
while True:
    try:
        commandValue = sys.stdin.readline()
        commandValue = commandValue.strip()
        
        if commandValue=="gg":
            break;

        commandValue = commandValue.split("\" ");
        commandValue = commandValue[1].split(" ");

        for command in commandValue:

            split = command.split(',')
            x= split[0][1:]
            y=split[1][:-1]
            x= int(x)
            y = int(y)
            pointsx.append(x)
            pointsy.append(y) 

        plt.plot(pointsx,pointsy,label="line"+str(i))
        pointsx=[]
        pointsy=[]
        i=i+1;         

    except Exception as e:
        print("Error: "+str(e), file=sys.stderr)



plt.xlabel('x - axis')
# naming the y axis
plt.ylabel('y - axis')
# giving a title to my graph
plt.title('Two lines on same graph!')
 
# show a legend on the plot
plt.legend()
 
# function to show the plot
plt.show()
