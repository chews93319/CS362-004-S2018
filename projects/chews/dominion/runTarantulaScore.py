#!/bin/python

import os
import sys
import subprocess
import random
import re
import math
import time

if (len(sys.argv) > 1):
  qtyrun = int(sys.argv[1])
else:
  qtyrun = 10

#run the test once to setup the array
subprocess.call(["rm","dominion.gcda"])
subprocess.call(["rm","dominion.c.gcov"])

childa = subprocess.Popen(["./tarantulaScore"], stdout=subprocess.PIPE)
childa.wait()
myRet = childa.poll()


#print child.stdout.read()
#print child.poll()

childb = subprocess.Popen(["gcov","dominion.c"], stdout=open("/dev/null","w"))
childb.wait()

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
    results.append([0,0,0,0.])

totalFail = 0.01
totalPass = 0.01


for testrun in xrange(0, qtyrun):
  print "Test Iteration: " + str(testrun + 1)
  
  #Run the test for real data
  subprocess.call(["rm","dominion.gcda"])
  subprocess.call(["rm","dominion.c.gcov"])
  
  child1 = subprocess.Popen(["./tarantulaScore"], stdout=subprocess.PIPE)
  child1.wait()
  myRet = child1.poll()
  
  child2 = subprocess.Popen(["gcov","dominion.c"], stdout=open("/dev/null","w"))
  child2.wait()
  
  time.sleep(.250)
  
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
        results[i][0] = i + 417
        results[i][3] = 1
      i = i + 1
  
  if ( myRet ==0 ):
    totalPass = totalPass + 1.0
  else:
    totalFail = totalFail + 1.0
  
  for i in xrange(0,len(results)):
    results[i][myRet + 1] = results[i][3] + results[i][myRet + 1]
    results[i][3] = 0
    #print results[i]
  


print "Total Summary"
print totalPass
print totalFail

if ((totalPass > 0) & (totalFail > 0)):
  for i in xrange(0,len(results)):
    if (results[i][0] != 0):
      #print results[i]
      results[i][3] = float(results[i][2]/totalFail) / (float(results[i][1]/totalPass)+float(results[i][2]/totalFail))
      print results[i]
else:
  print "Insufficient Pass/Fail Ratio. Repeat Tests"


