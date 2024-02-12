/*
** EPITECH PROJECT, 2023
** my_strcat
** File description:
** my_strcat
*/

#include "../my_hunter.h"

char *my_strcat(char *dest, char const *src)
{
    int length1 = my_strlen(dest);
    int length2 = my_strlen(src);
    int a = 0;

    for (int a = 0; a < length2; a++){
        dest[length1 + a] = src[a];
    }
    dest[length1 + a + length2] = '\0';
}
