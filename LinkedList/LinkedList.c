#include "LinkedList.h"


void CreateList(List *self, int datasize)
{
	Node *headNode, *tailNode;
	headNode = (Node *)malloc(sizeof(Node));
	tailNode = (Node *)malloc(sizeof(Node));

	headNode->llink = headNode;
	headNode->rlink = tailNode;
	headNode->data = NULL;

	tailNode->llink = headNode;
	tailNode->rlink = tailNode;
	tailNode->data = NULL;

	self->head = headNode;
	self->tail = tailNode;
	self->length = 0;
	self->datasize = datasize;
	self->current = self->head;
	self->DestroyList = DestroyList;
	self->InsertHeadList = InsertHeadList;
	self->InsertTailList = InsertTailList;
	self->InsertFrontList = InsertFrontList;
	self->InsertBackList = InsertBackList;
	self->DeleteHeadList = DeleteHeadList;
	self->DeleteTailList = DeleteTailList;
	self->DeleteFrontList = DeleteFrontList;
	self->DeleteBackList = DeleteBackList;
	self->DeleteDataList = DeleteDataList;
	self->DeleteAllList = DeleteAllList;
	self->SortList = SortList;
	self->SearchList = SearchList;
	self->TraverseList = TraverseList;
	self->GetLengthList = GetLengthList;
	self->MoveCurrentHead = MoveCurrentHead;
	self->MoveCurrentBack = MoveCurrentBack;
	self->MoveCurrentFront = MoveCurrentFront;
	self->MoveCurrentTail = MoveCurrentTail;
	self->GetDataList = GetDataList;
}

void DestroyList(List *self)
{
	self->DeleteAllList(self);
	free(self->head);
	free(self->tail);
	self->head = NULL;
	self->tail = NULL;
	self->current = NULL;
	self->length = 0;
}

void InsertHeadList(List *self, void *data)
{
	Node *inNode = (Node *)malloc(sizeof(Node));
	inNode->data = malloc(self->datasize);

	inNode->llink = self->head;
	inNode->rlink = self->head->rlink;

	inNode->rlink->llink = inNode;
	inNode->llink->rlink = inNode;

	memcpy((char *)inNode->data, (char *)data, self->datasize);

	(self->length)++;
}

void InsertTailList(List *self, void *data)
{
	Node *inNode = (Node *)malloc(sizeof(Node));
	inNode->data = malloc(self->datasize);

	inNode->rlink = self->tail;
	inNode->llink = self->tail->llink;

	inNode->llink->rlink = inNode;
	inNode->rlink->llink = inNode;

	memcpy(inNode->data, data, self->datasize);

	(self->length)++;
}

int InsertFrontList(List *self, void *currentdata, void *data, int(*compare)(void *, void *))
{
	Node *inNode = (Node *)malloc(sizeof(Node));
	inNode->data = malloc(self->datasize);

	if (self->SearchList(self, currentdata, compare)) {
		inNode->llink = self->current->llink;
		inNode->llink->rlink = inNode;

		inNode->rlink = self->current;
		inNode->rlink->llink = inNode;

		memcpy((char *)inNode->data, (char *)data, self->datasize);
		(self->length)++;

		return 1;
	}
	else
		return -1;
}

int InsertBackList(List *self, void *currentdata, void *data, int(*compare)(void *, void *))
{
	Node *inNode = (Node *)malloc(sizeof(Node));
	inNode->data = malloc(self->datasize);

	if (self->SearchList(self, currentdata, compare)) {
		inNode->rlink = self->current->rlink;
		inNode->rlink->llink = inNode;

		inNode->llink = self->current;
		inNode->llink->rlink = inNode;

		memcpy((char *)inNode->data, (char *)data, self->datasize);
		(self->length)++;

		return 1;
	}
	else
		return -1;
}

