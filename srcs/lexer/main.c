#include "minishell.h"

void print_tree(t_node *node)
{
	int i;

	i = 0;
	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		while (node->cmd->av[i])
		{
			printf("type = %d\n", node->type);
			printf("av[%d] = %s\n", i, node->cmd->av[i]);
			i++;
		}
	}
	else
	{
		print_tree(node->left);
		print_tree(node->right);
		printf("type = %d\n", node->type);
	}
}

int	main(void)
{
	char	buf[4096];
	t_token	*cur;
	t_token	token;
	t_node *node;

	while (1)
	{
		printf("minishell> ");
		fgets(buf, sizeof(buf), stdin);
		buf[strlen(buf) - 1] = '\0';
		cur = lexer(buf, &token);
		node = parse_and_or(&cur);
		print_tree(node);
			// while (cur)
			// {
			// 	printf("token->type=%d  value=%s\n", cur->token, cur->value);
			// 	cur = cur->next;
			// }
		free_token_lst(cur);
	}
}