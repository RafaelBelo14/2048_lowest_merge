#include <iostream>
using namespace std;

int check_move(int before_tile, int tile, int next_tile);


int main() {
  int reps, size, moves;
  int modifier, aux1, aux2;

  cin >> reps;

  for (int i = 0; i < reps; i++) {
    cin >> size;
    cin >> moves;
    int matriz[size][size];

    for(int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {
        cin >> matriz[j][k];
      }
    }

    // slide right

    for(int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {

        if (k != size - 1 && k > 0) {
          modifier = check_move(matriz[j][k - 1], matriz[j][k], matriz[j][k + 1]);

          if (modifier == 0) { // tiles iguais e ainda não houve soma
            aux1 = matriz[j][k - 1];
            matriz[j][k] += aux1;
            matriz[j][k - 1] = 0;
          }
          else if (modifier == 1) {
            aux1 = matriz[j][k - 1];
            matriz[j][k - 1] = 0;
            matriz[j][k] = aux1;
            matriz[j][k + 1] *= 2;
            ++k;
          }

          else if (modifier == -1) {
            aux1 = matriz[j][k - 1];
            aux2 = matriz[j][k];
            matriz[j][k - 1] = 0;
            matriz[j][k] = aux1;
            matriz[j][k + 1] = aux2;
          }

          else if (modifier == -2){
            aux1 = matriz[j][k - 1];
            matriz[j][k] = aux1;
            matriz[j][k - 1] = 0;
          }
        }
      }
    }

    cout << "================" << endl;

    for(int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {
        cout << matriz[j][k] << " ";
      }

      cout << endl;
    }
  }

  return 0;
}

int check_move(int before_tile, int tile, int next_tile) {
  if (before_tile == tile) {
    return 0;
  }
  else {
      if (tile == next_tile) {
        return 1;
      }
      else if (next_tile == 0) {
        return -1;
      }
      else if (next_tile != -1){
        return -2;
      }
  }

  return -3;
}