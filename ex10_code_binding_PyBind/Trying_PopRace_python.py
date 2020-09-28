#This program is to try the module pybind11_module_example that has been 
#implementet in c++ and binded to python by using pybind11

#The module has a class in it --> PopRace --> generates a queue filled with elements 
#by a producer() and emptied by a number of consumers() (participants) chosen by the user

#To initializate the class --> PopRace(iterations, participants, starting_point)
#itarations = number of elements that the producer will put in the queue
#participants = how many threads participate in the race
#starting_point --> The producer will start producing numbers from strating_point to (starting_point+iterations)

#Once generated the class, start the race by calling the function PoppingRace()
#Once it's done get the winner thread and the amount of pops that has done by calling GetWinner() and GetCounts()
 

import pybind11_module_example

p = pybind11_module_example.PopRace(100,3,5) #The 3 participants compete to pop 100 numbers from the queue (from 5 to 105)

p.PoppingRace() #Start the race

w = p.GetWinner() #Number of the winner participant
c = p.GetCounts() #Number of elements that the winner has popped out of the queue