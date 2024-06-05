#ifndef STATISTICSTRIE_HPP
#define STATISTICSTRIE_HPP

#include "nodes/utility.hpp"

// Generic trie class implementation plus realtime statistics functionality
// See documation for required statistics node interface
template <typename Node>
class StatisticsTrie {
    private:
        Node root;

    public:
        /** defualt trie functions **/

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

        /** statistics trie functions **/

        std::size_t size(){
            return root.size();
        }

        std::size_t descendants(){
            return root.descendants();
        }
};

#endif