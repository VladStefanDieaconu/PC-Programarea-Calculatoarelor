// Copyright [2018] Dieaconu Vlad Stefan
#include "./tools.h"

int main() {
  int N, M, i, j, max_steps, steps, total_toys, len_santa_bag, bag_size;
  steps = 0;
  total_toys = 0;
  len_santa_bag = 0;

  // citesc marimea hartii, coordonatele initiale si numarul maxim de pasi
  scanf("%d %d", &N, &M);
  scanf("%d %d", &i, &j);
  scanf("%d", &max_steps);

  // aloc dinamic sacul mosului care va avea prima data doar 2 elemente
  bag_size = 2;
  packet *santa_bag = malloc(bag_size * sizeof(packet));

  // aloc dinamic harta ca o matrice de structuri
  region **map = malloc(N * sizeof(region*));
  for (int s = 0; s < N; ++s) {
    map[s] = malloc(M * sizeof(region));
  }
  // citesc harta
  read_map(map, N, M);

    while (true) {
      // Daca regiunea are jucarii de luat continuam
      if (map[i][j].num_toy > 0) {
        collect_toy(i, j, &santa_bag, &map, &len_santa_bag,
                    &total_toys, &bag_size);
      }
      // daca am ajuns la numarul maxim de pasi ies din while
      if (max_steps == steps) {
        break;
      }
      // calculez urmatoarea pozitie
      make_step(&i, &j, map[i][j].dir);

      // verific daca este o pozitie valida sau am iesit din harta
      if (i < 0 || i >= N || j < 0 || j >= M) {
        printf("TOO MUCH SNOW !\n");
        break;
      }
      // incrementez numarul de pasi parcursi
      ++steps;
    }
    // afisez numarul de pasi parcursi si numarul de jucarii adunate
    printf("%d\n%d\n", steps, total_toys);
    // sortez sacul mosului
    sort_santa_bag(santa_bag, len_santa_bag);
    // afisez sacul mosului
    print_santa_bag(len_santa_bag, santa_bag);

    // eliberam memoria
    free(santa_bag);

    for (int s = 0; s < N; ++s) {
      free(map[s]);
    }
    free(map);

}
