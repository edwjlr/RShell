#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP

#include "base.hpp"

// Abstract class inherit Base, derive class will implement executed
class Connector : public Base
{
	public:
		Base * leftChild;
		Base * rightChild;
		Connector();
		Connector(Base * left, Base * right);

};

#endif
