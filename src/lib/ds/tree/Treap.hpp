#pragma once

#include <cstdlib>

class Treap {
	class Node {
	public:
		int key, priority;
		Node *left, *right;
		int arr[];

		Node(int k) : key(k), priority(rand()), left(nullptr), right(nullptr) {}

		Node* add(int k) {
			if (key < k) {
				if (right == nullptr) {
					right = new Node(k);
					if (priority < right->priority) {
						return rotateR();
					}
				} else {
					right = right->add(k);
					if (priority < right->priority) {
						return rotateR();
					}
				}
			} else if (key > k) {
				if (left == nullptr) {
					left = new Node(k);
					if (priority < left->priority) {
						return rotateL();
					}
				} else {
					left = left->add(k);
					if (priority < left->priority) {
						return rotateL();
					}
				}
			}
			return this;
		}

		Node* rotateL() {
			Node* newRoot = this->left;
			this->left = newRoot->right;
			newRoot->right = this;
			return newRoot;
		}

		Node* rotateR() {
			Node* newRoot = this->right;
			this->right = newRoot->left;
			newRoot->left = this;
			return newRoot;
		}
	};

	int size;
	Node* root;

public:
	Treap() : size(0), root(nullptr) {}

	void add(int key) {
		if (root == nullptr) {
			root = new Node(key);
			size++;
			return;
		}
		root = root->add(key);
	}
};
