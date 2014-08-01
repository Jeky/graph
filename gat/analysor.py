from ctypes import *
import os.path
import os

from graph import *

PRINT_LINE = 1000000

graphlib.computePageRank.argtypes = [POINTER(Graph), c_double]
graphlib.computePageRank.restype = POINTER(PRNode)

# export functions
def computePageRank(graph, jumpProb = 0.2):
    prnodePtr = graphlib.computePageRank(pointer(graph), jumpProb)
    prnodes = []
    for i in range(graph.nodeCount):
        prnodes.append(PRNode(prnodePtr[i].index, prnodePtr[i].pr))

    return prnodes


def printPageRank(prnodes, outputFile):
    output = open(outputFile, 'w')

    for prn in prnodes:
        output.write('%d\t%0.10f\n' % (prn.index, prn.pr))

    output.close()


def countDegree(graph):
    print 'Start Counting Degree in Graph...'
    nodes = []

    for i in range(graph.nodeCount):
        if i % PRINT_LINE == 0 and i != 0:
            print 'count', i, 'nodes'

        nodes.append({'index': i, 
                      'in'   : graph.nodes[i].contents.preNodes.contents.length,
                      'out'  : graph.nodes[i].contents.outlinkCount})

    print 'Finish Counting Degree'

    return nodes

SORT_BY_IN  = lambda x: -x['in']
SORT_BY_IN.__name__ = 'SORT BY INDEGREE'
SORT_BY_OUT = lambda x: -x['out']
SORT_BY_OUT.__name__ = 'SORT BY OUTDEGREE'

def sortDeg(nodes, comparator):
    print 'Sorting Degree Count, Using Comparator:', comparator.__name__
    nodes.sort(key = comparator)


def printDeg(degNodes, outputFile):
    print 'Writing Degree Counting to File:', outputFile
    output = open(outputFile, 'w')

    for degn in degNodes:
        output.write('%d\t%d\t%d\n' % (degn['index'], degn['in'], degn['out']))

    output.close()