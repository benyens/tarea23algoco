#ifndef COSTS_H
#define COSTS_H

#include <vector>
#include <string>

void leer_costos();
int cost_insert(char b);
int cost_delete(char b);
int cost_replace(char a, char b);
int cost_transpose(char a, char b);

#endif