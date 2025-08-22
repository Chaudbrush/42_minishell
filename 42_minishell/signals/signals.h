#ifndef SIGNALS_H
# define SIGNALS_H

# include "../minishell.h"

void	get_new_line(void);
void	sig_handler(void);
void	_handler(int signal);

// void	sig_handler_parent(void);
// void	sig_handler_child(void);
// void	get_new_line(void);
// void	_handler2(int signal);
// void	_handler(int signal);




// NEW

void	sig_handler_parent(void);
void	sig_handler_doc(void);
void	sig_handler_child(void);

#endif
