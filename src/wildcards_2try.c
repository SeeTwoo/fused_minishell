#include "minishell.h"

int	add_wild_tok(t_token **wild_toks, char *entry)
{
	t_token	*head;

	head = *wild_toks;
	while (head)
		head = head->next;
	head = malloc(sizeof(t_token));
	if (!head)
		return (1);
	head->value = NULL;
	head->type = WORD;
	head->prec = 2;
	head->expanded_value = ft_strdup(entry);
	if (!head->expanded_value)
		return (1);
	head->quote_mask = NULL;
	head->next = NULL;
	return (0);
}

int	create_wild_toks(char *wild, t_token **wild_toks)
{
	struct dirent	*entry;
	DIR				*dir;
	char			*wild_dup;

	*wild_toks = NULL;
	dir = opendir(".");
	entry = readdir(dir);
	while (entry)
	{
		wild_dup = ft_strdup(wild);
		if (are_matching(wild_dup, entry->d_name))
			add_wild_tok(wild_toks, entry->d_name);
		free(wild_dup);
		entry = readdir(dir);
	}
	print_tokens(*wild_tok
	return (0);
}

void	put_tail_back(t_token **wild_toks, t_token *list_tail)
{
	t_token *temp;

	temp = *wild_toks;
	while (temp->next)
		temp = temp->next;
	temp->next = list_tail;
}

int	insert_wild_toks(t_token **head)
{
	t_token	*wild_toks;
//	t_token	*former_head;
	t_token	*list_tail;

	create_wild_toks((*head)->value, &wild_toks);
	if (!wild_toks)
		return (0);
//	former_head = *head;
	list_tail = (*head)->next;
	*head = wild_toks;
	put_tail_back(&wild_toks, list_tail);
	return (0);
}

int	globbing(t_minishell *sh)
{
	int		prev;
	t_token	*temp;
	
	prev = PIPE;
	temp = sh->tok_list;
	while (temp)
	{
		if (prev == WORD && temp->type == WORD && ft_strchr(temp->value, '*'))
			insert_wild_toks(&temp);
		temp = temp->next;
	}
	return (1);
}
