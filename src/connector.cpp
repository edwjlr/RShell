#include "../header/base.hpp"
#include "../header/connector.hpp"

Connector::Connector(Base * left, Base * right): leftChild(left), rightChild(right) {
	this->leftChild = left;
	this->rightChild = right;
}

// implement default constructor
Connector::Connector()
{
	leftChild = nullptr;
	rightChild = nullptr;
}