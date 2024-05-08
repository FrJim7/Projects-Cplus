// adt_vector.h
// Toni Barella
// Algoritmos & Inteligencia Artificial
// ESAT 2018/2019
//
#ifndef __ADT_VECTOR_H__
#define __ADT_VECTOR_H__ 1

#include "adt_memory_node.h"

/**
 * Vector Class
 */
typedef struct adt_vector_s
{
	u16 head_;
	u16 tail_; 
	u16 capacity_;
	MemoryNode *storage_;
	struct vector_ops_s *ops_;
} Vector;

struct vector_ops_s
{
	/**
	 * @brief 	Pointer to destroy function
	 * 
	 * 			Destroy the vector and all his data
	 * @param 	Vector vector to destroy
	 */
	s16 (*destroy) (Vector *vector);
	/**
	 * @brief 	Pointer to reset function
	 * 
	 * 			Reset the data of the vector, doesnt destroy the storage 
	 * @param 	Vector vector to reset
	 */
	s16 (*reset) (Vector *vector);	
	/**
	 * @brief 	Pointer to resize function
	 * 
	 * 			Change the size of the vector, and copy as much data as
	 * 			it can, in case the new size is smaller data will be lose
	 * @param 	Vector vector to resize
	 * @param 	u16 new_size of the vector
	 */
	s16 (*resize)(Vector *vector, u16 new_size); 

	/**
	 * @brief 	Pointer to capcity function
	 * 
	 * 			Returm the vectors capacity
	 * @param 	Vector vector 
	 * @return 	u16 capacity
	 */
	u16 (*capacity)(Vector *vector);
	/**
	 * @brief 	Pointer to length function
	 * 
	 * 			Returns the number of elements in the vector
	 * @param 	Vector vector
	 * @return 	s16 length
	 */
	s16 (*length)(Vector *vector);
	/**
	 * @brief 	Pointer to isEmpty function
	 * 
	 * 			Returns true when the vector is empty false if at least one 
	 *		    element is inside
	 * @param 	Vector vector
	 */
	bool (*isEmpty) (Vector *vector);
	/**
	 * @brief 	Pointer to isFull function
	 * 
	 * Return 	true when the vector has reach his maximun capacity
	 * @param 	Vector vector
	 */
	bool (*isFull) (Vector *vector);
	
	// Data queries
	
	/**
	 * @brief 	Pointer to first funciton
	 * 
	 * 			returns the data of the first element in the vector
	 * @param 	Vector vector
	 */
	void* (*first)(Vector *vector); 
	/**
	 * @brief 	Pointer to last function
	 * 
	 * 			returns the data of the last element in the vector
	 * @param 	Vector vector
	 */
	void* (*last)(Vector *vector);
	/**
	 * @brief 	Pointer to at function
	 * 
	 * 			returns the data of a specific element in the array
	 * 			NULL value if the index is outside the range
	 * @param 	Vector vector
	 * @param 	u16 position
	 */
	void* (*at)(Vector *vector, u16 position); 

	// Insertion
	
	/**
	 * @brief 	Pointer to insertFirst function
	 * 
	 * 			Insert the data given in the first position of the vector,
	 *  		this function doesnt copy data.
	 * @param 	Vector vector
	 * @param 	Void data
	 * @param 	u16 bytes
	 */

	s16 (*insertFirst) (Vector *vector, void *data, u16 bytes); 
	/**
	 * @brief 	Pointer to insertLast function
	 * 
	 * 			Insert the data given in the last position of the vector,
	 *  		this function doesnt copy data.
	 * @param 	Vector vector
	 * @param 	Void data
	 * @param 	u16 bytes
	 */
	s16(*insertLast)  (Vector *vector, void *data, u16 bytes);
	 /**
	 * @brief 	Pointer to inserAt function
	 * 
	 * 			Insert the data given in a specigfic position of the vector,
	 *  		this function doesnt copy data.
	 * @param 	Vector vector
	 * @param 	Void data
	 * @param 	u16 bytes
	 * @param 	u16 position
	 */
	s16(*insertAt)  (Vector *vector, void *data, u16 bytes, u16 position); 
	
	// Extraction

	/**
	 * @brief 	Pointer to extractFirst function
	 * 
	 * 			Extract the first element of the vector
	 * @param 	Vector vector
	 */
	void*(*extractFirst) (Vector *vector); 
	/*// For debugging:
#if DEBUG
	void*(*extractFirst) (Vector *vector, u16 *size);
#endif // DEBUG
	void*(*extractFirst) (Vector *vector
#if DEBUG
	, u16 *size
#endif // DEBUG
		);	*/
	/**
	 * @brief 	Pointer to extractLast function
	 * 
	 * 			Extract the last element of the vector
	 * @param 	Vector vector
	 */
	void*(*extractLast) (Vector *vector); 
	/**
	 * @brief 	Pointer to extractFirst function
	 * 
	 * 			Extract the a specific element of the vector
	 * @param 	Vector vector
	 * @param 	u16 position
	 */
	void*(*extractAt) (Vector *vector, u16 position);
	// Miscellaneous
	
	/**
	 * @brief 	Pointer to concat function
	 * 
	 * 			Creates a new storage with the combination of size
	 * 			and data given
	 * @param 	Vector vector
	 * @param 	Vector vector_source
	 */
	s16(*concat) (Vector *vector, Vector *vector_src); 
	/**
	 * @brief 	Pointer to traverse function
	 * 
	 * 			Calls the function given with each element in the 
	 * 			vector
	 * @param 	Vector vector
	 * @param 	(void*) callback
	 */
	s16 (*traverse)(Vector *vector, void(*callback) (MemoryNode *)); 
	/**
	 * @brief 	Pointer to print function
	 * 
	 * 			Print the direction of each element in the vector
	 * @param 	Vector vector
	 */
	void(*print)(Vector *vector); 
};

/**
 * @brief      Creates a Vector
 *
 *				return a pointer to the crated vector 
 *				
 * @param[in]  capacity  The capacity
 */
Vector* VECTOR_create(u16 capacity); 
#endif //__ADT_VECTOR_H__











