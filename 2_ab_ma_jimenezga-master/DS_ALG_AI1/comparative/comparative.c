// comparative.c
// Toni Barella
// Algoritmos & Inteligencia Artificial
// ESAT 2016-2019
//
// File for comparative of ADTs
#include <windows.h>
#include <adt_dllist.h>
#include <adt_list.h>
#include <adt_vector.h>
#include "adt_memory_node.h"


#include "ABGS_MemoryManager\abgs_memory_manager.h"

#include ".\..\tests\test_base.c"

struct DataTest
{
	u32 *test_data1;
	u32 *test_data2;
	u32 *test_data3;
	u32 *test_data4;
}dataTest;

struct DataADT
{
	Vector *vec1;
	DLList *dlist1;
	List *list;
}adtTest;

void TESTBASE_generateDataForComparative()
{
	dataTest.test_data1 = (u32 *)malloc(sizeof(u32) * 1000);
	dataTest.test_data2 = (u32 *)malloc(sizeof(u32) * 1000);
	dataTest.test_data3 = (u32 *)malloc(sizeof(u32) * 1000);
	dataTest.test_data4 = (u32 *)malloc(sizeof(u32) * 1000);
	for (u32 i = 0; i < 1000; i++)
	{
		dataTest.test_data1[i] = i + 1;
		dataTest.test_data2[i] = i + 1;
		dataTest.test_data3[i] = i + 1;
		dataTest.test_data4[i] = i + 1;
	}

	adtTest.vec1   = VECTOR_create(1000);
	adtTest.list   = LIST_create(1000);
	adtTest.dlist1 = DLLIST_create(1000);
}

void calculateTimeForFunction()
{
	LARGE_INTEGER frequency;				// ticks per second
	LARGE_INTEGER  time_start, time_end;    // ticks in interval
	double elapsed_time = 0.0f;
	u32 repetitions = 1000;

	QueryPerformanceFrequency(&frequency);
	
	printf("\t VECTOR TEST TIMES\n");

	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		adtTest.vec1->ops_->insertFirst(adtTest.vec1, (void*)dataTest.test_data1[rep], sizeof(dataTest.test_data1[rep]));
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - Vector - InsertFirst:   %f \n", elapsed_time);

	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		 dataTest.test_data1[rep] = (u32)adtTest.vec1->ops_->extractFirst(adtTest.vec1);
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	adtTest.vec1->ops_->reset(adtTest.vec1);

	printf("\n- - - Vector - extractFirst:  %f \n", elapsed_time);
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		adtTest.vec1->ops_->insertLast(adtTest.vec1, (void*)dataTest.test_data1[rep], sizeof(dataTest.test_data1[rep]));
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - Vector - InsertLast:   %f \n", elapsed_time);

	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		dataTest.test_data1[rep] = (u32)adtTest.vec1->ops_->extractLast(adtTest.vec1);
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - Vector - extractLast:  %f \n", elapsed_time);

	adtTest.vec1->ops_->reset(adtTest.vec1);
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		adtTest.vec1->ops_->insertAt(adtTest.vec1, (void*)dataTest.test_data1[rep], sizeof(dataTest.test_data1[rep]), 500);
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - Vector - InsertAt:   %f \n", elapsed_time);

	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		dataTest.test_data1[rep] = (u32)adtTest.vec1->ops_->extractAt(adtTest.vec1, 500);
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - Vector - extractAt:  %f \n", elapsed_time);
	//////////////////////////////////////////////////////////////////////////////////////////////////////





	printf("\n\n\t LIST TEST TIMES\n");

	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		adtTest.list->ops_->insertFirst(adtTest.list, (void*)dataTest.test_data2[rep], sizeof(dataTest.test_data2[rep]));
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - List - InsertFirst:   %f \n", elapsed_time);
	
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		dataTest.test_data2[rep] = (u32)adtTest.list->ops_->extractFirst(adtTest.list);
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - List - extractFirst:  %f \n", elapsed_time);

	adtTest.list->ops_->reset(adtTest.list);
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		adtTest.list->ops_->insertLast(adtTest.list, (void*)dataTest.test_data2[rep], sizeof(dataTest.test_data2[rep]));
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - List - InsertLast:   %f \n", elapsed_time);

	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		dataTest.test_data2[rep] = (u32)adtTest.list->ops_->extractLast(adtTest.list);
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - List - extractLast:  %f \n", elapsed_time);

	adtTest.vec1->ops_->reset(adtTest.list);
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions ; ++rep)
	{
		adtTest.list->ops_->insertAt(adtTest.list, (void*)dataTest.test_data4[rep], sizeof(dataTest.test_data4[rep]), 5);
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - List - InsertAt:   %f \n", elapsed_time);

	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		dataTest.test_data4[rep] = (u32)adtTest.list->ops_->extractAt(adtTest.list, 500);
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - List - extractAt:  %f \n", elapsed_time);
	//////////////////////////////////////////////////////////////////////////////////////////////////////



	printf("\n\n\t DLIST TEST TIMES\n");

	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		adtTest.dlist1->ops_->insertFirst(adtTest.dlist1, (void*)dataTest.test_data3[rep], sizeof(dataTest.test_data3[rep]));
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - DList - InsertFirst:   %f \n", elapsed_time);

	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		dataTest.test_data3[rep] = (u32)adtTest.dlist1->ops_->extractFirst(adtTest.dlist1);
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - DList - extractFirst:  %f \n", elapsed_time);

	adtTest.dlist1->ops_->reset(adtTest.dlist1);
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		adtTest.dlist1->ops_->insertLast(adtTest.dlist1, (void*)dataTest.test_data3[rep], sizeof(dataTest.test_data3[rep]));
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - DList - InsertLast:   %f \n", elapsed_time);

	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		dataTest.test_data3[rep] = (u32)adtTest.dlist1->ops_->extractLast(adtTest.dlist1);
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - DList - extractLast:  %f \n", elapsed_time);

	adtTest.vec1->ops_->reset(adtTest.dlist1);
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		adtTest.dlist1->ops_->insertAt(adtTest.dlist1, (void*)dataTest.test_data3[rep], sizeof(dataTest.test_data3[rep]), 500);
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - DList - InsertAt:   %f \n", elapsed_time);

	QueryPerformanceCounter(&time_start);
	for (u32 rep = 0; rep < repetitions; ++rep)
	{
		dataTest.test_data3[rep] = (u32)adtTest.dlist1->ops_->extractAt(adtTest.dlist1, 2);
	}
	QueryPerformanceCounter(&time_end);

	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n- - - DList - extractAt:  %f \n", elapsed_time);
	//////////////////////////////////////////////////////////////////////////////////////////////////////


	
	free(dataTest.test_data1);
	free(dataTest.test_data2);
	free(dataTest.test_data3);
	/*adtTest.vec1->ops_->destroy(adtTest.vec1);
	adtTest.list->ops_->destroy(adtTest.list);
	adtTest.dlist1->ops_->destroy(adtTest.dlist1);*/
}

int main()
{
	MM->status();
	TESTBASE_generateDataForComparative();
	calculateTimeForFunction();
	MM->status();
	MM->destroy();
	printf("Press ENTER to continue\n");
	getchar();
	return 0;
}
