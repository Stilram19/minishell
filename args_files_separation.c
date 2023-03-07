/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_files_separation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:24:50 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/07 11:53:41 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// split with mask generation 4
// (*) if token is not in the set "()<>&|":
// (loop) if it is argument, push it in the queue of arguments
// (loop) if it is file, push it in the queue of files
// (break) when you encounter a token in the set "()<>&|"
// join the tokens.

char	**serve_queue(char **tokens, t_queue *queue)
{
	char	*new_token;

	new_token = queue_pop(queue);
	while (new_token)
	{
		*tokens = new_token;
		new_token = queue_pop(queue);
		tokens++;
	}
	return (tokens);
}

char	**rearrange_args_files(char **tokens, t_queue *files, t_queue *args)
{
	int		i;

	i = 0;
	while (*(tokens + i) && !ft_strchr("()&|", **(tokens + i)))
	{
		if (**(tokens + i) == '<' || **(tokens + i) == '>')
		{
			queue_push(files, *(tokens + i));
			queue_push(files, *(tokens + i + 1));
			i += 2;
			continue ;
		}
		queue_push(args, *(tokens + i));
		i++;
	}
	tokens = serve_queue(tokens, args);
	return (serve_queue(tokens, files));
}

void	rearrange_tokens(char **tokens)
{
	char	*token;
	t_queue	files;
	t_queue	args;

	queue_init(&files);
	queue_init(&args);
	while (*tokens)
	{
		token = *tokens;
		if (ft_strchr("()&|", *token) && tokens++)
			continue ;
		tokens = rearrange_args_files(tokens, &files, &args);
	}
}

//void	ft_display(char **tokens);

char	*args_files_separation(char *str)
{
	char	*ret;
	char	*temp;
	char	**tokens;

	tokens = produce_tokens(str, mask_generation4(str, "()<>&|"));
	rearrange_tokens(tokens);
	//ft_display(tokens);
	//return (0);
	temp = join_tokens(tokens);
	ret = ft_strtrim(temp, " ");
	ft_garbage_collector(SINGLE_RELEASE, 0, temp);
	return (ret);
}
