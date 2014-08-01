from ctypes import *
import os.path
import os

dirname, filename = os.path.split(os.path.abspath(__file__))
GRAPH_LIBRARY_NAME = dirname[:dirname.rindex('/', 1, len(dirname) - 1)] + '/src/graphlib.so'

if not os.path.exists(GRAPH_LIBRARY_NAME):
    # complie all lib
    MAKE_FILE_NAME = dirname[:dirname.rindex('/', 1, len(dirname) - 1)] + '/src/'
    os.system('make clean -C %s & make -C %s' % (MAKE_FILE_NAME, MAKE_FILE_NAME))

# define c struct
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

# load library
cdll.LoadLibrary(GRAPH_LIBRARY_NAME)
graphlib = CDLL(GRAPH_LIBRARY_NAME)

graphlib.loadGraph.argtypes = [c_char_p, c_int]
graphlib.loadGraph.restype = POINTER(Graph)

graphlib.destroyGraph.argtypes = [POINTER(Graph)]
graphlib.destroyGraph.restype = None

# export functions
def loadGraph(filename, nodeCount = None):
    if nodeCount:
        return graphlib.loadGraph(filename, nodeCount).contents


def destroyGraph(graph):
    graphlib.destroyGraph(pointer(graph))

