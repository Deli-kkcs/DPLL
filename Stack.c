#include"Definition.h"
//stack为当前的链栈，a表示入栈元素
struct Stack_Value* MyPush(struct Stack_Value* stack, struct ValueNode value)
{
	struct Stack_Value* new_elem = (struct Stack_Value*)malloc(sizeof(struct Stack_Value));
	if (!new_elem)
		return new_elem;
	new_elem->m_value = value;
	new_elem->next = stack;
	stack = new_elem;
	return stack;
}
struct Stack_Value* MyPop(struct Stack_Value* stack)
{
	if (!stack)
		return stack;
	struct Stack_Value* p = stack;
	stack = stack->next;
	free(p);
	return stack;
}