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
						return rotate_r();
					}
				} else {
					right = right->add(k);
					if (priority < right->priority) {
						return rotate_r();
					}
				}
			} else if (key > k) {
				if (left == nullptr) {
					left = new Node(k);
					if (priority < left->priority) {
						return rotate_l();
					}
				} else {
					left = left->add(k);
					if (priority < left->priority) {
						return rotate_l();
					}
				}
			}
			return this;
		}

		Node* rotate_l() {
			Node* new_root = this->left;
			this->left = new_root->right;
			new_root->right = this;
			return new_root;
		}

		Node* rotate_r() {
			Node* new_root = this->right;
			this->right = new_root->left;
			new_root->left = this;
			return new_root;
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
