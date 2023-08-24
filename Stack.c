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
struct Stack_ClauseHead* MyPush_2(struct Stack_ClauseHead* stack, struct ClauseHeadNode value)
{
	struct Stack_ClauseHead* new_elem = (struct Stack_ClauseHead*)malloc(sizeof(struct Stack_ClauseHead));
	if (!new_elem)
		return new_elem;
	new_elem->m_value = value;
	new_elem->next = stack;
	stack = new_elem;
	return stack;
}

struct Stack_ClauseHead* MyPop_2(struct Stack_ClauseHead* stack)
{
	if (!stack)
		return stack;
	struct Stack_ClauseHead* p = stack;
	stack = stack->next;
	free(p);
	return stack;
}

struct Stack_ValueHead* MyPush_3(struct Stack_ValueHead* stack, struct ValueHeadNode value)
{
	struct Stack_ValueHead* new_elem = (struct Stack_ValueHead*)malloc(sizeof(struct Stack_ValueHead));
	if (!new_elem)
		return new_elem;
	new_elem->m_value = value;
	new_elem->next = stack;
	stack = new_elem;
	return stack;
}
struct Stack_ValueHead* MyPop_3(struct Stack_ValueHead* stack)
{
	if (!stack)
		return stack;
	struct Stack_ValueHead* p = stack;
	stack = stack->next;
	free(p);
	return stack;
}