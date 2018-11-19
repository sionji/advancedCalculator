typedef char Element;

typedef struct tcalcNode {
	int data;
	struct tcalcNode *next;
}CalcNode;

typedef struct {
	CalcNode *top;
}CalcHead;

typedef struct tStackNode {
	Element data;
	struct tStackNode *next;
}StackNode;

typedef struct {
	int count;
	StackNode *top;
}StackHead;

StackHead* CreateStack();
CalcHead* CreateCalcStack();
Element topStack(StackHead* pStack);
Element popStack(StackHead* pStack);
void pushStack(StackHead* pStack, Element item);
void pushCalcStack(CalcHead* pStack, int item);
int popCalcStack(CalcHead* pStack);
void clearStack(StackHead* pStack);
int getPriority(char input);
Element* fromInfix_ToPostfix(Element* infix, StackHead* pStack);
int calculate_Postfix(char* postfix, StackHead* pStack);