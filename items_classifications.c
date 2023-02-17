/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_classifications.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:41:14 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/17 20:45:23 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	operand_construction(t_item *item, char **ptr_to_line)
{
	char	**tokens;
	char	*operand;

	operand = prepare_construction(ptr_to_line);
	tokens = produce_tokens(operand, mask_generation(operand));
	expanding(tokens);
	
}

void	*item_construction(char **ptr_to_line, int item_type)
{
	t_item	*item;

	item = ft_garbage_collector(ALLOCATE, sizeof(t_item), NULL);
	item->type = item_type;
	item->operand = NULL;
	if (item_type == OPERATOR && (**ptr_to_line == '&'
		|| (**ptr_to_line == '|' && *(*ptr_to_line + 1) == '|')))
		(*ptr_to_line)++;
	if (item_type != OPERAND && (*ptr_to_line)++)
		return (item);
	operand_construction(item, ptr_to_line);
	return (*ptr_to_line);
}

void	items_classification(char *line)
{
	void	*item;
	t_queue	q;

	queue_init(&q);
	while (*line)
	{
		if (*line == '(')
			item = item_construction(&line, L_PARENTH);
		else if (*line == ')')
			item = item_construction(&line, R_PARENTH);
		else if (fourth_production_rule(*line))
			item = item_construction(&line, OPERATOR);
		else
			item = item_construction(&line, OPERAND);
		queue_push(&q, item);
	}
}
