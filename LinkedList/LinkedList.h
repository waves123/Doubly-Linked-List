#pragma once
#ifndef __Link_List_H_
#define __Link_List_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

typedef struct __Node Node;
typedef struct __Node
{
	void *data;
	Node *llink;
	Node *rlink;
} Node;

typedef struct __List List;
typedef struct __List
{
	Node *head;
	Node *tail;
	int length;
	int datasize;
	Node *current;

	void(*DestroyList)(List *self);
	void(*InsertHeadList)(List *self, void *data);
	void(*InsertTailList)(List *self, void *data);
	int(*InsertFrontList)(List *self, void *currentdata, void *data, int(*compare)(void *, void *));
	int(*InsertBackList)(List *self, void *currentdata, void *data, int(*compare)(void *, void *));
	int(*DeleteHeadList)(List *self);
	int(*DeleteTailList)(List *self);
	int(*DeleteFrontList)(List *self, void *data, int(*compare)(void *, void *));
	int(*DeleteBackList)(List *self, void *data, int(*compare)(void *, void *));
	int(*DeleteDataList)(List *self, void *data, int(*compare)(void *, void *));
	void(*DeleteAllList)(List *self);
	void(*SortList)(List *self, void *data, int(*compare)(void *, void *));
	int(*SearchList)(List *self, void *data, int(*compare)(void *, void *));
	void(*TraverseList)(List *self, void(*traverse)(void *));
	int(*GetLengthList)(List *self);

	void(*MoveCurrentHead)(List *self);
	void(*MoveCurrentBack)(List *self);
	void(*MoveCurrentFront)(List *self);
	void(*MoveCurrentTail)(List *self);

	void* (*GetDataList)(List *self, int index);
} List;

void CreateList(List *self, int datasize);
void DestroyList(List *self);
void InsertHeadList(List *self, void *data);
void InsertTailList(List *self, void *data);
int InsertFrontList(List *self, void *currentdata, void *data, int(*compare)(void *, void *));
int InsertBackList(List *self, void *currentdata, void *data, int(*compare)(void *, void *));
int DeleteHeadList(List *self);
int DeleteTailList(List *self);
int DeleteFrontList(List *self, void *data, int(*compare)(void *, void *));
int DeleteBackList(List *self, void *data, int(*compare)(void *, void *));
int DeleteDataList(List *self, void *data, int(*compare)(void *, void *));
void DeleteAllList(List *self);
void SortList(List *self, void *data, int(*compare)(void *, void *));
int SearchList(List *self, void *data, int(*compare)(void *, void *));
int CompareInt(void *data1, void *data2);
int CompareStr(void *data1, void *data2);
void TraverseList(List *self, void(*traverse)(void *));
int GetLengthList(List *self);

void MoveCurrentHead(List *self);
void MoveCurrentBack(List *self);
void MoveCurrentFront(List *self);
void MoveCurrentTail(List *self);

void* GetDataList(List *self, int index);



#endif