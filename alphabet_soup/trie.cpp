#include <cassert>
#include "trie.hpp"

#ifdef assert
//We undefined this macro to not shadow our implementation of assert.
#undef assert
#endif

/**
 * @brief Check an assertion.
 * In Debug mode, if the assertion is not met, a segfault is generated.
 * @param assertion
 */
inline void assert(bool assertion)
{
#ifndef NDEBUG
    (void)((assertion) || (__assert ("Assert violation!", __FILE__, __LINE__),0));
#endif
}


TrieNode::TrieNode ()
{
    //TODO
    //Hint: Do you need to do something?
};

TrieNode::Ref TrieNode::create()
{
    return std::make_shared<TrieNode>();
}

bool
TrieNode::has(char k) const
{
    //TODO
    if (children_.find(k) == children_.end()) return false;
    return true;
    //
}

TrieNode::Ref
TrieNode::child(char k) const
{
    assert(has(k));
    TrieNode::Ref ret_v;
    //TODO
    ret_v = children_.find(k)->second;
    //
    return ret_v;
}

std::string const&
TrieNode::value() const
{
    return value_;
}

const std::map<char, TrieNode::Ref> &TrieNode::children() const
{
    return children_;
}

void
TrieNode::set_value(std::string const& new_v)
{
    value_ = new_v;
}

void
TrieNode::insert(char k, Ref node)
{
    //TODO
    children_.emplace(k, node);
    //
}

Trie::Trie()
{
    //TODO
    //Hint: Do you need to do something?
}

Trie::Ref Trie::create()
{
    return std::make_shared<Trie>();
}

TrieNode::Ref Trie::root() const
{
    //TODO
    return nullptr;
    //
}

bool
Trie::has(std::string const& k) const
{
    bool found = false;
    TrieNode::Ref auxNode;
    //TODO
    //Remember: The Trie can have a prefix==k but does not store the key k.
    auxNode = find_node(k);
    found = auxNode != nullptr && auxNode->value() == k;
    
    //
    return found;
}

std::vector<std::string>
Trie::keys(std::string const& pref) const
{
    std::vector<std::string> keys;
    //TODO
    auto node = find_node(pref);
    if (node != nullptr) preorder_traversal(node, keys);
    //
    return keys;
}


void
Trie::insert(std::string const& k)
{
    TrieNode::Ref auxNode;
    //TODO
    if (root_ == nullptr)
    {
        root_ = TrieNode::create();
    }
    auxNode = root_;
    for (size_t i = 0; i < k.size(); i++)
    {
        
        if (auxNode->has(k[i]))
        {
            auxNode = auxNode->child(k[i]);

        }else{

            auto newNode = TrieNode::create();
            auxNode->insert(k[i], newNode);
            auxNode = newNode;
        }
        
    }

    auxNode->set_value(k);

    //
    assert(has(k));
}

TrieNode::Ref
Trie::find_node(std::string const& pref) const
{
    TrieNode::Ref auxNode;
    unsigned int i;

    //TODO
    auxNode = root_;
    i = 0;
    while ( i < pref.size() and auxNode != nullptr)
    {
        if (auxNode->has(pref[i]))
        {
            auxNode = auxNode->child(pref[i]);
            i++;

        }else{

            auxNode = nullptr;
        }

    }

    //
    return auxNode;
}

void
Trie::preorder_traversal(TrieNode::Ref const& node,
                         std::vector<std::string> & keys) const
{
    //TODO
    
    if (node->value() != "") keys.push_back(node->value());

    for (std::map<char, std::shared_ptr<TrieNode>>::const_iterator i = node->children().begin(); i != node->children().end(); i++)
    {
        preorder_traversal(i->second, keys);
    }


    //
}
