#include <stdio.h>
#include <stdlib.h>
#include "calcHead.h"

void main()
{
	char infix[100];
	char* postfix;
	int result=0;
	StackHead* pStack = CreateStack();

	printf("���ڸ����� ����ϴ� ��ް��� �Դϴ�.\n");
	printf("������ ������� �Է��Ͻʽÿ� > ");
	scanf_s("%s", infix,sizeof(char)*100);

	postfix = fromInfix_ToPostfix(infix, pStack);
	result = calculate_Postfix(postfix, pStack);
	printf("����� %d �Դϴ� \n", result);

	system("pause");
	return;
}