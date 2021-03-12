#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <stack> 
using namespace std;

int limite;
vector<int> output;
stack<vector<vector <int> > > queueMatrix;
vector<string> test;


bool doCase(int slide, int flag, int level);

vector< vector<int> > inputMatrix(int size);

int checkDuplicates(vector< vector<int> > matriz);
bool badSlide(int slide, int flag);

vector< vector<int> > checkSlide(vector< vector<int> > matriz, int flag, int slide);
vector< vector<int> > doTranspose(vector< vector<int> > matriz);

vector< vector<int> > slide_left(vector< vector<int> > matriz, int flag);
vector< vector<int> > slide_right(vector< vector<int> > matriz, int flag);
vector<int> push_line_left(vector<int> line, int index);
vector<int> push_line_right(vector<int>, int index);

void print_line(vector<int>);
void printMatrix(vector< vector<int> > matriz);

int main()
{
      int reps, size;
      cin >> reps;
      

      for (int i = 0; i < reps; i++)
      {
            vector< vector<int> > matriz;
            cin >> size;
            cin >> limite;

            matriz = inputMatrix(size);
            queueMatrix.push(matriz);
            doCase(0, 0, 0);

            if (output.size() == 0) {
                  test.push_back("no solution");
            }
            else {
                  test.push_back(to_string(*min_element(output.begin(), output.end())));
            }

            output.clear();

      }

      for (auto i = test.begin(); i != test.end(); ++i) 
            cout << *i << endl; 
      
      test.clear();
      return 0;
}

bool doCase(int slide, int flag, int level) {

      if (badSlide(slide, flag) || level > limite) {           // teste de rejeição
            return false;
      }

      if (checkDuplicates(queueMatrix.top()) == 2) {
            output.push_back(level);
            limite = level;
            return false;                       // base case
      }

      for(int i = 1; i <= 4; i++) {
            if (doCase(i, flag, level + 1)) {
                  return true;
            }
            else {
                  queueMatrix.pop();
            }
      }

      return false;
}

vector< vector<int> > inputMatrix(int size)
{
      int aux;
      vector< vector<int> > matriz;

      for (int i = 0; i < size; i++) { 

        vector<int> row; 
  
        for (int j = 0; j < size; j++) { 
            cin >> aux;
            row.push_back(aux); 
        } 

        matriz.push_back(row); 
    }

    return matriz;
}

bool badSlide(int slide, int flag) {

      vector< vector<int> > matrizAux;

      if (slide == 0) {
            return false;
      }

      // 1º fazer o slide
      matrizAux = checkSlide(queueMatrix.top(), flag, slide);

      // 2º verificar se teve movimentos

      if (matrizAux == queueMatrix.top()) {
            queueMatrix.push(matrizAux);
            return true;
      }

      /*// 3º verificar se a matriz só tem zeros
      if (checkDuplicates(queueMatrix.top()) == -1 || checkDuplicates(queueMatrix.top()) == 3) {
            queueMatrix.push(matrizAux);
            return true;
      }*/
      
      queueMatrix.push(matrizAux);
      return false;
}

int checkDuplicates(vector< vector<int> > matriz)
{
      int num = matriz.size();
      set<int> table;

      for (int i = 0; i < num; i++)
      {
            for (int j = 0; j < num; j++)
            {
                  if (matriz[i][j] != 0)
                  {
                        if (table.find(matriz[i][j]) != table.end())
                        {
                              table.clear();
                              return -1; // HAS DUPLICATES
                        }
                        table.insert(matriz[i][j]);
                  }
            }
      }

      if (table.size() == 0) // ALL ZEROS
      {
            table.clear();
            return 3;
      }

      if (table.size() == 1) // WIN
      {
            table.clear();
            return 2;
      }

      table.clear();
      return 1;
}

vector< vector<int> > checkSlide(vector< vector<int> > matriz, int flag, int slide)
{
      if (slide == 1)
      {
            matriz = slide_right(matriz, flag);
      }

      else if (slide == 2)
      {
            matriz = slide_left(matriz, flag);
      }

      else
      {
            matriz = doTranspose(matriz);

            if (slide == 3)
            {
                  matriz = slide_left(matriz, flag);
            }

            else if (slide == 4)
            {
                  matriz = slide_right(matriz, flag);
            }

            matriz = doTranspose(matriz);
      }

      return matriz;
}

vector< vector<int> > doTranspose(vector< vector<int> > matriz)
{
      int aux;
      int num = matriz.size();

      for (int i = 0; i < num; ++i)
      {
            for (int j = i; j < num; ++j)
            {
                  aux = matriz[j][i];
                  matriz[j][i] = matriz[i][j];
                  matriz[i][j] = aux;
            }
      }

      return matriz;
}


vector<vector<int> > slide_left(vector< vector<int> > matriz, int flag)
{
      int num = matriz.size();

      for (int j = 0; j < num; j++)
      {
            for (int i = 0; i < num - 1; i++)
            {
                  if (matriz[j][i] == 0)
                  {
                        matriz[j] = push_line_left(matriz[j], i);
                        if (matriz[j][i + 1] != 0)
                        {
                              --i;
                        }
                  }
                  else if (matriz[j][i + 1] == 0)
                  {
                        matriz[j] = push_line_left(matriz[j], i + 1);
                        if (matriz[j][i + 1] != 0)
                        {
                              --i;
                        }
                  }
                  else
                  {
                        if (matriz[j][i] == matriz[j][i + 1] && flag == 0)
                        {
                              matriz[j][i + 1] = 0;
                              matriz[j][i] *= 2;
                              flag = 1;
                              i--;
                        }
                        else
                        {
                              flag = 0;
                        }
                  }
            }
            flag = 0;
      }

      return matriz;
}


vector<vector<int> > slide_right(vector<vector<int> > matriz, int flag)
{
      int num = matriz.size();

      for (int j = 0; j < num; j++)
      {
            for (int i = num - 1; i > 0; i--)
            {
                  if (matriz[j][i] == 0)
                  {
                        matriz[j] = push_line_right(matriz[j], i);
                        if (matriz[j][i - 1] != 0)
                        {
                              ++i;
                        }

                  }
                  else if (matriz[j][i - 1] == 0)
                  {
                        matriz[j] = push_line_right(matriz[j], i - 1);
                        if (matriz[j][i - 1] != 0)
                        {
                              ++i;
                        }
                  }
                  else
                  {
                        if (matriz[j][i] == matriz[j][i - 1] && flag == 0)
                        {
                              matriz[j][i - 1] = 0;
                              matriz[j][i] *= 2;
                              flag = 1;
                              ++i;
                        }
                        else
                        {
                              flag = 0;
                        }
                  }
            }
            flag = 0;
      }

      return matriz;
}

vector<int> push_line_left(vector<int> line, int index)
{
      int num = line.size();

      for (int j = index; j < num; j++)
      {
            for (int i = j + 1; i < num; i++)
            {
                  if (line[i] != 0)
                  {
                        line[j] = line[i];
                        line[i] = 0;
                        break;
                  }
            }
      }

      return line;
}

vector<int> push_line_right(vector<int> line, int index)
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

      return line;
}

void print_line(vector<int> line)
{
      int num = line.size();

      cout << "........" << endl;
      for (int i = 0; i < num; i++)
      {
            cout << line[i] << " ";
      }

      cout << endl;
}

void printMatrix(vector< vector<int> > matriz)
{
      int num = matriz.size();

      cout << "......" << endl;
      for (int j = 0; j < num; j++)
      {
            for (int k = 0; k < num; k++)
            {
                  cout << matriz[j][k] << " ";
            }
            cout << endl;
      }
}