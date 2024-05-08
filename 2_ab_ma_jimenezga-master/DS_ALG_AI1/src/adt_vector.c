#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"
#include "adt_vector.h"
#include "adt_memory_node.h"


#include "ABGS_MemoryManager\abgs_memory_manager.h"


// Vector Declarations
static s16 VECTOR_destroy(Vector *vector);
static s16 VECTOR_reset(Vector *vector);
static s16 VECTOR_resize(Vector *vector, u16 new_size);
static u16 VECTOR_capacity(Vector *vector);
static s16 VECTOR_length(Vector *vector);
static bool VECTOR_isEmpty(Vector *vector);
static bool VECTOR_isFull(Vector *vector);
static void* VECTOR_first(Vector *vector);
static void* VECTOR_last(Vector *vector);
static void* VECTOR_at(Vector *vector, u16 position);
static s16 VECTOR_insertFirst(Vector *vector, void *data, u16 bytes);
static s16 VECTOR_insertLast(Vector *vector, void *data, u16 bytes);
static s16 VECTOR_insertAt(Vector *vector, void *data, u16 bytes, u16 position);
static void* VECTOR_extractFirst(Vector *vector);
static void* VECTOR_extractLast(Vector *vector);
static void* VECTOR_extractAt(Vector *vector, u16 position);
static s16 VECTOR_concat(Vector *vector, Vector *vector_src);
static s16 VECTOR_traverse(Vector *vector, void(*callaback) (MemoryNode *));
static void VECTOR_print(Vector *vector);

// Vector's API Definitions
struct vector_ops_s vector_ops =
{
	.destroy = VECTOR_destroy,
	.reset = VECTOR_reset,
	.resize = VECTOR_resize,
	.capacity = VECTOR_capacity,
	.length = VECTOR_length,
	.isEmpty = VECTOR_isEmpty,
	.isFull = VECTOR_isFull,
	.first = VECTOR_first,
	.last = VECTOR_last,
	.at = VECTOR_at,
	.insertFirst = VECTOR_insertFirst,
	.insertLast = VECTOR_insertLast,
	.insertAt = VECTOR_insertAt,
	.extractFirst = VECTOR_extractFirst,
	.extractLast = VECTOR_extractLast,
	.extractAt = VECTOR_extractAt,
	.concat = VECTOR_concat,
	.traverse = VECTOR_traverse,
	.print = VECTOR_print
};

Vector* VECTOR_create(u16 capacity) 
{
	if (capacity <= 0) {
#ifdef VERBOSE_
		printf("Error: [%s] Invalid size in capacity\n", __FUNCTION__);
#endif
		return NULL;
	}
	Vector *aux_create_vector = (Vector*)MM->malloc(sizeof(Vector));

	aux_create_vector->head_ = 0;
	aux_create_vector->tail_ = 0;
	aux_create_vector->capacity_ = capacity;
	aux_create_vector->ops_ = &vector_ops;

#if TEST_
	aux_create_vector->storage_ = (MemoryNode *)malloc(sizeof(MemoryNode) * capacity);
#else
	aux_create_vector->storage_ = (MemoryNode*)MM->malloc(sizeof(MemoryNode) * capacity);
#endif

	
	for (u16 i = 0; i < capacity; i++) {
		MEMNODE_createLite(&aux_create_vector->storage_[i]);
	}

	return aux_create_vector;
}

s16 VECTOR_destroy(Vector *vector)
{
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_VectorNullReference;
	}

	if (vector->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_StorageNullReference;
	}

	vector->ops_->reset(vector);
#if TEST_
	free(vector->storage_);
#else
	MM->free(vector->storage_);
#endif
	
	MM->free(vector);

	vector->storage_ = NULL;
	vector = NULL;

	return kErrorCode_Ok;
}

s16 VECTOR_reset(Vector *vector) 
{
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_VectorNullReference;
	}

	if (vector->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_StorageNullReference;
	}

	for (u16 i = vector->head_; i < vector->capacity_; i++) 
	{
		vector->storage_->ops_->reset(&vector->storage_[i]);
	}

	vector->head_ = 0;
	vector->tail_ = 0;
	return kErrorCode_Ok;
}

