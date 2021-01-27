#include "bst.h"
#include "bst_functions.h"
#include <string>
#include <cstdlib> // for RNG

void print_insert(bool iter){

  if(iter){
    std::cout << "Inserted the node" << std::endl;
  } else{
    std::cout << "Node with the given key already exist" <<std::endl;
  }//if_else

}//print_insert

int main(){

  std::cout << "Testing the BST with `std::pair<int, int>` node type:\n" << std::endl;

  bst<int, int> tree;
  
  std::pair<int, int>  pair(5, 7);
  auto iter_pair = tree.insert(pair);
  print_insert(iter_pair.second);
  // std::cout << tree; // buggy
  iter_pair = tree.insert(std::make_pair(2,3));
  print_insert(iter_pair.second);
  iter_pair = tree.insert(std::make_pair(1,4));
  print_insert(iter_pair.second);
  iter_pair = tree.insert(std::make_pair(1,6));
  print_insert(iter_pair.second);

  auto iter = tree.begin();
  std::cout << "The first node of BST is"; iter.current->print_node();
  
  iter = tree.end();
  std::cout << "The last node of BST is"; iter.current->print_node();

  int num = 2;
  tree.find(num);
  tree.find(0);
  tree.find(1);
  
  tree.clear();

  std::cout << "\n\nTesting the BST with `std::pair<std::string, std::string>` node type:\n" << std::endl;

  bst<std::string, std::string> str_tree;
  
  std::pair<std::string, std::string>  str_pair("My", "name");
  auto iter_str_pair = str_tree.insert(str_pair);
  print_insert(iter_str_pair.second);
  iter_str_pair = str_tree.insert(std::make_pair("Your","game"));
  print_insert(iter_str_pair.second);
  iter_str_pair = str_tree.insert(std::make_pair("haha","hehe"));
  print_insert(iter_str_pair.second);
  iter_str_pair = str_tree.insert(std::make_pair("rofl","lol"));
  print_insert(iter_str_pair.second);

  auto iter_str = str_tree.begin();
  std::cout << "The first node of BST is"; iter_str.current->print_node();
  
  iter_str = str_tree.end();
  std::cout << "The last node of BST is"; iter_str.current->print_node();

  std::string str = "haha";
  str_tree.find(str);

  str_tree.find("My");
  str_tree.find("uwu");
  
  str_tree.clear();


  std::cout << "\n\nNow testing the pre-increment operator:\n" << std::endl;

  bst<double, double> double_tree;

  #define N 10

  srand48(time(0));
  for(int i=0; i<N; ++i){
    double_tree.insert(std::make_pair(drand48(), drand48()));
  }//for

  auto double_iter = double_tree.begin();
  // double_iter++;
  for(int i=0; i<N; ++i){
    (++double_iter).current->print_node();
  }//for


  std::cout << "\n\nNow testing the post-increment operator:\n" << std::endl;

  double_tree.clear();

  srand48(time(0));
  for(int i=0; i<N; ++i){
    double_tree.insert(std::make_pair(drand48(), drand48()));
  }//for

  double_iter = double_tree.begin();
  // double_iter++;
  for(int i=0; i<N; ++i){
    double_iter++.current->print_node();
  }//for


}//main
