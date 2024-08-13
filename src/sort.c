/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 07:52:48 by padam             #+#    #+#             */
/*   Updated: 2024/08/11 07:16:29 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief checks which file was+ modified last
 * @return `0` if `a` greater `b`, else `1`
*/
bool	compare_last_modified(t_inode *a, t_inode *b)
{
	return (a->st.st_mtime > b->st.st_mtime);
}

/**
 * @brief checks which file was accessed last
 * @return `0` if `a` greater `b`, else `1`
*/
bool	compare_last_accessed(t_inode *a, t_inode *b)
{
	return (a->st.st_atime > b->st.st_atime);
}

/**
 * @brief checks which name comes alphabetically first
 * @return `0` if `a` greater `b`, else `1`
*/
bool	compare_name(t_inode *a, t_inode *b)
{
	return (ft_strcmp(a->name, b->name) > 0);
}

/**
 * @brief sorts an arrary of inodes
 * @param compare the function used to decide sorting
*/
void	sort(t_inode *nodes, int (*compare)(t_inode*, t_inode*), int reverse)
{
	t_inode *fkldajsk;
	t_inode tmp;

	while (nodes)
	{
		fkldajsk = nodes;
		while (++fkldajsk)
		{
			if (compare(nodes, fkldajsk) != reverse)
			{
				tmp = *fkldajsk;
				*fkldajsk = *nodes;
				*nodes = tmp;
			}
		}
		nodes++;
	}
}

/**
 * @brief sorts the nodes array according to the flags
 * @return
*/
void	decide_sorting(t_inode *nodes, t_flags *flags)
{
	bool	reverse;

	reverse = (flags->r && !flags->f);
	if (flags->l || flags->g)
	{
		if (!flags->t)
			sort(nodes, &compare_name, reverse);
		else if (flags->u)
			sort(nodes, &compare_last_accessed, reverse);
		else
			sort(nodes, &compare_last_modified, reverse);
	}
	else if (flags->t)
	{
		if (flags->u)
			sort(nodes, &compare_last_accessed, reverse);
		else
			sort(nodes, &compare_last_modified, reverse);
	}
	else if (flags->u && !flags->f)
		sort(nodes, &compare_last_accessed, reverse);
	else if (!flags->f)
		sort(nodes, &compare_name, reverse);

}
