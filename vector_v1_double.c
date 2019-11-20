#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "vector_v1_double.h"

#ifndef __VECTOR_V1_DOUBLE__

p_s_vector_v1_double vector_v1_double_alloc(size_t n)
{
	p_s_vector_v1_double vector = malloc(sizeof(p_s_vector_v1_double));
	if (vector == NULL) return NULL;
	vector->elements = malloc(sizeof(double) * n);
	for (size_t i = 0; i < n; i++) vector->elements[i] = 0.0;
	vector->size = n;
	return vector;
}

void vector_v1_double_free(p_s_vector_v1_double p_vector)
{
	free(p_vector->elements);
	free(p_vector);
}

void vector_v1_double_set(p_s_vector_v1_double p_vector, size_t i, double v)
{
	if (0 > i || i > p_vector->size) return; // Si le i n'est pas dans le tableau
	p_vector->elements[i]	= v;
}

double get(p_s_vector_v1_double p_vector, size_t i)
{
	return (0 > i || i > p_vector->size)? -1.0 : p_vector->elements[i];
}

void vector_v1_double_insert(p_s_vector_v1_double p_vector, size_t i, double v)
{
	if (0 > i || i > p_vector->size) return; // Si le i n'est pas dans le tableau
	p_s_vector_v1_double vector = vector_v1_double_alloc(p_vector->size + 1);
	int replaced = 0;
	for (size_t j = 0; j < vector->size; j++) {
		if (i == j && replaced == 0) {
			replaced++;
			vector->elements[j] = v;
			j--;
		}
		else vector->elements[j + replaced] = p_vector->elements[j];
	}
	p_vector->elements = vector->elements;
	p_vector->size = vector->size;
}

void vector_v1_double_erase(p_s_vector_v1_double p_vector, size_t i)
{
	if (0 > i || i > p_vector->size) return; // Si le i n'est pas dans le tableau
	p_s_vector_v1_double vector = vector_v1_double_alloc(p_vector->size - 1);
	int replaced = 0;
	for (size_t j = 0; j < p_vector->size; j++) {
		if (i == j) replaced++;
		else vector->elements[j] = p_vector->elements[j - replaced];
	}
	p_vector->elements = vector->elements;
	p_vector->size = vector->size;
}

void vector_v1_double_push_back(p_s_vector_v1_double p_vector, double v)
{
	vector_v1_double_insert(p_vector, p_vector->size, v);
}

void vector_v1_double_pop_back(p_s_vector_v1_double p_vector)
{
	vector_v1_double_erase(p_vector, p_vector->size);
}

void vector_v1_double_clear(p_s_vector_v1_double p_vector)
{
	free(p_vector->elements);
	p_vector->size = 0;
}

int vector_v1_double_empty(p_s_vector_v1_double p_vector)
{
	return (!p_vector->size)? 1 : 0;
}

size_t vector_v1_double_size(p_s_vector_v1_double p_vector)
{
	return p_vector->size;
}

#endif
