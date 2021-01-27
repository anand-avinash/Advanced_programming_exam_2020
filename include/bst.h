#ifndef BST_H
#define BST_H

#include <iostream>
#include <memory>
#include <utility>
#include <functional>

// Node definition
template<typename T_node>
struct node{

  // We'll use std::pair<T_key, T_value> as T_node template
  // So node_value.first gives the key of the node and node_value.second will give the value stored by the node
  T_node node_value;

  node *parent_node = nullptr;
  std::unique_ptr<node> left_node, right_node;

  // default ctor
  node() = default;

  // cutom ctor
  node(const T_node &val)
  : node_value{val}, left_node{nullptr}, right_node{nullptr}, parent_node{nullptr}
  {}

  // default dtor
  ~node() noexcept = default;

  void print_node(){
  std::cout << "(key, value) = (" << this->node_value.first << ", " << this->node_value.second << ")" << std::endl;
}//print_node
};

// Binary search tree
template<typename T_key, typename T_value, typename T_compare = std::less<T_key>> class bst{

  public:

    T_compare compare;

    using pair_type = std::pair<const T_key, T_value>;
    using node_type = node<pair_type>;

    template<typename node_type> class _iterator;
    using iterator = _iterator<node_type>;
    using const_iterator = _iterator<const node_type>;

    // Default ctor
    bst() = default;

    // ctor when key and value of the head_node is supplied as pair_type
    explicit bst(pair_type new_node)
    : head_node {new node_type {new_node}}
    {}

    // ctor when key and value of the head_node is supplied seperately
    bst(T_key key, T_value value)
    : head_node {new node_type {pair_type(key, value)}}
    {}

    // default dtor
    ~bst() = default;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    // iterator end() noexcept{
    //   return iterator{nullptr};
    // }//iterator end

    // const_iterator end() const noexcept{
    //   return const_iterator{nullptr};
    // }//const_iterator end

    // const_iterator cend() const noexcept{
    //   return const_iterator{nullptr};
    // }//cend
    
    std::pair<iterator, bool> insert(const pair_type& x){
      return insert_function(x);
    }//insert_reference

    std::pair<iterator, bool> insert(pair_type&& x){
      return insert_function(std::move(x));
    }//insert_fwd_reference

    iterator find(const T_key& x){
      return find_function(x);
    }//find

    const_iterator find(const T_key& x) const{
      const_iterator iter {find_function(x)};
      return iter;
    }//const_find

    // Not implemented yet
    void balance();

    // We are not acquiring any resources in heap, so it is enough to reset the head node to clear the bst
    void clear() noexcept {
      head_node.reset();
      std::cout << "Cleared the BST" << std::endl;
    }//clear


  friend std::ostream& operator<<(std::ostream& os, const bst& x){

    if(x.head_node.get() == nullptr){
      std::cout << "The BST is empty" << std::endl;
      return os;
    }//for

    std::cout << "(key, value) --> ";

    for(auto i = x.begin(); i != x.end(); ++i){
      std::cout << "(" << i->node_value.first << ", " << i->node_value.second << ") --> ";
    }//for

    auto i = x.end();
    std::cout << "(" << i->node_value.first << ", " << i->node_value.second << ")" << std::endl;

    return os;
  }//ostream_overloading


  private:
  
    // Creating the unique pointer for head node with std::pair<key type, value type> as template
    std::unique_ptr<node_type> head_node;

    std::pair<iterator, bool> insert_function(pair_type&& x);
    iterator find_function(const T_key& x);

};


template<typename T_key, typename T_value, typename T_compare>
template<typename node_type>
class bst<T_key, T_value, T_compare>::_iterator{

  public:

    node_type* current;

    using value_type = node_type;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using reference = value_type&;
    using pointer = value_type*;

    // default ctor
    _iterator() = default;

    // custom ctor
    explicit _iterator(node_type* p) : current{p} {}

    // default ctor
    ~_iterator() = default;

    reference operator*() const { return current->value; }
    pointer operator->() const { return &**this; }

    // pre-increment operator
    _iterator &operator++() {
      if(current->right_node){
        
        current = current->right_node.get();
        while(current->left_node){
          current = current->left_node.get();
        }//while

      } else{
        
        if(current->parent_node==nullptr){
          current=nullptr;
          return *this;
        }//if
        
        while(current->parent_node->node_value.first != current->node_value.first){
          current = current->parent_node;
          if(!current->parent_node){
            current=nullptr;
            return *this;
          }
        }//while
        
      }//if_else
      return *this;
    }//pre-increment

    // post-increment operator
    _iterator operator++(int){
      _iterator tmp {*this};
      ++(*this);
      return tmp;
    }//post_increment

    friend bool operator<(iterator& a, iterator& b){
      return a.current.first < b.current.first;
    }//operator<

    friend bool operator>(iterator& a, iterator& b){
      return b.current.first < a.current.first;
    }//operator>

    friend bool operator==(_iterator& a, _iterator& b){
      return !(a < b) && !(a > b);
    }//operator==

    friend bool operator!=(_iterator& a, _iterator& b){
      return !(a == b);
    }//operator!=

    // friend bool operator!=(_iterator& a, _iterator& b){
    //   return a.current->node_value.first != b.current->node_value.first;
    // }//operator!=    

};

#endif
