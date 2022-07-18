#!/usr/bin/env python3

#
# Skeleton for ECE650 Test 1
# DO NOT DISTRIBUTE
#
# Complete the two provided functions. Implement as much functionality as you
# can. Make sure to not change the interface.
#
# More details are in the question on LEARN.
#
# You are allowed to use a Python IDE and Python Documentation available at
# https://docs.python.org/3/
#
# You are very likely to need to add extra functions and/or classes to organize
# your code. We will mark your code for functionality only. Using extra
# functions is not required, but is highly advised
#




def printListofString(data):

    print("---")
    for i in range(len(data)):
        print("- "+data[i])
    print("...")

def printListofDict(data):
    for i in range(len(data)):
        dictVal = data[i];

        for key in dictVal:
            if isinstance(dictVal[key],str) and isinstance(dictVal[key],str):
                continue;
            else:
                raise Exception("Wrong type of dict in list: ");

    print("---");
    for i in range(len(data)):
        dictVal = data[i];
        
        val = "- ";
        for key in dictVal:
            val=val+key+": "+dictVal[key];
            print(val);
            val="  ";
    print("...");        



def printList(data):

    isStringList = 0
    isDictList =0

    for i in range(len(data)):
        if isinstance(data[i],str) == True:
            isStringList =isStringList+1;
        else:
            if isinstance(data[i],dict)==True:
                isDictList=isDictList+1;

    if isStringList == len(data):
        printListofString(data)
    elif isDictList== len(data):
        printListofDict(data)
    else:
        raise Exception("Wrong type of data in list: ")       



def printDictofString(data):

    print("---")
    for key in data:
        print(key+": "+data[key]);
    print("...") 


def printDictofList(data):

    for key in data:
        listData = data[key];
        for i in range(len(listData)):
            if isinstance(listData[i],str) or isinstance(listData[i],int):
                continue;
            else:
                raise Exception("Wrong data in list of dict: ");

    print("---");
    for key in data:
        listData = data[key];
        print(key+":");
        for i in range(len(listData)):
            print("  - "+str(listData[i]));
    print("...");
   



def printDict(data):
    isListDict =0;
    isStringDict =0;

    for key in data:
        if isinstance(data[key],str) and isinstance(key,str):
            isStringDict = isStringDict+1;
        else:
            if isinstance(data[key],list) and isinstance(key,str):
                isListDict = isListDict+1;

    if isStringDict == len(data):
        printDictofString(data)
    elif isListDict == len(data):
        printDictofList(data)
    else:
        raise Exception("Wrong type of data in dict")                        


def print_syaml(data):
    """Print data in SYAML format. Raise an exception if this is not possible"""

    if isinstance(data, dict) or isinstance(data, list):
        if isinstance(data,dict)==True:
            printDict(data);
        else: 
            if isinstance(data,list)==True:
                printList(data);    
    else:
        raise Exception("Wrong type of data: " + str(data.__class__))


def parseList(lines):
    outputList=[];
    for i in range(len(lines)):
        if i==0 or i== len(lines)-1:
            continue;
        else:

            line = lines[i];
            line = line.rstrip();
            if line.startswith("- ")==True and line.find(": ")==-1:
                outputList.append(line[2:]);
            else:
                raise Exception("Incorrect format in list or : found");    

    return outputList;            

def parseDict(lines):
    outputDict={};
    for i in range(len(lines)):
        if i==0 or i==len(lines)-1:
            continue;
        else:

            line = lines[i];
            line = line.rstrip();
            if line.startswith("- ")==False:
                if line.find(": ")!=-1:    
                    keyVal = line.split(": ");
                    if len(keyVal)!=2:
                        raise Exception("Incorrect format in list");
                    outputDict[keyVal[0]]=keyVal[1];
                else:
                    raise Exception("data not in proper form for dict rep");
            else:
                raise Exception("error in data - found");
    return outputDict;                              



def parse_syaml(lines):
    """Parse SYAML document. See LEARN for details."""
    if not isinstance(lines, list):
        raise Exception("Expecting a list of strings")
    if not (len(lines) >= 2 and lines[0] == "---\n" and lines[-1] == "...\n"):
        raise Exception("Begin or end document is missing")

    if len(lines)==2:
        return None

    if lines[1].startswith("- ")==True:
        return parseList(lines);
    else:
        return parseDict(lines);        

    
    print("If you see this line, then your implementation is wrong!")
    return None


# This is a simple test function provided from your convenience
if __name__ == "__main__":
    #d1 = [{"one":"one","two":"two"}, {"one":"one","two":"two"}, {"one":"one","two":"two"}]
    #d1 = [{"one":"one","two":"two"}, {"one":"one","two":"two"}, {"one":"one","two":{"abhi":"abhi"}}]
    # d1 = {"one":"one","two":"two"}
    # d1 = {"one":["one","teo"],"two":[2]}

    # print_syaml(d1)

     t1 = ["---\n",
           "one: un\n",
           "two: deux\n",
           "three: trois\n",
           "...\n"]
     
     t2 = ["---\n",
           "- one\n",
           "- two\n",
           "- three\n",
           "...\n"]

     t2 = ["---\n",
           "...\n"]            
     d2 = parse_syaml(t2)
     print(d2)
     print_syaml(d2)
