// common_def.h
// Toni Barella
// Algoritmos & Inteligencia Artificial
// ESAT 2016-2019
//
#ifndef __COMMON_DEF_H__
#define __COMMON_DEF_H__

#define VERBOSE_

#define TEST_ 1

typedef enum
{
	kErrorCode_Ok = 0,
	kErrorCode_Memory = -10,
	kErrorCode_MemoryNodeNullReference = -11,
	kErrorCode_SourceNullReference = -12,
	kErrorCode_VectorNullReference = -15,
	kErrorCode_StorageNullReference = -16,
	kErrorCode_ListNullReference = -20,
	kErrorCode_LostReference = -21,
	kErrorCode_InvalidSize = -30,
	kErrorCode_FullVector = -31,
	kErrorCode_NullStack = -40,
} ErrorCode;

#endif // __COMMON_DEF_H__