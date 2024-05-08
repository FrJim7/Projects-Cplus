#ifndef __ADT_QUEUE_H__
#define __ADT_QUEUE_H__1

#include "adt_list.h"
#include "adt_memory_node.h"

typedef struct adt_queue_s
{
	List *storage_;
	struct queue_ops_s *ops_;
} Queue;

struct queue_ops_s
{
	/**
	 * @brief      Destroy function
	 * 
	 * 				Destroy the queue and all his data
	 * 			
	 * @param  		Queue Queue
	 */
	s16(*destroy) (Queue *queue);
	/**
	 * @brief      Reset function
	 * 	
	 * 				Reset the Queue without freeing the storage
	 * 				
	 * @param[in] Queue Queue 
	 */
	s16(*reset)   (Queue *queue);

	// State queries
	/**
	 * @brief      length function
	 * 
	 * 				Return the number of elements in the Queue
	 * 
	 * @param[in] Queue Queue 
	 */		
	u16(*length)  (Queue *queue);
	/**
	 * @brief      resize function
	 * 
	 * 				changes the size of the storage keeping as much
	 * 				elements as it can
	 * 				
	 * @param[in] Queue Queue
	 * @param[in] u16 new_size 
	 */
	s16(*resize)  (Queue *queue, u16 new_size);
	/**
	 * @brief      capacity function
	 * 				return the capacity of the Queue
	 * @param[in] Queue Queue 
	 */	
	s16(*capacity)(Queue *queue);
	/**
	 * @brief      isFull function
	 * 				return true if the Queue has reach his maximun capacity
	 * @param[in] Queue Queue  	
	 */
	bool(*isFull) (Queue *queue);
	/**
	 * @brief      isEmpty function
	 * 				return true if theres no elements in the Queue
	 * 				
	 * @param[in] Queue Queue  
	 */
	bool(*isEmpty)(Queue *queue);

	// Data queries
	/**
	 * @brief      Top function
	 * 
	 * 				returns the data of the last element introduced
	 * @param[in] Queue Queue 
	 */
	void* (*front)(Queue *queue);
	/**
	 * @brief      Top function
	 * 
	 * 				returns the data of the last element introduced
	 * @param[in] Queue Queue 
	 */
	void* (*back) (Queue *queue);

	// Insertion
	/**
	 * @brief      Push function
	 * 				insert a data in the Queue
	 * 	@param[in]  Queue Queue 
	 * 	@param[in]  void* data
	 * 	@param[in]	u16 bytes
	 */	
	s16(*enqueue)  (Queue *queue, void *data, u16 bytes);

	// Extraction
	/**
	 * @brief      Pop function
	 * 				extract the las data introduced
	 * @param[in]  Queue Queue 
	 */
	void*(*dequeue) (Queue *queue);

	// Miscellaneous
	/**
	 * @brief      Concat function
	 * 
	 * 			   join two Queue into a new one leaving the second
	 * @param[in] Queue Queue    
	 */
	s16(*concat)  (Queue *queue, Queue *queue_src);
	/**
	 * @brief      Traverse function
	 * 				calls a function for every element in the Queue
	 * @param[in] Queue Queue 
	 * @param[in] callback 
	 */
	s16(*traverse)(Queue *queue, void(*callback) (MemoryNode *));
	/**
	 * @brief      Print function
	 * 				print each element in the Queue
	 * 				
	 * 	@param[in] Queue Queue 
	 */	
	void(*print)  (Queue *queue);
};
/**
 * @brief      Create a queue
 *
 * @param[in]  capacity  The capacity
 *
 * @return     the queue pointer
 */
Queue* QUEUE_create(u16 capacity);
#endif //__ADT_QUEUE_H__