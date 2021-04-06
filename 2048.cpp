#include <iostream>
#include <algorithm>
#include<numeric>
#include <set>
#include <vector>
#include <string> 
#include <stack> 
#include <math.h>
#include <typeinfo>
#include <chrono>
#include <type_traits>
#include <cstdint>
using namespace std;
using namespace std::chrono;

int limite;
vector<int> output;
stack<vector<vector <int> > > queueMatrix;
vector<string> test;


int doCase(int slide, int level);

vector< vector<int> > inputMatrix(int size);

bool checkWin(vector< vector<int> > matriz);
bool badSlide(int slide);

vector< vector<int> > checkSlide(vector< vector<int> > matriz, int slide);

vector< vector<int> > slide_left(vector< vector<int> > matriz);
vector< vector<int> > slide_right(vector< vector<int> > matriz);
vector<vector<int> > slide_down(vector<vector<int> > matriz);
vector<vector<int> > slide_up(vector<vector<int> > matriz);

int main()
{
      int reps, size;
      cin >> reps;

      for (int i = 0; i < reps; i++)
      {
            vector< vector<int> > matriz;
            cin >> size;
            cin >> limite;

            limite++;

            if ((size < 1 || size > 20) || (limite < 1 || limite > 50)) {
                  test.push_back("no solution");
                  matriz = inputMatrix(size);
            }

            else {
                  matriz = inputMatrix(size);

                  if (matriz.size() == 0) {
                        test.push_back("no solution");
                  }

                  else {
                        queueMatrix.push(matriz);

                        doCase(0, 0);

                        if (output.size() == 0) {
                              test.push_back("no solution");
                        }
                        else {
                              test.push_back(to_string(*min_element(output.begin(), output.end())));
                        } 

                        output.clear();
                  }
            }
      }

      for (auto i = test.begin(); i != test.end(); ++i) 
            cout << *i << endl; 
      
      test.clear();
      return 0;
}

int doCase(int slide, int level) {

      if (level >= limite) {
            return 0;
      }

      if (badSlide(slide)) {          // teste de rejeição
            return 1;
      }

      if (checkWin(queueMatrix.top())) {
            output.push_back(level);
            limite = level;
            return 1;                       // base case
      }

      for(int i = 1; i <= 4; i++) {
            if (doCase(i, level + 1) == 1) {
                  queueMatrix.pop();
            }
      }

      return 1;
}

vector< vector<int> > inputMatrix(int size)
{
      int aux;
      int sum = 0;
      vector< vector<int> > matriz;

      for (int i = 0; i < size; i++) { 

            vector<int> row; 
      
            for (int j = 0; j < size; j++) { 
                  cin >> aux;
                  row.push_back(aux); 
            } 

            matriz.push_back(row);
            sum += accumulate(matriz[i].begin(), matriz[i].end(), 0);
      }

      if (log2(sum) != floor(log2(sum))) {
            matriz.clear();
            return matriz;
      }


    return matriz;
}

bool badSlide(int slide) {

      vector <vector<int> > matrizNova;
      vector <vector<int> > matrizAtual;
      vector <vector<int> > matrizAntiga;

      if (slide == 0) {
            return false;
      }

      matrizAtual = queueMatrix.top();
      queueMatrix.pop();

      if (!queueMatrix.empty()) {
            matrizAntiga = queueMatrix.top();
            queueMatrix.pop();
            queueMatrix.push(matrizAntiga);
      }
      
      queueMatrix.push(matrizAtual);

      // 1º fazer o slide
      matrizNova = checkSlide(queueMatrix.top(), slide);

      // 2º verificar se teve movimentos

      if (matrizNova == matrizAtual || matrizNova == matrizAntiga) {
            queueMatrix.push(matrizNova);
            return true;
      }

      queueMatrix.push(matrizNova);
      return false;
}

bool checkWin(vector< vector<int> > matriz)
{
      int num = matriz.size();
      int zeros = 0;

      for (int i = 0; i < num; i++)
      {
            zeros += count(matriz[i].begin(), matriz[i].end(), 0);
      }

      if (zeros == num * num - 1) // WIN
      {
            return true;
      }

      return false;
}

