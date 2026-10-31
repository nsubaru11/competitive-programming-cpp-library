#include "lib/ds/tree/Treap.hpp"

int main() {
	Treap* t = new Treap();
	for (int i = 0; i < 10; i++) {
		t->add(i);
	}
	delete t; // free -> delete に修正
}
