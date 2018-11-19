#include "calcHead.h"
#include <stdio.h>
#include <stdlib.h>

StackHead* CreateStack() {
	StackHead* pStack = (StackHead*)malloc(sizeof(StackHead));
	if (pStack == NULL)
		return NULL;
	pStack->count = 0;
	pStack->top = NULL;

	return pStack;
}

CalcHead* CreateCalcStack() {
	CalcHead* pStack = (CalcHead*)malloc(sizeof(CalcHead));
	if (pStack == NULL)
		return NULL;
	pStack->top = NULL;

	return pStack;
}

void pushStack(StackHead* pStack, Element item) {
	StackNode *pNewNode = (StackNode*)malloc(sizeof(StackNode));
	if (pNewNode == NULL)
		return NULL;
	pNewNode->data = item;
	pNewNode->next = pStack->top;
	pStack->top = pNewNode;
	pStack->count++;
}

void pushCalcStack(CalcHead* pStack, int item) {
	CalcNode *pNewNode = (CalcNode*)malloc(sizeof(CalcNode));
	if (pNewNode == NULL)
		return NULL;
	pNewNode->data = item;
	pNewNode->next = pStack->top;
	pStack->top = pNewNode;
}

Element topStack(StackHead* pStack) {
	if (pStack->top == NULL)
		return NULL;
	
	return pStack->top->data;
}

Element popStack(StackHead* pStack) {
	StackNode *pOldTop;

	if (pStack->top == NULL)
		return NULL;
	else {
		Element item = pStack->top->data;
		pOldTop = pStack->top;
		pStack->top = pOldTop->next;
		free(pOldTop);
		pStack->count--;
		return item;
	}
}

int popCalcStack(CalcHead* pStack) {
	CalcNode *pOldTop;

	if (pStack->top == NULL)
		return NULL;
	else {
		int item = pStack->top->data;
		pOldTop = pStack->top;
		pStack->top = pOldTop->next;
		free(pOldTop);
		return item;
	}
}

void clearStack(StackHead* pStack) {
	StackNode *pOldTop;
	while (pStack->top != NULL) {
		pOldTop = pStack->top;
		pStack->top = pOldTop->next;
		free(pOldTop);
		pStack->count--;
	}
}