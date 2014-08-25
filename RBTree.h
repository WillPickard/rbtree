/***************************
 *
 *
 *@file RBTree.h
 *
 *
 *
 *
 * **************************/
#ifndef RBTREE_H
#define RBTREE_H
#include "TreeNode.h"
template <class T>
class RBTree{
	private:
		TreeNode<T> * root;
		int size;
		TreeNode<T> * tNiL;
	public:
		RBTree();
		
		TreeNode<T>* getRoot();
		TreeNode<T>* getNil();

		void setRoot(TreeNode<T> *);
		void setNil(TreeNode<T> *);
		void setSize(int);

		int getSize();		
		void RBinsert(T);
		TreeNode<T>* deleteLookUp(TreeNode<T>*, T key);
		bool RBdelete(T);
		void RBinorder(TreeNode<T> *);
		void RBlevelorder();

		void leftRotate(TreeNode<T> *);	
		void rightRotate(TreeNode<T> *);	
		void transplant(TreeNode<T> *, TreeNode<T> *);
		TreeNode<T>* treeMin(TreeNode<T> *);
		void insertFixup(TreeNode<T> *);
		void deleteFixup(TreeNode<T> *);	
};
/*
 *@file
 *	RBTree.cpp
 *
 */
#include <queue>
#include <cstddef>//null
template <class T>
RBTree<T>::RBTree():
	size(0)
{
	TreeNode<T>* tnil = new TreeNode<T>();
	tnil -> makeNil();
	tnil->setColor(BLACK);
	setNil(tnil);
	setRoot(tnil);

};

template <class T>
void RBTree<T>::setRoot(TreeNode<T> * node){
	TreeNode<T>* nil = getNil();
	node->setParent(nil);
	nil->setRight(node);
	nil->setLeft(node);
	root = node;
}

template <class T>
void RBTree<T>::setNil(TreeNode<T> * node){
  tNiL = node;
}

template <class T>
void RBTree<T>::setSize(int s){
	size = s;
}

template <class T>
int RBTree<T>::getSize(){
	return size;
}

template <class T>
TreeNode<T>* RBTree<T>::getRoot(){
	return root;
}

template <class T>
TreeNode<T>* RBTree<T>::getNil(){
  	return tNiL; 
}

template <class T>
void RBTree<T>::RBinsert(T key){
	TreeNode<T> * node = new TreeNode<T>(key);
	TreeNode<T> * yNode = getNil();
	TreeNode<T> * xNode = getRoot();
	TreeNode<T> * tNil = getNil();
	
	while(xNode != tNil){
		yNode = xNode;
		if(*node < *xNode){
			xNode = xNode->getLeft();
		}
		else{
			xNode = xNode->getRight();
		}
	} 
	node->setParent(yNode);
	if(yNode == tNil){
		setRoot(node);
	}
	else if(*node < *yNode){
		yNode->setLeft(node);
	}
	else{
		yNode->setRight(node);
	}
	
	node->setLeft(tNil);
	node->setRight(tNil);
	node->setColor(RED);
	insertFixup(node);
	size++;
}
template <class T>
TreeNode<T>* RBTree<T>::deleteLookUp(TreeNode<T> *node, T key){
//parse the tree to find the key
	TreeNode<T> *keyNode = new TreeNode<T>(key);
	TreeNode<T> *returnNode = node;
	TreeNode<T> *nil = getNil();
	while(returnNode != nil){
		if(*keyNode == *returnNode)
			return returnNode;
		else if(*keyNode < *returnNode)
			returnNode = returnNode -> getLeft();
		else
			returnNode = returnNode -> getRight();
	}
	return returnNode;
}
template <class T>
bool RBTree<T>::RBdelete(T key){
	TreeNode<T> *node = deleteLookUp(root, key);
	if(node == getNil()){
		return false;
	}
	unsigned char origColor = node->getColor();
	TreeNode<T> * xNode;
	TreeNode<T> * yNode = node;
	TreeNode<T> * root = getRoot();
	TreeNode<T> * tNil = getNil();
	if(*(node->getLeft()) == *tNil){
		xNode = node->getRight();
		transplant(node, xNode);
	}
	else if(*(node->getRight()) == *tNil){
		xNode = node->getLeft();
		transplant(node, xNode);
	}
	else{
		yNode = treeMin(node->getRight());
		xNode = yNode->getRight();	
	}
	return true;
}

template <class T>
void RBTree<T>::RBinorder(TreeNode<T> *node){
	if(!(node->getLeft())->isNil())
		RBinorder(node->getLeft());
	node->print();
	if(!(node->getRight())->isNil())
		RBinorder(node->getRight());

return;
}

template <class T>
void RBTree<T>::RBlevelorder(){
	std::queue<TreeNode<T>*> queue;

	if(root)
		queue.push(root);
	while(!queue.empty()){
		TreeNode<T> *node = queue.front();
		queue.pop();
		node->print();
		
		if(!(node->getLeft()->isNil()))
			queue.push(node->getLeft());
		if(!(node->getRight()->isNil()))
			queue.push(node->getRight());
	}
}


