#include "../header/connector.hpp"
#include "../header/or.hpp"

Or::Or(Base * left, Base * right) : Connector(left, right) { }

bool Or::executed() {
	if (leftChild->executed() || rightChild->executed()) {
		return true;
	}
	return false;
}