s16 VECTOR_resize(Vector *vector, u16 new_size)
{
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_VectorNullReference;
	}

	if (vector->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_StorageNullReference;
	}

	if (new_size <= 0) {
#ifdef VERBOSE_
		printf("Error: [%s] Invalid size in capacity\n", __FUNCTION__);
#endif
		return kErrorCode_InvalidSize;
	}

	if (new_size == vector->capacity_) {
		return kErrorCode_Ok;
	}
	
	u16 aux_resize_size = 0;
	u16 aux_resize_tail = 0;

	MemoryNode *aux_resize_storage = (MemoryNode*)MM->malloc(sizeof(MemoryNode) * new_size);
	if (NULL == aux_resize_storage) {
		return kErrorCode_MemoryNodeNullReference;
	}

	for (u16 i = 0; i < new_size; i++) {
		MEMNODE_createLite(&aux_resize_storage[i]);
	}

	if (new_size < vector->capacity_) {
		aux_resize_size = new_size;
	} else {
		aux_resize_size = vector->tail_;
	}
	
	for (u16 i = vector->head_; i < aux_resize_size; i++) {

		vector->storage_->ops_->setData(&aux_resize_storage[i],
			vector->storage_->ops_->data(&vector->storage_[i]),
			vector->storage_->ops_->size(&vector->storage_[i]));

		vector->storage_->ops_->softReset(&vector->storage_[i]);

		aux_resize_tail++;
	}

	vector->ops_->reset(vector);
	vector->storage_->ops_->free(vector->storage_);


	vector->capacity_ = new_size;
	vector->storage_  = aux_resize_storage;
	vector->tail_     = aux_resize_tail;

	return kErrorCode_Ok;
}

u16 VECTOR_capacity(Vector *vector) 
{
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return 0;
	}

	if (vector->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return 0;
	}

	return vector->capacity_;
}

s16 VECTOR_length(Vector *vector)
{
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_VectorNullReference;
	}

	u16 aux_length = 0;

	for (u8 i = 0; i < vector->tail_; i++) {
		aux_length++;
	}

	return aux_length;
}

bool VECTOR_isEmpty(Vector *vector)
{
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return false;
	}

	return vector->head_ == vector->tail_;
}

bool VECTOR_isFull(Vector *vector)
{
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return true;
	}

	//Tail marks the last avalible block, if the vector is full tail is equal to capacity
	return vector->capacity_ == vector->tail_;
}

void* VECTOR_first(Vector *vector)
{
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	if (vector->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	return vector->storage_->ops_->data(&vector->storage_[vector->head_]);
}

void* VECTOR_last(Vector *vector)
{
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	if (vector->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	int position = 0;

	if (vector->tail_ != 0) {
		position = vector->tail_ - 1;
	}

	return vector->storage_->ops_->data(&vector->storage_[position]);
}

void* VECTOR_at(Vector *vector, u16 position)
{
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	if (vector->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	if (position >= vector->capacity_ || 0 > position) {
#ifdef VERBOSE_
		printf("Error: [%s] Invalid position index\n", __FUNCTION__);
#endif
		return NULL;
	}

	return vector->storage_->ops_->data(&vector->storage_[position]);
}

s16 VECTOR_insertFirst(Vector *vector, void *data, u16 bytes) 
{
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_VectorNullReference;
	}

	if (vector->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_StorageNullReference;
	}

	if (data == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Data NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_SourceNullReference;
	}

	if (bytes <= 0) {
#ifdef VERBOSE_
		printf("Error: [%s] Invalid size in bytes\n", __FUNCTION__);
#endif
		return kErrorCode_InvalidSize;
	}

	if (VECTOR_isFull(vector)) {
#ifdef VERBOSE_
		printf("Error: [%s] Full Vector\n", __FUNCTION__);
#endif
		return kErrorCode_FullVector;
	}

	for (u16 i = vector->tail_; i > vector->head_; i--) {
		vector->storage_->ops_->setData(&vector->storage_[i],
			vector->storage_->ops_->data(&vector->storage_[i - 1]),
			vector->storage_->ops_->size(&vector->storage_[i - 1]));
	}

	vector->storage_->ops_->setData(&vector->storage_[vector->head_], data, bytes);
	vector->tail_++;
	return kErrorCode_Ok;
}

s16 VECTOR_insertLast(Vector *vector, void *data, u16 bytes) 
{
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_VectorNullReference;
	}

	if (vector->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_StorageNullReference;
	}

	if (data == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Data NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_SourceNullReference;
	}

	if (bytes <= 0) {
#ifdef VERBOSE_
		printf("Error: [%s] Invalid size in bytes\n", __FUNCTION__);
#endif
		return kErrorCode_InvalidSize;
	}

	if (VECTOR_isFull(vector)) {
#ifdef VERBOSE_
		printf("Error: [%s] Full Vector\n", __FUNCTION__);
#endif
		return kErrorCode_FullVector;
	}

	vector->storage_->ops_->setData(&vector->storage_[vector->tail_], data, bytes);
	vector->tail_++;
	return kErrorCode_Ok;
}

s16 VECTOR_insertAt(Vector *vector, void *data, u16 bytes, u16 position) {
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_VectorNullReference;
	}

	if (vector->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_StorageNullReference;
	}

	if (data == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Data NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_SourceNullReference;
	}

	if (bytes <= 0) {
#ifdef VERBOSE_
		printf("Error: [%s] Invalid size in bytes\n", __FUNCTION__);
#endif
		return kErrorCode_InvalidSize;
	}

	if (VECTOR_isFull(vector)) {
#ifdef VERBOSE_
		printf("Error: [%s] Full Vector\n", __FUNCTION__);
#endif
		return kErrorCode_FullVector;
	}

	if ( position >= vector->capacity_) {
#ifdef VERBOSE_
		printf("Error: [%s] Invalid position index\n", __FUNCTION__);
#endif
		return kErrorCode_InvalidSize;
	}

	if (position < 0) {
#ifdef VERBOSE_
		printf("Error: [%s] Invalid position index\n", __FUNCTION__);
#endif
		return kErrorCode_InvalidSize;
	}

	if (position == vector->head_) {
		return VECTOR_insertFirst(vector, data, bytes);
	}

	if (position >= vector->tail_) {
		return VECTOR_insertLast(vector, data, bytes);
	}

	for (u16 i = vector->tail_; i > position; i--) {
		vector->storage_->ops_->setData(&vector->storage_[i],
			vector->storage_->ops_->data(&vector->storage_[i - 1]),
			vector->storage_->ops_->size(&vector->storage_[i - 1]));
	}

	vector->storage_->ops_->setData(&vector->storage_[position], data, bytes);
	vector->tail_++;

	return kErrorCode_Ok;
}

