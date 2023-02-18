/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_classification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:41:14 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/18 15:08:30 by obednaou         ###   ########.fr       */
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

char	*prepare_construction(char **ptr_to_line)
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

void	operand_construction(t_item *item, char **ptr_to_line, int inside_parenth)
{
	char	**tokens;
	char	*operand;
	t_queue	args;

	operand = prepare_construction(ptr_to_line);
	tokens = produce_tokens(operand, mask_generation(operand));
	expanding(tokens);
	item->operand = ft_garbage_collector(ALLOCATE, sizeof(t_operand), NULL);
	item->operand->status = inside_parenth;
	item->operand->ambig_redirect = check_ambiguous_redirect(tokens);
	remove_quotes(tokens);
	item->operand->cmd = get_command(tokens);
	item->operand->args = get_args(tokens);
	item->operand->files = get_files(tokens);
}

void	*item_construction(char **ptr_to_line, int item_type, int *inside_parenth)
{
	t_item	*item;

	item = ft_garbage_collector(ALLOCATE, sizeof(t_item), NULL);
	item->type = item_type;
	item->operand = NULL;
	if ((item_type = OR || item_type == AND))
		(*ptr_to_line)++;
	if (item_type == L_PARENTH)
		(*inside_parenth)++;
	if (item_type == R_PARENTH)
		(*inside_parenth)--;
	if (item_type != OPERAND && (*ptr_to_line)++)
		return (item);
	operand_construction(item, ptr_to_line, *inside_parenth);
	return (*ptr_to_line);
}

void	items_classification(char *line)
{
	int		inside_parenth;
	void	*item;
	t_queue	q;

	inside_parenth = 0;
	queue_init(&q);
	while (*line)
	{
		if (*line == '(')
			item = item_construction(&line, L_PARENTH, &inside_parenth);
		else if (*line == ')')
			item = item_construction(&line, R_PARENTH, &inside_parenth);
		else if (fourth_production_rule(*line))
			item = item_construction(&line, get_operator(line), &inside_parenth);
		else
			item = item_construction(&line, OPERAND, &inside_parenth);
		queue_push(&q, item);
	}
}
