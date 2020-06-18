/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego <ediego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 21:32:21 by ediego            #+#    #+#             */
/*   Updated: 2019/12/21 14:35:48 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		concat_fl(t_lst *cur, char *numb1, char *numb2)
{
	int i;

	cur->plus ? cur->sign = 1 : 0;
	cur->fl < 0 ? cur->signmin = 1 : 0;
	real_num(cur);
	cur->len += len_num(cur->fl);
	cur->str = itoa_f1(cur, numb1);
	if (cur->isnull && !cur->sharp)
		return (len_str(cur->str));
	else if (cur->isnull && cur->sharp)
		return (len_str(cur->str = ft_strcat(cur->str, ".")));
	i = atoi_i(cur->str);
	if (cur->fl < 0)
		i *= -1;
	cur->fl = cur->fl - i;
	find_len2(cur);
	cur->str2 = itoa_f2(cur, cur->len2, numb2);
	cur->str = ft_strcat(cur->str, cur->str2);
	return (len_str(cur->str));
}

void	out_f_left(t_lst *cur)
{
	if (cur->signmin)
		cur->lenprint += put_symb(1, '-');
	else if (cur->sign && !cur->signmin)
		cur->lenprint += put_symb(1, '+');
	ft_putstr(cur->str);
	if (cur->lenspace)
		cur->lenprint += put_symb(cur->lenspace, ' ');
}

void	out_f_right(t_lst *cur)
{
	if (cur->lenspace)
		cur->lenprint += put_symb(cur->lenspace, ' ');
	if (cur->signmin)
		cur->lenprint += put_symb(1, '-');
	else if (cur->plus && !cur->signmin)
		cur->lenprint += put_symb(1, '+');
	if (cur->lenzero)
		cur->lenprint += put_symb(cur->lenzero, '0');
	ft_putstr(cur->str);
}

void	fill_cur_f(t_lst *cur, char *numb1, char *numb2)
{
	if (cur->fl < 0 || cur->plus)
		cur->sign = 1;
	if (cur->space && !cur->sign)
	{
		cur->lenprint = put_symb(1, ' ');
		cur->width--;
	}
	cur->len = concat_fl(cur, numb1, numb2);
	if (cur->prec > cur->len)
		cur->lenzero = cur->prec - cur->len;
	if (!cur->minus && cur->width > cur->len && cur->zero)
		cur->lenzero = cur->width - cur->len - cur->sign;
	if (cur->width > cur->len && cur->len >= cur->prec && !cur->lenzero)
		cur->lenspace = cur->width - (cur->len + cur->sign);
	if (cur->width > cur->len && cur->prec >= cur->len)
		cur->lenspace = cur->width - (cur->prec + cur->sign);
}

int		out_f(t_lst *cur, va_list args)
{
	char *numb1;
	char arr1[60];
	char *numb2;
	char arr2[60];

	numb1 = arr1;
	numb2 = arr2;
	if (cur->size == 3)
		cur->fl = va_arg(args, long double);
	else
		cur->fl = va_arg(args, double);
	fill_cur_f(cur, numb1, numb2);
	if (cur->minus)
		out_f_left(cur);
	else
		out_f_right(cur);
	return (cur->len + cur->lenprint);
}