int DeleteHeadList(List *self)
{
	if (self->length > 0) {
		Node *deleteNode = self->head->rlink;

		self->head->rlink = self->head->rlink->rlink;
		self->head->rlink->llink = self->head;

		free(deleteNode->data);
		free(deleteNode);
		(self->length)--;

		return 1;
	}
	else
		return -1;
}

int DeleteTailList(List *self)
{
	if (self->length > 0) {
		Node *deleteNode = self->tail->llink;

		self->tail->llink = self->tail->llink->llink;
		self->tail->llink->rlink = self->tail;


		free(deleteNode);
		(self->length)--;

		return 1;
	}
	else
		return -1;
}

int DeleteFrontList(List *self, void *data, int(*compare)(void *, void *))
{
	if (self->length > 0 && self->SearchList(self, data, compare) && self->current != self->head->rlink) {
		Node *deleteNode = self->current->llink;

		deleteNode->rlink->llink = deleteNode->llink;
		deleteNode->llink->rlink = deleteNode->rlink;

		free(deleteNode);
		(self->length)--;

		return 1;
	}
	else
		return -1;
}

int DeleteBackList(List *self, void *data, int(*compare)(void *, void *))
{
	if (self->length > 0 && self->SearchList(self, data, compare) && self->current != self->tail->llink) {
		Node *deleteNode = self->current->rlink;

		deleteNode->rlink->llink = deleteNode->llink;
		deleteNode->llink->rlink = deleteNode->rlink;

		free(deleteNode);
		(self->length)--;

		return 1;
	}
	else
		return -1;
}

int DeleteDataList(List *self, void *data, int(*compare)(void *, void *))
{
	if (self->length > 0 && self->SearchList(self, data, compare)) {
		Node *deleteNode = self->current;

		deleteNode->rlink->llink = deleteNode->llink;
		deleteNode->llink->rlink = deleteNode->rlink;

		free(deleteNode);
		(self->length)--;

		return 1;
	}
	else
		return -1;
}

void DeleteAllList(List *self)
{
	while (self->length)
		self->DeleteHeadList(self);
}

void SortList(List *self, void *data, int(*compare)(void *, void *))
{
	int i;
	if (self->length)
	{
		Node *currentNode = self->head->rlink;
		for (i = 0; i<self->length; i++) {
			if (compare(currentNode->data, data) > 0) {
				self->InsertFrontList(self, currentNode->data, data, compare);
				return;
			}
			currentNode = currentNode->rlink;
		}
		self->InsertTailList(self, data);
	}
	else
	{
		self->InsertHeadList(self, data);
	}
}

int SearchList(List *self, void *data, int(*compare)(void *, void *))
{
	int i;
	Node *currentNode = self->head->rlink;
	for (i = 0; i<self->length; i++) {
		if (compare(currentNode->data, data) == 0) {
			self->current = currentNode;
			return 1;
		}
		currentNode = currentNode->rlink;
	}
	return 0;
}

void TraverseList(List *self, void(*traverse)(void *))
{
	int i;
	Node *currentNode = self->head->rlink;
	for (i = 0; i<self->length; i++) {
		traverse(currentNode->data);
		currentNode = currentNode->rlink;
	}
}

int GetLengthList(List *self)
{
	return self->length;
}

int CompareInt(void *data1, void *data2)
{
	return *(int *)data1 - *(int *)data2;
}

int CompareStr(void *data1, void *data2)
{
	return strcmp((char *)data1, (char *)data2);
}

void MoveCurrentHead(List *self)
{
	self->current = self->head;
}
void MoveCurrentBack(List *self)
{
	self->current = self->current->rlink;
}
void MoveCurrentFront(List *self)
{
	self->current = self->current->llink;
}

void MoveCurrentTail(List *self)
{
	self->current = self->tail;
}

void* GetDataList(List *self, int index)
{
	int i;
	self->MoveCurrentHead(self);
	if (index < self->length) {
		for (i = 0; i <= index; i++) {
			self->MoveCurrentBack(self);
		}
		return self->current->data;
	}
	return 0;
}