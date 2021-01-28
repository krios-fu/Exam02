/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:58:54 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/21 15:34:01 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

size_t ft_strlen (const char *s)
{
    size_t i = 0;

    while (s [i] != '\0')
        i++;
    return (i);
}

int ft_intlen(long long num, int base)
{
    int i;

    i = 1;
    while(num >= base || num <= -base)
    {
        num /= base;
        i++;
    }
    return (i);
}

void ft_print_num (long long num, int base_l, char *base)
{

    if(num >= base_l)
        ft_print_num(num / base_l, base_l, base);
    write(1, &base[num%base_l], 1);
}

int ft_printf(const char *format, ...)
{
    va_list list;

    char *s, *base, *str;

    str = (char *)format;

    va_start (list, format);
     int w = 0, p = 0, basel = 0, spc = 0, dot = 0, zero = 0, len_str = 0, len = 0, num = 0, neg = 0;

     while (*str != '\0')
     {
         if (*str == '%')
         {
              w = 0, p = 0, basel = 0, spc = 0, dot = 0, zero = 0, len = 0, num = 0, neg = 0;
             str++;
             while (*str >= '0' && *str <= '9')
             {
                 w = w * 10 + (*str - 48);
                 str++;
             }
             if(*str == '.')
             {
                 str++; 
                while (*str >= '0' && *str <= '9')
                  {
                     p = p * 10 + (*str - 48);
                     str++;
                 }
                 dot = 1;
             }
             if (*str == 's')
             {
                 s = va_arg(list, char *);
                 if(!s)
                    s = "(null)";
                len = ft_strlen(s);
             }
             else if (*str == 'd')
             {
                 num = va_arg(list, int);
                 if(num < 0)
                 {
                    num *= -1;
                    neg = 1;
                 }
                    basel = 10;
                    base = "0123456789";
                len = ft_intlen(num, basel);
             }
              else if (*str == 'x')
             {
                 num = va_arg(list, unsigned);
                 basel = 16;
                 base = "0123456789abcdef";
                len =  ft_intlen(num, basel);
             }
             if(dot == 1 && p >= len && *str != 's')
                zero = p - len;
            if (dot == 1 && *str == 's' && p < len)
                len = p;
            if (dot == 1 && p == 0 && (*str == 's' | num == 0))
                len = 0;
            spc = w - len - zero;

        while (spc-- > 0)
            len_str += write(1, " ", 1);
        if (neg == 1)
            len_str += write(1, "-", 1);
        while (zero-- > 0)
            len_str += write(1, "0", 1);
        if (*str == 's')
            len_str += write(1, s, len);
        else if (num >= 0)
        {
            len_str += len;
            ft_print_num(num, basel, base);
        }
     }
        else 
           len_str +=  write (1, str, 1);
        str++;

      
     }
       va_end(list);
        return (len_str);
}

int main ()
{
    printf("----> Mio\n");
    printf("\n%d\n", ft_printf("holala%d %10.s", 12, "42\0"));
    printf("\n----> Original\n");
    printf("\n%d\n", printf("holala%d %10.s", 12, "42\0"));
    return(0);
}

