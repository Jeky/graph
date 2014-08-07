from ctypes import *
from datetime import datetime
import os.path
import os
import sys

from graph import *

# export functions

# randomNodeSample() in sample.h
graphlib.randomNodeSample.argtypes = [c_int, c_int]
graphlib.randomNodeSample.restype = POINTER(c_int)

def randomNodeSample(nodeCount, count):
    return graphlib.randomNodeSample(nodeCount, count)[:count]

def printNodes(nodes, outputFile):
    if outputFile:
        fout = open(outputFile, 'w')
    else:
        fout = sys.stdout

    for n in nodes:
        fout.write('%d\n' % n)

    if outputFile:
        print 'Finish Printing Nodes. Output:', outputFile
        fout.close()
    else:
        print 'Finish Printing Nodes.'


# randomEdgeSample() in sample.h
class Edge(Structure):
    _fields_ = [('fromId', c_int),
                ('toId', c_int)]

graphlib.randomEdgeSample.argtypes = [c_char_p, c_int, c_int]
graphlib.randomEdgeSample.restype = POINTER(Edge)

def randomEdgeSample(inputFile, edgeCount, count):
    return graphlib.randomEdgeSample(inputFile, edgeCount, count)[:count]

def countEdge(inputFile):
    fin = open(inputFile)
    count = 0

    print "Start Counting Edges in Graph From File: %s." % inputFile
    begin = datetime.now()
    for i in fin.xreadlines():
        count += 1

    end = datetime.now()
    print "Edge Count: %d. Total Time: %0.2lf sec." % (count, (end - begin).total_seconds())

    return count

def printEdges(edges, outputFile):
    if outputFile:
        fout = open(outputFile, 'w')
    else:
        fout = sys.stdout

    for e in edges:
        fout.write('%d\t%d\n' % (e.fromId, e.toId))

    if outputFile:
        print 'Finish Printing Edges. Output:', outputFile
        fout.close()
    else:
        print 'Finish Printing Edges.'

