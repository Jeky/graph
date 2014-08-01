from gat import compressor, analysor, graph
import argparse
    
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description = '')
    group = parser.add_mutually_exclusive_group()
    group.add_argument('-compress', dest = 'compress_args', nargs = 3, 
                        metavar = ('INPUT', 'MAP', 'OUTPUT'), 
                        help = 'compress input graph file')
    group.add_argument('-decompress', dest = 'decompress_args', nargs = 3, 
                        metavar = ('INPUT', 'MAP', 'OUTPUT'), 
                        help = 'decompress input graph file with map file')
    group.add_argument('-pagerank', dest = 'pagerank_args', nargs = 4, 
                        metavar = ('INPUT', 'NODE_COUNT', 'JUMP_PROB', 'OUTPUT'), 
                        help = 'compute pagerank value of input graph')
    group.add_argument('-degree', dest = 'degree_args', nargs = 3, 
                        metavar = ('INPUT', 'NODE_COUNT', 'OUTPUT'), 
                        help = 'count the degree of input graph')

    args = parser.parse_args()

    if args.compress_args:
        compressor.compress(args.compress_args[0], 
                            args.compress_args[1], 
                            args.compress_args[2])

    elif args.decompress_args:
        compressor.decompress(args.decompress_args[0], 
                              args.decompress_args[1], 
                              args.decompress_args[2])

    elif args.pagerank_args:
        g = graph.loadGraph(args.pagerank_args[0], int(args.pagerank_args[1]))
        prnodes = analysor.computePageRank(g, float(args.pagerank_args[2]))
        analysor.printPageRank(prnodes, args.pagerank_args[3])
        graph.destroyGraph(g)

    elif args.degree_args:
        g = graph.loadGraph(args.degree_args[0], int(args.degree_args[1]))
        nodes = analysor.countDegree(g)
        analysor.sortDeg(nodes, analysor.SORT_BY_IN)
        analysor.printDeg(nodes, args.degree_args[2])
        graph.destroyGraph(g)

    else:
        parser.print_help()
