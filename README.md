#Graph Analyse Toolkit

This is a graph analyse toolkit which provides calculating pagerank, random sampling and other functions.

This library is written by C, but it also has a python interface which is strongly recommend to be used.

**PageRank Computer** is optimized by changing data structure into adjacency list and changing algorithm of power iteration, so it can compute large graph.

##File description

* **graph.h & graph.c** - graph data structure

* **analyse.h & analyse.c** - graph analyse tools which includes

	* PageRank Computer

	* Degree Counter

* **utils.h & utils.c** - utility tools (include some convenient macros)

* **gat** - python interface and command line interface

##Usage

* usage: graphtool.py 

	* **[-h]** - show this help message and exit

    * **[-compress INPUT MAP OUTPUT]** - compress input graph file

    * **[-decompress INPUT MAP OUTPUT]** - decompress input graph file with map file

    * **[-pagerank INPUT NODE_COUNT JUMP_PROB OUTPUT]** - compute pagerank value of input graph

    * **[-degree INPUT NODE_COUNT OUTPUT]** - count the degree of input graph

##Update Log

* **Jul 31.** Update usage, add degree counter and command line interface

* **Jul 31.** Add python interface

* **Jul 31.** Add pageRank counter

* **Jul 30.** Finish build all data structure