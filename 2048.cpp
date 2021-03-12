#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

int limite;
vector<int> output;
stack<vector<vector<int> > > queueMatrix;
vector<string> test;

bool doCase(int slide, int level);

vector<vector<int> > inputMatrix(int size);

int checkDuplicates(vector<vector<int> > matriz);
bool badSlide(int slide);

vector<vector<int> > checkSlide(vector<vector<int> > matriz, int slide);
vector<vector<int> > doTranspose(vector<vector<int> > matriz);

vector<vector<int> > slide_left(vector<vector<int> > matriz);
vector<int> shift_left(vector <int> line);

vector<vector<int> > slide_right(vector<vector<int> > matriz);
vector<int> shift_right(vector <int> line);

void print_line(vector<int>);
void printMatrix(vector<vector<int> > matriz);

int main()
{
      int reps, size;
      cin >> reps;

      auto start = high_resolution_clock::now();

      for (int i = 0; i < reps; i++)
      {
            vector<vector<int> > matriz;
            cin >> size;
            cin >> limite;

            matriz = inputMatrix(size);
            queueMatrix.push(matriz);

            doCase(0, 0);

            if (output.size() == 0)
            {
                  test.push_back("no solution");
            }
            else
            {
                  test.push_back(to_string(*min_element(output.begin(), output.end())));
            }

            output.clear();
      }

      for (auto i = test.begin(); i != test.end(); ++i)
            cout << *i << endl;

      test.clear();

      auto stop = high_resolution_clock::now();
      auto duration = duration_cast<milliseconds>(stop - start);
      cout << duration.count() << endl;

      return 0;
}

bool doCase(int slide, int level)
{

      if (badSlide(slide) || level > limite)
      { // teste de rejeição
            return false;
      }

      if (checkDuplicates(queueMatrix.top()) == 2)
      {
            output.push_back(level);
            limite = level;
            return false; // base case
      }

      for (int i = 1; i <= 4; i++)
      {
            if (doCase(i, level + 1))
            {
                  return true;
            }
            else
            {
                  queueMatrix.pop();
            }
      }

      return false;
}

vector<vector<int> > inputMatrix(int size)
{
      int aux;
      vector<vector<int> > matriz;

      for (int i = 0; i < size; i++)
      {

            vector<int> row;

            for (int j = 0; j < size; j++)
            {
                  cin >> aux;
                  row.push_back(aux);
            }

            matriz.push_back(row);
      }

      return matriz;
}

bool badSlide(int slide) {

      vector< vector<int> > matrizAux;

      if (slide == 0) {
            return false;
      }

      // 1º fazer o slide
      matrizAux = checkSlide(queueMatrix.top(), slide);

      // 2º verificar se teve movimentos

      if (matrizAux == queueMatrix.top()) {
            queueMatrix.push(matrizAux);
            return true;
      }
      
      queueMatrix.push(matrizAux);
      return false;
}

int checkDuplicates(vector<vector<int> > matriz)
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

vector<vector<int> > checkSlide(vector<vector<int> > matriz, int slide)
{
      if (slide == 1)
      {
            matriz = slide_right(matriz);
      }

      else if (slide == 2)
      {
            matriz = slide_left(matriz);
      }

      else
      {
            matriz = doTranspose(matriz);

            if (slide == 3)
            {
                  matriz = slide_left(matriz);
            }

            else if (slide == 4)
            {
                  matriz = slide_right(matriz);
            }

            matriz = doTranspose(matriz);
      }

      return matriz;
}

vector<vector<int> > doTranspose(vector<vector<int> > matriz)
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

vector<vector<int> > slide_right(vector<vector<int> > matriz)
{
      int num = matriz.size();

      for (int i = 0; i < num; i++) {

            matriz[i] = shift_right(matriz[i]);

            for (int x = 0; x > 0; x--) {
                  if ((x - 1 >= 0) && ((matriz[i][x] + matriz[i][x - 1]) > 0))
                  {
                        if (matriz[i][x] == matriz[i][x - 1])
                        {
                              matriz[i][x] *= 2;
                              matriz[i][x - 1] = 0;
                        }
                  }
            } 

            matriz[i] = shift_right(matriz[i]);
      }

      return matriz;
}

vector<int> shift_right(vector <int> line) {

      int num = line.size();
      int marker = num - 1;
      vector<int> temp(num, 0);

      for(int x = num - 1; x >= 0; x--) {
            if(line[x] > 0){
                  temp[marker] = line[x];
                  marker--;
            }
      }

      return temp;
}

vector<vector<int> > slide_left(vector<vector<int> > matriz)
{
      int num = matriz.size();

      for (int i = 0; i < num; i++) {

            matriz[i] = shift_left(matriz[i]);

            for (int x = 0; x < num; x++) {
                  if ((x < num - 1) && ((matriz[i][x] + matriz[i][x + 1]) > 0))
                  {
                        if (matriz[i][x] == matriz[i][x + 1])
                        {
                              matriz[i][x] *= 2;
                              matriz[i][x + 1] = 0;
                        }
                  }
            }  

            matriz[i] = shift_left(matriz[i]);
      }

      return matriz;
}

vector<int> shift_left(vector <int> line) {

      int num = line.size();
      int marker = 0;
      vector<int> temp(num, 0);

            for(int x = 0; x < num; x++) {
			if(line[x] > 0){
				temp[marker] = line[x];
				marker++;
			}
            }

      return temp;
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

void printMatrix(vector<vector<int> > matriz)
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