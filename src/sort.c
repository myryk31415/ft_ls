/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 07:52:48 by padam             #+#    #+#             */
/*   Updated: 2024/08/25 08:56:32 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief strcmp adjusted to the needs of ls. Ignores starting `.`, groups caps and noncaps
 */
int	ft_strcmp_ls(const char *s1, const char *s2)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	while (*str1 == '.')
		str1++;
	while (*str2 == '.')
		str2++;
	while (*str1 && ft_tolower(*str1) == ft_tolower(*str2))
	{
		str1++;
		str2++;
	}
	if (ft_isalnum(*str1) && !ft_isalnum(*str2))
		return (1);
	if (!ft_isalnum(*str1) && ft_isalnum(*str2))
		return (-1);
	return (ft_tolower(*str1) - ft_tolower(*str2));
}

/**
 * @brief checks which file was+ modified last
 * @return `0` if `a` greater `b`, else `1`
*/
bool	compare_last_modified(t_inode *a, t_inode *b)
{
	return (a->st.st_mtime < b->st.st_mtime);
}

/**
 * @brief checks which file was accessed last
 * @return `0` if `a` greater `b`, else `1`
*/
bool	compare_last_accessed(t_inode *a, t_inode *b)
{
	return (a->st.st_atime < b->st.st_atime);
}

/**
 * @brief checks which name comes alphabetically first
 * @return `0` if `a` greater `b`, else `1`
*/
bool	compare_name(t_inode *a, t_inode *b)
{
	// int	j;
	// int k;

	// j = 0;
	// while (a->name[j] == '.')
	// 	j++;
	// k = 0;
	// while (b->name[k] == '.')
	// 	k++;
	return (ft_strcmp_ls(a->name, b->name) > 0);
}

/**
 * @brief sorts an arrary of inodes
 * @param compare the function used to decide sorting
*/
void	sort(t_inode **inodes, bool (*compare)(t_inode*, t_inode*), int reverse)
{
	t_inode **fkldajsk;
	t_inode *tmp;

	while (*inodes)
	{
		fkldajsk = inodes;
		fkldajsk++;
		while (*fkldajsk)
		{
			if (compare(*inodes, *fkldajsk) != reverse)
			{
				tmp = *fkldajsk;
				*fkldajsk = *inodes;
				*inodes = tmp;
			}
			fkldajsk++;
		}
		inodes++;
	}
}

/**
 * @brief sorts the inodes array according to the flags
 * @return
*/
void	decide_sorting(t_inode **inodes, t_flags *flags)
{
	bool	reverse;

	reverse = (flags->r && !flags->f);
	if (flags->l || flags->g)
	{
		if (!flags->t)
			sort(inodes, &compare_name, reverse);
		else if (flags->u)
			sort(inodes, &compare_last_accessed, reverse);
		else
			sort(inodes, &compare_last_modified, reverse);
	}
	else if (flags->t)
	{
		if (flags->u)
			sort(inodes, &compare_last_accessed, reverse);
		else
			sort(inodes, &compare_last_modified, reverse);
	}
	else if (flags->u && !flags->f)
		sort(inodes, &compare_last_accessed, reverse);
	else if (!flags->f)
		sort(inodes, &compare_name, reverse);

}
