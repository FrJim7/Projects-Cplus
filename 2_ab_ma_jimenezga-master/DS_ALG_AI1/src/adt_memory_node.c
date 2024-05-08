
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"
#include "adt_memory_node.h"

#include "ABGS_MemoryManager\abgs_memory_manager.h"


// Memory Node Declarations
static s16 MEMNODE_initWithoutCheck(MemoryNode *node);	
static void* MEMNODE_data(MemoryNode *node);
static u16 MEMNODE_size(MemoryNode *node);
static MemoryNode* MEMNODE_next(MemoryNode *node);
static MemoryNode* MEMNODE_prev(MemoryNode *node);
static s16 MEMNODE_setData(MemoryNode *node, void *src, u16 bytes);
static s16 MEMNODE_setNext(MemoryNode *node, MemoryNode *next);
static s16 MEMNODE_setPrev(MemoryNode *node, MemoryNode *prev);
static s16 MEMNODE_reset(MemoryNode *node);
static s16 MEMNODE_softReset(MemoryNode *node);
static s16 MEMNODE_free(MemoryNode *node);
static s16 MEMNODE_softFree(MemoryNode *node);
static s16 MEMNODE_memSet(MemoryNode *node, u8 value);
static void MEMNODE_print(MemoryNode *node);
static s16 MEMNODE_memCopy(MemoryNode *node, void *src, u16 bytes);
static s16 MEMNODE_memConcat(MemoryNode *node, void *src, u16 bytes);
static s16 MEMNODE_memMask(MemoryNode *node, u8 mask);


// Memory Node's API Definitions
struct memory_node_ops_s memory_node_ops =
{
	.data = MEMNODE_data,
	.size = MEMNODE_size,
	.next = MEMNODE_next,
	.prev = MEMNODE_prev,
	.setData = MEMNODE_setData,
	.setNext = MEMNODE_setNext,
	.setPrev = MEMNODE_setPrev,
	.reset = MEMNODE_reset,
	.softReset = MEMNODE_softReset,
	.free = MEMNODE_free,
	.softFree = MEMNODE_softFree,
	.print = MEMNODE_print,
	.memSet = MEMNODE_memSet,
	.memCopy = MEMNODE_memCopy,
	.memConcat = MEMNODE_memConcat,
	.memMask = MEMNODE_memMask
};

s16 MEMNODE_initWithoutCheck(MemoryNode *node)
{
	node->data_ = NULL;
	node->size_ = 0;
	node->next_ = NULL;
	node->prev_ = NULL;
	node->ops_ = &memory_node_ops;
	return kErrorCode_Ok;
}

// Memory Node Definitions
MemoryNode* MEMNODE_create()
{
#if TEST_
	MemoryNode *node = malloc(sizeof(MemoryNode));
#else
	MemoryNode *node = MM->malloc(sizeof(MemoryNode));
#endif
	if (node == NULL)
	{
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
		return NULL;
	}
	MEMNODE_initWithoutCheck(node);
	return node;
}

s16 MEMNODE_createFromRef(MemoryNode **node)
{
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_MemoryNodeNullReference;
	}
	*node = MEMNODE_create();
	if (*node == NULL)
	{
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
		return kErrorCode_Memory;
	}
	
	return kErrorCode_Ok;
}

s16 MEMNODE_createLite(MemoryNode *node) 
{
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_MemoryNodeNullReference;
	}
	MEMNODE_initWithoutCheck(node);
	return kErrorCode_Ok;
}

void* MEMNODE_data(MemoryNode *node)
{
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}
	return node->data_;
}

u16	MEMNODE_size(MemoryNode *node)
{
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return 0;
	}
	return node->size_;
}

MemoryNode* MEMNODE_next(MemoryNode *node) 
{
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}
	return (MemoryNode*)node->next_;
}

MemoryNode* MEMNODE_prev(MemoryNode *node)
{
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}
	return (MemoryNode*)node->prev_;
}

s16 MEMNODE_setData(MemoryNode *node, void *src, u16 bytes) 
{
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_MemoryNodeNullReference;
	}
	if (src == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Source NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_SourceNullReference;
	}
	if (bytes <= 0) {
#ifdef VERBOSE_
		printf("Error: [%s] Invalid size in bytes\n", __FUNCTION__);
#endif
		return kErrorCode_InvalidSize;
	}
	node->data_ = src;
	node->size_ = bytes;
	return kErrorCode_Ok;
}

