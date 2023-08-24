void/* struct ClauseHeadNode* */ GetSingleValue_in_clause(int* f_index_value, bool** f_isTrue);
void GetSingleValue_in_value(int* f_index_value, bool** f_isTrue);
void ChooseValue(int* f_index_value);
void SetValue
(
	int* f_index_value, bool* f_isTrue,
	struct Stack_Value* f_stack_RemovedValue,
	struct Stack_ClauseHead* f_stack_RemovedClauseHead,
	struct Stack_ValueHead* f_stack_RemovedValueHead
);
bool CheckEmptyCNF();
bool CheckEmptyClause();
void RevertChange
(
	struct Stack_Value* f_stack_RemovedValue,
	struct Stack_ClauseHead* f_stack_RemovedClauseHead,
	struct Stack_ValueHead* f_stack_RemovedValueHead
);
bool DPLL();