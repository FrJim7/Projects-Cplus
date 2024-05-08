#ifndef __ADT_LIST_H__
#define __ADT_LIST_H__ 1

#include "adt_memory_node.h"

typedef struct adt_list_s
{
	MemoryNode *head_;
	MemoryNode *tail_;
	u16 length_;
	u16 capacity_;
	struct list_ops_s *ops_;
} List;

struct list_ops_s
{
	/**
	 * @brief 	Pointer to destroy function
	 * 
	 * 			Destroy the List and all his data
	 * @param 	List List to destroy
	 */
	s16(*destroy) (List *list);	
	/**
	 * @brief 	Pointer to reset function
	 * 
	 * 			Reset the data of the List, doesnt destroy the storage 
	 * @param 	List List to reset
	 */
	s16(*reset)   (List *list);		

	// State queries
	/**
	 * @brief 	Pointer to length function
	 * 
	 * 			Returns the number of elements in the List
	 * @param 	List List
	 * @return 	s16 length
	 */
	u16(*length)  (List *list);
	/**
	 * @brief 	Pointer to resize function
	 * 
	 * 			Change the size of the List, and copy as much data as
	 * 			it can, in case the new size is smaller data will be lose
	 * @param 	List List to resize
	 * @param 	u16 new_size of the List
	 */
	s16(*resize)  (List *list, u16 new_size);
	/**
	 * @brief 	Pointer to capcity function
	 * 
	 * 			Returm the Lists capacity
	 * @param 	List List 
	 * @return 	u16 capacity
	 */
	s16(*capacity)(List *list);
	/**
	 * @brief 	Pointer to isFull function
	 * 
	 * Return 	true when the List has reach his maximun capacity
	 * @param 	List List
	 */
	bool(*isFull) (List *list);
	/**
	 * @brief 	Pointer to isEmpty function
	 * 
	 * 			Returns true when the List is empty false if at least one 
	 *		    element is inside
	 * @param 	List List
	 */
	bool(*isEmpty)(List *list);

	// Data queries
	/**
	 * @brief 	Pointer to first funciton
	 * 
	 * 			returns the data of the first element in the List
	 * @param 	List List
	 */
	void* (*first)(List *list); 
	/**
	 * @brief 	Pointer to last function
	 * 
	 * 			returns the data of the last element in the List
	 * @param 	List List
	 */
	void* (*last) (List *list); 
	/**
	 * @brief 	Pointer to at function
	 * 
	 * 			returns the data of a specific element in the array
	 * 			NULL value if the index is outside the range
	 * @param 	List List
	 * @param 	u16 position
	 */
	void* (*at)   (List *list, u16 position); 

	// Insertion
	/**
	 * @brief 	Pointer to insertFirst function
	 * 
	 * 			Insert the data given in the first position of the List,
	 *  		this function doesnt copy data.
	 * @param 	List List
	 * @param 	Void data
	 * @param 	u16 bytes
	 */
	s16(*insertFirst) (List *list, void *data, u16 bytes); 
	/**
	 * @brief 	Pointer to insertLast function
	 * 
	 * 			Insert the data given in the last position of the List,
	 *  		this function doesnt copy data.
	 * @param 	List List
	 * @param 	Void data
	 * @param 	u16 bytes
	 */
	s16(*insertLast)  (List *list, void *data, u16 bytes); 
	/**
	 * @brief 	Pointer to inserAt function
	 * 
	 * 			Insert the data given in a specigfic position of the List,
	 *  		this function doesnt copy data.
	 * @param 	List List
	 * @param 	Void data
	 * @param 	u16 bytes
	 * @param 	u16 position
	 */
	s16(*insertAt)    (List *list, void *data, u16 position, u16 bytes); 

	// Extraction
	/**
	 * @brief 	Pointer to extractFirst function
	 * 
	 * 			Extract the first element of the List
	 * @param 	List List
	 */
	void*(*extractFirst) (List *list); 
	/**
	 * @brief 	Pointer to extractLast function
	 * 
	 * 			Extract the last element of the List
	 * @param 	List List
	 */
	void*(*extractLast)  (List *list); 
	/**
	 * @brief 	Pointer to extractFirst function
	 * 
	 * 			Extract the a specific element of the List
	 * @param 	List List
	 * @param 	u16 position
	 */
	void*(*extractAt)    (List *list, u16 position);

	// Miscellaneous
	/**
	 * @brief 	Pointer to concat function
	 * 
	 * 			Creates a new storage with the combination of size
	 * 			and data given
	 * @param 	List List
	 * @param 	List List_source
	 */
	s16(*concat)  (List *list, List *list_src);
	/**
	 * @brief 	Pointer to traverse function
	 * 
	 * 			Calls the function given with each element in the 
	 * 			List
	 * @param 	List List
	 * @param 	(void*) callback
	 */ 
	s16(*traverse)(List *list, void(*callback) (MemoryNode *));
	/**
	 * @brief 	Pointer to print function
	 * 
	 * 			Print the direction of each element in the List
	 * @param 	List List
	 */
	void(*print)  (List *list); 
};
/**
 * @brief      Creates a list 
 *
 * @param[in]  capacity  The capacity
 *
 * @return     return the pointer of the list
 */
List* LIST_create(u16 capacity);
#endif //__ADT_LIST_H__