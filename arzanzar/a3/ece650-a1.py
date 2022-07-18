#!/usr/bin/env python3
import sys

streetsDB = {}

class Point:
    def __init__(self,x,y):
        self.x=x
        self.y=y

    def __repr__(self):
        return f"({self.x},{self.y})"    


def parseCoordinates(unparsedCoordinates):
    
    #print(f'coordinate to check {unparsedCoordinates}   ')

    unparsedCoordinates = unparsedCoordinates.strip()


    for i in unparsedCoordinates:
        if  i=='-' or i=='(' or i==')' or i==' ' or i==',' or (i>='0' and i<='9'):
            continue
        else:
            raise Exception('error unwanted characters in coordinates list')  


    if unparsedCoordinates.find("- ") > -1:
        
        raise Exception("sign problem in input. no space between number and - sign")

    if unparsedCoordinates.count('(') != unparsedCoordinates.count(')'):
        raise Exception('open and close brackets do not match')

    coordinatesList = []
    openBracketFlag = 0
    contentInBracket=''
    spaceBetweenCoordinates=1
    for c in unparsedCoordinates:


        if c=='(': 

            if openBracketFlag !=0 or spaceBetweenCoordinates!=1:
                raise Exception("open brackets not in order or no space beteen to coordinates")

            openBracketFlag=1
            
        
        elif c==')':
            
            if openBracketFlag!=1:
                raise Exception('closed brackets not in order')

            contentInBracket = contentInBracket.strip()
            vertexStringList = contentInBracket.split(',')
            
            if len(vertexStringList)!=2:  #should check length of list elements?
                raise Exception("coordinate is not proper inputted")

            try:
                xCoordinate = int(vertexStringList[0])
                yCoordinate = int(vertexStringList[1])
                pointInstance = Point(xCoordinate,yCoordinate)
                coordinatesList.append(pointInstance)

            except:
                raise Exception('Error in pasring string to integer')

            openBracketFlag=0
            spaceBetweenCoordinates =0
            contentInBracket =''

        elif c==' ' and openBracketFlag==0:
            spaceBetweenCoordinates=1
        
        elif openBracketFlag==1:
            contentInBracket=contentInBracket+c
        
        else:
            raise Exception("wrong input issue in passing coordinate in proper format")    


    return coordinatesList


def checkStreetName(uncheckedStreetName):

    for i in uncheckedStreetName:
        if (i>='a' and i<='z') or  i==' ':
            continue
        else:
            return False

    if len(uncheckedStreetName)== uncheckedStreetName.count(' '):
        return False        

    return True        


def parseAddStreet(commandValue):
    
    addCommandValueList = commandValue.split(' "',maxsplit=1)
    
    
    if len(addCommandValueList)!=2 or len(addCommandValueList[1])==0:
        raise Exception("there is start quote problem for add")

    addCommand = addCommandValueList[0]
   # print(f'before stripping addCommand length: {len(addCommand)}');
    addCommand = addCommand.strip()
   # print(f'after stripping addCommand length: {len(addCommand)}');

    if addCommand != "add":
        raise Exception(" there is error in input in add command might not proper")

    
    addCommandArgList = addCommandValueList[1].split('" ',maxsplit=1)

    if len(addCommandArgList)!=2:
        raise Exception("there is end quote problem for add")

    uncheckedStreetName = addCommandArgList[0]
    unparsedCoordinates = addCommandArgList[1]
    #print(f'before lowering {uncheckedStreetName}');
    
    uncheckedStreetName = uncheckedStreetName.lower()
    #print(f'after lowering {uncheckedStreetName}')

    if checkStreetName(uncheckedStreetName) == False:
        raise Exception("Street name not formed with proper char")

    
    if len(uncheckedStreetName)==0:
        raise Exception("there is error in street name. size should be not zero")

    if streetsDB.get(uncheckedStreetName)!=None:
        raise Exception("there is an error in add. street name already exists")

    
    coordinatesList = parseCoordinates(unparsedCoordinates)

    if len(coordinatesList)<2:
        raise Exception('coordinates list is less than 2. so wrong input')
        
    streetsDB[uncheckedStreetName] = coordinatesList

    #print(addCommandArgList);


    return "Add working properly"


def parseModStreet(commandValue):
    

    modCommandValueList = commandValue.split(' "',maxsplit=1)

    if len(modCommandValueList)!=2 or len(modCommandValueList[1])==0:
        raise Exception("there is start quote problem for mod")

    modCommand = modCommandValueList[0]
   # print(f'before stripping modCommand length: {len(modCommand)}');
    modCommand = modCommand.strip()
   # print(f'after stripping modCommand length: {len(modCommand)}');

    if modCommand != "mod":
        raise Exception(" there is error in input in mod command might not proper")

    modCommandArgList = modCommandValueList[1].split('" ',maxsplit=1)

    if len(modCommandArgList)!=2:
        raise Exception("there is end quote problem for mod")

    uncheckedStreetName = modCommandArgList[0]
    unparsedCoordinates = modCommandArgList[1]
    #print(f'before lowering {uncheckedStreetName}');
    uncheckedStreetName = uncheckedStreetName.lower()
    #print(f'after lowering {uncheckedStreetName}')

    if streetsDB.get(uncheckedStreetName)==None:
        raise Exception("there is an error in mod. no such street name  exists")

    coordinatesList = parseCoordinates(unparsedCoordinates)

    if len(coordinatesList)<2:
        raise Exception('coordinates list is less than 2. so wrong input')
        
    streetsDB[uncheckedStreetName] = coordinatesList

    return "Mod working properly"


