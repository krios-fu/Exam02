#include <unistd.h> // Incluyo librería del write, del pritnf y la de leer los argumentos
#include <stdio.h>
#include <stdarg.h>

size_t      ft_strlen(const char *s) // Strlen para calcular largo de strings
{
    size_t  c = 0;
    while (s[c])
        c++;
    return (c);
}

int         ft_numlen(long long n, int base_l) // Función para calcular el largo del nº. Se le pasa long long n y base_l
{
    int     i = 1; // Declaro una variable i que va a ser el largo
    while (n >= base_l || n <= -base_l) // Mientras sea mayor o igual que base_l o menor o igual que -base_l
    {
        n /= base_l; // N = N / base_l
        i++; // Sumo elemento
    }
    return (i); // Devuelvo el largo del nº final
}

void        ft_put_num(long long n, int base_l, char *base) // Función para poner nº. Se le pasa long long n, basel y base
{
    if (n >= base_l) // Si es mayor o igual que base_l, recursividad pasandole todo igual menos n / base_l
        ft_put_num(n / base_l, base_l, base);
	write(1, &base[n%base_l], 1); // Escribe &base[n%base_l]
}

int         ft_printf(const char *format, ...) // Función principal
{
    va_list list; // Declaro va_list para que me lea los argumentos
    char    *str, *s, *base; // Declaro str, s y base
    long    num; // Declaro un long num
    int     w = 0, p = 0, bolp = 0, n = 0, base_l = 0, len = 0, spc = 0, neg = 0, zero = 0; // Width, prec, boolp, n, base_l, len, espacio, cero y neg

    va_start(list, format); // Abro la lectura de argumentos por así decirlo
    str = (char *)format; // Meto format en str para poder moverme por el sin modificarlo
    while (*str != '\0') // Mientras exista str
    {
        if (*str == '%') // Si estoy en un %
        {
            str++; // Pasa a la siguiente posición
            w = 0, p = 0, bolp = 0, n = 0, spc = 0, neg = 0, zero = 0; // Igualo todo menos base_l a 0
            while (*str >= '0' && *str <= '9') // Si estoy en un nº este nº es el width
            {
                w = w * 10 + (*str - 48); // Resto 48 para pasarlo a carácter
                str++;
            }
            if (*str == '.') // Si estoy en un punto pasa a la siguiente posición
            {
                str++;
                while (*str >= '0' && *str <= '9') // El nº que haya después del punto lo meto en precisión
                {
                    p = p * 10 + (*str - 48);
                    str++;
                }
                bolp = 1; // Pongo a 1 el boolean de prec
            }
            if (*str == 's') // Si estoy en formato s
            {
                s = va_arg(list, char *); // S = el argumento que me pasen en formato char *
                if (!s) // Si no existe
                    s = "(null)"; // La igualo a "(null)"
                n = ft_strlen(s); // Mido la frase y la meto en n
            }
            if (*str == 'x') // Si estoy en formato x
            {
                num = va_arg(list, unsigned); // Meto el argumento en num como unsigned
                base = "0123456789abcdef"; // base = base hexadecimal
                base_l = 16; // base_l = 16 por hexa
                n = ft_numlen(num, base_l); // Mido el nº y lo meto en n
            }
            if (*str == 'd') // Si estoy en formato int
            {
                num = va_arg(list, int); // Meto en num el argument como int
                base = "0123456789"; // Base 10
                base_l = 10; // Base 10
                if (num < 0) // Si el nº es negativo lo pasa a positivo y neg = 1
                {
                    num *= -1;
                    neg = 1;
                }
                n = ft_numlen(num, base_l); // Mido el nº y lo meto en n
            }
            if (bolp == 1 && p >= n && *str != 's') // Si hay prec, es mayor o igual que n y no es formato s
                zero = p - n; // Calulo ceros
            else if (bolp == 1 && p < n && *str == 's') // Si hay prec, es menor que n y es s
                n = p; // El largo de la frase será la prec
            else if (bolp == 1 && p == 0 && (*str == 's' || num == 0)) // Si hay prec == 0 && num = 0 o formato s
                n = 0; // El largo de la frase o nº es 0
            spc = w - n - zero; // Calculo espacios. w - n - zero
            while (spc-- > 0) // Mientras haya espacios los imprimo y sumo el largo
            {
                write(1, " ", 1);
                len++;
            }
            if (neg == 1) // Si hay un negativo imprimo el signo
            {
                write(1, "-", 1);
                len++;
            }
            while (zero-- > 0) // Mientras haya ceros los imprimo y sumo el largo
            {
                write(1, "0", 1);
                len++;
            }
            if (*str == 's') // Si el formato es s
                write(1, s, n); // Imprimo s con n de largo
            else if (n > 0) // Si es un nº y es mayor que 0
                ft_put_num(num, base_l, base); // Pasamos la función recursiva para que imprima el nº
            len += n; // sumo n al largo
            str++; // Paso posición y vuelvo a evaluar
        }
        else // Si no estoy en un %
        {
            write(1, str, 1); // Escribo la posición en la que estoy, y sumo posición y laro y vuelvo a evaluar
            str++;
            len++;
        }
    }
    va_end(list); // Cierro la lectura de argumentos
    return (len); // Devuelvo el largo de la frase creada
}


int main ()
{
    printf("mio:  --->\n");
    printf("%d: ",ft_printf("Hola %3.10d %s\n", -3, "hola mundo"));
    printf("origina --->\n");
    printf("%d: ",printf("Hola %3.10d %s\n", -3, "hola mundo"));

}