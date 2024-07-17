#include <gtest/gtest.h>

#include "../nodes/node.hpp"
#include "../tries/trie.hpp"

TEST(SystemTest, TrieSanityCheck) {
    Trie<Node> trie;

    trie.insert("hello");

    EXPECT_TRUE(trie.contains("hello"));
    EXPECT_FALSE(trie.contains("hell"));

    EXPECT_TRUE(trie.is_prefix("hell"));
}