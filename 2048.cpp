#include <iostream>
#include <set>
using namespace std;

void slide_left(int line[], int size, int flag);
void push_line_left(int line[], int index, int size);

void slide_right(int line[], int size, int flag);
void push_line_right(int line[], int index);

void print_line(int line[], int size);

int main()
{
  int reps, size, moves, aux;
  int flag = 0;
  string move;
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

    while (cin >> move)
    {

      if (move.compare("R") == 0)
      {
        for (int j = 0; j < size; j++)
        {
          slide_right(matriz[j], size, flag);
        }
      }

      else if (move.compare("L") == 0)
      {
        for (int j = 0; j < size; j++)
        {
          slide_left(matriz[j], size, flag);
        }
      }

      else
      {
        for (int i = 0; i < size; ++i)
        {
          for (int j = i; j < size; ++j)
          {
            aux = matriz[j][i];
            matriz[j][i] = matriz[i][j];
            matriz[i][j] = aux;
          }
        }

        if (move.compare("U") == 0)
        {
          for (int j = 0; j < size; j++)
          {
            slide_right(matriz[j], size, flag);
          }
        }

        else
        {
          for (int j = 0; j < size; j++)
          {
            slide_left(matriz[j], size, flag);
          }
        }

        for (int i = 0; i < size; ++i)
        {
          for (int j = i; j < size; ++j)
          {
            aux = matriz[j][i];
            matriz[j][i] = matriz[i][j];
            matriz[i][j] = aux;
          }
        }
      }
    }

    cout << "======= FINAL =========" << endl;

    for (int j = 0; j < size; j++)
    {
      for (int k = 0; k < size; k++)
      {
        cout << matriz[j][k] << " ";
      }

      cout << endl;
    }
  }

  return 0;
}

void slide_left(int line[], int size, int flag)
{

  for (int i = 0; i < size - 1; i++)
  {
    if (line[i] == line[i + 1] && flag == 0)
    {
      line[i + 1] *= 2;
      push_line_left(line, i, size);
      flag = 1;
    }

    else if (line[i] == line[i + 1] && flag == 1)
    {
      flag = 0;
    }

    else if (line[i + 1] == 0)
    {
      push_line_left(line, i + 1, size);
    }

    else
    {
      flag = 0;
    }

    //print_line(line, size);
  }
}

void slide_right(int line[], int size, int flag)
{

  for (int i = size - 1; i > 0; i--)
  {
    if (line[i] == line[i - 1] && flag == 0)
    {
      line[i - 1] *= 2;
      push_line_right(line, i);
      flag = 1;
    }

    else if (line[i] == line[i - 1] && flag == 1)
    {
      flag = 0;
    }

    else if (line[i - 1] == 0)
    {
      push_line_right(line, i - 1);
    }

    else
    {
      flag = 0;
    }

    //print_line(line, size);
  }
}

void push_line_right(int line[], int index)
{
  for (int i = index; i > 0; i--)
  {
    line[i] = line[i - 1];
  }
  line[0] = 0;
}

void push_line_left(int line[], int index, int size)
{
  for (int i = index; i < size; i++)
  {
    line[i] = line[i + 1];
  }
  line[size - 1] = 0;
}

void print_line(int line[], int size)
{
  cout << "........" << endl;
  for (int i = 0; i < size; i++)
  {
    cout << line[i] << " ";
  }

  cout << endl;
}