void* VECTOR_extractFirst(Vector *vector)
{
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	if (vector->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	void *aux_extract_first_mn;
	aux_extract_first_mn = vector->storage_->ops_->data(&vector->storage_[vector->head_]);

	vector->storage_->ops_->softReset(&vector->storage_[vector->head_]);
	for (u16 i = vector->head_; i < vector->tail_ - 1; i++) {
		vector->storage_->ops_->setData(&vector->storage_[i],
			vector->storage_->ops_->data(&vector->storage_[i + 1]),
			vector->storage_->ops_->size(&vector->storage_[i + 1]));
	}
	vector->storage_->ops_->softReset(&vector->storage_[vector->tail_ - 1]);
	vector->tail_--;

	return aux_extract_first_mn;
}

void* VECTOR_extractLast(Vector *vector) 
{
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	if (vector->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	void *aux_extract_last_mn;
	aux_extract_last_mn = vector->storage_->ops_->data(&vector->storage_[vector->tail_ - 1]);

	vector->storage_->ops_->softReset(&vector->storage_[vector->tail_ - 1]);
	vector->tail_--;

	return aux_extract_last_mn;
}

void* VECTOR_extractAt(Vector *vector, u16 position) 
{
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	if (vector->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	if (0 > position || position >= vector->capacity_) {
#ifdef VERBOSE_
		printf("Error: [%s] Invalid position index\n", __FUNCTION__);
#endif
		return NULL;
	}

	if (position >= vector->tail_) {
		return VECTOR_extractLast(vector);
	}

	if (position == 0) {
		return VECTOR_extractFirst(vector);
	}

	void *aux_at_void;
	aux_at_void = vector->storage_->ops_->data(&vector->storage_[position]);

	vector->storage_->ops_->softReset(&vector->storage_[position]);
	for (u16 i = position; i < vector->tail_ - 1; i++) {
		vector->storage_->ops_->setData(&vector->storage_[i],
			vector->storage_->ops_->data(&vector->storage_[i + 1]),
			vector->storage_->ops_->size(&vector->storage_[i + 1]));
	}
	vector->storage_->ops_->softReset(&vector->storage_[vector->tail_ - 1]);
	vector->tail_--;

	return aux_at_void;
}

s16 VECTOR_concat(Vector *vector, Vector *vector_src) {
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_VectorNullReference;
	}

	if (vector->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_StorageNullReference;
	}

	if (vector_src == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_VectorNullReference;
	}

	if (vector_src->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_StorageNullReference;
	}

	vector->ops_->resize(vector, vector->capacity_ + vector_src->capacity_);

	for (u16 i = vector_src->head_; i < vector_src->tail_; i++) {
		vector->storage_->ops_->memCopy(&vector->storage_[vector->tail_],
			vector->storage_->ops_->data(&vector_src->storage_[i]),
			vector->storage_->ops_->size(&vector_src->storage_[i]));
		vector->tail_++;
	}
	return kErrorCode_Ok;
}

s16 VECTOR_traverse(Vector *vector, void(*callback) (MemoryNode *)) {
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_VectorNullReference;
	}

	if (vector->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_StorageNullReference;
	}

	if (callback == NULL) {
		return kErrorCode_SourceNullReference;
	}

	for (u16 i = vector->head_; i <vector->tail_; i++)
	{
		callback(&vector->storage_[i]);
	}

	return kErrorCode_Ok;
}

void VECTOR_print(Vector *vector) {
	if (vector == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Vector NULL reference error\n", __FUNCTION__);
#endif
		return;
	}

	if (vector->storage_ == NULL) {
#ifdef VERBOSE_
		printf("Error: [%s] Storage NULL reference error\n", __FUNCTION__);
#endif
		return;
	}

	printf("\n----------------------------------------------------------------------\n");
	for (u16 i = vector->head_; i < vector->tail_; i++) {
		printf("\nNODE %d:", i);
		vector->storage_->ops_->print(&vector->storage_[i]);
	}
	printf("\n----------------------------------------------------------------------\n");
}