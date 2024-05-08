#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"
#include "adt_dllist.h"
#include "adt_memory_node.h"


#include "ABGS_MemoryManager\abgs_memory_manager.h"


// List Declarations
static s16 DLLIST_destroy(DLList *list);
static s16 DLLIST_reset(DLList *list);
static u16 DLLIST_length(DLList *list);
static s16 DLLIST_resize(DLList *list, u16 new_size);
static s16 DLLIST_capacity(DLList *list);
static bool DLLIST_isEmpty(DLList *list);
static bool DLLIST_isFull(DLList *list);
static void* DLLIST_first(DLList *list);
static void* DLLIST_last(DLList *list);
static void* DLLIST_at(DLList *list, u16 position);
static s16 DLLIST_insertFirst(DLList *list, void *data, u16 bytes);
static s16 DLLIST_insertLast(DLList *list, void *data, u16 bytes);
static s16 DLLIST_insertAt(DLList *list, void *data, u16 position, u16 bytes);
static void* DLLIST_extractFirst(DLList *list);
static void* DLLIST_extractLast(DLList *list);
static void* DLLIST_extractAt(DLList *list, u16 position);
static s16 DLLIST_concat(DLList *list, DLList *list_src);
static s16 DLLIST_traverse(DLList *list, void(*callaback) (MemoryNode *));
static void DLLIST_print(DLList *list);

// list's API Definitions
struct dllist_ops_s dllist_ops =
{
	.destroy = DLLIST_destroy,
	.reset = DLLIST_reset,
	.length = DLLIST_length,
	.resize = DLLIST_resize,
	.capacity = DLLIST_capacity,
	.isFull = DLLIST_isFull,
	.isEmpty = DLLIST_isEmpty,
	.first = DLLIST_first,
	.last = DLLIST_last,
	.at = DLLIST_at,
	.insertFirst = DLLIST_insertFirst,
	.insertLast = DLLIST_insertLast,
	.insertAt = DLLIST_insertAt,
	.extractFirst = DLLIST_extractFirst,
	.extractLast = DLLIST_extractLast,
	.extractAt = DLLIST_extractAt,
	.concat = DLLIST_concat,
	.traverse = DLLIST_traverse,
	.print = DLLIST_print
};

DLList* DLLIST_create(u16 capacity) 
{
	DLList* list = (DLList*)MM->malloc(sizeof(DLList));
	if (NULL == list)
	{
		return NULL;
	}
	list->capacity_ = capacity;
	list->head_ = NULL;
	list->tail_ = NULL;
	list->length_ = 0;
	list->ops_ = &dllist_ops;

	return list;
}

s16 DLLIST_destroy(DLList *list) 
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_ListNullReference;
	}

	DLLIST_reset(list);
	MM->free(list);
	return kErrorCode_Ok;
}

s16 DLLIST_reset(DLList *list) 
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_ListNullReference;
	}

	MemoryNode *current_destroy_node = list->head_;
	MemoryNode *next_destroy_node;

	for (u16 i = 0; i < list->length_; i++) {
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

s16 DLLIST_resize(DLList *list, u16 new_size) {
	if (list == NULL) {
		return kErrorCode_ListNullReference;
	}

	list->capacity_ = new_size;
	return kErrorCode_Ok;
}

s16 DLLIST_capacity(DLList *list) {
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return kErrorCode_ListNullReference;
	}

	return list->capacity_;
}

bool DLLIST_isFull(DLList *list) {
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return true;
	}

	return list->length_ == list->capacity_;
}

bool DLLIST_isEmpty(DLList *list) {
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return false;
	}

	return true;
}

u16 DLLIST_length(DLList *list) 
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return 0;
	}
	return list->length_;
}

void* DLLIST_first(DLList *list) 
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

void* DLLIST_last(DLList *list)
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

void* DLLIST_at(DLList *list, u16 position)
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

