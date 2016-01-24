#include "Calculator.h"

char NUMBER[] = {'0', '1', '2', '3', '4', '5', '6','7','8','9','.'};

// 숫자인지 확인. 숫자를 써놓고 하나씩 비교를 하는구나...
int IsNumber(char Cipher)
{
	int i = 0;
	int ArrayLength = sizeof(NUMBER);

	for (i = 0; i < ArrayLength; i++)
	{
		if (Cipher == NUMBER[i])
		{
			return 1;
		}
	}

	return 0;
}

unsigned int GetNextToken(char* Expression, char* Token, int* TYPE)
{
	unsigned int i = 0;

	for ( i = 0; 0 != Expression[i]; i++)
	{
		Token[i] = Expression[i];

		if (IsNumber(Expression[i]) == 1)
		{
			*TYPE = OPERAND;

			if (IsNumber(Expression[i+1]) != 1)
			{
				break;
			}
		}
		else
		{
			*TYPE = Expression[i];
			break;
		}
	}

	Token[++i] = '\0';
	return i;
}

int GetPriority(char Operator, int InStack)
{
	int Priority = -1;

	switch (Operator)
	{
		case LEFT_PARENTHESIS:
			if (InStack)
			{
				Priority = 0;
			}
			else
			{
				Priority = 3;
			}
			break;

		case MULTIPLY:
		case DIVIDE:
			Priority = 2;
			break;

		case PLUS:
		case MINUS:
			Priority = 1;
			break;
	}

	return Priority;
}

int IsPrior(char OperatorInStack, char OperatorInToken)
{
	return (GetPriority(OperatorInStack, 1) > GetPriority(OperatorInToken, 0));
}

// 중위 표현식을 후위 표현식으로 변환한다.
void GetPostfix(char* InfixExpression, char* PostfixExpression)
{
	LinkedListStack* Stack; 	// 변환에 사용할 링크드리스트 스택 포인트 변수

	char Token[32];				// 연산자 또는 피연산자 토큰 저장용
	int Type = -1;				// 연산자/피연산자 구분 타입
	unsigned int Position = 0;	// 변환하는 위치
	unsigned int Length = strlen(InfixExpression); // 중위표현식 문자열 길이

	LLS_CreateStack(&Stack);	// 스택 생성

	while (Position < Length)	// 중위표현식 문자열 길이만큼 반복.
	{
		// 중위표현식의 다음 연산자 또는 피연산자를 해당 변수에 저장하고 그 길이만큼 포지션 이동.
		Position += GetNextToken(&InfixExpression[Position], Token, &Type);

		// 저장된 토큰의 타입(연산자/피연산자 구분)에 따라 처리 
		if (Type == OPERAND)
		{
			// 피연산자인 경우 후위표현식 문자열에 이어붙인다.
			strcat(PostfixExpression, Token);
			strcat(PostfixExpression, " ");
		}
		else if (Type == RIGHT_PARENTHESIS)
		{
			// 오른쪽 괄호인 경우 스택에서 왼쪽 괄호가 나올떄까지 스택에서 꺼내고 후위표현식 문자열에 연결.
			while (!LLS_IsEmpty(Stack))
			{
				Node* Popped = LLS_Pop(Stack); // 스택에서 하나 꺼낸다. 

				if (Popped->Data[0] == LEFT_PARENTHESIS) // 스택에서 꺼낸 Node 가 왼쪽 괄호이면 
				{
					LLS_DestroyNode(Popped); // 그냥 제거
					break; // 끝
				}
				else // 스택에서 꺼낸 Node 가 왼쪽 괄호가 아닌경우는
				{
					strcat(PostfixExpression, Popped->Data); // 후위표현식 문자열에 이어붙인다. 
					LLS_DestroyNode(Popped); // 그리고 Node는 제거
				}
			}
		}
		else
		{
			// 연산자면서 오른쪽 괄호가 아닌 경우
			// 스택에서 하나씩 꺼내면서 우선순위가 토큰보다 낮으면 후위표현식 문자열에 붙이고, 
			// 토큰보다 우선순위가 높으면 토큰을 스택에 push
			while (!LLS_IsEmpty(Stack) &&
				IsPrior(LLS_Top(Stack)->Data[0], Token[0])) 
			{
				Node* Popped = LLS_Pop(Stack);	// 스택에서 Node를 하나 꺼낸다.

				if (Popped->Data[0] != LEFT_PARENTHESIS) // 꺼낸 Node가 왼쪽 괄호가 아니면 
				{
					strcat(PostfixExpression, Popped->Data); // 후위표현식 문자열에 이어 붙임.
				}

				LLS_DestroyNode(Popped); // 꺼낸 Node 제거
			}

			LLS_Push(Stack, LLS_CreateNode(Token));
		}
	}

	// 스택에 남은 연산자들 꺼내서 후위표현식 문자열에 붙인다.
	while (!LLS_IsEmpty(Stack))
	{
		Node* Popped = LLS_Pop(Stack);

		if (Popped->Data[0] != LEFT_PARENTHESIS)
		{
			strcat(PostfixExpression, Popped->Data);
		}
		LLS_DestroyNode(Popped);
	}

	LLS_DestroyStack(Stack);
}

double Calculate(char* PostfixExpression)
{
	LinkedListStack* Stack;
	Node* ResultNode;

	double Result; // 계산 결과값 
	char Token[32];
	int Type = -1;
	unsigned int Read = 0;
	unsigned int Length = strlen(PostfixExpression);

	LLS_CreateStack(&Stack);

	while (Read < Length)
	{
		Read += GetNextToken(&PostfixExpression[Read], Token, &Type);

		if (Type == SPACE)
		{
			continue;
		}

		// 피연산자인 경우 스택에 push
		if (Type == OPERAND)
		{
			Node* NewNode = LLS_CreateNode(Token);
			LLS_Push(Stack, NewNode);
		}
		else
		{
			char ResultString[32];
			double Operator1, Operator2, TempResult;
			Node* OperatorNode;

			OperatorNode = LLS_Pop(Stack);
			Operator2 = atof(OperatorNode->Data); // atof 함수는 문자열을 double값으로 변환
			LLS_DestroyNode(OperatorNode); // 꺼낸 노드 제거

			OperatorNode = LLS_Pop(Stack);
			Operator1 = atof(OperatorNode->Data);
			LLS_DestroyNode(OperatorNode);

			switch (Type)
			{
				case PLUS: TempResult = Operator1 + Operator2; break;
				case MINUS: TempResult = Operator1 - Operator2; break;
				case MULTIPLY: TempResult = Operator1 * Operator2; break;
				case DIVIDE: TempResult = Operator1 / Operator2; break;
			}

			gcvt(TempResult, 10, ResultString); // 계산된 결과인 double 을 문자열 ResultString 에
			LLS_Push(Stack, LLS_CreateNode(ResultString));// 계산 결과를 다시 스택에 넣는다.
		}
	}

	ResultNode = LLS_Pop(Stack); 	// 최종 계산 결과를 꺼낸다.
	Result = atof(ResultNode->Data);
	LLS_DestroyNode(ResultNode);

	LLS_DestroyStack(Stack);

	return Result;
}