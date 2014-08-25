#include "TreeNode.h"
#include "RBTree.h"
#include <stdio.h>
#include <string>


int main(void){

	printf("main called\n");
	RBTree<int> *tree = new RBTree<int>();
	tree->RBinsert(178);
	tree->RBinsert(78478);
	tree->RBinsert(6);
	tree->RBinsert(-178);
	tree->RBinsert(23428);
	tree->RBinsert(17324);
	tree->RBinsert(328);
	printf("calling inorder...\n");
	tree->RBinorder(tree->getRoot());
	
	printf("calling levelOrder...\n");
	tree->RBlevelorder();

	tree->RBdelete(178);
	printf("inorder after deleting 178\n");
	tree->RBinorder(tree->getRoot());

	printf("size: %d\n", tree->getSize());
return 0;
}
