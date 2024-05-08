#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"
#include "adt_list.h"
#include "adt_vector.h"
#include "adt_memory_node.h"

#include "ABGS_MemoryManager\abgs_memory_manager.h"


// List Declarations
static s16 LIST_destroy(List *list);
static s16 LIST_reset(List *list);
static u16 LIST_length(List *list);
static s16 LIST_resize(List *list, u16 new_size);
static s16 LIST_capacity(List *list);
static bool LIST_isEmpty(List *list);
static bool LIST_isFull(List *list);
static void* LIST_first(List *list);
static void* LIST_last(List *list);
static void* LIST_at(List *list, u16 position);
static s16 LIST_insertFirst(List *list, void *data, u16 bytes);
static s16 LIST_insertLast(List *list, void *data, u16 bytes);
static s16 LIST_insertAt(List *list, void *data, u16 position, u16 bytes);
static void* LIST_extractFirst(List *list);
static void* LIST_extractLast(List *list);
static void* LIST_extractAt(List *list, u16 position);
static s16 LIST_concat(List *list, List *list_src);
static s16 LIST_traverse(List *list, void(*callaback) (MemoryNode *));
static void LIST_print(List *list);

// list's API Definitions
struct list_ops_s list_ops =
{
	.destroy = LIST_destroy,
	.reset = LIST_reset,
	.resize = LIST_resize,
	.capacity = LIST_capacity,
	.isFull = LIST_isFull,
	.isEmpty = LIST_isEmpty,
	.length = LIST_length,
	.first = LIST_first,
	.last = LIST_last,
	.at = LIST_at,
	.insertFirst = LIST_insertFirst,
	.insertLast = LIST_insertLast,
	.insertAt = LIST_insertAt,
	.extractFirst = LIST_extractFirst,
	.extractLast = LIST_extractLast,
	.extractAt = LIST_extractAt,
	.concat = LIST_concat,
	.traverse = LIST_traverse,
	.print = LIST_print
};

List* LIST_create(u16 capacity)
{
	List* list = (List*)MM->malloc(sizeof(List));
	if (NULL == list)
	{
		return NULL;
	}

	list->capacity_ = capacity;

	list->head_ = NULL;
	list->tail_ = NULL;
	list->length_ = 0;
	list->ops_ = &list_ops;

	return list;
}

s16 LIST_destroy(List *list) 
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_ListNullReference;
	}

	LIST_reset(list);
	MM->free(list);
	return kErrorCode_Ok;
}

s16 LIST_reset(List *list) 
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_ListNullReference;
	}

	MemoryNode *current_destroy_node = list->head_;
	MemoryNode *next_destroy_node;

	for (int i = 0; i < list->length_; i++) {
		if (NULL == current_destroy_node) {
#ifdef VERBOSE_
			printf("Error: [%s] A reference was lost\n", __FUNCTION__);
#endif
			return kErrorCode_LostReference;
		}
		next_destroy_node = current_destroy_node->ops_->next(current_destroy_node);
		current_destroy_node->ops_->free(current_destroy_node);
		current_destroy_node = next_destroy_node;
	}

	list->head_ = NULL;
	list->tail_ = NULL;
	list->length_ = 0;
	return kErrorCode_Ok;
}

s16 LIST_resize(List *list, u16 new_size) {
	if (list == NULL) {
		return kErrorCode_ListNullReference;
	}

	list->capacity_ = new_size;
	return kErrorCode_Ok;
}

s16 LIST_capacity(List *list) {
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_ListNullReference;
	}

	return list->capacity_;
}

bool LIST_isFull(List *list) {
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return true;
	}

	return list->length_ == list->capacity_;
}

bool LIST_isEmpty(List *list) {
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return false;
	}

	return true;
}

u16 LIST_length(List *list) 
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return 0;
	}

	return list->length_;
}

void* LIST_first(List *list) 
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}
	if (NULL == list->head_) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}
	return list->head_->ops_->data(list->head_);
}

void* LIST_last(List *list)
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	if (NULL == list->tail_) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	return list->tail_->ops_->data(list->tail_);
}

void* LIST_at(List *list, u16 position)
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}
	if (0 >= position) {
#ifdef VERBOSE_
		printf("Error: [%s] Invalid position <= 0\n", __FUNCTION__);
#endif
		return NULL;
	}
	if (position > list->length_) {
#ifdef VERBOSE_
		printf("Error: [%s] Invalid position > length\n", __FUNCTION__);
#endif
		return NULL;
	}

	MemoryNode *current = list->head_;

	for (u16 i = 0; i < position; i++) {
		if (NULL == current) {
#ifdef VERBOSE_
			printf("Error: [%s] A reference was lost\n", __FUNCTION__);
#endif
			return NULL;
		}
		current = current->ops_->next(current);
	}

	return current->ops_->data(current);
}

s16 LIST_insertFirst(List *list, void *data, u16 bytes) 
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_ListNullReference;
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

	MemoryNode *aux_insert = MEMNODE_create();
	if (aux_insert == NULL) {
		return kErrorCode_LostReference;
	}

	if (aux_insert->ops_->setData(aux_insert, data, bytes) < 0) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_ListNullReference;
	}

	if (list->head_ == NULL) {
		list->head_ = aux_insert;
		list->tail_ = aux_insert;
		list->length_++;
		return kErrorCode_Ok;
	}

	aux_insert->ops_->setNext(aux_insert, list->head_);
	list->head_ = aux_insert;
	list->length_++;
	return kErrorCode_Ok;
}

