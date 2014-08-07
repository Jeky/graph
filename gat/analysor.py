from ctypes import *
import os.path
import os
import sys

from graph import *

PRINT_LINE = 1000000

# export functions

# computePageRank in pagerank.h
graphlib.computePageRank.argtypes = [POINTER(BackwardGraph), c_double]
graphlib.computePageRank.restype = POINTER(PRNode)

def computePageRank(graph, jumpProb):
    prnodePtr = graphlib.computePageRank(pointer(graph), jumpProb)
    return prnodePtr[:graph.nodeCount]


def printPageRank(prnodes, outputFile):
    if outputFile:
        output = open(outputFile, 'w')
    else:
        output = sys.stdout

    for prn in prnodes:
        output.write('%d\t%0.10f\n' % (prn.index, prn.pr))

    if outputFile:
        output.close()

# countNode() in counter.h
graphlib.countNode.argtypes = [c_char_p]
graphlib.countNode.restype = c_int

def countNode(input):
    return graphlib.countNode(input)


# countDegree() in counter.h
class DegNode(Structure):
    _fields_ = [('index', c_int),
                ('inDeg', c_int),
                ('outDeg', c_int)]

    def __str__(self):
        return 'Node[in = %d, out = %d]' % \
               (self.inDeg, self.outDeg)

graphlib.countDegree.argtypes = [c_char_p, c_int, c_int]
graphlib.countDegree.restype = POINTER(DegNode)

def countDegree(input, nodeCount, sortBy):
    sort = 0
    if sortBy == 'in':
        sort = 1
    elif sortBy == 'out':
        sort = 2

    return graphlib.countDegree(input, nodeCount, sort)[:nodeCount]


def printDegree(nodes, outputFile, degFilter):
    if outputFile:
        output = open(outputFile, 'w')
    else:
        output = sys.stdout

    for dn in nodes:
        if degFilter == 'in':
            output.write('%d\t%d\n' % (dn.index, dn.inDeg))
        elif degFilter == 'out':
            output.write('%d\t%d\n' % (dn.index, dn.outDeg))
        else:
            output.write('%d\t%d\t%d\n' % (dn.index, dn.inDeg, dn.outDeg))


    if outputFile:
        output.close()