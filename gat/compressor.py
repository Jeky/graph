from sets import Set
import sys

PRINT_LINE = 1000000

def compress(inputFilename, mapFilename, outputFilename):
    print 'Compressing', inputFilename

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
    if outputFilename:
        fout = open(outputFilename, 'w')
    else:
        fout = sys.stdout
    for i, l in enumerate(fin.xreadlines()):
        if i != 0 and i % PRINT_LINE == 0:
            print 'write', i, 'lines'

        fromId, toId = [int(nid) for nid in l.strip().split('\t')]
        fout.write('%d\t%d\n' % (nodeMap[fromId], nodeMap[toId]))

    fin.close()
    if outputFilename:
        fout.close()
        print 'Finish compressing graph file. Output:', outputFilename
    else:
        print 'Finish compressing graph file.'


def decompress(inputFilename, mapFilename, outputFilename, fileType):
    print 'Decompressing', inputFilename, ', using mapfile:', mapFilename

    nodeList = []
    fmap = open(mapFilename)
    for i, l in enumerate(fmap.xreadlines()):
        if i != 0 and i % PRINT_LINE == 0:
            print 'read', i, 'lines'

        nodeList.append(int(l))

    fmap.close()
    print 'Finish reading map file:', mapFilename, 'Total node count:', len(nodeList)

    fin = open(inputFilename)
    if outputFilename:
        fout = open(outputFilename, 'w')
    else:
        fout = sys.stdout

    for i, l in enumerate(fin.xreadlines()):
        if i != 0 and i % PRINT_LINE == 0:
            print 'read', i, 'lines'

        info = l.strip().split('\t')
        if fileType == 'graph':
            fromIndex = int(info[0])
            toIndex = int(info[1])
            fout.write('%d\t%d\n' % (nodeList[fromIndex], nodeList[toIndex]))
        else:
            nodeIndex = int(info[0])
            fout.write('%d\t%s\n' % (nodeList[nodeIndex], '\t'.join(info[1:])))

    fin.close()
    if outputFilename:
        fout.close()
        print 'Finish decompressing page rank file. Output: ', outputFilename
    else:
        print 'Finish decompressing page rank file.'