#Graph Analyse Toolkit

This is a graph analyse toolkit which provides calculating pagerank, random sampling and other functions.

This library is written by C, but it also has a python interface which is strongly recommend to be used.

**PageRank Calculator** is optimized by changing data structure into adjacency list and changing algorithm of power iteration, so it can compute large graph.



##File description

* **graph.h & graph.c** - graph data structure and basic graph load functions

* **counter.h & counter.c** - node counter and degree counter

* **pagerank.h & pagerank.c** - pagerank calculator

* **sample.h & sample.c** - sampling methods

* **utils.h & utils.c** - utility tools (include some convenient macros)

* **gat** - python interface

* **graphtool.py** - command line interface



##Usage

###Compile C Library

First thing is to compile all the c codes. Modify src/Makefile to satisfy your environment. And then:

```shell
$ cd src
$ make
```

This will compile all the codes into **graphlib.so**. Then you can either use this c library or use python interface.

###Input Data Format

* Each line in input graph file is: FROM_NODE_ID \t TO_NODE_ID

* Output file from degree component is: ID \t IN_DEGREE \t OUT_DEGREE

* Output file from pagerank component is: ID \t PAGERANK_VALUE

###How to use CLI

usage: graphtool.py [-h] [-q] {compress,decompress,pagerank,degree}

optional arguments:

*  **-q**                    quiet mode


###compress

compress input graph file

usage: graphtool.py compress [-h] -i INPUT -m MAP [-o OUTPUT]

optional arguments:

* **-i INPUT**    original graph file

* **-m MAP**      output map file, which will be used when decompressing

* **-o OUTPUT**   compressed graph file. If not indicated, output will be stdout



###decompress

decompress input graph file with map file

usage: graphtool.py decompress [-h] -i INPUT -m MAP [-t {graph,pagerank,degree}] [-o OUTPUT]

optional arguments:

* **-i INPUT**              compressed file

* **-m MAP**                map file

* **-t {graph,pagerank,degree}** file type

* **-o OUTPUT**             decompressed file. If not indicated, output will be stdout



###pagerank

compute pagerank value of input graph

usage: graphtool.py pagerank [-h] -i INPUT [-o OUTPUT] [-j JP] [-n NODECOUNT]

optional arguments:

* **-i INPUT**      compressed graph file

* **-o OUTPUT**     pagerank file. If not indicated, output will be stdout

* **-j JP**         jump probability when computing pagerank

* **-n NODECOUNT**  node count of graph



###degree

count the degree of input graph

usage: graphtool.py degree [-h] -i INPUT [-o OUTPUT] [-d {in,out,all}] [-s {in,out,id}] [-n NODECOUNT]

optional arguments:

* **-i INPUT**         graph file

* **-o OUTPUT**        degree file. If not indicated, output will be stdout

* **-d {in,out,all}**  count which degree, in|out|all

* **-s {in,out,id}**   sort by which one, in|out|id

* **-n NODECOUNT**     node count of graph



###randnode

usage: graphtool.py randnode [-h] -i INPUT -c COUNT [-o OUTPUT] [-n NODECOUNT]

optional arguments:

* **-i INPUT**     graph file

* **-c COUNT**      sample count

* **-o OUTPUT**     sample file. If not indicated, output will be stdout

* **-n NODECOUNT**  node count of graph



###randedge

usage: graphtool.py randedge [-h] -i INPUT -c COUNT [-o OUTPUT] [-n EDGECOUNT]

optional arguments:

* **-i INPUT**    graph file
  
* **-c COUNT**      sample count
  
* **-o OUTPUT**     sample file. If not indicated, output will be stdout
  
* **-n EDGECOUNT**  edge count of graph



###randwalk

usage: graphtool.py randwalk [-h] -i INPUT -c COUNT [-o OUTPUT] [-n NODECOUNT] [-j JP]

optional arguments:

* **-i INPUT**      graph file

* **-c COUNT**      sample count

* **-o OUTPUT**     sample file. If not indicated, output will be stdout

* **-n NODECOUNT**  node count of graph

* **-j JP**         jump probability when walking


##Update Log

* **Aug 7.**  Add random node, random edge and random walk sampling methods.

* **Aug 7.**  Add new CLI, fix bugs and refactor structure of files

* **Jul 31.** Update usage, add degree counter and command line interface

* **Jul 31.** Add python interface

* **Jul 31.** Add pageRank counter

* **Jul 30.** Finish build all data structure