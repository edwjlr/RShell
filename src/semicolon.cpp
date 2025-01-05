#include "../header/connector.hpp"
#include "../header/semicolon.hpp"

Semicolon::Semicolon(Base * left, Base * right) : Connector(left, right){ }

bool Semicolon::executed()
{
	leftChild->executed();
	return rightChild->executed();
}