s16 DLLIST_insertFirst(DLList *list, void *data, u16 bytes) 
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

	list->head_->ops_->setNext(aux_insert, list->head_);
	list->head_->ops_->setPrev(list->head_, aux_insert);
	list->head_ = aux_insert;
	list->length_++;
	return kErrorCode_Ok;
}

s16 DLLIST_insertLast(DLList *list, void *data, u16 bytes)
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

	list->tail_->ops_->setPrev(aux_insert, list->tail_);
	list->tail_->ops_->setNext(list->tail_, aux_insert);
	list->tail_ = aux_insert;
	list->length_++;
	return kErrorCode_Ok;
}

s16 DLLIST_insertAt(DLList *list, void *data, u16 bytes, u16 position)
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
		DLLIST_insertFirst(list, data, bytes);
		return kErrorCode_Ok;
	}

	if (position >= list->length_) {
		DLLIST_insertLast(list, data, bytes);
		return kErrorCode_Ok;
	}

	if (list->head_ == NULL) {
		DLLIST_insertFirst(list, data, bytes);
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

	for (u16 i = 0; i < position; i++) {
		if (NULL == current) {
#ifdef VERBOSE_
			printf("Error: [%s] A reference was lost\n", __FUNCTION__);
#endif
			return kErrorCode_MemoryNodeNullReference;
		}
		current = current->ops_->next(current);
	}
	aux_insert->ops_->setNext(aux_insert, current);
	aux_insert->ops_->setNext(current->ops_->prev(current), aux_insert);
	aux_insert->ops_->setPrev(aux_insert, current->ops_->prev(current));
	aux_insert->ops_->setPrev(current, aux_insert);
	list->length_++;
	return kErrorCode_Ok;
}

void* DLLIST_extractFirst(DLList *list) 
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	void *extract_aux = list->head_->ops_->data(list->head_);
	MemoryNode *next = list->head_->ops_->next(list->head_);

	if (list->head_ == list->tail_) {
		list->head_->ops_->softFree(list->head_);
		list->head_ = NULL;
		list->tail_ = NULL;
		list->length_--;
		return extract_aux;
	}

	list->head_->ops_->softFree(list->head_);
	list->head_ = next;
	list->length_--;
	return extract_aux;
}

void* DLLIST_extractLast(DLList *list)
{
	if (NULL == list) {
#ifdef VERBOSE_
		printf("Error: [%s] LIST NULL reference error\n", __FUNCTION__);
#endif
		return NULL;
	}

	void *extract_aux = list->tail_->ops_->data(list->tail_);
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

void* DLLIST_extractAt(DLList *list, u16 position)
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
		return NULL;
	}

	if (0 == position) {
		return DLLIST_extractFirst(list);
	}

	if (position >= list->length_) {
		return DLLIST_extractLast(list);
	}

	MemoryNode* current_ = list->head_;

	for (int i = 0; i < position - 1; i++) {
		current_ = current_->ops_->next(current_);
	}

	void *extract_aux = list->head_->ops_->data(current_);
	
	if (list->head_ == list->tail_) {
		list->tail_->ops_->softFree(list->tail_);
		list->tail_ = NULL;
		list->head_ = NULL;
		list->length_--;
		return extract_aux;
	}

	current_->ops_->setNext(current_->ops_->prev(current_), 
							current_->ops_->next(current_));
	current_->ops_->setPrev(current_->ops_->next(current_), 
							current_->ops_->prev(current_));

	current_->ops_->softFree(current_);

	list->length_--;
	return extract_aux;
}

s16 DLLIST_concat(DLList *list, DLList *list_src) {
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
			list->tail_->ops_->setPrev(aux, list->tail_);
		}
		list->tail_ = aux;
		list->length_++;
		//aux->ops_->softFree(aux);
		next = aux->ops_->next(next);
	}
	return kErrorCode_Ok;
}

s16 DLLIST_traverse(DLList *list, void(*callaback) (MemoryNode *)) {
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

void DLLIST_print(DLList *list) {
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