def parseRmStreet(commandValue):
    

    rmCommandValueList = commandValue.split(' "',maxsplit=1)

    if len(rmCommandValueList)!=2 or len(rmCommandValueList[1])==0:
        raise Exception("there is start quote problem for rm")

    rmCommand = rmCommandValueList[0]
   # print(f'before stripping rmCommand length: {len(rmCommand)}');
    rmCommand = rmCommand.strip()
   # print(f'after stripping rmCommand length: {len(rmCommand)}');

    if rmCommand != "rm":
        raise Exception(" there is error in input in rm command might not proper")

    rmCommandArgList = rmCommandValueList[1].split('"',maxsplit=1)
    

    if len(rmCommandArgList)!=2 or rmCommandArgList[1] != '':
        raise Exception("there is error in arg of rm coomand.")

    if len(rmCommandArgList[0]) ==0:
        raise Exception("street name should not be of length zero for rm")

    removeStreetName = rmCommandArgList[0]

    removeStreetName = removeStreetName.lower() #gave error so added line


    if streetsDB.get(removeStreetName)==None:
        raise Exception("no such street to remove for rm command")

    streetsDB.pop(removeStreetName)



    return "Remove worked successfully"

def findIntersection(streetAP1,streetAP2,streetBP1,streetBP2):

    x1 = streetAP1.x
    y1 = streetAP1.y
    x2 = streetAP2.x
    y2 = streetAP2.y

    x3 = streetBP1.x
    y3 = streetBP1.y
    x4 = streetBP2.x
    y4 = streetBP2.y

    xnum = (x4-x3)*(x2*y1-x1*y2) - (x2-x1)*(x4*y3-x3*y4)

    ynum = (y4-y3)*(x2*y1-x1*y2) - (y2-y1)*(x4*y3-x3*y4)

    deno = (y4-y3)*(x2-x1) - (y2-y1)*(x4-x3)

    if deno!=0:

        xIntersect = xnum/deno
        yIntersect = ynum/deno

        if xIntersect == 0:
            xIntersect=0

        if yIntersect == 0:
            yIntersect=0    

        if min(x1,x2)<= xIntersect <= max(x1,x2) and min(y1,y2) <= yIntersect <= max(y1,y2): 
            if min(x3,x4) <= xIntersect <= max(x3,x4) and min(y3,y4)<= yIntersect <= max(y3,y4):
                return xIntersect, yIntersect
            else:
                return None, None
        else:
            return None, None

    else:

        if x1 == x2 and y1 ==y2:
            xIntersect = x1
            yIntersect = y1
            return xIntersect, yIntersect

        elif x1 == x3 and y1 == y3:
            xIntersect = x1
            yIntersect = y1
            return xIntersect, yIntersect

        elif x1 == x4 and y1 == y4:
            xIntersect = x1
            yIntersect = y1
            return xIntersect, yIntersect

        elif x2 == x3 and y2 == y3:
            xIntersect = x2
            yIntersect = y2
            return xIntersect, yIntersect

        elif x2 == x4 and y2 == y4:
            xIntersect = x2
            yIntersect = y2
            return xIntersect, yIntersect

        elif x3 == x4 and y3 == y4:
            xIntersect = x3
            yIntersect = y3
            return xIntersect, yIntersect

        else:
            return None, None


