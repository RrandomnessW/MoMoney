#include <iostream>
#include "History.hpp"
#include "Transaction.hpp"
#include "History_Transaction_definitions.cpp"
#include "project4.hpp"
#include "project4.cpp"


#ifndef MARMOSET_TESTING
unsigned int Transaction::assigned_trans_id = 0;
int main() {
  /*Transaction t1{"grow" ,  12 , 10 , 2004 , true , 10 , 50 };
  Transaction t2{"grow" ,  13 , 10 , 2004 , false , 10 , 50 };

  std::cout << "Id 1: " << t1.get_trans_id() << std::endl;
  std::cout << "Id 2: " << t2.get_trans_id() << std::endl;

  if(t1<t2){
    std::cout << "This should be true" << std::endl;
  }*/

  History trans_history{};
  trans_history.read_history();

  std::cout << "[Starting history]:" << std::endl;
  trans_history.print();
  trans_history.sort_by_date();
  trans_history.sort_by_date();
  trans_history.sort_by_date();

  std::cout << "[Sorted          ]:" << std::endl;
  trans_history.print();

  trans_history.update_acb_cgl();
  trans_history.print();

  std::cout << "[CGL for 2018    ]: " << trans_history.compute_cgl(2018) << std::endl;
  std::cout << "[CGL for 2019    ]: " << trans_history.compute_cgl(2019) << std::endl;

  return 0;
}
#endif
