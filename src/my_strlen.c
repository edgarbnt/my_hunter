/*
** EPITECH PROJECT, 2023
** my_strlen.c
** File description:
** task03
*/

#include "../my_hunter.h"

int my_strlen(char const *str)
{
    int var = 0;

    while (str[var] != '\0' ){
    var++;
    }
    return (var);
}
