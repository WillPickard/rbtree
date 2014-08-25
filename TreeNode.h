/******************
 *
 *@file
 *	 TreeNode.h
 *  
 * This file is the header file for a tree node
 * The tree node is managed by the t3Solver
 *
 * *****************/
#ifndef TREENODE_H
#define TREENODE_H
#include <iostream>
#ifndef COLORS
#define COLORS
const unsigned char RED = 1;
const unsigned char BLACK = 2; 
#endif 
template <class T>
class TreeNode{
   private:
	bool nil;
	TreeNode * parent;
	unsigned char color;
	TreeNode * left;
	TreeNode * right;
	T data; //template data
   public:
	TreeNode():
		nil(false)
	{};
	TreeNode(T);
	
	void setParent(TreeNode *);
	void addChild(TreeNode *);
	void setLeft(TreeNode *);
	void setColor(unsigned char);
	void setRight(TreeNode *);
	void setData(T);
	
	void makeNil();
	bool isNil();

	unsigned char getColor() const;
	TreeNode * getParent() const;
	TreeNode * getLeft() const;
	TreeNode * getRight() const;
	T getData() const;

	void print() const;
	
	inline bool operator<(TreeNode<T>& B){
		T dataA = getData();
		T dataB = B.getData();
		return dataA < dataB;
	}
	inline bool operator<=(TreeNode<T>& B){
		T dataA = getData();
		T dataB = B.getData();
		return dataA <= dataB;
	}
	inline bool operator>(TreeNode<T>& B){
		T dataA = getData();
		T dataB = B.getData();
		return dataA > dataB;
	}
	inline bool operator>=(TreeNode<T>& B){
		T dataA = getData();
		T dataB = B.getData();
		return dataA >= dataB;
	}
	inline bool operator==(TreeNode<T>& B){
		T dataA = getData();
		T dataB = B.getData();
		return dataA == dataB;
	}
	inline bool operator!=(TreeNode<T>& B){
		T dataA = getData();
		T dataB = B.getData();
		return dataA != dataB;
	}
};
/*
 *
 *#file
 *	TreeNode.cpp
 *
 *
 *This file implements TreeNode.h
 *
 */

#include <stdio.h>
#include <string>
#include <iostream>
#include<vector>
template<class T>
TreeNode<T>::TreeNode(T d):
	data(d),
	nil(false),
	parent(NULL),
	color(RED),
	left(NULL),
	right(NULL)	
{};

template<class T>
void TreeNode<T>::setParent(TreeNode * n){
  parent = n;
}

template<class T>
void TreeNode<T>::addChild(TreeNode *c){
  T myData = getData();
  T childData = c->getData();
  if(childData < myData)
	setLeft(c);
  else
	setRight(c);
}
template<class T>
void TreeNode<T>::setData(T d){
  data = d;
}
template<class T>
void TreeNode<T>::setLeft(TreeNode * n){
  left = n;
}
template<class T>
void TreeNode<T>::setRight(TreeNode * n){
  right = n;
}
template<class T>
void TreeNode<T>::setColor(unsigned char c){
  color = c;
}

template<class T>
void TreeNode<T>::makeNil(){
	nil = true;
}

template<class T>
bool TreeNode<T>::isNil(){
	return nil;
}
template<class T>
void TreeNode<T>::print() const{
	std::string col;
	if(color == RED) col = "R";
	else col = "B";

	std::cout << data << "(" << col << ")" << std::endl;
}

template<class T>
unsigned char TreeNode<T>::getColor() const{
  return color;
}

template<class T>
TreeNode<T> * TreeNode<T>::getParent() const{
  return parent;
}

template<class T>
TreeNode<T> * TreeNode<T>::getLeft() const{
  return left;
}
template<class T>
TreeNode<T> * TreeNode<T>::getRight() const{
  return right;
}
template<class T>
T TreeNode<T>::getData() const{
  return data;
}
#endif