s16 MEMNODE_setNext(MemoryNode *node, MemoryNode *next) 
{
	/*if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_MemoryNodeNullReference;
	}*/
	node->next_ = next;
	return kErrorCode_Ok;
}

s16 MEMNODE_setPrev(MemoryNode *node, MemoryNode *prev)
{
	/*if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_MemoryNodeNullReference;
	}*/
	node->prev_ = prev;
	return kErrorCode_Ok;
}

s16 MEMNODE_reset(MemoryNode *node)
{
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_MemoryNodeNullReference;
	}
	if (node->data_ != NULL) {
		MM->free(node->data_);
	}
	node->data_ = NULL;
	node->next_ = NULL;
	node->prev_ = NULL;
	node->size_ = 0;
	return kErrorCode_Ok;
}

s16 MEMNODE_softReset(MemoryNode *node)
{
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_MemoryNodeNullReference;
	}
	node->data_ = NULL;
	node->next_ = NULL;
	node->prev_ = NULL;
	node->size_ = 0;
	return kErrorCode_Ok;
}

s16 MEMNODE_free(MemoryNode *node) {
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_MemoryNodeNullReference;
	}
	MEMNODE_reset(node);
#if TEST_
	free(node);
#else
	MM->free(node);
#endif
	node = NULL;
	return kErrorCode_Ok;
}

s16 MEMNODE_softFree(MemoryNode *node) {
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_MemoryNodeNullReference;
	}
	MEMNODE_softReset(node);
#if TEST_
	free(node);
#else
	MM->free(node);
#endif
	return kErrorCode_Ok;
}

s16 MEMNODE_memSet(MemoryNode *node, u8 value) {
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_MemoryNodeNullReference;
	}
	memset(node->data_, value, node->size_);
	return kErrorCode_Ok;
}

s16 MEMNODE_memCopy(MemoryNode *node, void *src, u16 bytes) {
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_MemoryNodeNullReference;
	}
	if (src == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Source NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_SourceNullReference;
	}
	if (bytes <= 0) {
#ifdef VERBOSE_
		printf("Error: [%s] Invalid size in bytes\n", __FUNCTION__);
#endif
		return kErrorCode_InvalidSize;
	}
	void *memcopy_aux_data = MM->malloc(bytes);

	memcpy(memcopy_aux_data, src, bytes);
	if (node->data_ != NULL) {
		MM->free(node->data_);
		node->data_ = NULL;
	}

	node->data_ = memcopy_aux_data;
	node->size_ = bytes;
	return kErrorCode_Ok;
}

s16 MEMNODE_memConcat(MemoryNode *node, void *src, u16 bytes) {
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_MemoryNodeNullReference;
	}
	if (src == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Source NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_SourceNullReference;
	}
	if (bytes <= 0) {
#ifdef VERBOSE_
		printf("Error: [%s] Invalid size in bytes\n", __FUNCTION__);
#endif
		return kErrorCode_InvalidSize;
	}

	u8 *memcomcat_aux_data = (u8*)MM->malloc(node->size_ + bytes);

	if (node->data_ == NULL) {
		memcpy(memcomcat_aux_data, src, bytes);
		node->data_ = memcomcat_aux_data;
		node->size_ = bytes;
		return kErrorCode_Ok;
	}
	memcpy(memcomcat_aux_data, node->data_, node->size_);
	MM->free(node->data_);
	node->data_ = memcomcat_aux_data;
	memcpy(memcomcat_aux_data + node->size_, src, bytes);
	node->size_ += bytes;
	return kErrorCode_Ok;
}

s16 MEMNODE_memMask(MemoryNode *node, u8 mask) {
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_MemoryNodeNullReference;
	}
	if (node->data_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Source NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_SourceNullReference;
	}
	u8 *memmask_aux_data = node->data_;
	for (u16 i = 0; i < node->size_; i++) {
		memmask_aux_data =& mask;
		memmask_aux_data++;
	}
	return kErrorCode_Ok;
}

void MEMNODE_print(MemoryNode *node) {
	if (node == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] MemoryNode NULL reference error\n", __FUNCTION__);
#endif
		return;
	}
	if (node->data_ == NULL) {
#ifdef VERBOSE_
			printf("Error: [%s] Source NULL reference error\n", __FUNCTION__);
#endif
			return;
	}
	u8* print_aux_data = node->data_;
	printf("\n");
	for (u16 i = 0; i < node->size_; i++) {
		printf("-%p- ", print_aux_data++);
	}
	printf("\n");
}