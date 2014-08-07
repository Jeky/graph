from ctypes import *
from datetime import datetime
import os.path
import os
import sys

import graph

# export functions

# randomNodeSample() in sample.h
graph.graphlib.randomNodeSample.argtypes = [c_int, c_int]
graph.graphlib.randomNodeSample.restype = POINTER(c_int)

def randomNodeSample(nodeCount, count):
    return graph.graphlib.randomNodeSample(nodeCount, count)[:count]

def printNodes(nodes, outputFile):
    if outputFile:
        fout = open(outputFile, 'w')
    else:
        fout = sys.stdout

    for n in nodes:
        fout.write('%d\n' % n)

    if outputFile:
        if not graph.quiet:
            print 'Finish Printing Nodes. Output:', outputFile
        fout.close()
    else:
        if not graph.quiet:
            print 'Finish Printing Nodes.'


# randomEdgeSample() in sample.h
class Edge(Structure):
    _fields_ = [('fromId', c_int),
                ('toId', c_int)]

graph.graphlib.randomEdgeSample.argtypes = [c_char_p, c_int, c_int]
graph.graphlib.randomEdgeSample.restype = POINTER(Edge)

def randomEdgeSample(inputFile, edgeCount, count):
    return graph.graphlib.randomEdgeSample(inputFile, edgeCount, count)[:count]

def countEdge(inputFile):
    fin = open(inputFile)
    count = 0

    if not graph.quiet:
        print "Start Counting Edges in Graph From File: %s." % inputFile
    begin = datetime.now()
    for i in fin.xreadlines():
        count += 1

    end = datetime.now()
    if not graph.quiet:
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
        if not graph.quiet:
            print 'Finish Printing Edges. Output:', outputFile
        fout.close()
    else:
        if not graph.quiet:
            print 'Finish Printing Edges.'


# randomWalkSample() in sample.h

class Step(Structure):
    _fields_ = [('index', c_int),
                ('tag', c_int)]

graph.graphlib.randomWalkSample.argtypes = [c_char_p, c_int, c_double, c_int]
graph.graphlib.randomWalkSample.restype = POINTER(Step)

def randomWalkSample(inputFile, nodeCount, jp, count):
    return graph.graphlib.randomWalkSample(inputFile, nodeCount, jp, count)[:count]

def printSteps(steps, outputFile):
    if outputFile:
        fout = open(outputFile, 'w')
    else:
        fout = sys.stdout

    for s in steps:
        fout.write('%d\t%d\n' % (s.index, s.tag))

    if outputFile:
        if not graph.quiet:
            print 'Finish Printing Steps. Output:', outputFile
        fout.close()
    else:
        if not graph.quiet:
            print 'Finish Printing Steps.'


