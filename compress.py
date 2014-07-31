from sets import Set
import argparse

PRINT_LINE = 1000000

def compress(inputFilename, outputFilename, mapFilename):
    print 'compressing', inputFilename

    nodeSet = Set()
    lineCount = 0

    fin = open(inputFilename)
    for i, l in enumerate(fin.xreadlines()):
        if i != 0 and i % PRINT_STEP_COUNT == 0:
            print 'read', i, 'lines'

        fromId, toId = l.strip().split('\t')
        nodeSet.add(int(fromId))
        nodeSet.add(int(toId))
        lineCount += 1

    fin.close()
    print 'Read %s lines. Node Count: %d' % (lineCount, len(nodeSet))

    nodeList = list(nodeSet)
    fmap = open(mapFilename, 'w')
    for i, nid in enumerate(nodeList):
        if i != 0 and i % PRINT_STEP_COUNT == 0:
            print 'write', i, 'nodes'

        fmap.write('%d\n' % nid)

    fmap.close()
    print 'Finish writing map file:', mapFilename

    fin = open(inputFilename)
    fout = open(outputFilename, 'w')
    for i, l in enumerate(fin.xreadlines()):
        if i != 0 and i % PRINT_STEP_COUNT == 0:
            print 'write', i, 'lines'

        fromId, toId = l.strip().split('\t')
        nodeSet.add(int(fromId))
        nodeSet.add(int(toId))

        fout.write('%d\t%d\n' % (fromId, toId))

    fin.close()
    fout.close()

    print 'Finish compressing graph file. Output:', outputFilename


def decompress(inputFilename, outputFilename, mapFilename):
    print 'decompressing', inputFilename, ', using mapfile:', mapFilename


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description = '''\
        Compress or decompress graph file. 
        If node ids in graph file are not continuous, compressor should be used.'''.strip())

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