#!/bin/python

import os
import sys
import subprocess
import random
import re
import math
import time


#run the test once to setup the array
subprocess.call(["rm","dominion.gcda"])
subprocess.call(["rm","dominion.c.gcov"])

child = subprocess.Popen(["./tarantulaScore"], stdout=subprocess.PIPE)
child.wait()
myRet = child.poll()


#print child.stdout.read()
#print child.poll()

child = subprocess.Popen(["gcov","dominion.c"], stdout=open("/dev/null","w"))
child.wait()


fileName = 'dominion.c.gcov'
with open(fileName, 'r') as myFile:
  content = myFile.read().splitlines()
  myFile.close()


results = []
rgx = '4(1[7-9]|2[0-9]|3[0-9]|4[0-9]|5[0-9]|6[0-9]|7[0-2]):'
for line in content:
  m = re.search( r'.*'+rgx+'.*', line, re.M)
  if m:
    #print m.group()
    results.append([0,0,0,0])




testrun = 0
while (testrun < 20):
  time.sleep(.750)
  print "Test Iteration: " + str(testrun + 1)
  
  #Run the test for real data
  subprocess.call(["rm","dominion.gcda"])
  subprocess.call(["rm","dominion.c.gcov"])
  
  child = subprocess.Popen(["./tarantulaScore"], stdout=subprocess.PIPE)
  child.wait()
  myRet = child.poll()
  
  child = subprocess.Popen(["gcov","dominion.c"], stdout=open("/dev/null","w"))
  child.wait()
  
  with open(fileName, 'r') as myFile:
    content = myFile.read().splitlines()
    myFile.close()
  
  
  section = []
  for line in content:
    m = re.search( r'.*'+rgx+'.*', line, re.M)
    if m:
      #print m.group()
      section.append(m.group())
  
  if len(section) == len(results):
    i = 0
    for item in section:
      m = re.search( r'\s*\d+:\s*'+rgx+'.*', item, re.M)
      if m:
        #print m.group()
        results[i][0] = 1
        results[i][3] = i + 417
      i = i + 1
  
  i=0
  while (i<len(results)):
    results[i][myRet + 1] = results[i][0] + results[i][myRet + 1]
    results[i][0] = 0
    #print results[i]
    i = i + 1
  
  testrun = testrun + 1


  
i = 0
while (i<len(results)):
  print results[i]
  i = i + 1