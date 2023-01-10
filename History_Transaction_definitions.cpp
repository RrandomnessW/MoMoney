#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

//class Transaction;
//class History;

/*
struct
*/

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 1
//
Transaction::Transaction( std::string ticker_symbol,  unsigned int day_date,  
        unsigned int month_date,  unsigned year_date, 
        bool buy_sell_trans,  unsigned int number_shares,  
        double trans_amount ) :
        symbol { ticker_symbol }, 
        day { day_date },
        month { month_date },
        year { year_date },
        trans_type {},
        shares { number_shares },
        amount { trans_amount },
        trans_id { assigned_trans_id },
        p_next { nullptr },
        acb {},
        acb_per_share {},
        share_balance {},
        cgl {}
        {
          //trans_type   buy_sell_trans -> value is buy or sell 0-false. 1-true
          if(buy_sell_trans){
            trans_type = "Buy";
          }else{
            trans_type = "Sell";
          }
          //trans_id - Unique transaction identifier for every transaction ??
          ++assigned_trans_id;
          //initialize the pointer so that there are no floating pointers so that when we delete the memory located at the pointer, we can access it properly
        }


// Destructor
// TASK 1
//
//deallocate dynamic memory -> deallocate pointers
//delete - deallocates memory at the given address
//deallocates the object at p_next which will then have to deallocate the object at it's p_next because that would e its destructor
Transaction::~Transaction(){
  
  delete this->p_next; 
  this->p_next = nullptr;
}

// Overloaded < operator.
// TASK 2
//
bool Transaction::operator<( Transaction const &other ){
  //comparing Transaction, based on which transaction occured first chronologically.
  //return treu if and only if transaction date for left operand occurs prior to the transaction date of the right operand
  //if equal if and only if the transaction id of the left operand is greater than th transaction id of the right operand
  //*p_next stores address of the next transaction in the linked-list
  //http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html

  //initizlizing then assigning causes memory corruption or memory errors. Initialize with {}. 
  //don't do Transaction left = *this. because it is initializing and obejct w/o a thing
  //review this initiazlizing and assigning issue!!!
  
  //Transaction left{*this};
  if( this->get_year() < other.get_year() ) {
    return true;
  }
  else if( this->get_year() == other.get_year() && this->get_month() < other.get_month() ){
    return true;
  }
  else if( this->get_year() == other.get_year() && this->get_month() == other.get_month() && this->get_day() < other.get_day() ){
    return true;
  }
  else if( this->get_year() == other.get_year() && this->get_month() == other.get_month() && this->get_day() == other.get_day() ){
    
    if( this->get_trans_id() > other.get_trans_id() ){
      return true;
    }
  }
  
  return false;
}

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK 3
//
History::History() {

  p_head = nullptr;
}

// Destructor
// TASK 3
//
History::~History() {

  delete p_head;
  p_head = nullptr;
}


// read_history(...): Read the transaction history from file.
// TASK 4
//
void History::read_history ( ) {
  /*Reads the transaction history from the input file (transaction_history.txt) and creates the linked-list.
Helper functions for reading the input file are provided in the project4.hpp/project4.cpp files. See section on
Helper Functions - File Reading for details on provided helper functions.
This function calls the insert(...) function to add the new Transaction to the linked-list. The Transactions
are to be added to the linked-list in the same order that they are read from the input file.
The transactions in the input file are not necessarily in any sorted order. Refer to the provided sample
transaction_history.txt for an example of an input file.
To be defined by the student.
  */
  // p_head = address of first node -> that remembers the next node and the next and the next -> first initialized as empty (nullptr)
  ece150::open_file();

  while ( ece150::next_trans_entry() ) {

    insert( new Transaction { ece150::get_trans_symbol(), ece150::get_trans_day(),  
        ece150::get_trans_month(),  ece150::get_trans_year() , 
        ece150::get_trans_type(), ece150::get_trans_shares(),  
        ece150::get_trans_amount()} );
  } 
  ece150::close_file();
}

// insert(...): Insert transaction into linked list.
// TASK 5
//
void History::insert( Transaction *p_new_trans ) {
  /*
  Adds the passed Transaction instance to the end of the linked-list of Transactions. To be defined by the
  student.
  we don't change p_head, we change the p_next of the p_head and stuff...??
  while loop through the nodes to get the address of the last 
  */

 //if the linke dlist is empty, add the node to the p_head
  if( p_head == nullptr ){ 

    p_head = p_new_trans;
    p_head->set_next( nullptr );
  } else {
    
    Transaction *p_current_tail{ p_head };
    while( p_current_tail -> get_next() != nullptr ){
    // Use the arrow operator.
      p_current_tail= p_current_tail -> get_next();
    }
    //have the address of the last node
    //set_next for last node to equal address of p_new_trans
    p_current_tail -> set_next( p_new_trans );

    //deallocate pointer memory
    //delete p_current_tail;//this deletes/cleans up the memory that was created. the memory created was for p_new_trans. thus this deletes the entry p_new_trans on the linked list. WRONG
    p_current_tail = nullptr;
  }

  
}

// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//
void History::sort_by_date() {
  /*
  Sorts the linked list in ascending order of trade date (or transaction id). Uses the overloaded less-than
  operator to define sort order. To be defined by the student

  sort by transaction id when dates are the same
  */
  Transaction *p_unsorted { get_p_head() };
  Transaction *p_sorted { nullptr };
  Transaction *p_tmp { nullptr };
  Transaction *p_previous { nullptr };

  while ( p_unsorted != nullptr ) {

    p_tmp = p_unsorted;
    p_unsorted = p_unsorted -> get_next();
    
    if ( p_sorted == nullptr ){
      p_sorted = p_tmp;
      p_tmp -> set_next( nullptr );
    } 
    else {
      
      p_previous = nullptr;

      Transaction *p_i = p_sorted; 
      
      while( p_i != nullptr ){

        if( (*p_tmp) < (*p_i) ){

          p_tmp -> set_next( p_i );

          if ( p_previous == nullptr ){
            p_sorted = p_tmp;
          }
          else{
            p_previous->set_next( p_tmp );
          }

          break;
        }
        else if ( p_i->get_next() == nullptr ) {

          p_tmp -> set_next( nullptr );
          p_i->set_next( p_tmp );

          break;
        }

        p_previous = p_i;
        p_i = p_i -> get_next();
      }
    }
  }

    p_head = p_sorted;
    p_unsorted = nullptr;
    p_sorted = nullptr;
    p_tmp = nullptr;
}

// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//
void History::update_acb_cgl() {
  /*
  Walks through the linked-list and updates the following private member variables: acb, acb_per_share,
  share_balance, and cgl for each Transaction. See section on Computing gains and losses using Adjusted Cost
  Base for additional details on how these values are calculated. To be defined by the student.
  */
 Transaction *p_list { get_p_head() };
 Transaction *p_previous { nullptr };

 while ( p_list != nullptr){

  //true if it is a buy
  if( p_list -> get_trans_type() ) {

    if( p_previous == nullptr ){

      p_list -> set_acb( p_list -> get_amount() );
      p_list -> set_share_balance( p_list -> get_shares() );
    }
    else {

      p_list -> set_acb( ( p_previous -> get_acb() ) + ( p_list -> get_amount() ) );
      p_list -> set_share_balance( ( p_previous -> get_share_balance() ) + ( p_list -> get_shares() ) );
    }
  } 
  else {

    p_list -> set_acb( ( p_previous -> get_acb() ) - ( ( p_list -> get_shares() )*( p_previous -> get_acb_per_share() ) ) );
    p_list -> set_share_balance( ( p_previous -> get_share_balance() ) - ( p_list -> get_shares() ) );
    p_list -> set_cgl( ( p_list -> get_amount() ) - ( ( p_list -> get_shares() )*( p_previous -> get_acb_per_share() ) ) );
  }

  p_list -> set_acb_per_share( ( p_list -> get_acb() )/( p_list -> get_share_balance() ) );

  p_previous = p_list;
  p_list = p_list -> get_next();

 }
}


// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8
double History::compute_cgl(unsigned int year) { 
  
  Transaction *p_list { get_p_head() };
  double totalCgl{ 0.0 };

  while( p_list != nullptr ) {

    if( p_list -> get_year() == year ){
      totalCgl += p_list->get_cgl();
    }
    p_list = p_list -> get_next();
  }
  return totalCgl;
}



// print() Print the transaction history.
//TASK 9
//
void History::print() {
  //Prints to the console output the transaction history from the input file. To be defined by the student.
  //is supposed to print what is on the linked list.
  //ece150::open_file();
  //so we have p_head -> accesses the first Transaction thingy
  std::cout<< "========== BEGIN TRANSACTION HISTORY ============" << std::endl;

  Transaction *p_i = get_p_head();

  while( p_i != nullptr )
  {

    p_i->print();
    p_i = p_i->get_next();
  }

  std::cout << "========== END TRANSACTION HISTORY ============" << std::endl;
}


// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }
