#include <stdio.h>
#include <stdlib.h>
#include "calcHead.h"

void main()
{
	char infix[100];
	char* postfix;
	int result=0;
	StackHead* pStack = CreateStack();

	printf("한자릿수를 계산하는 고급계산기 입니다.\n");
	printf("수식을 공백없이 입력하십시오 > ");
	scanf_s("%s", infix,sizeof(char)*100);

	postfix = fromInfix_ToPostfix(infix, pStack);
	result = calculate_Postfix(postfix, pStack);
	printf("결과는 %d 입니다 \n", result);

	system("pause");
	return;
}