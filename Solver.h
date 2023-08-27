bool XOR(bool A, int B);
void GetSingleValue_in_clause(int* f_index_value, int** f_isTrue);
void GetSingleValue_in_value(int* f_index_value, int** f_isTrue);
void ChooseValue(int* f_index_value,int* f_isTrue);
void RemoveValue_in_clause(struct Stack_Value** f_stack_RemovedValue, struct ValueNode* removed_value);
void RemoveValue_in_value(struct Stack_ValueHead** f_stack_RemovedValueHead, struct ValueNode* removed_value);
void RemoveClauseHead(struct Stack_ClauseHead** f_stack_RemovedClauseHead, struct ClauseHeadNode* removed_clauseHead);
void RemoveValueHead(struct Stack_ValueHead** f_stack_RemovedValueHead, struct ValueHeadNode* removed_valueHead);
void SetValue
(
	int* f_index_value,
	int* f_isTrue,
	struct Stack_Value** f_stack_RemovedValue,
	struct Stack_ClauseHead** f_stack_RemovedClauseHead,
	struct Stack_ValueHead** f_stack_RemovedValueHead
);
bool CheckEmptyCNF();
bool CheckEmptyClause();
void RevertChange
(
	struct Stack_Value** f_stack_RemovedValue,
	struct Stack_ClauseHead** f_stack_RemovedClauseHead,
	struct Stack_ValueHead** f_stack_RemovedValueHead
);
void MyPrintResult();
bool DPLL();
