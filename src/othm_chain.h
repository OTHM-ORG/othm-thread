#ifndef OTHM_CHAIN_H
#define OTHM_CHAIN_H

#include <stdlib.h>
#include <othm_base.h>
#include <othm_symbols.h>
#include <stdarg.h>



#define OTHM_CHAIN_DEFUN(NAME, SYMBOL_NAME)				\
	void NAME(struct othm_list *position,				\
		  struct othm_thread_control *control,			\
		  struct othm_thread_control *lower_control);		\
	OTHM_PRIM_FUNCT_INIT(NAME, SYMBOL_NAME, void);			\
	void NAME(struct othm_list *position,				\
		  struct othm_thread_control *control,			\
		  struct othm_thread_control *lower_control)

#define OTHM_CHAIN_DEFUN_TAGGED_LEFT(NAME, SYMBOL_NAME, LTAG_TYPE, ...)	\
	void NAME(struct othm_list *position,				\
		  struct othm_thread_control *control,			\
		  struct othm_thread_control *lower_control);		\
	OTHM_PRIM_FUNCT_INIT_TAGGED_LEFT(NAME, SYMBOL_NAME,		\
					 void,				\
					 LTAG_TYPE,			\
					 __VA_ARGS__);			\
	void NAME(struct othm_list *position,				\
		  struct othm_thread_control *control,			\
		  struct othm_thread_control *lower_control)

#define OTHM_CHAIN_DEFUN_TAGGED_RIGHT(NAME, SYMBOL_NAME, RTAG_TYPE, ...) \
	void NAME(struct othm_list *position,				\
		  struct othm_thread_control *control,			\
		  struct othm_thread_control *lower_control);		\
	OTHM_PRIM_FUNCT_INIT_TAGGED_RIGHT(NAME, SYMBOL_NAME,		\
					  void,				\
					  RTAG_TYPE,			\
					  __VA_ARGS__);			\
	void NAME(struct othm_list *position,				\
		  struct othm_thread_control *control,			\
		  struct othm_thread_control *lower_control)

#define OTHM_CHAIN_DEFUN_TAGGED_BOTH(NAME, SYMBOL_NAME,			\
				     LTAG_TYPE, RTAG_TYPE, ...)		\
	void NAME(struct othm_list *position,				\
		  struct othm_thread_control *control,			\
		  struct othm_thread_control *lower_control);		\
	OTHM_PRIM_FUNCT_INIT_TAGGED_BOTH(NAME, SYMBOL_NAME,		\
					 void,				\
					 LTAG_TYPE,			\
					 RTAG_TYPE,			\
					 __VA_ARGS__);			\
	void NAME(struct othm_list *position,				\
		  struct othm_thread_control *control,			\
		  struct othm_thread_control *lower_control)

#define OTHM_CHAIN_FUNCT void (*) (struct othm_list *,			\
				   struct othm_thread_control *,	\
				   struct othm_thread_control *)

#define OTHM_CHAIN_DIRECT_BETA(X) othm_comp_from_prim(OTHM_PRIM_FUNCT(X)),

#define OTHM_CHAIN_DIRECT(LIST_CHAIN_GEN, ...)				\
	othm_chain_direct						\
	(LIST_CHAIN_GEN,						\
	 OTHM_CPP_EVAL(OTHM_CPP_MAP(OTHM_CHAIN_DIRECT_BETA, __VA_ARGS__)) \
	 NULL)

struct othm_comp {
	struct othm_symbol_struct *prim;
};


struct othm_comp *othm_comp_from_prim(struct othm_symbol_struct *prim);

struct othm_list *othm_chain_direct(struct othm_list *(*list_gen_arg)(void),
				    struct othm_comp *first, ...);

#endif
