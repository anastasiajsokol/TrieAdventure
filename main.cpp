#include <iostream>

#include "nodes/node.hpp"
#include "trie.hpp"

int main(){
	std::cout << "You have successfully built Trie Adventure!\n";

	Trie<Node> trie;

	trie.insert("hello");

	std::cout << "contains hello: " << trie.contains("hello") << "\ncontains hell: " << trie.contains("hell") << "\nprefix hell: " << trie.is_prefix("hell") << '\n';

	return EXIT_SUCCESS;
}

