# advancedCalculator  
 It is an advanced calculator that guarantees one-digit arithmetic operation priority.  
 This code is written in C language and custom stack.  
 <br />
 한자릿수의 사칙연산과 괄호 우선순위를 보장하는 고급계산기 입니다.  
 이 코드는 C언어로 작성하였고 커스텀 stack 자료구조를 이용해 작성하였습니다.  
 
## 들어가기 전에
 custom stack을 구현한 stackADT.c 파일의 구문의 설명은 생략하였습니다. (push, pop의 기본적인 함수입니다.)    
 postfix 변환 과정에서 2자리 이상의 연산을 구분할 수 없으므로 1자리 연산만 지원합니다.  
 또한 입력받는 숫자는 음수를 입력받을 수 없습니다. (계산결과는 음수표시가 가능합니다.)  
 
## main 함수
```
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
```
 입력받는 수식은 최대 100byte 크기를 지원합니다.  

## getPriority 함수  
 ```
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
 ```
 infix를 postfix로 바꿀 때 stack에 넣을 우선순위를 반환합니다.  
 우선순위가 낮을수록 stack 에 바로 push 합니다.  
 예를 들면, '+'와 '-'는 곱하기, 나누기 연산보다 우선순위가 낮습니다.  
 
## fromInfix_ToPostfix 함수   
```
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
```
 infix를 postfix로 바꾸는 함수입니다.  
 infix notation을 인자로 넣으면 postfix 변환값을 출력합니다.  
 변환 알고리즘은 [여기](http://makebob.tistory.com/18)를 참고했습니다.

      
## calculate_Postfix 함수
```
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
```
 infix 변환값을 인자로 넣으면, stack을 이용해 계산한 결과를 반환합니다.  
 이용할 stack의 헤드 포인터를 같이 인자로 넣어줍니다.  
 기본 알고리즘은 다음과 같습니다.
 > 1. 들어온 값이 숫자면 stack에 push 합니다.
 > 2. 들어온 값이 연산자면 stack의 값을 2번 pop 한 후 연산결과를 다시 push합니다.
 > 3. 값이 다 들어오면 stack의 값을 pop하여 반환합니다.

 
## 실행 결과
 ![calculator_result](https://user-images.githubusercontent.com/41851641/48905784-d2e46c80-eea5-11e8-9383-da2b9cfc0a9c.PNG)

