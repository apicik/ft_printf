/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_di.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego <ediego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 14:48:49 by ediego            #+#    #+#             */
/*   Updated: 2019/12/20 23:26:39 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_plusdi(t_lst *cur)
{
	if (cur->num < 0)
		cur->signmin = 1;
	if (cur->lenspace > 0)
		cur->lenprint += put_symb(cur->lenspace, ' ');
	if (cur->lenzero && cur->plus && cur->num >= 0)
		cur->lenprint += put_symb(1, '+');
	if (cur->lenzero && cur->signmin)
	{
		cur->lenprint += put_symb(1, '-');
		cur->num *= -1;
	}
	if (cur->lenzero)
		cur->lenprint += put_symb(cur->lenzero, '0');
	if (!cur->lenzero && cur->plus && cur->num >= 0)
		cur->lenprint += put_symb(1, '+');
	if (!cur->lenzero && cur->signmin)
	{
		cur->lenprint += put_symb(1, '-');
		cur->num *= -1;
	}
	putnbrl(cur->num);
	return (cur->lenprint + cur->len);
}

int	print_rightdi(t_lst *cur)
{
	if (cur->num < 0)
		cur->signmin = 1;
	if (cur->plus)
		return (print_plusdi(cur));
	if (cur->lenspace > 0)
		cur->lenprint += put_symb(cur->lenspace, ' ');
	if (cur->signmin)
	{
		cur->lenprint += put_symb(1, '-');
		cur->num *= -1;
	}
	if (cur->lenzero)
		cur->lenprint += put_symb(cur->lenzero, '0');
	putnbrl(cur->num);
	return (cur->lenprint + cur->len);
}

int	print_leftdi(t_lst *cur)
{
	if (cur->num < 0)
		cur->signmin = 1;
	if (cur->sign && cur->signmin)
	{
		cur->lenprint += put_symb(1, '-');
		cur->num *= -1;
	}
	if (cur->sign && !cur->signmin)
		cur->lenprint += put_symb(1, '+');
	if (cur->lenzero)
		cur->lenprint += put_symb(cur->lenzero, '0');
	putnbrl(cur->num);
	if (cur->lenspace > 0)
		cur->lenprint += put_symb(cur->lenspace, ' ');
	return (cur->lenprint + cur->len);
}

int	output_digital(t_lst *cur)
{
	cur->len = len_num(cur->num);
	if (cur->plus || cur->num < 0)
		cur->sign = 1;
	if (cur->space && !cur->sign)
	{
		cur->lenprint = put_symb(1, ' ');
		cur->width--;
	}
	if (cur->prec > cur->len)
		cur->lenzero = cur->prec - cur->len;
	if (!cur->prec && cur->width > cur->len && cur->zero)
		cur->lenzero = cur->width - cur->len - cur->sign;
	if (cur->width > cur->len && cur->len >= cur->prec && !cur->lenzero)
		cur->lenspace = cur->width - (cur->len + cur->sign);
	if (cur->width > cur->len && cur->prec >= cur->len)
		cur->lenspace = cur->width - (cur->prec + cur->sign);
	if (cur->num == 0 && cur->isnull)
		return (print_zerodi(cur));
	if (cur->minus)
		return (print_leftdi(cur));
	return (print_rightdi(cur));
}

int	out_di(t_lst *cur, va_list args)
{
	if (cur->size == 1 || cur->size == 2)
		cur->num = va_arg(args, long long);
	else
		cur->num = va_arg(args, int);
	if (cur->size == 5)
		cur->num = (short int)cur->num;
	if (cur->size == 4)
		cur->num = (char)cur->num;
	if (cur->minus)
		cur->zero = 0;
	return (output_digital(cur));
}
