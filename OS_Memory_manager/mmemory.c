#include <stdlib.h>
#include <stdbool.h>
#include "mmemory.h"

#define VIRTUAL_ADRESS_SPACE_SIZE		1024 * 1024;
#define LAST_ACCESSIBLE_VIRTUAL_ADRESS	(VIRTUAL_ADRESS_SPACE_SIZE / sizeof(VA) - 1);

VA firstFreeVirtualAdress = NULL;


typedef struct {
	VA	startingVirtualAdress;
	int size;
} Segment;

typedef struct {
	Segment segment;
	void*	physicalAdress;
	bool	isInPhysicalMemory;
} SegmentTableRecord;

typedef struct {
	SegmentTableRecord* firstRecord;
	int					size;
} SegmentTable;

#define SEGMENT_TABLE_RECORDS_COUNT_DEFAULT 1000;
#define SEGMENT_TABLE_SIZE_DEFAULT			(sizeof(SegmentTable) + sizeof(SegmentTableRecord) * SEGMENT_TABLE_RECORDS_COUNT_DEFAULT);

SegmentTable* segmentTable;


void create_record (VA*		segmentVirtualAdress,
					size_t	segmentSize) 
{
	SegmentTableRecord* recordPtr = segmentTable->firstRecord + segmentTable->size;

	SegmentTableRecord recordInfo;
	recordInfo.physicalAdress = NULL;
	recordInfo.isInPhysicalMemory = false;
	recordInfo.segment.startingVirtualAdress = segmentVirtualAdress;
	recordInfo.segment.size = segmentSize;

	memcpy((void*)recordPtr, (void*)&recordInfo, sizeof(SegmentTableRecord));

	segmentTable->size++;
	firstFreeVirtualAdress = segmentVirtualAdress + segmentSize - 1;
}