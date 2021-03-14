#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <stack> 
#include <chrono>
using namespace std;

vector< vector<int> > inputMatrix(int size);

int bestWay(vector< vector<int> > matriz);
vector<int> performTest(vector< vector<int> > matriz, int firstSlide);
int checkScore(vector< vector<int> > matriz);

vector< vector<int> > slide_left(vector< vector<int> > matriz);
vector<int> push_line_left(vector<int> line, int index);

vector< vector<int> > slide_right(vector< vector<int> > matriz);
vector<int> push_line_right(vector<int>, int index);

vector<vector<int> > slide_down(vector<vector<int> > matriz);
vector<vector<int> > push_line_down(vector<vector<int> > matriz, int column, int index);

vector<vector<int> > slide_up(vector<vector<int> > matriz);
vector<vector<int> > push_line_up(vector<vector<int> > matriz, int column, int index);

void printMatrix(vector< vector<int> > matriz);

int main() {

      int size, move, best;

      vector< vector<int> > matriz;
      cin >> size;

      matriz = inputMatrix(size);

      while(true)
      {
            best = bestWay(matriz);
            cout << "Pc move: " << best << endl;

            cin >> move;
            if (move == 1) {
                  matriz = slide_right(matriz);
            }
            if (move == 2) {
                  matriz = slide_up(matriz);
            }
            if (move == 3) {
                  matriz = slide_left(matriz);
            }
            if (move == 4) {
                  matriz = slide_down(matriz);
            }

            printMatrix(matriz);
      }
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

int bestWay(vector< vector<int> > matriz) {           // Monte-Carlo Algorithm

      vector<int> bestMoveCombination(4);
      int bestScore = 0;

      vector<int> moveCombination;
      int scoreAux;

      vector<vector<int> > matrizAux = matriz;

      // L
      for (int i = 0; i < 4; i++) {
            moveCombination = performTest(matrizAux, 3);

            if (moveCombination[moveCombination.size() - 1] != 1) {
                  if (bestScore < moveCombination[moveCombination.size() - 1]) {
                        bestScore = moveCombination[moveCombination.size() - 1];
                        auto start = moveCombination.begin(); 
                        auto end = moveCombination.begin() + 4;
                        copy(start, end, bestMoveCombination.begin()); 
                  }
            }
            
      }

      // R
      for (int i = 0; i < 4; i++) {
            moveCombination = performTest(matrizAux, 1);
            if (moveCombination[moveCombination.size() - 1] != 1) {
                  if (bestScore < moveCombination[moveCombination.size() - 1]) {
                        bestScore = moveCombination[moveCombination.size() - 1];
                        auto start = moveCombination.begin(); 
                        auto end = moveCombination.begin() + 4;
                        copy(start, end, bestMoveCombination.begin()); 
                  }
            }
      }

      // U
      for (int i = 0; i < 4; i++) {
            moveCombination = performTest(matrizAux, 2);
            if (moveCombination[moveCombination.size() - 1] != 1) {
                  if (bestScore < moveCombination[moveCombination.size() - 1]) {
                        bestScore = moveCombination[moveCombination.size() - 1];
                        auto start = moveCombination.begin(); 
                        auto end = moveCombination.begin() + 4;
                        copy(start, end, bestMoveCombination.begin()); 
                  }
            }
      }

      // D
      for (int i = 0; i < 4; i++) {
            moveCombination = performTest(matrizAux, 4);
            if (moveCombination[moveCombination.size() - 1] != 1) {
                  if (bestScore < moveCombination[moveCombination.size() - 1]) {
                        bestScore = moveCombination[moveCombination.size() - 1];
                        auto start = moveCombination.begin(); 
                        auto end = moveCombination.begin() + 4;
                        copy(start, end, bestMoveCombination.begin()); 
                  }
            }
      }
      
      cout << "BestScore: " << bestScore << endl;
      for (auto i = bestMoveCombination.begin(); i != bestMoveCombination.end(); ++i) 
            cout << *i << " -> "; 

      cout << endl;

      return bestMoveCombination[0];
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
      }


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

      for (auto i = moveCombination.begin(); i != moveCombination.end(); ++i) 
            cout << *i << " -> "; 

      cout << endl;

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