vector< vector<int> > checkSlide(vector< vector<int> > matriz, int slide)
{
      if (slide == 1)
      {
            matriz = slide_right(matriz);
      }

      else if (slide == 2)
      {
            matriz = slide_left(matriz);
      }

      else if (slide == 3)
      {
            matriz = slide_up(matriz);
      }

      else if (slide == 4)
      {
            matriz = slide_down(matriz);
      }

      return matriz;
}

vector <vector<int> > slide_left(vector <vector<int> > matriz) 
{
      int tamanho = matriz.size();
      int pos_ultimo, somou, index;

      for (int i = 0; i < tamanho; i++) {

            vector<int> linha(tamanho);
            pos_ultimo = 0;
            index = 0;
            somou = 0;

            for (int j = 0; j < tamanho; j++) {

                  if (matriz[i][j] != 0) {

                        if (linha[pos_ultimo] == matriz[i][j] && somou == 0) {
                              linha[pos_ultimo] *= 2;
                              somou = 1;
                        }
                        else {
                              linha[index] = matriz[i][j];
                              index++;
                              pos_ultimo = index - 1;
                              somou = 0;
                        }
                  }
            }

            matriz[i] = linha;
      }
      return matriz;
}

vector <vector<int> > slide_right(vector <vector<int> > matriz) 
{
      int tamanho = matriz.size();
      int pos_ultimo, somou, index;

      for (int i = 0; i < tamanho; i++) {

            vector<int> linha(tamanho);
            pos_ultimo = tamanho - 1;
            index = tamanho - 1;
            somou = 0;

            for (int j = tamanho - 1; j >= 0; j--) {

                  if (matriz[i][j] != 0) {

                        if (linha[pos_ultimo] == matriz[i][j] && somou == 0) {
                              linha[pos_ultimo] *= 2;
                              somou = 1;
                        }
                        else {
                              linha[index] = matriz[i][j];
                              index--;
                              pos_ultimo = index + 1;
                              somou = 0;
                        }
                  }
            }

            matriz[i] = linha;
      }
      return matriz;
}

vector <vector<int> > slide_up(vector <vector<int> > matriz) 
{
      int tamanho = matriz.size();
      int pos_ultimo, somou, index;

      for (int j = 0; j < tamanho; j++) {

            vector<int> linha(tamanho);
            pos_ultimo = 0;
            index = 0;
            somou = 0;

            for (int i = 0; i < tamanho; i++) {

                  if (matriz[i][j] != 0) {

                        if (linha[pos_ultimo] == matriz[i][j] && somou == 0) {
                              linha[pos_ultimo] *= 2;
                              somou = 1;
                        }
                        else {
                              linha[index] = matriz[i][j];
                              index++;
                              pos_ultimo = index - 1;
                              somou = 0;
                        }
                  }
            }

            for (int i = 0; i < tamanho; i++) {
                  matriz[i][j] = linha[i];
            }
      }
      return matriz;
}

vector <vector<int> > slide_down(vector <vector<int> > matriz) 
{
      int tamanho = matriz.size();
      int pos_ultimo, somou, index;

      for (int j = 0; j < tamanho; j++) {

            vector<int> linha(tamanho);
            pos_ultimo = tamanho - 1;
            index = tamanho - 1;
            somou = 0;

            for (int i = tamanho - 1; i >= 0; i--) {

                  if (matriz[i][j] != 0) {

                        if (linha[pos_ultimo] == matriz[i][j] && somou == 0) {
                              linha[pos_ultimo] *= 2;
                              somou = 1;
                        }
                        else {
                              linha[index] = matriz[i][j];
                              index--;
                              pos_ultimo = index + 1;
                              somou = 0;
                        }
                  }
            }

            for (int i = tamanho - 1; i >= 0; i--) {
                  matriz[i][j] = linha[i];
            }
      }
      return matriz;
}
