TestTreeNode: treenode.h TestTreeNode.cpp
	g++ -std=c++11 -o TestTreeNode TestTreeNode.cpp

TestTree: treenode.h tree.h TestTree.cpp
	g++ -std=c++11 -o TestTree TestTree.cpp

TestTreeMap: treenode.h tree.h treemap.h TestTreeMap.cpp
	g++ -std=c++11 -o TestTreeMap TestTreeMap.cpp


TestTreeD:  treenode.h tree.h TestTreeD.cpp
	g++ -std=c++11 -o TestTreeD TestTreeD.cpp

all: TestTreeNode TestTree TestTreeMap TestTreeD
