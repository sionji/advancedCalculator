#include <stdio.h>
#include <stdlib.h>
#include <string.h>    
#include "calcHead.h"

int getPriority(char input) {
	switch (input) {
	case '+': 
	case '-':
		return 12;
	case '*': 
	case '/': 
		return 13;
		break;
	case '(':
		return 0;
	case ')':
		return 19;
	default : 
		return 0;
	}
}

Element* fromInfix_ToPostfix(Element* infix, StackHead* pStack) {
	int length = strlen(infix);
	int i = 0, d = 0;		// i 는 infix의 위치, d는 postfix 의 위치
	Element character;
	Element popChar;
	Element *postfix = (Element*)malloc(sizeof(Element)*(length + 1));
	clearStack(pStack);

	character = infix[0];
	while (character != NULL) {
		switch (character) {
		case '+':
		case '-':
		case '*':
		case '/':
			popChar = topStack(pStack);
			if (getPriority(popChar) < getPriority(character)) {
				pushStack(pStack, character);
				break;
			}
			else {
				while (getPriority(popChar) >= getPriority(character)) {
					popChar = popStack(pStack);
					postfix[d] = popChar;
					d++;
					popChar = topStack(pStack);
				}
				pushStack(pStack, character);
				break;
			}

		case '(':
			pushStack(pStack, character);
			break;

		case ')':
			popChar = popStack(pStack);
			while (popChar != '(') {
				postfix[d] = popChar;
				d++;
				popChar = popStack(pStack);
			}
			break;

		default:
			postfix[d] = character;
			d++;
			break;
		}
		i++;
		character = infix[i];
	}
	while (pStack->top != NULL) {
		postfix[d] = popStack(pStack);
		d++;
	}
	postfix[d] = character; // postfix의 맨 마지막에 NULL을 추가
	printf("postfix 변환결과 > %s\n", postfix);	// 잘 변환되었는지 출력

	return postfix;

}

int calculate_Postfix(char* postfix, StackHead* pStack) {
	CalcHead* pCalc = CreateCalcStack();
	int d = 0; //postfix 위치
	int op1=0, op2=0, value=0;
	while (postfix[d] != NULL) {
		switch (postfix[d]) {
		case '+':
			op1 = popCalcStack(pCalc);
			op2 = popCalcStack(pCalc);
			pushCalcStack(pCalc, op2 + op1);
			break;
		case '-':
			op1 = popCalcStack(pCalc);
			op2 = popCalcStack(pCalc);
			pushCalcStack(pCalc, op2 - op1);
			break;
		case '*':
			op1 = popCalcStack(pCalc);
			op2 = popCalcStack(pCalc);
			pushCalcStack(pCalc, op2 * op1);
			break;
		case '/':			
			op1 = popCalcStack(pCalc);
			op2 = popCalcStack(pCalc);
			pushCalcStack(pCalc, op2 / op1);
			break;
		default:
			value = postfix[d] - '0';
			pushCalcStack(pCalc,value);
		}
		d++;
	}

	return popCalcStack(pCalc);

}
