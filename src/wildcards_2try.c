#include "minishell.h"

int	add_wild_tok(t_token **wild_toks, char *entry)
{
	t_token	*current;
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (1);
	new->value = NULL;
	new->type = WORD;
	new->prec = 2;
	new->expanded_value = ft_strdup(entry);
	if (!new->expanded_value)
		return (1);
	new->quote_mask = NULL;
	new->next = NULL;
	if (!(*wild_toks))
	{
		*wild_toks = new;
	}
	else
	{
		current = *wild_toks;
		while (current->next)
			current = current->next;
		current->next = new;
	}
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
	return (0);
}

int	insert_wild_toks(t_token **head)
{
	t_token	*wild_toks;
	t_token	*list_tail;
	t_token	*last_wild;

	print_tokens((*head));				//printing tokens
	printf("current head value is %s\n\n", (*head)->value);
	create_wild_toks((*head)->value, &wild_toks);
	if (!wild_toks)
		return (0);
	list_tail = (*head)->next;
	print_tokens(list_tail);			//printing tokens
	last_wild = wild_toks;
	while (last_wild->next)
		last_wild = last_wild->next;
	if (!(last_wild->next))
		printf("last wild is indeed the wild\n\n");
	last_wild->next = list_tail;
	print_tokens(wild_toks);			//printing tokens
	*head = wild_toks;
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
		prev = temp->type;
		temp = temp->next;
	}
	return (1);
}
