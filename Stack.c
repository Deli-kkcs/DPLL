#include"Definition.h"
#include"Stack.h"
void MyPush(struct Stack_Value** f_stack, struct ValueNode* value)
{
	struct Stack_Value* new_elem = (struct Stack_Value*)malloc(sizeof(struct Stack_Value));
	new_elem->m_value = value;
	new_elem->next = *f_stack;
	*f_stack = new_elem;
}
struct ValueNode* MyPop(struct Stack_Value** f_stack)
{
	if (!*f_stack)
		return NULL;
	struct Stack_Value* p = *f_stack;
	*f_stack = (*f_stack)->next;
	//free(p);
	return p->m_value;
}
void MyPush_2(struct Stack_ClauseHead** f_stack, struct ClauseHeadNode* value)
{
	struct Stack_ClauseHead* new_elem = (struct Stack_ClauseHead*)malloc(sizeof(struct Stack_ClauseHead));
	new_elem->m_value = value;
	new_elem->next = *f_stack;
	*f_stack = new_elem;
}
struct ClauseHeadNode* MyPop_2(struct Stack_ClauseHead** f_stack)
{
	if (!*f_stack)
		return NULL;
	struct Stack_ClauseHead* p = *f_stack;
	*f_stack = (*f_stack)->next;
	//free(p);
	return p->m_value;
}
void MyPush_3(struct Stack_ValueHead** f_stack, struct ValueHeadNode* value)
{
	struct Stack_ValueHead* new_elem = (struct Stack_ValueHead*)malloc(sizeof(struct Stack_ValueHead));
	new_elem->m_value = value;
	new_elem->next = *f_stack;
	*f_stack = new_elem;
}
struct ValueHeadNode* MyPop_3(struct Stack_ValueHead** f_stack)
{
	if (!*f_stack)
		return NULL;
	struct Stack_ValueHead* p = *f_stack;
	*f_stack = (*f_stack)->next;
	//free(p);
	return p->m_value;
}