template <class T>
void RBTree<T>::leftRotate(TreeNode<T> * node){
	TreeNode<T> *yNode = node->getRight();
	node->setRight(yNode->getLeft());
	
	if(yNode->getLeft() != getNil()){
		yNode->getLeft()->setParent(node);
	}

	yNode->setParent(node->getParent());
	
	if(node->getParent() == getNil()){
		setRoot(yNode);
	}
	else if(*node == *(node->getParent()->getLeft())){
		node->getParent()->setLeft(yNode);
	} 
	else{
		node->getParent()->setRight(yNode);
	}
	yNode->setLeft(node);
	node->setParent(yNode);	
}

template <class T>
void RBTree<T>::rightRotate(TreeNode<T> * node){
	TreeNode<T> *yNode = node->getLeft();
	node->setLeft(yNode->getRight());
	
	if(*(yNode->getRight()) != *(getNil())){
		yNode->getRight()->setParent(node);
	}

	yNode->setParent(node->getParent());
	
	if(*(node->getParent()) == *(getNil())){
		setRoot(yNode);
	}
	else if(*node == *(node->getParent()->getLeft())){
		node->getParent()->setLeft(yNode);
	} 
	else{
		node->getParent()->setRight(yNode);
	}

	yNode->setRight(node);
	node->setParent(yNode);	
}

template <class T>
void RBTree<T>::transplant(TreeNode<T> * nodeU, TreeNode<T> * nodeV){
	if(*(nodeU->getParent()) == *(getNil())){
		setRoot(nodeV);
	}
	else if(*nodeU == *(nodeU->getParent()->getLeft())){
		nodeU->getParent()->setLeft(nodeV);
	}
	else{
		nodeU->getParent()->setRight(nodeV);
	}
	nodeV->setParent(nodeU->getParent());
}

template <class T>
TreeNode<T>* RBTree<T>::treeMin(TreeNode<T> * node){
	if(*(node->getLeft()) != *(getNil())){
		treeMin(node->getLeft());
	}
	else{
		return node;
	}
}

template <class T>
void RBTree<T>::insertFixup(TreeNode<T> * node){
	TreeNode<T> *nodeY;
	while(node->getParent()->getColor() == RED){
		if(*(node->getParent()) == *(node->getParent()->getParent()->getLeft())){
			nodeY = node->getParent()->getParent()->getRight();
			if(nodeY->getColor() == RED){
				node->getParent()->setColor(BLACK);
				nodeY->setColor(BLACK);
				node->getParent()->getParent()->setColor(RED);
				node = node->getParent()->getParent();
			}	
			else{
				if(*node == *(node->getParent()->getRight())){
					node = node->getParent();
					leftRotate(node);
				}
				node->getParent()->setColor(BLACK);
				node->getParent()->getParent()->setColor(RED);
				rightRotate(node->getParent()->getParent());
			}
		}
		else{
			nodeY = node->getParent()->getParent()->getLeft();
			if(nodeY->getColor() == RED){
				node->getParent()->setColor(BLACK);
				nodeY->setColor(BLACK);
				node->getParent()->getParent()->setColor(RED);
				node = node->getParent()->getParent();
			}	
			else{ 
				if(*node == *(node->getParent()->getLeft())){
					node = node->getParent();
					rightRotate(node);
				}
				node->getParent()->setColor(BLACK);
				node->getParent()->getParent()->setColor(RED);
				leftRotate(node->getParent()->getParent());
			}
		}
	}
	root->setColor(BLACK);
}

template <class T>
void RBTree<T>::deleteFixup(TreeNode<T> * node){
	TreeNode<T> *root = getRoot();
	while(*node!=*root && node->getColor()==BLACK){
		if(*node == *(node->getParent()->getLeft())){
			TreeNode<T> *nodeW = node->getParent()->getRight();
			if(nodeW->getColor() == RED){
				nodeW->setColor(BLACK);
				node->getParent()->setColor(RED);
				leftRotate(node->getParent());
				nodeW = node->getParent()->getRight();
			}
			else if(nodeW->getRight()->getColor() == nodeW->getLeft()->getColor() && nodeW->getLeft()->getColor()==BLACK){
				nodeW->setColor(RED);
				node = node->getParent();
			}
			else if(nodeW->getRight()->getColor() == BLACK){
				nodeW->getLeft()->setColor(BLACK);
				nodeW->setColor(RED);
				rightRotate(nodeW);
				nodeW = node->getParent()->getRight();
			}
			else{
				nodeW->setColor(node->getParent()->getColor());
				node->getParent()->setColor(BLACK);
				nodeW->getRight()->setColor(BLACK);
				leftRotate(node->getParent());
				node = root;
			}
		
		}
		else{
			TreeNode<T> *nodeW = node->getParent()->getLeft();
			if(nodeW->getColor() == RED){
				nodeW->setColor(BLACK);
				node->getParent()->setColor(RED);
				rightRotate(node->getParent());
				nodeW = node->getParent()->getLeft();
			}
			else if(nodeW->getLeft()->getColor() == nodeW->getRight()->getColor() && nodeW->getLeft()->getColor()==BLACK){
				nodeW->setColor(RED);
				node = node->getParent();
			}
			else if(nodeW->getLeft()->getColor() == BLACK){
				nodeW->getRight()->setColor(BLACK);
				nodeW->setColor(RED);
				leftRotate(nodeW);
				nodeW = node->getParent()->getLeft();
			}
			else{
				nodeW->setColor(node->getParent()->getColor());
				node->getParent()->setColor(BLACK);
				nodeW->getLeft()->setColor(BLACK);
				rightRotate(node->getParent());
				node = root;
			}	
		}
	}
	node->setColor(BLACK);
}
#endif
