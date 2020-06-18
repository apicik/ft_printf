/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_u.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego <ediego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:57:41 by ediego            #+#    #+#             */
/*   Updated: 2019/12/21 00:24:21 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	len_unum(unsigned long long num)
{
	int c;

	c = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= 10;
		c++;
	}
	return (c);
}

int	print_rightu(t_lst *cur)
{
	if (cur->lenspace > 0)
		cur->lenprint += put_symb(cur->lenspace, ' ');
	if (cur->lenzero)
		cur->lenprint += put_symb(cur->lenzero, '0');
	if (!cur->isnull)
		putnbrl(cur->unum);
	if (!cur->isnull)
		return (cur->lenprint + cur->len);
	else
		return (cur->lenprint);
}

int	print_leftu(t_lst *cur)
{
	if (cur->lenzero)
		cur->lenprint += put_symb(cur->lenzero, '0');
	if (!cur->isnull)
		putnbrl(cur->unum);
	if (cur->lenspace > 0)
		cur->lenprint += put_symb(cur->lenspace, ' ');
	if (!cur->isnull)
		return (cur->lenprint + cur->len);
	else
		return (cur->lenprint);
}

int	out_u(t_lst *cur, va_list args)
{
	if (!cur->size)
		cur->unum = va_arg(args, unsigned long long) % 4294967296;
	else
		cur->unum = va_arg(args, unsigned long long);
	if (cur->size == 4)
		cur->unum %= 256;
	if (cur->size == 5)
		cur->unum %= 65536;
	if (!cur->isnull)
		cur->len = len_unum(cur->unum);
	if (cur->prec > cur->len)
		cur->lenzero = cur->prec - cur->len;
	if (!cur->prec && cur->width > cur->len && cur->zero)
		cur->lenzero = cur->width - cur->len;
	if (cur->width > cur->len && cur->len >= cur->prec && !cur->lenzero)
		cur->lenspace = cur->width - cur->len;
	if (cur->width > cur->len && cur->prec >= cur->len)
		cur->lenspace = cur->width - cur->prec;
	if (cur->minus)
		return (print_leftu(cur));
	return (print_rightu(cur));
}
