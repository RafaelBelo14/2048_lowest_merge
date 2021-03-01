#include <iostream>
#include <set>
using namespace std;

void slide_left(int line[], int size, int flag);
void push_line_left(int line[], int index, int size);

void slide_right(int line[], int size, int flag);
void push_line_right(int line[], int index, int size);

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
                                    slide_left(matriz[j], size, flag);
                              }
                        }

                        else
                        {
                              for (int j = 0; j < size; j++)
                              {
                                    slide_right(matriz[j], size, flag);
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
            if (line[i] == 0) {
                  push_line_left(line, i, size);
                  if (line[i + 1] != 0) {
                        --i;
                  }
            }
            else if (line[i + 1] == 0)
            {
                  push_line_left(line, i + 1, size);
                  if (line[i + 1] != 0) {
                        --i;
                  }
            }
            else
            {
                  if (line[i] == line[i + 1] && flag == 0)
                  {
                        line[i + 1] = 0;
                        line[i] *= 2;
                        flag = 1;
                        i--;
                  }
                  else
                  {
                        flag = 0;
                  }
            }
      }
}

void slide_right(int line[], int size, int flag) 
{
      for (int i = size - 1; i > 0; i--)
      {
            if (line[i] == 0) {
                  push_line_right(line, i, size);
                  if (line[i - 1] != 0) {
                        ++i;
                  }
            }
            else if (line[i - 1] == 0)
            {
                  push_line_right(line, i - 1, size);
                  if (line[i - 1] != 0) {
                        ++i;
                  }
            }
            else
            {
                  if (line[i] == line[i - 1] && flag == 0)
                  {
                        line[i - 1] = 0;
                        line[i] *= 2;
                        flag = 1;
                        ++i;
                  }
                  else
                  {
                        flag = 0;
                  }
            }

            print_line(line, size);
      }
}

void push_line_left(int line[], int index, int size)
{
      for (int j = index; j < size; j++)
      {
            for (int i = j + 1; i < size; i++)
            {
                  if (line[i] != 0)
                  {
                        line[j] = line[i];
                        line[i] = 0;
                        break;
                  }
            }
      }
}

void push_line_right(int line[], int index, int size)
{
      for (int j = index; j > 0; j--)
      {
            for (int i = j - 1; i >= 0; i--)
            {
                  if (line[i] != 0)
                  {
                        line[j] = line[i];
                        line[i] = 0;
                        break;
                  }
            }
      }
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