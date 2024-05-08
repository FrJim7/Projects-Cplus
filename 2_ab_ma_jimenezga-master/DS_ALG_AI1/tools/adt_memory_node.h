
#ifndef __ADT_MEMORY_NODE_H__
#define __ADT_MEMORY_NODE_H__ 1

#include "ABGS_MemoryManager\abgs_platform_types.h"

// Memory Node type
typedef struct memory_node_s
{
	void *data_;
	void *next_;
	void *prev_;
	u16 size_;
	struct memory_node_ops_s *ops_;
} MemoryNode;

// Memory Node's API Declarations
struct memory_node_ops_s
{
	void*(*data) (MemoryNode *node);
	u16(*size) (MemoryNode *node);
	MemoryNode*(*next) (MemoryNode *node);
	MemoryNode*(*prev) (MemoryNode *node);

	s16(*setData) (MemoryNode *node, void *src, u16 bytes);
	s16(*setNext) (MemoryNode *node, MemoryNode *next);
	s16(*setPrev) (MemoryNode *node, MemoryNode *prev);

	s16(*reset) (MemoryNode *node);		// reset content of memory node
	s16(*softReset) (MemoryNode *node); 
	s16(*free) (MemoryNode *node);		// free memory, both data and node
	s16(*softFree) (MemoryNode *node);	// free only the node (its mmory, not its data)

	s16(*memSet) (MemoryNode *node, u8 value);
	s16(*memCopy) (MemoryNode *node, void *src, u16 bytes);
	s16(*memConcat) (MemoryNode *node, void *src, u16 bytes);
	s16(*memMask) (MemoryNode *node, u8 mask);

	void(*print) (MemoryNode *node);
};

MemoryNode* MEMNODE_create();
s16 MEMNODE_createFromRef(MemoryNode **node);
s16 MEMNODE_createLite(MemoryNode *node); // Creates a memory node without memory allocation

#endif // __ADT_MEMORY_NODE_H__