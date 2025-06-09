/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:20:57 by gfontagn          #+#    #+#             */
/*   Updated: 2024/12/08 15:54:29 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>

typedef struct s_form
{
	int		minus;
	int		zero;
	int		hash;
	int		space;
	int		plus;
	int		width;
	int		precision;
	int		hxnnul;
	char	specifier;
	int		count;
	char	*res;
	int		negative;

}		t_form;

// ft_printf.c
int		ft_printf(const char *s, ...);

// f_found.c
int		f_found(char *s, va_list apt);
t_form	new_formatter(void);

// set_args.c
t_form	set_flags(char *s, t_form form);

// fter.c
t_form	fter_char(t_form form, va_list apt);
t_form	fter_str(t_form form, va_list apt);
t_form	fter_dec(t_form form, va_list apt);
t_form	fter_udec(t_form form, va_list apt);
t_form	fter_prct(t_form form, va_list apt);

// fter_hex.c
t_form	fter_ptr(t_form form, va_list apt);
t_form	fter_hexlow(t_form form, va_list apt);
t_form	fter_hexup(t_form form, va_list apt);

// precision.c
char	*trim_str(int precision, char *str);
char	*add_padding_nbr(int precision, char *str, char sign);

// format.c
t_form	format_output(t_form form);
char	*add_prefix_hex(t_form form);

// utils.c
char	*ft_uitoa(unsigned long n);
void	reverse_string(char *str);
char	*ft_empty(void);
int		no_specifier(void);

// add_neg.c
char	*add_negative_sign(char *str);
#endif
