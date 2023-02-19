/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_classification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:41:14 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/19 20:54:48 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_operator_type(char *str)
{
	if (*str == '|' && *(str + 1) == '|')
		return (OR);
	if (*str == '|')
		return (PIPE);
	return (AND);
}

char	*prepare_construct(char **ptr_to_line)
{
	int		i;
	int		ignore;
	char	*operand;

	i = 0;
	ignore = 0;
	operand = ft_strdup(*ptr_to_line);
	while (*(operand + i))
	{
		open_close_quotes(*(operand + i), &ignore);
		if (!ignore && fourth_production_rule(*(operand + i))
			|| *(operand + i) == '(' || *(operand + i) == ')')
			break ;
		i++;
	}
	*(operand + i) = '\0';
	*ptr_to_line += i;
	return (operand);
}

void	operand_construct(t_item *item, char **ptr_to_line, int status)
{
	char	**tokens;
	char	*operand;
	t_queue	args;

	operand = prepare_construct(ptr_to_line);
	tokens = produce_tokens(operand, mask_generation(operand));
	expanding(tokens);
	item->operand = ft_garbage_collector(ALLOCATE, sizeof(t_operand), NULL);
	item->operand->status = status;
	item->operand->files = get_files(tokens);
	item->operand->cmd = get_command(tokens);
	queue_push(&args, item->operand->cmd);
	item->operand->args = get_args(tokens, &args);
}

void	*item_construct(char **ptr_to_line, int item_type, int *status)
{
	t_item	*item;

	item = ft_garbage_collector(ALLOCATE, sizeof(t_item), NULL);
	item->type = item_type;
	item->operand = NULL;
	if (item_type == OR || item_type == AND)
		(*ptr_to_line)++;
	else if (item_type == L_PARENTH)
		(*status)++;
	else if (item_type == R_PARENTH)
		(*status)--;
	if (item_type != OPERAND && (*ptr_to_line)++)
		return (item);
	operand_construct(item, ptr_to_line, *status);
	return (item);
}

void	items_classification(char *line)
{
	int		inside_parenth;
	void	*item;
	t_queue	items;

	inside_parenth = 0;
	queue_init(&items);
	while (*line)
	{
		if (*line == '(')
			item = item_construct(&line, L_PARENTH, &inside_parenth);
		else if (*line == ')')
			item = item_construct(&line, R_PARENTH, &inside_parenth);
		else if (fourth_production_rule(*line))
			item = item_construct(&line, get_operator(line), &inside_parenth);
		else
			item = item_construct(&line, OPERAND, &inside_parenth);
		queue_push(&items, item);
	}
}
//(, ), |, ||, &&, cmd
//(ls -l | cat) || (la | wc -l) && grep 123
//{(, ls -l, |, cat, ), ||, (, la, |, wc -l, ), &&, grep 123}
// --> && || | "ls -l" "cat" | "la" "wc -l" "grep 123"