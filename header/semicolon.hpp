#ifndef SEMICOLON_H
#define SEMICOLON_H

#include "connector.hpp"

class Semicolon : public Connector {
	public:
		Semicolon(Base * left, Base * right);
		bool executed();
};

#endif
