/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padam <padam@student.42heilbronn.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:37:52 by padam             #+#    #+#             */
/*   Updated: 2024/08/10 01:07:33 by padam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"

typedef struct flags
{
	bool a;
	bool d;
	bool f;
	bool g;
	bool l;
	bool u;
	bool r;
	bool R;
	bool t;
} t_flags;

void	init_flags(t_flags *flags);
char	**parse_arguments(char **argv, t_flags *flags);
int	list_entity(char *path);

#endif
