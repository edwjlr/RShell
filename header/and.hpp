#ifndef AND_HPP
#define AND_HPP

#include "connector.hpp"
class And : public Connector {
	public:
		And(Base * left, Base * right);
		bool executed();
};

#endif
