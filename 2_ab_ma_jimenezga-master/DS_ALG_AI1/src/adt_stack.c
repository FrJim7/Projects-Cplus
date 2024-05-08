#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"
#include "adt_stack.h"
#include "adt_vector.h"
#include "adt_memory_node.h"


#include "ABGS_MemoryManager\abgs_memory_manager.h"


// Stack Declarations
static s16 STACK_destroy(Stack *stack);
static s16 STACK_reset(Stack *stack);
static s16 STACK_resize(Stack *stack, u16 new_size);
static u16 STACK_capacity(Stack *stack);
static s16 STACK_length(Stack *stack);
static bool STACK_isEmpty(Stack *stack);
static bool STACK_isFull(Stack *stack);
static void* STACK_top(Stack *stack);
static s16 STACK_push(Stack *stack, void *data, u16 bytes);
static void* STACK_pop(Stack *stack);
static s16 STACK_concat(Stack *stack, Stack *stack_src);
static s16 STACK_traverse(Stack *stack, void(*callaback) (MemoryNode *));
static void STACK_print(Stack *stack);


struct stack_ops_s stack_ops =
{
	.destroy = STACK_destroy,
	.reset = STACK_reset,
	.resize = STACK_resize,
	.capacity = STACK_capacity,
	.length = STACK_length,
	.isEmpty = STACK_isEmpty,
	.isFull = STACK_isFull,
	.top = STACK_top,
	.push = STACK_push,
	.pop = STACK_pop,
	.concat = STACK_concat,
	.traverse = STACK_traverse,
	.print = STACK_print
};


Stack* STACK_create(u16 capacity) {
	if (0 >= capacity) {
		return NULL;
	}

	Stack *aux_create = (Stack*)MM->malloc(sizeof(Stack));
	if (aux_create == NULL) {
		return NULL;
	}

	aux_create->storage_ = VECTOR_create(capacity);
	if (aux_create->storage_ == NULL) {
		return NULL;
	}

	aux_create->ops_ = &stack_ops;
	return aux_create;
}

s16 STACK_destroy(Stack *stack) {
	if (stack == NULL) {
		return kErrorCode_NullStack;
	}

	if (stack->storage_ == NULL) {
		return kErrorCode_StorageNullReference;
	}

	stack->storage_->ops_->destroy(stack->storage_);
	MM->free(stack);
	stack = NULL;

	return kErrorCode_Ok;
}

s16 STACK_reset(Stack *stack) {
	if (stack == NULL) {
		return kErrorCode_NullStack;
	}

	if (stack->storage_ == NULL) {
		return kErrorCode_StorageNullReference;
	}

	return stack->storage_->ops_->reset(stack->storage_);
}

s16 STACK_resize(Stack *stack, u16 new_size) {
	if (stack == NULL) {
		return kErrorCode_NullStack;
	}

	if (stack->storage_ == NULL) {
		return kErrorCode_StorageNullReference;
	}

	if (0 > new_size) {
		return kErrorCode_InvalidSize;
	}

	return stack->storage_->ops_->resize(stack->storage_, new_size);
}

s16 STACK_capacity(Stack *stack) {
	if (stack == NULL) {
		return kErrorCode_NullStack;
	}

	if (stack->storage_ == NULL) {
		return kErrorCode_StorageNullReference;
	}

	return stack->storage_->ops_->capacity(stack->storage_);
}

s16 STACK_length(Stack *stack) {
	if (stack == NULL) {
		return kErrorCode_NullStack;
	}

	if (stack->storage_ == NULL) {
		return kErrorCode_StorageNullReference;
	}

	return stack->storage_->ops_->length(stack->storage_);
}

bool STACK_isEmpty(Stack *stack) {
	if (stack == NULL) {
		return false;
	}

	if (stack->storage_ == NULL) {
		return false;
	}
	return stack->storage_->ops_->isEmpty(stack->storage_);
}

bool STACK_isFull(Stack *stack) {
	if (stack == NULL) {
		return true;
	}

	if (stack->storage_ == NULL) {
		return true;
	}
	return stack->storage_->ops_->isFull(stack->storage_);
}

void* STACK_top(Stack *stack) {
	if (stack == NULL) {
		return NULL;
	}

	if (stack->storage_ == NULL) {
		return NULL;
	}

	return stack->storage_->ops_->last(stack->storage_);
}

s16 STACK_push(Stack *stack, void *data, u16 bytes) {
	if (stack == NULL) {
		return kErrorCode_NullStack;
	}

	if (stack->storage_ == NULL) {
		return kErrorCode_StorageNullReference;
	}

	if (data == NULL) {
		return kErrorCode_SourceNullReference;
	}

	if (bytes <= 0) {
		return kErrorCode_InvalidSize;
	}

	return stack->storage_->ops_->insertLast(stack->storage_, data, bytes);
}

void* STACK_pop(Stack *stack) {
	if (stack == NULL) {
		return NULL;
	}

	if (stack->storage_ == NULL) {
		return NULL;
	}

	return stack->storage_->ops_->extractLast(stack->storage_);
}

s16 STACK_concat(Stack *stack, Stack *stack_src) {
	if (stack == NULL) {
		return kErrorCode_NullStack;
	}

	if (stack_src == NULL) {
		return kErrorCode_NullStack;
	}

	if (stack->storage_ == NULL) {
		return kErrorCode_StorageNullReference;
	}

	if (stack_src->storage_ == NULL) {
		return kErrorCode_StorageNullReference;
	}

	return stack->storage_->ops_->concat(stack->storage_, stack_src->storage_);
}

s16 STACK_traverse(Stack *stack, void(*callaback) (MemoryNode *)) {
	if (stack == NULL) {
		return kErrorCode_NullStack;
	}

	if (stack->storage_ == NULL) {
		return kErrorCode_StorageNullReference;
	}

	if (callaback == NULL) {
		return kErrorCode_SourceNullReference;
	}

	return stack->storage_->ops_->traverse(stack->storage_, callaback);
}

void STACK_print(Stack *stack) {
	if (stack == NULL) {
		return;
	}

	if (stack->storage_ == NULL) {
		return;
	}

	stack->storage_->ops_->print(stack->storage_);
}