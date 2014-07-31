from ctypes import *
import os.path
import os

GRAPH_LIBRARY_NAME = 'graphlib.so'

class Array(Structure):
    _fields_ = [('length', c_int),
                ('values', POINTER(c_int)),
                ('capacity', c_int)]

class Node(Structure):
    _fields_ = [('outlinkCount', c_int),
                ('preNodes', POINTER(Array))]

class Graph(Structure):
    _fields_ = [('nodes', POINTER(POINTER(Node))),
                ('deadends', POINTER(Array)),
                ('capacity', c_int),
                ('nodeCount', c_int),
                ('edgeCount', c_int)]

    def __str__(self):
        return 'Graph[V = %d, E = %d, D = %d]' %\
               (self.nodeCount, self.edgeCount, self.deadends.contents.length)


class PRNode(Structure):
    _fields_ = [('index', c_int),
                ('pr', c_double)]

    def __str__(self):
        return 'Node[id = %d, pr = %lf]' % \
               (self.index, self.pr)


if not os.path.exists(GRAPH_LIBRARY_NAME):
    # complie all lib
    os.system('make clean & make')

# load library
cdll.LoadLibrary(GRAPH_LIBRARY_NAME)
graphlib = CDLL(GRAPH_LIBRARY_NAME)

graphlib.loadGraph.argtypes = [c_char_p, c_int]
graphlib.loadGraph.restype = POINTER(Graph)

graphlib.destroyGraph.argtypes = [POINTER(Graph)]
graphlib.destroyGraph.restype = None

graphlib.computePageRank.argtypes = [POINTER(Graph), c_double]
graphlib.computePageRank.restype = POINTER(PRNode)

# import functions
def loadGraph(filename, nodeCount = None):
    if nodeCount:
        return graphlib.loadGraph(filename, nodeCount).contents


def destroyGraph(graph):
    graphlib.destroyGraph(pointer(graph))


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

if __name__ == '__main__':
    g = loadGraph('/Users/jeky/dataset/samples/Amazon0505WCC.dat', 410236)
    prnodes = computePageRank(g)
    printPageRank(prnodes, 'test/Amazon0505WCC-pagerank-0.2.list')    
    destroyGraph(g)
