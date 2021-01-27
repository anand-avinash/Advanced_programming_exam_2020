#include "bst.h"

// begin
template <typename T_key, typename T_value, typename T_compare>
typename bst<T_key, T_value, T_compare>::iterator
bst<T_key, T_value, T_compare>::begin() noexcept{

  if(!head_node){
    return iterator{nullptr};
  }//if
   
  node_type* temp = head_node.get();
  while(temp->left_node){
    temp = temp->left_node.get();
  }//while

  return iterator{temp};
}//begin

// const cbegin
template <typename T_key, typename T_value, typename T_compare>
typename bst<T_key, T_value, T_compare>::const_iterator
bst<T_key, T_value, T_compare>::cbegin() const noexcept{
  if (!head_node){
    return const_iterator{nullptr};
  }//if

  node_type* temp = head_node.get();
  while(temp->left_node){
    temp = temp->left_node.get();
  }//while

  return const_iterator{temp};
}//cbegin

// const begin
template <typename T_key, typename T_value, typename T_compare>
typename bst<T_key, T_value, T_compare>::const_iterator
bst<T_key, T_value, T_compare>::begin() const noexcept{
  
  // Note that begin() returns iterator or const_iterator as per the overloading while cbegin returns only const_iterator. So `const_iterator begin()` is same as `const_iterator cbegin()`
  return cbegin();

}//const_begin

template <typename T_key, typename T_value, typename T_compare>
typename bst<T_key, T_value, T_compare>::iterator
bst<T_key, T_value, T_compare>::end() noexcept{

  if(!head_node){
    return iterator{nullptr};
  }//if

  node_type* temp = head_node.get();
  while(temp->right_node){
    temp = temp->right_node.get();
  }//while

  return iterator{temp};
}//end

// const cend
template <typename T_key, typename T_value, typename T_compare>
typename bst<T_key, T_value, T_compare>::const_iterator
bst<T_key, T_value, T_compare>::cend() const noexcept{
  if (!head_node){
    return const_iterator{nullptr};
  }//if

  node_type* temp = head_node.get();
  while(temp->right_node){
    temp = temp->right_node.get();
  }//while

  return const_iterator{temp};
}//cend

// const end
template <typename T_key, typename T_value, typename T_compare>
typename bst<T_key, T_value, T_compare>::const_iterator
bst<T_key, T_value, T_compare>::end() const noexcept{
  
  return cend();
}//const_end

template <typename T_key, typename T_value, typename T_compare>
std::pair<typename bst<T_key, T_value, T_compare>::iterator, bool>
bst<T_key, T_value, T_compare>::insert_function(bst<T_key, T_value, T_compare>::pair_type&& x){

  // x is a pair, not a node. So we should create a node from it by calling a ctor
  // node_type* temp {new node_type{x}};
  // That's why you see `foo.reset(new node_type{x})`

  node_type *temp = head_node.get();

  while(temp){
    
    if(compare(x.first, temp->node_value.first)){

      if(temp->left_node){
        temp = temp->left_node.get();
      } else{
        temp->left_node.reset(new node_type{x});
        iterator iter {temp->left_node.get()};
        return std::make_pair(iter, true);
      }

    } else if(compare(temp->node_value.first, x.first)){

      if(temp->right_node){
        temp = temp->right_node.get();
      } else{
        temp->right_node.reset(new node_type{x});
        iterator iter {temp->right_node.get()};
        return std::make_pair(iter, true);
      }

    } else{

      // When key of x is same as the key of temp, simply replace temp's data with x's data (second parameter of std::pair)
      temp->node_value.second = x.second;
      iterator iter {temp};
      return std::make_pair(iter, false);

    }//if_elif_else

  }//while

  // If head_node is empty
  head_node.reset(new node_type{x});
  iterator iter {head_node.get()};
  return std::make_pair(iter, true);

}//insert_function

// This is similar to the insert_function
template <typename T_key, typename T_value, typename T_compare>
typename bst<T_key, T_value, T_compare>::iterator
bst<T_key, T_value, T_compare>::find_function(const T_key& x){

  node_type *temp = head_node.get();

  while(temp){
    
    if(compare(x, temp->node_value.first)){

      if(temp->left_node){
        temp = temp->left_node.get();
      } else{
        std::cout << "Couldn't find node with key " << x << std::endl;
        return end();
      }//if_elif_if

    } else if(compare(temp->node_value.first, x)){

      if(temp->right_node){
        temp = temp->right_node.get();
      } else{
        std::cout << "Couldn't find node with key " << x << std::endl;
        return end();
      }//if_elif_if

    } else{

      iterator iter {temp};
      std::cout << "Found the node with key " << x << ": (key, value) = (" << iter.current->node_value.first << ", " << iter.current->node_value.second << ")" << std::endl;
      return iter;

    }//if_elif_else

  }//while

  // If head_node is empty
  return end();

}//insert_function

// template <typename T_key, typename T_value, typename T_compare>
// void bst<T_key, T_value, T_compare>::balance(){

//   for(auto i=begin(); i!=end(); ++i){
//     TODO;
//   }
// }//balance
