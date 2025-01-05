#ifndef OR_HPP
#define OR_HPP

#include "connector.hpp"

class Or : public Connector {
        public:
                Or(Base * left, Base * right);
		bool executed();
};

#endif
