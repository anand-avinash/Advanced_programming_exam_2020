# Binary Search Tree

In this project, I have implemented a templated binary search tree (BST) and associated member functions with the help of an iterator class. For the nodes of BST, I used a `node` struct. The `node` struct was defined outside the `bst` class as they don't share the template.

To compile the code, simply run the `make` command.

## struct `node`

In my implementation, `node` struct has four members:

1. `node_value`  
   It is the local identifier of the node. I used `node` struct by templating it with `std::pair<const key_type, value_type>`. In a BST, there may exist only a unique node of a given key while this is not true for the data associated with key.
2. `parent_node`  
   It is a pointer to the `node` struct intended to keep the node's association with other nodes.
3. `left_node`  
   It is a `unique_ptr` to the `node` struct to serve as the left branch of the node.
4. `right_node`  
   It is a `unique_ptr` to the `node` struct to serve as the right branch of the node.

By declaring `left_node` and `right_node` as `unique_ptr`, I ensured that at an instance, a given node can only be a left branch or a right branch of a unique parent node. On the other hand, declaring parent node as raw pointer highlights that it can be a parent to more than one node at an instance.

## class `bst`

`bst` class has one private data type, the `head_node` which is the `unique_ptr` to head/root node of the BST. `bst` class has multiple public members, namely

1. `iterator begin()`  
   `const_iterator begin()`  
   `const_iterator cbegin()`  
   They return the iterator to the left-most node of the BST. The search for the left-most node was performed by traversing through the left node of each BST node starting from the head node until a `nullptr` was encountered.
2. `iterator end()`  
   `const_iterator end()`  
   `const_iterator cend()`  
   They return the iterator to the right-most node of the BST. The search for the right-most node was performed by traversing through the right node of each BST node starting from the head node until a `nullptr` was encountered. Note that they cannot simply return an iterator to `nullptr` as it is possible for many other nodes to have empty right nodes while the `end()` iterators can point to only one.
3. `std::pair<iterator, bool> insert(const pair_type& x)`  
   `std::pair<iterator, bool> insert(pair_type&& x)`  
   These functions insert a specified node to the bst. The insertion happens only if there is no node in the bst having same provided key. In case, a node with given key exist, the corresponding data is replaced with the provided one. These functions return an iterator to the inserted node and `True` if the node insertion is successful. Otherwise, they return an iterator to the node of given key and `False` parameter. The insertion takes help of the `std::less<>` comparator to compare the given key with left and right node to traverse through the BST until it finds a right spot for insertion. Both insert functions are implemented using a private member function `std::pair<iterator, bool> insert_function(pair_type&& x)` to avoid code redundancy.
4. `iterator find(const T_key& x)`  
   `const_iterator find(const T_key& x)`  
   Both of these member functions return an iterator to the node containing the given key. They both work in same manner as `insert()` functions and use another private member function `iterator find_function(const T_key& x)` to avoid code redundancy.
5. `clear()`  
   This function clears the BST. As BST doesn't acquires any heap resources, it is enough to just reset its head node which is a `unique_ptr`.
6. **Put-to operator**  
   The idea was to use range-based for loop but it didn't worked due as I couldn't implement `!=` operator correctly.

## class `iterator`

`iterator` class was declared in `bst` class. Here I implemented the overloading of reference, dereference, pre-increment and post-increment operators. I also tried to implement overloading of less-than, greater-than, equal-to and not-equal-to operators unsuccessfully.
