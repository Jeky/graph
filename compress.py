from sets import Set
import argparse

PRINT_LINE = 1000000

def compress(inputFilename, outputFilename, mapFilename):
    print 'compressing', inputFilename

    nodeSet = Set()
    lineCount = 0

    fin = open(inputFilename)
    for i, l in enumerate(fin.xreadlines()):
        if i != 0 and i % PRINT_LINE == 0:
            print 'read', i, 'lines'

        fromId, toId = l.strip().split('\t')
        nodeSet.add(int(fromId))
        nodeSet.add(int(toId))
        lineCount += 1

    fin.close()
    print 'Read %s lines. Node Count: %d' % (lineCount, len(nodeSet))

    fmap = open(mapFilename, 'w')
    nodeMap = {}
    for i, nid in enumerate(nodeSet):
        if i != 0 and i % PRINT_LINE == 0:
            print 'write', i, 'nodes'

        fmap.write('%d\n' % nid)
        nodeMap[nid] = i

    fmap.close()
    print 'Finish writing map file:', mapFilename

    fin = open(inputFilename)
    fout = open(outputFilename, 'w')
    for i, l in enumerate(fin.xreadlines()):
        if i != 0 and i % PRINT_LINE == 0:
            print 'write', i, 'lines'

        fromId, toId = [int(nid) for nid in l.strip().split('\t')]
        fout.write('%d\t%d\n' % (nodeMap[fromId], nodeMap[toId]))

    fin.close()
    fout.close()

    print 'Finish compressing graph file. Output:', outputFilename


def decompress(inputFilename, outputFilename, mapFilename):
    print 'decompressing', inputFilename, ', using mapfile:', mapFilename

    nodeList = []
    fmap = open(mapFilename)
    for i, l in enumerate(fmap.xreadlines()):
        if i != 0 and i % PRINT_LINE == 0:
            print 'read', i, 'lines'

        nodeList.append(int(l))

    fmap.close()
    print 'Finish reading map file:', mapFilename, 'Total node count:', len(nodeList)

    fin = open(inputFilename)
    fout = open(outputFilename, 'w')

    for i, l in enumerate(fin.xreadlines()):
        if i != 0 and i % PRINT_LINE == 0:
            print 'read', i, 'lines'

        nodeIndex, prv = l.strip().split('\t')
        nodeIndex = int(nodeIndex)
        fout.write('%d\t%s\n' % (nodeList[nodeIndex], prv))

    fin.close()
    fout.close()
    print 'FInish decompressing page rank file. Output: ', outputFilename


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description = '''\
        Compress or decompress graph file. 
        If node ids in graph file are not continuous, compressor should be used.
        And after pagerank is calculated, using decompressor to get the result.''')

    parser.add_argument('-c', dest = 'action', action='store_const', const = compress,\
                        help = 'compress this file')
    parser.add_argument('-d', dest = 'action', action='store_const', const = decompress,\
                        help = 'decompress this file')
    
    parser.add_argument('INPUT', type = str, \
                        help = 'input file name')
    parser.add_argument('OUTPUT', type = str, \
                        help = 'output file name')
    parser.add_argument('MAP', type = str, \
                        help = 'map file name')

    args = parser.parse_args()
    if not args.action:
        print 'usage: compress.py [-h] [-c] [-d] INPUT OUTPUT MAP'
        print 'compress.py: error: should choose -c or -d as an option.'
    else:
        args.action(args.INPUT, args.OUTPUT, args.MAP)