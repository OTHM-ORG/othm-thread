#include "othm_chain.h"

struct othm_comp *othm_comp_from_prim(struct othm_symbol_struct *prim)
{
	struct othm_comp *new_comp;

	new_comp = malloc(sizeof(struct othm_comp));
	new_comp->prim = prim;

	return new_comp;
}

struct othm_list *othm_chain_malloc_list(void)
{
	return malloc(sizeof(struct othm_list));
}

struct othm_list *othm_chain_direct(struct othm_list *(*list_gen_arg)(void),
				    struct othm_comp *first, ...)
{
	va_list argp;
	struct othm_comp *comp;
	struct othm_list *head;
	struct othm_list *tail;
	struct othm_list *(*list_gen)(void);

	if (first == NULL)
		return NULL;
	if (list_gen_arg != NULL)
		list_gen = list_gen_arg;
	else
		list_gen = othm_chain_malloc_list;

	comp = first;
	head = list_gen();
	tail = head;
	va_start(argp, first);
	do {
		tail->here = comp;
	} while ((comp = va_arg(argp, struct othm_comp *))
		 ? (tail->next = list_gen(),
		    tail = tail->next, 1)
		 : 0);

	/* This while is used to only allocate another part of the list
	   if the list is not null! it does this using the comma operator
	   and the conditional operator */

	tail->next = NULL;
	va_end(argp);

	return head;
}
