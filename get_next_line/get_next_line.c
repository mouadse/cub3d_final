/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:08:01 by msennane          #+#    #+#             */
/*   Updated: 2025/06/05 14:16:23 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*gnl_queue(void)
{
	static t_list	queue;
	static int		ready = 0;

	if (!ready)
	{
		initialize_queue(&queue);
		ready = 1;
	}
	return (&queue);
}

// static char	*extract_line(t_list *node)
// {
// 	char				*line;
// 	int					i;
// 	struct s_list_node	*temp;

// 	i = 0;
// 	temp = node->head;
// 	while (temp && temp->data != '\n')
// 	{
// 		temp = temp->next;
// 		i++;
// 	}
// 	line = malloc(sizeof(char) * (i + 2));
// 	if (!line)
// 		return (NULL);
// 	i = 0;
// 	while (node->head && node->head->data != '\n')
// 		line[i++] = pop_node(node);
// 	line[i++] = pop_node(node);
// 	line[i] = '\0';
// 	return (line);
// }

static char	*extract_rest(t_list *node)
{
	char				*rest;
	int					i;
	struct s_list_node	*temp;

	i = 0;
	temp = node->head;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	rest = malloc(sizeof(char) * (i + 1));
	if (!rest)
		return (NULL);
	i = 0;
	while (node->head)
		rest[i++] = pop_node(node);
	rest[i] = '\0';
	return (rest);
}

static char	*handle_cases(ssize_t bytes, t_list *node, char *rest, int *fd)
{
	ssize_t	i;

	if (bytes == -1)
	{
		free(rest);
		free_queue(node);
		return (NULL);
	}
	else if (bytes == 0)
	{
		free(rest);
		if (is_it_empty(node))
			return (NULL);
		else
			return (extract_rest(node));
	}
	else
	{
		i = 0;
		while (i < bytes)
			push_node(node, rest[i++]);
		free(rest);
		return (get_next_line(*fd));
	}
}

char	*get_next_line(int fd)
{
	t_list	*q;
	ssize_t	bytes;
	char	*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	q = gnl_queue();
	if (!is_it_empty(q) && has_new_line(q))
		return (extract_line(q));
	buf = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buf)
		return (NULL);
	bytes = read(fd, buf, BUFFER_SIZE);
	return (handle_cases(bytes, q, buf, &fd));
}

void	cleanup_get_next_line(void)
{
	t_list	*q;

	q = gnl_queue();
	if (!is_it_empty(q))
		free_queue(q);
}
