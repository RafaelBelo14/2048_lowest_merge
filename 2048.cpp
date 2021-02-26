#include <iostream>
#include <list>
using namespace std;

void slide_right(int line[], int size, int flag);
void push_line_right(int line[], int index);

void slide_left(int line[], int size, int flag);
void push_line_left(int line[], int index, int size);

void slide_up(int line[], int size, int flag);
void push_line_up(int line[], int index, int size);

void slide_down(int line[], int size, int flag);
void push_line_down(int line[], int index, int size);

void print_line(int line[], int size);

int main()
{
  int reps, size, moves;
  int flag = 0;
  int slide_help_iterator = 0;
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

    for (int j = 0; j < size; j++)
    {
      slide_left(matriz[j], size, flag);
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

  return 0;
}

void slide_right(int line[], int size, int flag)
{

  for (int i = 0; i < size - 1; i++)
  {
    if (line[i] == line[i + 1] && flag == 0)
    {
      line[i + 1] *= 2;
      push_line_right(line, i);
      flag = 1;
    }

    else if (line[i] == line[i + 1] && flag == 1)
    {
      flag = 0;
    }

    else if (line[i + 1] == 0)
    {
      push_line_right(line, i + 1);
    }

    else
    {
      flag = 0;
    }

    //print_line(line, size);
  }
}

void slide_left(int line[], int size, int flag)
{

  for (int i = size - 1; i > 0; i--)
  {
    if (line[i] == line[i - 1] && flag == 0)
    {
      line[i - 1] *= 2;
      push_line_left(line, i, size);
      flag = 1;
    }

    else if (line[i] == line[i - 1] && flag == 1)
    {
      flag = 0;
    }

    else if (line[i - 1] == 0)
    {
      push_line_left(line, i - 1, size);
    }

    else
    {
      flag = 0;
    }

    //print_line(line, size);
  }
}

/*
void slide_up(int line[], int size, int flag)
{

  for (int i = 0; i < size - 1; i++)
  {
    if (line[i] == line[i + 1] && flag == 0)
    {
      line[i + 1] *= 2;
      push_line(line, i);
      flag = 1;
    }

    else if (line[i] == line[i + 1] && flag == 1)
    {
      flag = 0;
    }

    else if (line[i + 1] == 0)
    {
      push_line(line, i + 1);
    }

    else {
      flag = 0;
    }

    //print_line(line, size);
  }
}

void slide_down(int line[], int size, int flag)
{

  for (int i = 0; i < size - 1; i++)
  {
    if (line[i] == line[i + 1] && flag == 0)
    {
      line[i + 1] *= 2;
      push_line(line, i);
      flag = 1;
    }

    else if (line[i] == line[i + 1] && flag == 1)
    {
      flag = 0;
    }

    else if (line[i + 1] == 0)
    {
      push_line(line, i + 1);
    }

    else {
      flag = 0;
    }

    //print_line(line, size);
  }
}
*/

void push_line_right(int line[], int index)
{
  /*if (index == 0)
  {
    line[0] = 0;
    return;
  }
  else
  {*/
  for (int i = index; i > 0; i--)
  {
    line[i] = line[i - 1]; //move all element to the left except first one
  }
  line[0] = 0;
  //}
}

void push_line_left(int line[], int index, int size)
{
  for (int i = index; i < size; i++)
  {
    line[i] = line[i + 1]; //move all element to the left except first one
  }
  line[size - 1] = 0;
}

/*
void push_line_up(int line[], int index, int size)
{
  for (int i = index; i < size; i++)
  {
    line[i] = line[i + 1]; //move all element to the left except first one
  }
  line[size - 1] = 0;
}

void push_line_down(int line[], int index, int size)
{
  for (int i = index; i < size; i++)
  {
    line[i] = line[i + 1]; //move all element to the left except first one
  }
  line[size - 1] = 0;
}
*/

void print_line(int line[], int size)
{
  cout << "........" << endl;
  for (int i = 0; i < size; i++)
  {
    cout << line[i] << " ";
  }

  cout << endl;
}