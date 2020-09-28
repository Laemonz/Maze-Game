#include "Link.h"

Link::Link() {
	below = nullptr;
}

Link::~Link() {
	//dtor
}

Link* Link::getBelow() {
	return below;
}

void Link::setBelow(Link* myLink) {
	below = myLink;
}

TYPE Link::getContents() {
	return contents;
}

void Link::setContents(TYPE myContents) {
	contents = myContents;
}
