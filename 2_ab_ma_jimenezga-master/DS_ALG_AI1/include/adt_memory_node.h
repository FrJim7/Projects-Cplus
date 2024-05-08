// adt_memory_node.h
// Toni Barella
// Algoritmos & Inteligencia Artificial
// ESAT 2016-2019
//
#ifndef __ADT_MEMORY_NODE_H__
#define __ADT_MEMORY_NODE_H__

#include "platform_types.h"

// Memory Node type
typedef struct memory_node_s
{
	void *data_;
	void *next_;
	void *prev_;
	u16 size_;
	struct memory_node_ops_s *ops_;
} MemoryNode;


/**
 * @brief      Memory Node's API Declarations.
 *
 *             Declarations of all Memory Node's Declarations.
 */
struct memory_node_ops_s
{
	/**
	 * @brief      data Function
	 *
	 *             Pointer to store data function.
	 *
	 * @param[in]  node  pointer to node.
	 * @return     void * to the data in the located in the node.
	 */
	void*(*data) (MemoryNode *node);

	/**
	 * ´@brief 		setData Function
	 *
	 * 						Set the data with a source given. This release the source and set the data
	 * 						of the given node with his content.
	 *
	 * @param[in]  node  pointer to node.
	 * @param[in]  src   source to set the node.
	 * @param[in]  size  size of the source.
	 * @return     Error Code
	 */
	s16(*setData) (MemoryNode *node, void *src, u16 bytes);

	
	/**
	 * @brief      setNext Function
	 *
	 *             set the pointer to the next MemoryMNode.
	 *             
	 * @param[in]  node  pointer to node.
	 * @param[in]  next  next memorynode.
	 * @return     Error Code
	 */
	s16(*setNext) (MemoryNode *node, MemoryNode *next);

	/**
	 * @brief      setPrev Function
	 *
	 *             set the pointer to the previous MemoryMNode.
	 *             
	 * @param[in]  node  pointer to node.
	 * @param[in]  prev  previous memorynode.
	 * @return     Error Code
	 */
	s16(*setPrev) (MemoryNode *node, MemoryNode *prev);

	s16(*softReset) (MemoryNode *node);

	/**
	 * @brief      size Function
	 *
	 *             Pointer to the size function.
	 *             
	 * @param[in]  node  pointer to node.
	 * @return     Error Code
	 */
	u16(*size) (MemoryNode *node);
	/**
	 * @brief      next Function
	 * 
	 * 				Next memory node
	 * @param[in]   node 
	 */
	MemoryNode*(*next) (MemoryNode *node);
	
	/**
	 * @brief      prev Function
	 * 
	 * 				Previous memory node
	 * @param[in]   node 
	 */
	MemoryNode*(*prev) (MemoryNode *node);

  /**
   * @brief      reset Function
   *
   *             Reset the content of memory node, without touch the node
   *             himself.
   *
   * @param[in]  node  pointer to node.
   * @return     Error Code
   */
	s16(*reset) (MemoryNode *node);		// reset content of memory node
	/**
	 * @brief      free Function
	 *
	 *             Release all the memory stored by the memory node
	 *
	 * @param[in]  node  pointer to node.
	 * @return     Error Code
	 */
	s16(*free) (MemoryNode *node);		// free memory, both data and node
	
	/**
	 * @brief      softFree Function
	 *
	 *             Free only the node, it let the data untouch.
	 *
	 * @param[in]  node  pointer to node.
	 * @return     Error Code
	 */
	s16(*softFree) (MemoryNode *node);	// free only the node (its mmory, not its data)


	/**
	 * @brief      memSet Function
	 *
	 *             Set the memory data with a value given.
	 * @param[in]  node   pointer to node.
	 * @param[in]  value  value to set memory.
	 * @return     Error Code
	 */
	s16(*memSet) (MemoryNode *node, u8 value);

	/**
	 * @brief      memCopy Function
	 *
	 *             Set the memory with a copy of the source given
	 *
	 * @param[in]  node  pointer to node.
	 * @param[in]  src   source to set the node.
	 * @param[in]  size  size of the source.
	 * @return     Error Code
	 */
	s16(*memCopy) (MemoryNode *node, void *src, u16 bytes);

	/**
	 * @brief      memConcat Function
	 *
	 *             Set the memory with conbination of the node.data and the source in the node.data
	 *
	 * @param[in]  node  pointer to node.
	 * @param[in]  src   source to set the node.
	 * @param[in]  size  size of the source.
	 * @return     Error Code
	 */
	s16(*memConcat) (MemoryNode *node, void *src, u16 bytes);

	/**
	 * @brief      memMask Function
	 *
	 *             Apply a mask to the memory in node.data
	 * @param[in]  node  pointer to node.
	 * @param[in]  mask  mask value.
	 * @return     Error Code
	 */
	s16(*memMask) (MemoryNode *node, u8 mask);

	/**
	 * @brief      print Function
	 *
	 *             Show in the screen the value of each byte in memory data.
	 *
	 * @param[in]  node  pointer to node.
	 * @return     Error Code
	 */
	void(*print) (MemoryNode *node);
};

/**
 * @brief      Creates a Node
 *
 * @return     Error Code.
 */
MemoryNode* MEMNODE_create();

/**
 * @brief      Creates a Node 
 *	
 *			   From a MemoryNode reference
 *
 * @param      node  The node
 *
 * @return     Error Code
 */
s16 MEMNODE_createFromRef(MemoryNode **node);

s16 MEMNODE_createLite(MemoryNode *node); // Creates a memory node without memory allocation

#endif // __ADT_MEMORY_NODE_H__