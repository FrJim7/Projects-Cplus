#ifndef __ADT_STACK_H__
#define __ADT_STACK_H__ 1

#include "adt_memory_node.h"
#include "adt_vector.h"

/**
 * Stack class
 */
typedef struct adt_stack_s
{
	Vector *storage_;
	struct stack_ops_s *ops_;
} Stack;

struct stack_ops_s
{
	/**
	 * @brief      Destroy function
	 * 
	 * 				Destroy the stack and all his data
	 * 			
	 * @param  		Stack stack
	 */
	s16(*destroy) (Stack *stack);
	/**
	 * @brief      Reset function
	 * 	
	 * 				Reset the stack without freeing the storage
	 * 				
	 * @param[in] Stack stack 
	 */
	s16(*reset)   (Stack *stack);

	// State queries

	/**
	 * @brief      length function
	 * 
	 * 				Return the number of elements in the stack
	 * 
	 * @param[in] Stack stack 
	 */		
	u16(*length)  (Stack *stack);
	/**
	 * @brief      resize function
	 * 
	 * 				changes the size of the storage keeping as much
	 * 				elements as it can
	 * 				
	 * @param[in] Stack stack
	 * @param[in] u16 new_size 
	 */
	s16(*resize)  (Stack *stack, u16 new_size);
	/**
	 * @brief      capacity function
	 * 				return the capacity of the stack
	 * @param[in] Stack stack 
	 */	
	s16(*capacity)(Stack *stack);
	/**
	 * @brief      isFull function
	 * 				return true if the stack has reach his maximun capacity
	 * @param[in] Stack stack  	
	 */
	bool(*isFull) (Stack *stack);
	/**
	 * @brief      isEmpty function
	 * 				return true if theres no elements in the stack
	 * 				
	 * @param[in] Stack stack  
	 */
	bool(*isEmpty)(Stack *stack);

	// Data queries
	
	/**
	 * @brief      Top function
	 * 
	 * 				returns the data of the last element introduced
	 * @param[in] Stack stack 
	 */
	void* (*top) (Stack *stack);
	
	// Insertion
	
	/**
	 * @brief      Push function
	 * 				insert a data in the stack
	 * 	@param[in]  Stack stack 
	 * 	@param[in]  void* data
	 * 	@param[in]	u16 bytes
	 */	
	s16(*push)  (Stack *stack, void *data, u16 bytes);


	// Extraction

	/**
	 * @brief      Pop function
	 * 				extract the las data introduced
	 * @param[in]  Stack stack 
	 */
	void*(*pop)  (Stack *stack);
	
	// Miscellaneous

	/**
	 * @brief      Concat function
	 * 
	 * 			   join two stack into a new one leaving the second
	 * @param[in] Stack stack    
	 */
	s16(*concat)  (Stack *stack, Stack *stack_src);
	/**
	 * @brief      Traverse function
	 * 				calls a function for every element in the stack
	 * @param[in] Stack stack 
	 * @param[in] callback 
	 */	
	s16(*traverse)(Stack *stack, void(*callback) (MemoryNode *));
	/**
	 * @brief      Print function
	 * 				print each element in the stack
	 * 				
	 * 	@param[in] Stack stack 
	 */	
	void(*print)  (Stack *stack);
};


/**
 * @brief      Create a stack
 *
 * @param[in]  capacity  The capacity
 *
 * @return     stack pointer
 */
Stack* STACK_create(u16 capacity);
#endif //__ADT_STACK_H__