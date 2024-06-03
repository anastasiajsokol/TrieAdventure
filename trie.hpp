#ifndef TRIE_H
#define TRIE_H

#include "nodes/utility.hpp"

// Generic trie class implementation
// See documation for required node interface
template <typename Node>
class Trie {
    private:
        Node root;

    public:
        void insert(prefix_t word){
            // get a prefix, creating new nodes as needed, then mark complete
            root.getprefix(word, true).value()->mark_complete();
        }

        bool contains(prefix_t word){
            if(const auto node = root.getprefix(word)){
                // if the prefix exists, check if it is complete
                return node.value()->is_complete();
            }
            // otherwise false
            return false;
        }

        bool is_prefix(prefix_t prefix){
            // check if the prefix exists
            return root.getprefix(prefix).has_value();
        }
};

#endif