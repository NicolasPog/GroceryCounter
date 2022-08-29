import re
import string
import pprint 


#Location of where the text file is on the computer
TextFile = r"C:\Users\Nicolas\Desktop\NICK SNHU\Section 7\FinalProjectCPP\FinalProjectCPP\inputTxtFile.txt" 



#Counts the number of times a produce is on the list and prints the number
def DisplayList(produce):
    file = open(TextFile, "rt") #Read only open format on text file
    data = file.read() #interprets the data
    produceList = data.split() #uses the split function to split the data in a list
    produceNumber = data.count(produce) #Uses the count function to count how many times the produce has occured in the text file
    file.close() #Closes file stream
    return produceNumber #return the produce count

#counts the number of items in the text file
def DisplayPurchases():
    file = open(TextFile, "rt") #Read only open format on text file
    data = file.read() #interprets the data
    produceList = data.split() #uses the split function to split the data in a list
    print('Quantity of produce inside the text file :', len(produceList)) #prints all items from produceList
    producelist_dic = {item: produceList.count(item) for item in produceList} #Makes the items into a dictionary based on how many times they showed up.
    pprint.pprint(producelist_dic, width=1) #prints the dictionary, not too sure how it works had the tutor help me with this.
    file.close() #Closes file stream

#Produces the values and numbers of produce in a histogram compatible data set
def DisplayHistogram():
    file = open(TextFile, "rt")#Read only open format on text file
    data = file.read() #interprets the data
    produceList = data.split() #uses the split function to split the data in a list
    producelist_dic = {item: produceList.count(item) for item in produceList} #Makes the items into a dictionary based on how many times they showed up.
    with open(r"C:\Users\Nicolas\Desktop\NICK SNHU\Section 7\FinalProjectCPP\FinalProjectCPP\frequency.dat", 'wt') as datFile: #Creates the .dat file
        for key, value in producelist_dic.items(): #retuns the files as a tuple from dictionary. Not too sure how on this part the tutor helped me out with this as well.
            datFile.write(str(key)) 
            datFile.write(" ")
            datFile.write(str(value))
            datFile.write('\n')
    datFile.close() #Closes file stream