s16 LIST_insertLast(List *list, void *data, u16 bytes)
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_ListNullReference;
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

	MemoryNode *aux_insert = MEMNODE_create();
	if (aux_insert == NULL) {
		return kErrorCode_LostReference;
	}

	if (aux_insert->ops_->setData(aux_insert, data, bytes) < 0) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_ListNullReference;
	}
	
	if (list->head_ == NULL) {
		list->head_ = aux_insert;
		list->tail_ = aux_insert;
		list->length_++;
		return kErrorCode_Ok;
	}

	list->tail_->ops_->setNext(list->tail_, aux_insert);
	list->tail_ = aux_insert;
	list->length_++;
	return kErrorCode_Ok;
}

s16 LIST_insertAt(List *list, void *data, u16 bytes, u16 position)
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_ListNullReference;
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

	if (0 > position) {
#ifdef VERBOSE_
		printf("Error: [%s] Invalid position index\n", __FUNCTION__);
#endif
		return kErrorCode_InvalidSize;
		
	}

	if (0 == position) {
		LIST_insertFirst(list, data, bytes);
		return kErrorCode_Ok;
	}

	if (position >= list->length_) {
		LIST_insertLast(list, data, bytes);
		return kErrorCode_Ok;
	}

	if (list->head_ == NULL) {
		LIST_insertFirst(list, data, bytes);
		return kErrorCode_Ok;
	}

	MemoryNode *aux_insert = MEMNODE_create();
	if (aux_insert == NULL) {
		return kErrorCode_LostReference;
	}

	MemoryNode *current = list->head_;
	if (aux_insert->ops_->setData(aux_insert, data, bytes) < 0) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_ListNullReference;
	}

	for (u16 i = 0; i < position - 1; i++) {
		if (NULL == current) {
#ifdef VERBOSE_
			printf("Error: [%s] A reference was lost\n", __FUNCTION__);
#endif
			return kErrorCode_MemoryNodeNullReference;
		}
		current = current->ops_->next(current);
	}

	aux_insert->ops_->setNext(aux_insert, current->next_);
	aux_insert->ops_->setNext(current, aux_insert);
	list->length_++;
	return kErrorCode_Ok;
}

void* LIST_extractFirst(List *list) 
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}
	void *extract_aux = NULL;

	extract_aux = list->tail_->ops_->data(list->head_);

	if (list->head_ == list->tail_) {
		list->head_->ops_->softFree(list->head_);
		list->head_ = NULL;
		list->tail_ = NULL;
		list->length_--;
		return extract_aux;
	}

	MemoryNode *next = list->head_->ops_->next(list->head_);
	list->head_->ops_->softFree(list->head_);
	list->head_ = next;
	list->length_--;

	return extract_aux;
}

void* LIST_extractLast(List *list)
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	void *extract_aux = list->head_->ops_->data(list->tail_);
	MemoryNode *prev = list->head_;

	if (list->head_ == list->tail_) {
		list->tail_->ops_->softFree(list->tail_);
		list->tail_ = NULL;
		list->head_ = NULL;
		list->length_--;
		return extract_aux;
	}

	for (int i = 0; i < list->length_ - 2; i++) {
		prev = prev->ops_->next(prev);
	}

	list->tail_->ops_->softFree(list->tail_);
	list->tail_ = prev;
	list->length_--;
	return extract_aux;
}

void* LIST_extractAt(List *list, u16 position)
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	if (0 > position) {
#ifdef VERBOSE_
		printf("Error: [%s] Invalid position index\n", __FUNCTION__);
#endif
		return kErrorCode_InvalidSize;
	}

	if (0 == position) {
		return LIST_extractFirst(list);
	}

	if (list->length_ <= position) {
		return LIST_extractLast(list);
	}

	

	MemoryNode* current_ = list->head_;
	MemoryNode* at_ = NULL;

	for (int i = 0; i < position - 2; i++) {
		current_ = current_->ops_->next(current_);
	}

	void *extract_aux = list->head_->ops_->data(current_->ops_->next(current_));

	if (list->head_ == list->tail_) {
		list->tail_->ops_->softFree(list->tail_);
		list->tail_ = NULL;
		list->head_ = NULL;
		list->length_--;
		return extract_aux;
	}

	at_ = current_->ops_->next(current_);

	current_->ops_->setNext(current_, current_->ops_->next(at_));

	if(at_ != NULL)
	at_->ops_->softFree(at_);

	list->length_--;
	return extract_aux;
}

s16 LIST_concat(List *list, List *list_src) {
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_ListNullReference;
	}

	if (NULL == list_src) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_ListNullReference;
	}
	MemoryNode *next = list_src->head_;
	for (int i = 0; i < list_src->length_; i++) {
		MemoryNode *aux = MEMNODE_create();
		aux->ops_->memCopy(aux, aux->ops_->data(next), aux->ops_->size(next));
		if (list->tail_ == NULL) {
			list->head_ = aux;
		}
		else {
			list->tail_->ops_->setNext(list->tail_, aux);
		}
		list->tail_ = aux;
		list->length_++;
		//aux->ops_->softFree(aux);
		next = aux->ops_->next(next);
	}
	return kErrorCode_Ok;
}

s16 LIST_traverse(List *list, void(*callaback) (MemoryNode *)) {
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_ListNullReference;
	}

	if (callaback == NULL) {
		return kErrorCode_SourceNullReference;
	}

	MemoryNode *aux = list->head_;

	for (int i = 0; i < list->length_; i++)
	{
		callaback(aux);
		aux = aux->ops_->next(aux);
	}
	return kErrorCode_Ok;
}

void LIST_print(List *list) {
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return;
	}

	MemoryNode* current = list->head_;
	for (u16 i = 0; i < list->length_; i++) {
		if (NULL == current) {
#ifdef VERBOSE_
			printf("Error: [%s] A reference was lost\n", __FUNCTION__);
#endif
			return;
		}
		current->ops_->print(current);
		current = current->ops_->next(current);
	}
}