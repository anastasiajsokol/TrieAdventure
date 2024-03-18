#include "random220.h"
#include "trie.h"

#include "liltrie.h"

int main()
{
	trie t;
#if defined(TEST_NODE_FUNCTIONS) || 0
	std::vector<std::string> v = {"intergossip", "homovanillin", "restiaceous", "misguidingly", "travelled" };
	test_node_functions<trie>( t, v );
#endif
	return 0;
}

