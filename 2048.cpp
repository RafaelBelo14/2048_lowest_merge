// 1 - right
// 2 - up
// 3 - left
// 4 - down

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
vector<vector<int> > first_matrix;
stack<vector<vector <int> > > queueMatrix;
vector<string> test;

bool doCase(int slide, int level);

vector< vector<int> > inputMatrix(int size);

int checkDuplicates(vector< vector<int> > matriz);
bool badSlide(int slide);
int checkZeros(vector< vector<int> > matriz);

int bestWay(vector< vector<int> > matriz);
vector<int> performTest(vector< vector<int> > matriz, int firstSlide);
int checkScore(vector< vector<int> > matriz);

vector< vector<int> > checkSlide(vector< vector<int> > matriz, int slide);
vector< vector<int> > doTranspose(vector< vector<int> > matriz);

vector< vector<int> > slide_left(vector< vector<int> > matriz);
vector<int> push_line_left(vector<int> line, int index);

vector< vector<int> > slide_right(vector< vector<int> > matriz);
vector<int> push_line_right(vector<int>, int index);

vector<vector<int> > slide_down(vector<vector<int> > matriz);
vector<vector<int> > push_line_down(vector<vector<int> > matriz, int column, int index);

vector<vector<int> > slide_up(vector<vector<int> > matriz);
vector<vector<int> > push_line_up(vector<vector<int> > matriz, int column, int index);

void print_line(vector<int>);
void printMatrix(vector< vector<int> > matriz);

