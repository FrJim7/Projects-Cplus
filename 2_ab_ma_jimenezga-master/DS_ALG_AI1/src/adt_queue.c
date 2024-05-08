#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"
#include "adt_queue.h"
#include "adt_list.h"
#include "adt_memory_node.h"


#include "ABGS_MemoryManager\abgs_memory_manager.h"


// Queue Declarations
static s16 QUEUE_destroy(Queue *queue);
static s16 QUEUE_reset(Queue *queue);
static s16 QUEUE_resize(Queue *queue, u16 new_size);
static u16 QUEUE_capacity(Queue *queue);
static s16 QUEUE_length(Queue *queue);
static bool QUEUE_isEmpty(Queue *queue);
static bool QUEUE_isFull(Queue *queue);
static void* QUEUE_front(Queue *queue);
static void* QUEUE_back(Queue *queue);
static s16 QUEUE_enqueue(Queue *queue, void *data, u16 bytes);
static void* QUEUE_dequeue(Queue *queue);
static s16 QUEUE_concat(Queue *queue, Queue *queue_src);
static s16 QUEUE_traverse(Queue *queue, void(*callaback) (MemoryNode *));
static void QUEUE_print(Queue *queue
);


struct queue_ops_s queue_ops =
{
	.destroy = QUEUE_destroy,
	.reset = QUEUE_reset,
	.resize = QUEUE_resize,
	.capacity = QUEUE_capacity,
	.length = QUEUE_length,
	.isEmpty = QUEUE_isEmpty,
	.isFull = QUEUE_isFull,
	.front = QUEUE_front,
	.back = QUEUE_back,
	.enqueue = QUEUE_enqueue,
	.dequeue = QUEUE_dequeue,
	.concat = QUEUE_concat,
	.traverse = QUEUE_traverse,
	.print = QUEUE_print
};


Queue* QUEUE_create(u16 capacity) {
	if (0 >= capacity) {
		return NULL;
	}

	Queue* aux_create = (Queue*)MM->malloc(sizeof(Queue));
	if (NULL == aux_create) {
		return NULL;
	}

	aux_create->storage_ = LIST_create(capacity);
	if (NULL == aux_create->storage_) {
		return NULL;
	}

	aux_create->ops_ = &queue_ops;

	return aux_create;
}

s16 QUEUE_destroy(Queue *queue) {
	if (NULL == queue) {
		return kErrorCode_Memory;
	}

	if (NULL == queue->storage_) {
		return kErrorCode_StorageNullReference;
	}

	queue->storage_->ops_->destroy(queue->storage_);
	MM->free(queue);
	queue = NULL;

	return kErrorCode_Ok;
}

s16 QUEUE_reset(Queue *queue) {
	if (NULL == queue) {
		return kErrorCode_Memory;
	}
	
	if (NULL == queue->storage_) {
		return kErrorCode_StorageNullReference;
	}

	return queue->storage_->ops_->reset(queue->storage_);
}

s16 QUEUE_resize(Queue *queue, u16 new_size) {
	if (0 > new_size) {
		return kErrorCode_InvalidSize;
	}

	if (NULL == queue) {
		return kErrorCode_Memory;
	}

	if (NULL == queue->storage_) {
		return kErrorCode_StorageNullReference;
	}

	return queue->storage_->ops_->resize(queue->storage_, new_size);
}

s16 QUEUE_capacity(Queue *queue) {
	if (NULL == queue) {
		return kErrorCode_Memory;
	}

	if (NULL == queue->storage_) {
		return kErrorCode_StorageNullReference;
	}

	return queue->storage_->ops_->capacity(queue->storage_);
}

s16 QUEUE_length(Queue *queue) {
	if (NULL == queue) {
		return kErrorCode_Memory;
	}

	if (NULL == queue->storage_) {
		return kErrorCode_StorageNullReference;
	}

	return queue->storage_->ops_->length(queue->storage_);
}

bool QUEUE_isEmpty(Queue *queue) {
	if (NULL == queue) {
		return false;
	}

	if (NULL == queue->storage_) {
		return false;
	}

	return queue->storage_->ops_->isEmpty(queue->storage_);
}

bool QUEUE_isFull(Queue *queue) {
	if (NULL == queue) {
		return true;
	}

	if (NULL == queue->storage_) {
		return true;
	}

	return queue->storage_->ops_->isFull(queue->storage_);
}

void* QUEUE_front(Queue *queue) {
	if (NULL == queue) {
		return NULL;
	}

	if (NULL == queue->storage_) {
		return NULL;
	}

	return queue->storage_->ops_->first(queue->storage_);
}

void* QUEUE_back(Queue *queue) {
	if (NULL == queue) {
		return NULL;
	}

	if (NULL == queue->storage_) {
		return NULL;
	}

	return queue->storage_->ops_->last(queue->storage_);
}

s16 QUEUE_enqueue(Queue *queue, void *data, u16 bytes) {
	if (NULL == queue) {
		return kErrorCode_Memory;
	}

	if (NULL == queue->storage_) {
		return kErrorCode_StorageNullReference;
	}

	if (data == NULL) {
		return kErrorCode_SourceNullReference;
	}

	if (bytes <= 0) {
		return kErrorCode_InvalidSize;
	}

	return queue->storage_->ops_->insertLast(queue->storage_, data, bytes);
}

void* QUEUE_dequeue(Queue *queue) {
	if (NULL == queue) {
		return NULL;
	}

	if (NULL == queue->storage_) {
		return NULL;
	}

	return queue->storage_->ops_->extractFirst(queue->storage_);
}

s16 QUEUE_concat(Queue *queue, Queue *queue_src) {
	if (NULL == queue) {
		return kErrorCode_Memory;
	}

	if (NULL == queue_src) {
		return kErrorCode_Memory;
	}

	if (NULL == queue->storage_) {
		return kErrorCode_StorageNullReference;
	}

	if (NULL == queue_src->storage_) {
		return kErrorCode_StorageNullReference;
	}

	return queue->storage_->ops_->concat(queue->storage_, queue_src->storage_);
}

s16 QUEUE_traverse(Queue *queue, void(*callaback) (MemoryNode *)) {
	if (NULL == queue) {
		return kErrorCode_Memory;
	}

	if (NULL == queue->storage_) {
		return kErrorCode_StorageNullReference;
	}

	if (NULL == callaback) {
		return kErrorCode_Memory;
	}

	return queue->storage_->ops_->traverse(queue->storage_, callaback);
}

void QUEUE_print(Queue *queue) {
	if (NULL == queue) {
		return;
	}

	if (NULL == queue->storage_) {
		return;
	}

	queue->storage_->ops_->print(queue->storage_);
}