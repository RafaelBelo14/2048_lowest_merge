#include <iostream>
using namespace std;

int check_move(int tile, int next_tile);

int main()
{
  int reps, size, moves;
  int modifier, aux1, aux2;

  cin >> reps;

  for (int i = 0; i < reps; i++)
  {
    cin >> size;
    cin >> moves;
    int matriz[size][size];

    for (int j = 0; j < size; j++)
    {
      for (int k = 0; k < size; k++)
      {
        cin >> matriz[j][k];
      }
    }

    // slide right        

    for (int j = 0; j < size; j++)
    {
      for (int k = 0; k < size; k++)
      {
        if (k != size - 1)
        {
          modifier = check_move(matriz[j][k], matriz[j][k + 1]);

          if (modifier == 1)
          {
            matriz[j][k] = 0;
            matriz[j][k + 1] *= 2;
            
          }

          else if (modifier == -1)
          {
            aux1 = matriz[j][k];
            matriz[j][k] = 0;
            matriz[j][k + 1] = aux1;
          }
        }
      }
    }

    cout << "================" << endl;

    for (int j = 0; j < size; j++)
    {
      for (int k = 0; k < size; k++)
      {
        cout << matriz[j][k] << " ";
      }

      cout << endl;
    }
  }
  cout << "cona" << endl;

  return 0;
}

int check_move(int tile, int next_tile)
{
  if (tile == next_tile)
  {
    return 1;
  }
  else if (next_tile == 0)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}