int main()
{
      int reps, size, check;
      cin >> reps;

      //auto start = high_resolution_clock::now(); 

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
                  first_matrix = matriz;

                  check = checkDuplicates(matriz);

                  if (check == 1) {
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
      
      /*auto stop = high_resolution_clock::now(); 
      auto duration = duration_cast<milliseconds>(stop - start); 
      cout << duration.count() << endl;*/
      
      test.clear();
      return 0;
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

bool doCase(int slide, int level) {

      if (badSlide(slide) || level >= limite) {             // teste de rejeição
            return false;
      }

      int check = checkDuplicates(queueMatrix.top());

      if (check == 1) {
            return false;                                   // teste de rejeição
      }

      if (check == 2) {
            output.push_back(level);
            limite = level;
            return false;                                   // base case
      }

      if (doCase(bestWay(queueMatrix.top()), level + 1)) {
            return true;
      }
      else {
            if (!queueMatrix.empty() == 0) {
                  queueMatrix.pop();
            }
      }   

      return false;
}

int bestWay(vector< vector<int> > matriz) {           // Monte-Carlo Algorithm

      int bestSlide = 0;
      int bestScore = 0;
      vector<int> moveCombination;
      vector<vector<int> > matrizAux = matriz;

      // L
      for (int i = 0; i < 4; i++) {
            moveCombination = performTest(matrizAux, 3);
            if (moveCombination[0] != -1) {
                  if (bestScore < moveCombination[moveCombination.size() - 1]) {
                        bestScore = moveCombination[moveCombination.size() - 1];
                        bestSlide = moveCombination[0];
                  }
            }
            moveCombination.clear();
      }

      // R
      for (int i = 0; i < 4; i++) {
            moveCombination = performTest(matrizAux, 1);
            if (moveCombination[0] != -1) {
                  if (bestScore < moveCombination[moveCombination.size() - 1]) {
                        bestScore = moveCombination[moveCombination.size() - 1];
                        bestSlide = moveCombination[0]; 
                  }
            }
            moveCombination.clear();
      }

      // U
      for (int i = 0; i < 4; i++) {
            moveCombination = performTest(matrizAux, 2);
            if (moveCombination[0] != -1) {
                  if (bestScore < moveCombination[moveCombination.size() - 1]) {
                        bestScore = moveCombination[moveCombination.size() - 1];
                        bestSlide = moveCombination[0];
                  }
            }
            moveCombination.clear();
      }

      // D
      for (int i = 0; i < 4; i++) {
            moveCombination = performTest(matrizAux, 4);
            if (moveCombination[0] != -1) {
                  if (bestScore < moveCombination[moveCombination.size() - 1]) {
                        bestScore = moveCombination[moveCombination.size() - 1];
                        bestSlide = moveCombination[0];
                  }
            }
            moveCombination.clear();
      }

      moveCombination.clear();
      matrizAux.clear();
      return bestSlide;
}

vector<int> performTest(vector< vector<int> > matriz, int firstSlide) {

      vector<int> moveCombination;
      int zeros = 0;
      vector<vector<int> > matrizAux = matriz;
      int randomMove;

      if(firstSlide == 1){
            matrizAux = slide_right(matrizAux);
      }
      if(firstSlide == 2){
            matrizAux = slide_up(matrizAux);
      }
      if(firstSlide == 3){
            matrizAux = slide_left(matrizAux);
      }
      if(firstSlide == 4){
            matrizAux = slide_down(matrizAux);
      }

      if (matriz == matrizAux) {
            moveCombination.push_back(-1);
            return moveCombination;
      }

      zeros += checkScore(matrizAux);
      moveCombination.push_back(firstSlide);

      for (int j = 0; j < 3; j++) {
            randomMove = rand() % 4 + 1;
            if (randomMove == 1) {
                  matrizAux = slide_right(matrizAux);
            }
            if (randomMove == 2) {
                  matrizAux = slide_up(matrizAux);
            }
            if (randomMove == 3) {
                  matrizAux = slide_left(matrizAux);
            }
            if (randomMove == 4) {
                  matrizAux = slide_down(matrizAux);
            }

            zeros += checkScore(matrizAux); 
            moveCombination.push_back(randomMove);
      } 

      moveCombination.push_back(zeros);

      matrizAux.clear();
      return moveCombination;
}

int checkScore(vector< vector<int> > matriz) {
      int num = matriz.size();
      int res = 0;

      for (int i = 0; i < num; i++)
      {
            res += count(matriz[i].begin(), matriz[i].end(), 0);
      }

      return res;
}

bool badSlide(int slide) {

      vector< vector<int> > matrizAux;

      if (slide == 0) {
            return false;
      }

      matrizAux = checkSlide(queueMatrix.top(), slide);

      if (matrizAux == queueMatrix.top()) {
            queueMatrix.push(matrizAux);
            return true;
      }
      
      queueMatrix.push(matrizAux);
      return false;
}

int checkDuplicates(vector< vector<int> > matriz)
{
      int num = matriz.size();
      int sum = 0;
      int zeros = 0;

      for (int i = 0; i < num; i++)
      {
            sum += accumulate(matriz[i].begin(), matriz[i].end(), 0);
            zeros += count(matriz[i].begin(), matriz[i].end(), 0);
      }

      if (log2(sum) != floor(log2(sum))) {
            //cout << "Se acabou" << endl;
            return 1;
      }

      if (zeros == num * num - 1) // WIN
      {
            return 2;
      }

      return -1;
}

int checkZeros(vector< vector<int> > matriz) {
      int num = matriz.size();
      int res = 0;

      for (int i = 0; i < num; i++)
      {
            res += count(matriz[i].begin(), matriz[i].end(), 0);
      }

      if (res == num * num) // WIN
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

      else if (slide == 3)
      {
            matriz = slide_left(matriz);
      }

      else if (slide == 2)
      {
            matriz = slide_up(matriz);
      }

      else if (slide == 4)
      {
            matriz = slide_down(matriz);
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


vector<vector<int> > slide_left(vector< vector<int> > matriz)
{
      int flag = 0;
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


vector<vector<int> > slide_right(vector<vector<int> > matriz)
{
      int flag = 0;
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

vector<vector<int> > slide_down(vector<vector<int> > matriz)
{
      int flag = 0;
      int num = matriz.size();

      for (int j = 0; j < num; j++)
      {
            for (int i = num - 1; i > 0; i--)
            {
                  if (matriz[i][j] == 0)
                  {
                        matriz = push_line_down(matriz, j, i);
                        if (matriz[i - 1][j] != 0)
                        {
                              ++i;
                        }

                  }
                  else if (matriz[i - 1][j] == 0)
                  {
                        matriz = push_line_down(matriz, j, i - 1);
                        if (matriz[i - 1][j] != 0)
                        {
                              ++i;
                        }
                  }
                  else
                  {
                        if (matriz[i][j] == matriz[i - 1][j] && flag == 0)
                        {
                              matriz[i - 1][j] = 0;
                              matriz[i][j] *= 2;
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

vector<vector<int> > push_line_down(vector<vector<int> > matriz, int column, int index)
{
      for (int j = index; j > 0; j--)
      {
            for (int i = j - 1; i >= 0; i--)
            {
                  if (matriz[i][column] != 0)
                  {
                        matriz[j][column] = matriz[i][column];
                        matriz[i][column] = 0;
                        break;
                  }
            }
      }

      return matriz;
}

vector<vector<int> > slide_up(vector<vector<int> > matriz)
{
      int flag = 0;
      int num = matriz.size();

      for (int j = 0; j < num; j++)
      {
            for (int i = 0; i < num - 1; i++)
            {
                  if (matriz[i][j] == 0)
                  {
                        matriz = push_line_up(matriz, j, i);
                        if (matriz[i + 1][j] != 0)
                        {
                              --i;
                        }

                  }
                  else if (matriz[i + 1][j] == 0)
                  {
                        matriz = push_line_up(matriz, j, i + 1);
                        if (matriz[i + 1][j] != 0)
                        {
                              --i;
                        }
                  }
                  else
                  {
                        if (matriz[i][j] == matriz[i + 1][j] && flag == 0)
                        {
                              matriz[i + 1][j] = 0;
                              matriz[i][j] *= 2;
                              flag = 1;
                              --i;
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

vector<vector<int> > push_line_up(vector<vector<int> > matriz, int column, int index)
{
      int num = matriz.size();

      for (int j = index; j < num; j++)
      {
            for (int i = j + 1; i < num; i++)
            {
                  if (matriz[i][column] != 0)
                  {
                        matriz[j][column] = matriz[i][column];
                        matriz[i][column] = 0;
                        break;
                  }
            }
      }

      return matriz;
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

      for (int j = 0; j < num; j++)
      {
            for (int k = 0; k < num; k++)
            {
                  if (to_string(matriz[j][k]).length() == 1) {
                        cout << matriz[j][k] << "   |   ";
                  }
                  if (to_string(matriz[j][k]).length() == 2) {
                        cout << matriz[j][k] << "  |   ";
                  }
                  if (to_string(matriz[j][k]).length() == 3) {
                        cout << matriz[j][k] << " |   ";
                  }
            }
            cout << endl;
            cout << "---- ------- ------- -------" << endl;
      }
}