def printOutput(outputVertices,segmentAndIntersectList):

    spec=""
    spec=spec+ "V "+str(len(outputVertices))+"\n"
    # print(spec,flush=True)
    # sys.stdout.write(spec)
    # sys.stdout.flush()
    # spec=""
    outputVerticesList = list(outputVertices)
    edgeOrder = list()

    segmentAndIntersectList = list(segmentAndIntersectList.items())

    #print(segmentAndIntersectList)
    #print("---------------")

    
    
    for i in range(len(segmentAndIntersectList)):
        tempStore = set()
        tempStore.add(segmentAndIntersectList[i][0][0])
        tempStore.add(segmentAndIntersectList[i][0][1])

        intersectSet = segmentAndIntersectList[i][1]
        tempStore.update(intersectSet)
        
        #print(tempStore);
        
        #tempStoreList = list(tempStore)
        
        tempStoreList = sorted(tempStore,key=lambda element: (element[0], element[1]))
        #print(tempStoreList)

        for j in range(len(tempStoreList)-1):
            # if edgeOrder.count([outputVerticesList.index(tempStoreList[j])+1,outputVerticesList.index(tempStoreList[j+1])+1])==0:
            #    if edgeOrder.count([outputVerticesList.index(tempStoreList[j+1])+1,outputVerticesList.index(tempStoreList[j])+1])==0:
            edgeOrder.append([outputVerticesList.index(tempStoreList[j])+1,outputVerticesList.index(tempStoreList[j+1])+1])
        
    #print(edgeOrder)

    spec= spec+ "E {"

    if len(edgeOrder)==0:
        spec=spec+"}"
        print(spec,flush=True)
        # sys.stdout.write(spec)
        # sys.stdout.flush()
        return;
    
    for t in range(len(edgeOrder)):
        if t+1 == len(edgeOrder):
            endprint = '>'
        else:
            endprint = '>,'    
        spec=spec+"<"+str(edgeOrder[t][0])+","+str(edgeOrder[t][1])+endprint

    spec=spec+"}"
    print(spec,flush=True)
    # sys.stdout.write(spec)
    # sys.stdout.flush()

    # sys.stdout.write("s 1 4\n")
    # sys.stdout.flush()








def parseGenerate(commandValue):
    

    outputVertices = set()
    segmentAndIntersectList = {}
    streetsDBList = list(streetsDB.items())

    for i in range(len(streetsDBList)):
        streetAVertices = streetsDBList[i][1]
        
        for j in range(len(streetAVertices)):
            
            if j+1 < len(streetAVertices):
                streetAP1 = streetAVertices[j]
                streetAP2 = streetAVertices[j+1]

                for t in range(i+1,len(streetsDBList)):

                    if t==i:
                        #print("here for"+i+"::"+w)
                        continue;

                    streetBVertices = streetsDBList[t][1]

                    for w in range(len(streetBVertices)):

                        if w+1 < len(streetBVertices):
                            streetBP1  = streetBVertices[w]
                            streetBP2 = streetBVertices[w+1]
                            
                            xIntersect , yIntersect = findIntersection(streetAP1,streetAP2,streetBP1,streetBP2)
                            
                            
                            # print(streetAP1)
                            # print(streetAP2)
                            # print(streetBP1)
                            # print(streetBP2)
                            # print(f'{xIntersect},{yIntersect}')
                            # print("--------------------------------")
                            
                            if xIntersect!=None and yIntersect!=None:

                                outputVertices.add((streetAP1.x,streetAP1.y))
                                outputVertices.add((streetAP2.x,streetAP2.y))
                                outputVertices.add((streetBP1.x,streetBP1.y))
                                outputVertices.add((streetBP2.x,streetBP2.y))
                                outputVertices.add((xIntersect,yIntersect))    

                                if segmentAndIntersectList.get(((streetAP1.x,streetAP1.y),(streetAP2.x,streetAP2.y)))==None:
                                    segmentAndIntersectList[((streetAP1.x,streetAP1.y),(streetAP2.x,streetAP2.y))]=set()

                                segmentAndIntersectList[((streetAP1.x,streetAP1.y),(streetAP2.x,streetAP2.y))].add((xIntersect,yIntersect))

                                if segmentAndIntersectList.get(((streetBP1.x,streetBP1.y),(streetBP2.x,streetBP2.y)))==None:
                                    segmentAndIntersectList[((streetBP1.x,streetBP1.y),(streetBP2.x,streetBP2.y))]=set()

                                segmentAndIntersectList[((streetBP1.x,streetBP1.y),(streetBP2.x,streetBP2.y))].add((xIntersect,yIntersect))

    #printVertices(outputVertices)
    printOutput(outputVertices,segmentAndIntersectList)

    #print(segmentAndIntersectList)
    #print(type(streetsDB));
    #print(outputVertices)
    return "graph generate successfully"

 

def parseCommand2(commandValue):
    
    if commandValue.startswith("add ")==True:
        return "add"
    elif commandValue.startswith("mod ")==True:
        return "mod"
    elif commandValue.startswith("rm ")==True:
        return "rm"
    elif commandValue.startswith("gg")==True and len(commandValue)==2: ##len added as ggg should fail
        return "gg"
    else:
        raise Exception("input command is not proper")                

      


def main():

    while True:
        try:
            commandValue = sys.stdin.readline()
            
            
            if commandValue == "":
                break

            commandValue = commandValue.strip()
            #print(commandValue)
            
            order = parseCommand2(commandValue)
            

            if order == "add":
                commandAdd = parseAddStreet(commandValue)
                
            elif order == "mod":
                commandMod = parseModStreet(commandValue)
                
            elif order == "rm":
                commandRm = parseRmStreet(commandValue)
                
            else:
                commandGen = parseGenerate(commandValue)
                
                #print(streetsDB)

                

        except Exception as e:
            print("Error: "+str(e), file=sys.stderr)
            

    sys.exit(0)        


if __name__ == '__main__':
    main()
