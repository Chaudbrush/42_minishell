// #include "readline.h"

// int	check_quotes(char *str);
// int	check_parentesis(char *str);

// int	main(void)
// {
// 	printf("expected: 0 - %d\n", check_quotes("\'he\"llo\'\'\'"));
// 	printf("expected: 0 - %d\n", check_quotes("\"he\'llo\'\'\'\""));
// 	printf("expected: 1 - %d\n", check_quotes("\"he\"llo\'\'\'"));
// 	printf("expected: 1 - %d\n", check_quotes("\'he\"llo\'\'\'\'"));
// 	printf("expected: 1 - %d\n", check_quotes("\'he\"llo\'\'\'\""));
// 	printf("expected: 1 - %d\n", check_quotes("\'he\"l\"\"\'lo\'\'\'"));


// 	printf("\n\nparentesis\n\n");

// 	printf("expected: 0 - %d\n", check_parentesis("hello"));
// 	printf("expected: 0 - %d\n", check_parentesis("\"hello()\""));
// 	printf("expected: 1 - %d\n", check_parentesis("hello("));
// 	printf("expected: 1 - %d\n", check_parentesis("hello)"));
// 	printf("expected: 1 - %d\n", check_parentesis("\'hello(\'there)"));
// 	printf("expected: 1 - %d\n", check_parentesis("\'()\')"));
// }