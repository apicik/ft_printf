/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_f_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego <ediego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 18:33:23 by ediego            #+#    #+#             */
/*   Updated: 2019/12/21 14:23:02 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*itoa_f1(t_lst *cur, char *res)
{
	long long	tmp1;
	int			c;

	tmp1 = (long long)cur->fl;
	if (cur->fl < 0)
		tmp1 *= -1;
	c = cur->len;
	while (tmp1 > 0)
	{
		res[--c] = tmp1 % 10 + '0';
		tmp1 /= 10;
	}
	res[cur->len] = '\0';
	if ((int)cur->fl == 0)
		res[--c] = '0';
	return (res);
}

void	real_num(t_lst *cur)
{
	int			lendel;
	long double	res;
	double		del;

	del = 10;
	if (!cur->prec && !cur->isnull)
		lendel = 6;
	else if (cur->isnull)
		lendel = 0;
	else
		lendel = cur->prec;
	while (lendel--)
		del *= 10;
	res = (long double)(5.0 / del);
	if (cur->fl < 0)
		cur->fl -= res;
	else if (cur->fl == 2.5)
		cur->fl = 2.5;
	else
		cur->fl += res;
}

char	*itoa_f2(t_lst *cur, int len2, char *res)
{
	long long	tmp2;
	int			c;

	c = 1;
	if (cur->fl < 0)
		cur->fl *= -1;
	res[0] = '.';
	while (c <= len2)
	{
		cur->fl *= 10;
		tmp2 = (long long)cur->fl;
		res[c++] = tmp2 % 10 + '0';
		cur->fl -= tmp2;
	}
	res[len2 + 1] = '\0';
	cur->len += c;
	if (cur->prec >= 20 && cur->fl >= 0.5)
		res[cur->prec] = (char)(res[cur->prec] + 1);
	return (res);
}

void	find_len2(t_lst *cur)
{
	if (!cur->width && !cur->prec)
		cur->len2 = 6;
	else if (cur->prec)
		cur->len2 = cur->prec;
	else
		cur->len2 = cur->width;
}
