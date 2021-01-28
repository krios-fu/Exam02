/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:34:03 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/28 20:16:39 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char * ft_aux (char *s, int c)
{
    char *str;
    int i;

    i = 0;

    while (s[i])
        i++;
    if (!(str  = (char *) malloc (1 + i)))
       return (0);
       i = 0;
       while (s[i])
       {
           str[i] = s[i];
           i++;
       }
       str[i] = c;
       str[i + 1] = '\0';
       free(s);
       return(str);
}

int get_next_line (char **line)
{
    char buffer;
    int flag;

    if(!line  || !(*line = malloc (1)))
        return (-1);
        *line [0] = '\0';
        while ((flag = read(0, &buffer, 1) > 0))
        {
            if (buffer == '\n')
                break;
            *line = ft_aux (*line, buffer);
        }
        return (flag);
}

int main (int argc, char ** argv)
{
    char *line;
   while (get_next_line(&line))
   {
        printf("%s", line);
   }
        
        
    
    return (0);
}