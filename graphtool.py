from gat import compressor, analysor, graph, sample
import argparse
import sys
import os.path
    
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description = 
        '''This is a graph analyse toolkit which provides calculating pagerank, random sampling and other functions.''')
    parser.add_argument('-q', dest = 'quiet', required = False, 
                        help = 'quiet mode', 
                        action = 'store_true', default = False)

    subparsers = parser.add_subparsers(dest = 'action', title = 'actions')

    compressParser = subparsers.add_parser('compress', help = 'compress input graph file')
    compressParser.add_argument('-i', dest = 'input', required = True,  
                                help = 'original graph file')
    compressParser.add_argument('-m', dest = 'map', required = True,  
                                help = 'output map file, which will be used when decompressing')
    compressParser.add_argument('-o', dest = 'output', required = False, 
                                help = 'compressed graph file. If not indicated, output will be stdout')

    decompressParser = subparsers.add_parser('decompress', help = 'decompress input graph file with map file')
    decompressParser.add_argument('-i', dest = 'input', required = True,  
                                  help = 'compressed file')
    decompressParser.add_argument('-m', dest = 'map', required = True,  
                                  help = 'map file')
    decompressParser.add_argument('-t', dest = 'type', required = False,  
                                  help = 'file type',
                                  default = 'graph', choices = ['graph', 'pagerank', 'degree'])
    decompressParser.add_argument('-o', dest = 'output', required = False, 
                                  help = 'decompressed file. If not indicated, output will be stdout')

    pagerankParser = subparsers.add_parser('pagerank', help = 'compute pagerank value of input graph')
    pagerankParser.add_argument('-i', dest = 'input', required = True,  
                                help = 'compressed graph file')
    pagerankParser.add_argument('-o', dest = 'output', required = False, 
                                help = 'pagerank file. If not indicated, output will be stdout')
    pagerankParser.add_argument('-j', dest = 'jp', required = False, 
                                help = 'jump probability when computing pagerank', 
                                type = float, default = 0.15)
    pagerankParser.add_argument('-n', dest = 'nodeCount', required = False, 
                                help = 'node count of graph', 
                                type = int, default = 0)

    degreeParser = subparsers.add_parser('degree', help = 'count the degree of input graph')
    degreeParser.add_argument('-i', dest = 'input', required = True,  
                              help = 'graph file')
    degreeParser.add_argument('-o', dest = 'output', required = False, 
                              help = 'degree file. If not indicated, output will be stdout')
    degreeParser.add_argument('-d', dest = 'direct', required = False, 
                              help = 'count which degree, in|out|all', 
                              choices = ['in', 'out', 'all'], default = 'all')
    degreeParser.add_argument('-s', dest = 'sort', required = False,
                              help = 'sort by which one, in|out|id',
                              choices = ['in', 'out', 'id'], default = 'id')
    degreeParser.add_argument('-n', dest = 'nodeCount', required = False, 
                              help = 'node count of graph', 
                              type = int, default = 0)

    rnParser = subparsers.add_parser('randnode', help = 'random node sampling')
    rnParser.add_argument('-i', dest = 'input', required = True,  
                          help = 'graph file')
    rnParser.add_argument('-c', dest = 'count', required = True,
                          help = 'sample count',
                          type = int)
    rnParser.add_argument('-o', dest = 'output', required = False, 
                          help = 'sample file. If not indicated, output will be stdout')
    rnParser.add_argument('-n', dest = 'nodeCount', required = False, 
                          help = 'node count of graph', 
                          type = int, default = 0)

    reParser = subparsers.add_parser('randedge', help = 'random edge sampling')
    reParser.add_argument('-i', dest = 'input', required = True,  
                          help = 'graph file')
    reParser.add_argument('-c', dest = 'count', required = True,
                          help = 'sample count',
                          type = int)
    reParser.add_argument('-o', dest = 'output', required = False, 
                          help = 'sample file. If not indicated, output will be stdout')
    reParser.add_argument('-n', dest = 'edgeCount', required = False, 
                          help = 'edge count of graph', 
                          type = int, default = 0)

    rwParser = subparsers.add_parser('randwalk', help = 'random walk sampling')
    rwParser.add_argument('-i', dest = 'input', required = True,  
                          help = 'graph file')
    rwParser.add_argument('-c', dest = 'count', required = True,
                          help = 'sample count',
                          type = int)
    rwParser.add_argument('-o', dest = 'output', required = False, 
                          help = 'sample file. If not indicated, output will be stdout')
    rwParser.add_argument('-n', dest = 'nodeCount', required = False, 
                          help = 'node count of graph', 
                          type = int, default = 0)
    rwParser.add_argument('-j', dest = 'jp', required = False, 
                          help = 'jump probability when walking', 
                          type = float, default = 0.15)

    args = parser.parse_args()

    if args.quiet:
        graph.setOutput(False)

    if args.action == 'compress':
        compressor.compress(args.input, args.map, args.output)

    elif args.action == 'decompress':
        compressor.decompress(args.input, args.map, args.output, args.type)

    elif args.action == 'pagerank':
        if args.nodeCount == 0:
            args.nodeCount = analysor.countNode(args.input)

        g = graph.loadBackwardGraph(args.input, args.nodeCount)
        prnodes = analysor.computePageRank(g, args.jp)
        analysor.printPageRank(prnodes, args.output)
        graph.destroyBackwardGraph(g)

    elif args.action == 'degree':
        if args.nodeCount == 0:
            args.nodeCount = analysor.countNode(args.input)

        degnodes = analysor.countDegree(args.input, args.nodeCount, args.sort)
        analysor.printDegree(degnodes, args.output, args.direct)
    elif args.action == 'randnode':
        if args.nodeCount == 0:
            args.nodeCount = analysor.countNode(args.input)

        nodes = sample.randomNodeSample(args.nodeCount, args.count)
        sample.printNodes(nodes, args.output)
    elif args.action == 'randedge':
        if args.edgeCount == 0:
            args.edgeCount = sample.countEdge(args.input)

        edges = sample.randomEdgeSample(args.input, args.edgeCount, args.count)
        sample.printEdges(edges, args.output)
    elif args.action == 'randwalk':
        if args.nodeCount == 0:
            args.nodeCount = analysor.countNode(args.input)

        steps = sample.randomWalkSample(args.input, args.nodeCount, args.jp, args.count)
        sample.printSteps(steps, args.output)
    else:
        parser.print_help()
