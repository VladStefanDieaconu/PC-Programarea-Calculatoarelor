// Copyright [2018] Dieaconu Vlad Stefan
#ifndef TOOLS
#define TOOLS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define MAX 200

// reprezinta o regiune de pe harta
typedef struct {
  char city[MAX];
  char toy[MAX];
  int num_toy;
  char dir;
} region;

typedef struct {
  char toy[MAX];
  int num_toy;
} gift;

// reprezinta un cadou din sacul mosului
typedef struct {
  char city[MAX];
  gift gifts[MAX];
  int len_gifts;
} packet;

// functie pentru citirea hartii
void read_map(region** map, int N, int M);

// functie pentru compararea a doua orase lexicografic
int compare_cities(const void * a, const void * b);

// functie pentru compararea a doua cadouri
int compare_gifts(const void * a, const void * b);

// functie care ne deplaseaza pe harta in functie de directia primita
void make_step(int *i, int *j, char directie);

// functie pentru printarea sacului mosului
void print_santa_bag(int len_santa_bag, packet* santa_bag);

// functie de sortare a oraselor si apoi a cadourilor pentru fiecare oras
void sort_santa_bag(packet* santa_bag, int len_santa_bag);

// functie pentru dublarea marimii sacului mosului
void realloc_santa_bag(int bag_size, packet** santa_bag);

// functie pentru colectat jucarii
void collect_toy(int i, int j, packet** santa_bag, region*** map,
                      int* len_santa_bag, int* total_toys, int* bag_size);

#endif
