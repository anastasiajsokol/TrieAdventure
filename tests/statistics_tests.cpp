#include <gtest/gtest.h>

#include "../nodes/statistics.hpp"
#include "../tries/statisticstrie.hpp"

TEST(StatisticsTest, TrieSanityCheck) {
    StatisticsTrie<StatisticsNode> trie;

    trie.insert("hello");

    EXPECT_TRUE(trie.contains("hello"));
    EXPECT_FALSE(trie.contains("hell"));

    EXPECT_TRUE(trie.is_prefix("hell"));
}

TEST(StatisticsTest, StatisticsSanityCheck) {
    StatisticsTrie<StatisticsNode> trie;

    EXPECT_EQ(trie.descendants(), 0);
    EXPECT_EQ(trie.size(), 0);

    trie.insert("hello");

    EXPECT_EQ(trie.descendants(), 5);
    EXPECT_EQ(trie.size(), 1);

    trie.insert("hell");
    
    EXPECT_EQ(trie.descendants(), 5);
    EXPECT_EQ(trie.size(), 2);
}