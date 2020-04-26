// Copyright [2018] Dieaconu Vlad Stefan
#include "./tools.h"

// functie pentru citirea hartii
void read_map(region** map, int N, int M) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      scanf("%s ", map[i][j].city);
      scanf("%s ", map[i][j].toy);
      scanf("%d ", &map[i][j].num_toy);
      scanf("%c\n", &map[i][j].dir);
    }
  }
}
// functie pentru compararea a doua orase lexicografic
int compare_cities(const void * a, const void * b) {
  packet *orderA = (packet *)a;
  packet *orderB = (packet *)b;
  return strcmp(orderA->city, orderB->city);
}

// functie pentru compararea a doua cadouri
int compare_gifts(const void * a, const void * b) {
  gift *orderA = (gift *)a;
  gift *orderB = (gift *)b;

  // daca 2 jucarii au acelasi numar de aparitii
  // comparatia se face pe baza de numele tipului de jucarie
  if (orderA->num_toy == orderB->num_toy) {
    return strcmp(orderA->toy, orderB->toy);
  }

  // in caz contrat comparatia se va face pe baza numarului de aparitii al
  // fiecarei jucarii
  return - orderA->num_toy + orderB->num_toy;
}

// functie care ne deplaseaza pe harta in functie de directia primita
void make_step(int *i, int *j, char directie) {
  if (directie == 'U') {
    --(*i);
  } else if (directie == 'D') {
    ++(*i);
  } else if (directie == 'L') {
    --(*j);
  } else if (directie == 'R') {
    ++(*j);
  }
}

// functie pentru printarea sacului mosului
void print_santa_bag(int len_santa_bag, packet* santa_bag) {
  for (int i = 0; i < len_santa_bag; ++i) {
    printf("%s:\n", santa_bag[i].city);
    for (int j = 0; j < santa_bag[i].len_gifts; ++j) {
      printf("  %d %s\n", santa_bag[i].gifts[j].num_toy,
        santa_bag[i].gifts[j].toy);
    }
  }
}

// functie de sortare a oraselor si apoi a cadourilor pentru fiecare oras
void sort_santa_bag(packet* santa_bag, int len_santa_bag) {
  qsort(santa_bag, len_santa_bag, sizeof(packet), compare_cities);
  for (int k = 0; k < len_santa_bag; ++k) {
    qsort(santa_bag[k].gifts, santa_bag[k].len_gifts,
      sizeof(gift), compare_gifts);
  }
}

// functie pentru dublarea marimii sacului mosului
void realloc_santa_bag(int bag_size, packet** santa_bag) {
  *santa_bag = realloc(*santa_bag, bag_size * sizeof(packet));
}

// functie pentru colectat jucarii
void collect_toy(int i, int j, packet** santa_bag, region*** map,
                      int* len_santa_bag, int* total_toys, int* bag_size) {
  bool city_found, toy_found;
  city_found = false;

  for (int k = 0; k < *len_santa_bag; ++k) {
    // verific daca am mai intalnit orasul respectiv inainte sau este
    // un oras nou si trebuie sa il adaug in memorie
    if (strcmp((*santa_bag)[k].city, (*map)[i][j].city) == 0) {
      city_found = true;
      toy_found = false;
      for (int l = 0; l < (*santa_bag)[k].len_gifts; ++l) {
        // verific daca am mai intalnit acest tip de jucarie la acest oras
        if (strcmp((*santa_bag)[k].gifts[l].toy, (*map)[i][j].toy) == 0) {
          ++(*santa_bag)[k].gifts[l].num_toy;
          toy_found = true;

          break;
        }
      }

      // daca nu am mai intalnit acest tip de jucarie o adaug in sac
      if ( !toy_found ) {
        strcpy((*santa_bag)[k].gifts[(*santa_bag)[k].len_gifts].toy,
          (*map)[i][j].toy);
        ++(*santa_bag)[k].gifts[(*santa_bag)[k].len_gifts].num_toy;
        ++(*santa_bag)[k].len_gifts;
      }
      break;
    }
  }

  // daca nu am mai intalnit acest oras il adaug in memorie si adaug si
  // jucaria respectiva
  if (!city_found) {
    // daca sacul meu s-a umplut ii dublez marimea
    if ((*len_santa_bag) == (*bag_size)) {
      (*bag_size) *= 2;
      realloc_santa_bag((*bag_size), santa_bag);
    }

    (*santa_bag)[(*len_santa_bag)].len_gifts = 1;
    strcpy((*santa_bag)[(*len_santa_bag)].city, (*map)[i][j].city);
    strcpy((*santa_bag)[(*len_santa_bag)].gifts[0].toy, (*map)[i][j].toy);
    (*santa_bag)[(*len_santa_bag)].gifts[0].num_toy = 1;
    ++(*len_santa_bag);
  }

  --(*map)[i][j].num_toy;
  ++(*total_toys);
}
