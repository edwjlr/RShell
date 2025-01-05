#include "../header/connector.hpp"
#include "../header/and.hpp"


And::And(Base * left, Base * right) : Connector(left, right) { }

bool And::executed() {
	if (leftChild->executed() && rightChild->executed()) {
		return true;
	}
	return false;
}
