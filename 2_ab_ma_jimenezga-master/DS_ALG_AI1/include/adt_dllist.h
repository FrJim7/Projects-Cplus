#ifndef __ADT_DLLIST_H__
#define __ADT_DLLIST_H__ 1

#include "adt_memory_node.h"

typedef struct adt_dllist_s
{
	MemoryNode *head_;
	MemoryNode *tail_;
	u16 length_;
	u16 capacity_;
	struct dllist_ops_s *ops_;
} DLList;

struct dllist_ops_s
{
	/**
	 * @brief 	Pointer to destroy function
	 * 
	 * 			Destroy the List and all his data
	 * @param 	List List to destroy
	 */
	s16(*destroy) (DLList *list);	
	/**
	 * @brief 	Pointer to reset function
	 * 
	 * 			Reset the data of the List, doesnt destroy the storage 
	 * @param 	List List to reset
	 */
	s16(*reset) (DLList *list);		

	// State queries
	/**
	 * @brief 	Pointer to length function
	 * 
	 * 			Returns the number of elements in the List
	 * @param 	List List
	 * @return 	s16 length
	 */
	u16(*length)(DLList *list);
	/**
	 * @brief 	Pointer to resize function
	 * 
	 * 			Change the size of the List, and copy as much data as
	 * 			it can, in case the new size is smaller data will be lose
	 * @param 	List List to resize
	 * @param 	u16 new_size of the List
	 */	
	s16(*resize)  (DLList *list, u16 new_size);
	/**
	 * @brief 	Pointer to capcity function
	 * 
	 * 			Returm the Lists capacity
	 * @param 	List List 
	 * @return 	u16 capacity
	 */
	s16(*capacity)(DLList *list);
	/**
	 * @brief 	Pointer to isFull function
	 * 
	 * Return 	true when the List has reach his maximun capacity
	 * @param 	List List
	 */
	bool(*isFull) (DLList *list);
	/**
	 * @brief 	Pointer to isEmpty function
	 * 
	 * 			Returns true when the List is empty false if at least one 
	 *		    element is inside
	 * @param 	List List
	 */
	bool(*isEmpty)(DLList *list);

	// Data queries
	/**
	 * @brief 	Pointer to first funciton
	 * 
	 * 			returns the data of the first element in the List
	 * @param 	List List
	 */
	void* (*first)(DLList *list);
	/**
	 * @brief 	Pointer to last function
	 * 
	 * 			returns the data of the last element in the List
	 * @param 	List List
	 */ 
	void* (*last)(DLList *list); 
	/**
	 * @brief 	Pointer to at function
	 * 
	 * 			returns the data of a specific element in the array
	 * 			NULL value if the index is outside the range
	 * @param 	List List
	 * @param 	u16 position
	 */
	void* (*at)(DLList *list, u16 position); 

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
	s16(*insertFirst) (DLList *list, void *data, u16 bytes); 
	 /**
	  * @brief 	Pointer to insertLast function
	 * 
	 * 			Insert the data given in the last position of the List,
	 *  		this function doesnt copy data.
	 * @param 	List List
	 * @param 	Void data
	 * @param 	u16 bytes
	 */
	s16(*insertLast) (DLList *list, void *data, u16 bytes); 
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
	s16(*insertAt) (DLList *list, void *data, u16 position, u16 bytes); 

	// Extraction
	/**
	 * @brief 	Pointer to extractFirst function
	 * 
	 * 			Extract the first element of the List
	 * @param 	List List
	 */
	void*(*extractFirst) (DLList *list); 
	/**
	 * @brief 	Pointer to extractLast function
	 * 
	 * 			Extract the last element of the List
	 * @param 	List List
	 */
	void*(*extractLast) (DLList *list);
	/**
	 * @brief 	Pointer to extractFirst function
	 * 
	 * 			Extract the a specific element of the List
	 * @param 	List List
	 * @param 	u16 position
	 */
	void*(*extractAt) (DLList *list, u16 position);

	// Miscellaneous
	/**
	 * @brief 	Pointer to concat function
	 * 
	 * 			Creates a new storage with the combination of size
	 * 			and data given
	 * @param 	List List
	 * @param 	List List_source
	 */
	s16(*concat) (DLList *list, DLList *dllist_src);
	/**
	 * @brief 	Pointer to traverse function
	 * 
	 * 			Calls the function given with each element in the 
	 * 			List
	 * @param 	List List
	 * @param 	(void*) callback
	 */ 
	s16(*traverse)(DLList *list, void(*callback) (MemoryNode *));
	/**
	 * @brief 	Pointer to print function
	 * 
	 * 			Print the direction of each element in the List
	 * @param 	List List
	 */
	void(*print)(DLList *list);
};
/**
 * @brief      Create a DLList
 *
 * @param[in]  capacity  The capacity
 *
 * @return     the dllist pointer
 */
DLList* DLList_Create(u16 capacity);
#endif //__ADT_DLListç_H__