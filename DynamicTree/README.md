# Dynamic Tree

Implement dynamic tree (a.k.a. link cut tree). Three operations are implemented.

1. Link(u,v) : add edge between u and v. after this operation, v will be a parent of u. be sure that u doesn't have its parent, and u and v are in other trees.

2. Cut(v) : cut edge between v and its parent.

3. LCA(u,v) : find lowest Common Ancestor of u and v. be sure that u and v are in same tree.

# Input Format

1. line 1: n Q ; n is # of total node, Q is # of queries

2. line 2~(Q+1): one of three types

- 1 u v : Link(u, v)
- 2 v : Cut(v)
- 3 u v : LCA(u, v)

# Files and Folders

1. /DynamicTree.cpp : implement dynamic tree with three operations.

2. /DynamicTreeViz.cpp : visualizing forests.

3. /DataMaker/

	1. /DataMaker/dm.cpp : make arbitrary valid input file

	2. /DataMaker/dm_link.cpp : valid input file but link whole nodes and rest queries are all LCA query.

	3. /DataMaker/comparator.cpp : compare brute force version and dynamic tree version, requires /data/inputList.txt which contains input file names.

	4. /DataMaker/time_checker.cpp : evaluate time for dynamic tree version, requires /data/inputList.txt which contains input file names.

4. /data/ : make 80 input files using dm.cpp.

5. /data_link/ : make 80 input files using dm_link.cpp.

# How to execute

1. DynamicTree

`$ g++ --std=c++14 -o DynamicTree DynamicTree.cpp`
`$ ./DynamicTree`

2. DynamicTreeViz

`$ g++ --std=c++14 -o DynamicTreeViz DynamicTreeViz.cpp`
`$ ./DynamicTreeViz`
