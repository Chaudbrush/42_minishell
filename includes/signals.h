#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	sig_handler_parent(void);
void	sig_handler_doc(void);
void	sig_handler_child(void);

#endif
