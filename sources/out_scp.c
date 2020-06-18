/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_scp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego <ediego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:28:16 by ediego            #+#    #+#             */
/*   Updated: 2019/12/21 15:13:46 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_cur_xp16(t_lst *cur)
{
	if (cur->prec > cur->len)
		cur->lenzero = cur->prec - cur->len;
	if (!cur->prec && cur->width > cur->len && cur->zero)
		cur->lenzero = cur->width - cur->len;
	if (cur->width > cur->len && cur->len >= cur->prec && !cur->lenzero)
		cur->lenspace = cur->width - cur->len;
	if (cur->width > cur->len && cur->prec >= cur->len)
		cur->lenspace = cur->width - cur->prec;
}

int		put_c(int n, char sym)
{
	int c;

	c = 0;
	while (c++ < n - 1)
		ft_putchar(sym);
	return (c);
}

int		out_c(t_lst *cur, va_list args)
{
	unsigned char	res;
	int				c;

	c = 0;
	res = (unsigned char)va_arg(args, int);
	if (cur->size)
		return (-1);
	if (cur->width && !cur->minus)
		c = put_symb(cur->width - 1, ' ');
	ft_putchar(res);
	if (cur->minus && cur->width > 1)
		c = put_symb(cur->width - 1, ' ');
	return (c + 1);
}

int		out_s(t_lst *cur, va_list args)
{
	char	*str;

	str = va_arg(args, char*);
	if (str == NULL && !cur->isnull)
		str = "(null)";
	cur->len = len_str(str);
	if (cur->prec && cur->prec < cur->len)
		cur->len = cur->prec;
	if (cur->width > cur->len && !cur->isnull)
		cur->lenspace = cur->width - cur->len;
	if (cur->width > cur->len && cur->isnull)
		cur->lenspace = cur->width;
	if (cur->lenspace && !cur->minus)
		cur->lenprint += put_symb(cur->lenspace, ' ');
	if (!cur->isnull)
		cur->lenprint += put_lstr(str, cur->len);
	if (cur->lenspace && cur->minus)
		cur->lenprint += put_symb(cur->lenspace, ' ');
	if (cur->isnull && cur->width && !cur->lenprint)
		cur->lenprint += put_symb(cur->width, ' ');
	return (cur->lenprint);
}

int		out_proc(t_lst *cur)
{
	if (cur->minus)
	{
		cur->lenprint += put_symb(1, '%');
		if (cur->width)
			cur->lenprint += put_symb(cur->width - 1, ' ');
	}
	else
	{
		if (cur->width > 1 && !cur->zero)
			cur->lenprint += put_symb(cur->width - 1, ' ');
		if (cur->width && cur->zero)
			cur->lenprint += put_symb(cur->width - 1, '0');
		cur->lenprint += put_symb(1, '%');
	}
	return (cur->lenprint);
}
