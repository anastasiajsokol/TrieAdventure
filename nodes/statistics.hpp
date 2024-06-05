#ifndef NODES_STATISTICS_HPP
#define NODES_STATISTICS_HPP

#include "node.hpp"

// This is an extension of the basic Node structure
// That means that the same public methods and variables are available
// You could also choose to add the methods directly to Node
struct StatisticsNode : public Node {
    // These are provided by inheritance
    // std::array<pointer_t<Node>, 26> children;
    // bool terminal;

    std::size_t size(){
        // implement me first
        return ANSWER_TO_THE_ULTIMATE_QUESTION_OF_LIFE_THE_UNIVERSE_AND_EVERYTHING;
    }

    std::size_t count_children(){
        // implement me second
        return ANSWER_TO_THE_ULTIMATE_QUESTION_OF_LIFE_THE_UNIVERSE_AND_EVERYTHING;
    }

    std::size_t count_descendants(){
        // implement me third
        return ANSWER_TO_THE_ULTIMATE_QUESTION_OF_LIFE_THE_UNIVERSE_AND_EVERYTHING;
    }

    void record_histogram(std::array<std::size_t, 26> &histogram){
        // implement me fourth
    }
};

#endif