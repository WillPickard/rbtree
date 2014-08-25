all:	TreeNode.h RBTree.h
	g++ -std=c++11 -c TreeNode.h RBTree.h
run:	all 
	g++ -std=c++11 -o tester tester.cpp TreeNode.h RBTree.h
	./tester
