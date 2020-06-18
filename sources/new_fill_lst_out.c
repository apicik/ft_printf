/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_fill_lst_out.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediego <ediego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 21:40:32 by ediego            #+#    #+#             */
/*   Updated: 2019/12/20 20:43:01 by ediego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_list(int *i, char *str, t_lst *new, va_list args)
{
	while (new->type == 0 && str[*i])
	{
		*i = *i + 1;
		if (str[*i] == '-' || str[*i] == '+' || str[*i] == ' ' ||
		str[*i] == '#' || str[*i] == '0')
			fill_flag(i, str, new);
		if ((str[*i] >= '1' && str[*i] <= '9') || str[*i] == '*')
			fill_width(i, str, new, args);
		if (str[*i] == '.')
			fill_prec(i, str, new, args);
		if (str[*i] == 'l' || str[*i] == 'h' || str[*i] == 'L')
			fill_size(i, str, new);
		if (str[*i] == 'd' || str[*i] == 'i' || str[*i] == 'o' ||
		str[*i] == 'u' || str[*i] == 'x' || str[*i] == 'X' || str[*i] == 'c' ||
		str[*i] == 's' || str[*i] == 'p' || str[*i] == '%' || !str[*i] ||
		str[*i] == 'f')
			fill_type(i, str, new);
	}
}

t_lst	*new_list(void)
{
	t_lst	*new;

	new = (t_lst*)ft_memalloc(sizeof(t_lst));
	return (new);
}

int		chk_buf(int *i, const char *str, va_list args)
{
	t_lst	*new;
	int		ret;

	new = new_list();
	fill_list(i, (char*)str, new, args);
	ret = out_list(new, args);
	free(new);
	return (ret);
}

int		out_list(t_lst *cur, va_list args)
{
	if (cur->type == 1)
		return (out_di(cur, args));
	if (cur->type == 2)
		return (out_o(cur, args));
	if (cur->type == 3)
		return (out_u(cur, args));
	if (cur->type == 4 || cur->type == 5)
		return (out_x16(cur, args));
	if (cur->type == 6)
		return (out_f(cur, args));
	if (cur->type == 10)
		return (out_c(cur, args));
	if (cur->type == 11)
		return (out_s(cur, args));
	if (cur->type == 12)
		return (out_p16(cur, args));
	if (cur->type == 888)
		return (out_proc(cur));
	return (0);
}
