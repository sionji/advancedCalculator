# advancedCalculator  
 It is an advanced calculator that guarantees one-digit arithmetic operation priority.  
 This code is written in C language and custom stack.  
 <br />
 한자릿수의 사칙연산과 괄호 우선순위를 보장하는 고급계산기 입니다.  
 이 코드는 C언어로 작성하였고 커스텀 stack 자료구조를 이용해 작성하였습니다.  
 
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
      
## 기타
 custom stack을 구현한 stackADT.c 파일의 구문은 생략하였습니다.  
 postfix 변환 과정에서 2자리 이상의 연산을 구분할 수 없으므로 1자리 연산만 지원합니다.  
