#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int limite;
vector<int> output;
vector<string> teste;

struct Node
{
      char slide;
      int numZeros;
      int level;
      vector<vector<int> > matriz;
      Node *nodeFather;
      Node *nodeBrother;
      Node *nodeSon;
};

typedef struct Node node;

node *insertNode(char slide, int level, node *nodeFather, node *nodeSon)
{
      node *auxNode = (node *)malloc(sizeof(node));
      auxNode->slide = slide;
      auxNode->level = level;
      auxNode->nodeFather = nodeFather;
      auxNode->nodeSon = nodeSon;
      auxNode->nodeBrother = NULL;

      return auxNode;
}

node * buildTree(node *raiz, int level, int nodeLevel, int brotherCount)
{

      node * auxNode = NULL;

      if (nodeLevel == level)
      {
            return raiz;
      }

      if (raiz->nodeSon == NULL && raiz->level + 1 != level)
      {
            auxNode = insertNode('L', raiz->level + 1, raiz, NULL);
            raiz->nodeSon = buildTree(auxNode, level, auxNode->level, 0);
      }

      if (raiz->nodeFather != NULL)
      {
            auxNode = insertNode('R', raiz->level, NULL, NULL);
            raiz->nodeBrother = buildTree(auxNode, level, auxNode->level, 1);
            brotherCount = 0;
      }

      else if (raiz->nodeFather == NULL && brotherCount != 3 && raiz->level != 0)
      {
            if (raiz->slide == 'L')
            {
                  auxNode = insertNode('R', raiz->level, NULL, NULL);
            }
            else if (raiz->slide == 'R')
            {
                  auxNode = insertNode('U', raiz->level, NULL, NULL);
            }
            if (raiz->slide == 'U')
            {
                  auxNode = insertNode('D', raiz->level, NULL, NULL);
            }

            raiz->nodeBrother = buildTree(auxNode, level, auxNode->level, ++brotherCount);
      }

      return raiz;
}

void doCases(int size);
vector< vector<int> > inputMatrix(int size);
vector< vector<int> > doTranspose(vector< vector<int> > matriz, int size);
int checkDuplicates(vector< vector<int> > matriz, int size);
vector< vector<int> > slide_left(vector< vector<int> > matriz, int size, int flag);
vector< vector<int> > slide_right(vector< vector<int> > matriz, int size, int flag);
vector<int> push_line_left(vector<int> line, int index, int size);
vector<int> push_line_right(vector<int>, int index);
void print_line(vector<int>, int size);
void print_tree(node *n, int nivel);
void printMatrix(vector< vector<int> > matriz, int size);
vector< vector<int> > checkSlide(vector< vector<int> > matriz, int size, int flag, node *nodeAux);
void searchSolution(int size, int flag, node *nodeAux);
void free_tree(node *n, int nivel);

int main()
{
      int reps, size;

      cin >> reps;

      for (int i = 0; i < reps; i++)
      {
            cin >> size;
            cin >> limite;

            doCases(size);

      }

      for (auto i = teste.begin(); i != teste.end(); ++i) 
            cout << *i << endl; 
      
      teste.clear();
      return 0;
}

void doCases(int size) {

      node * nodeAux = NULL;
      int flag = 0;
      int duplicates;

      nodeAux = insertNode('M', 0, NULL, NULL);
      nodeAux = buildTree(nodeAux, limite + 1, nodeAux->level, 0);

      nodeAux->matriz = inputMatrix(size);

      duplicates = checkDuplicates(nodeAux->matriz, size);

      if (duplicates == 1)
      {
            teste.push_back("no solution");
      }
      else if (duplicates == 2)
      {
            teste.push_back(0);
      }
      else {
            searchSolution(size, flag, nodeAux);

            if (output.size() == 0) {
            teste.push_back("no solution");
            }
            else {
                  teste.push_back(to_string(*min_element(output.begin(), output.end())));
            }
      }

      output.clear();
      free_tree(nodeAux, limite);
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


vector< vector<int> > doTranspose(vector< vector<int> > matriz, int size)
{
      int aux;

      for (int i = 0; i < size; ++i)
      {
            for (int j = i; j < size; ++j)
            {
                  aux = matriz[j][i];
                  matriz[j][i] = matriz[i][j];
                  matriz[i][j] = aux;
            }
      }

      return matriz;
}

int checkDuplicates(vector< vector<int> > matriz, int size)
{

      set<int> table;

      for (int i = 0; i < size; ++i)
      {
            for (int j = 0; j < size; ++j)
            {
                  if (matriz[i][j] != 0)
                  {
                        if (table.find(matriz[i][j]) != table.end())
                        {
                              table.clear();
                              return -1;
                        }
                        table.insert(matriz[i][j]);
                  }
            }
      }

      if (table.size() == 1)
      {
            table.clear();
            return 2;
      }

      table.clear();
      return 1;
}


vector<vector<int> > slide_left(vector< vector<int> > matriz, int size, int flag)
{

      for (int j = 0; j < size; j++)
      {
            for (int i = 0; i < size - 1; i++)
            {
                  if (matriz[j][i] == 0)
                  {
                        matriz[j] = push_line_left(matriz[j], i, size);
                        if (matriz[j][i + 1] != 0)
                        {
                              --i;
                        }
                  }
                  else if (matriz[j][i + 1] == 0)
                  {
                        matriz[j] = push_line_left(matriz[j], i + 1, size);
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


vector<vector<int> > slide_right(vector<vector<int> > matriz, int size, int flag)
{

      for (int j = 0; j < size; j++)
      {
            for (int i = size - 1; i > 0; i--)
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

vector<int> push_line_left(vector<int> line, int index, int size)
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

void print_line(vector<int> line, int size)
{
      cout << "........" << endl;
      for (int i = 0; i < size; i++)
      {
            cout << line[i] << " ";
      }

      cout << endl;
}

void print_tree(node * n, int nivel)
{
      if (n == NULL)
            return;

      for (int i = 0; i < nivel; ++i)
      {
            cout << "..";
      }
      cout << n->slide << endl;

      if (n->nodeSon != NULL) {
            print_tree(n->nodeSon, nivel + 1);
      }

      if (n->nodeBrother != NULL) {
            print_tree(n->nodeBrother, nivel);
      }

}

void free_tree(node * n, int nivel)
{
      if (n == NULL)
            return;

      if (n->nodeSon != NULL) {
            free_tree(n->nodeSon, nivel + 1);
      }

      if (n->nodeBrother != NULL) {
            free_tree(n->nodeBrother, nivel);
      }

      //cout << "Im free slide: " << n->slide << " | level: " << n->level << endl;
      free(n);
}

void printMatrix(vector< vector<int> > matriz, int size)
{
      cout << "......" << endl;
      for (int j = 0; j < size; j++)
      {
            for (int k = 0; k < size; k++)
            {
                  cout << matriz[j][k] << " ";
            }
            cout << endl;
      }
}

vector< vector<int> > checkSlide(vector< vector<int> > matriz, int size, int flag, node *nodeAux)
{

      if (nodeAux->slide == 'R')
      {
            matriz = slide_right(matriz, size, flag);
      }

      else if (nodeAux->slide == 'L')
      {
            matriz = slide_left(matriz, size, flag);
      }

      else
      {
            matriz = doTranspose(matriz, size);

            if (nodeAux->slide == 'U')
            {
                  matriz = slide_left(matriz, size, flag);
            }

            else if (nodeAux->slide == 'D')
            {
                  matriz = slide_right(matriz, size, flag);
            }

            matriz = doTranspose(matriz, size);
      }
      return matriz;
}

void searchSolution(int size, int flag, node * nodeAux) {

      int duplicates = 0;

      nodeAux->matriz = checkSlide(nodeAux->matriz, size, flag, nodeAux);
      duplicates = checkDuplicates(nodeAux->matriz, size);

      if (duplicates == 2)
      {
            output.push_back(nodeAux->level);
            limite = nodeAux->level;
            //cout << "Win" << endl;
            return;
      }

      if (nodeAux->level == limite) {
            //cout << "Ultimo" << endl;

            if (nodeAux->nodeBrother != NULL)
            {
                  searchSolution(size, flag, nodeAux->nodeBrother);
            }
            
            return;
      }

      if (nodeAux->nodeSon != NULL) {
            //cout << "Filho" << endl;
            nodeAux->nodeSon->matriz = nodeAux->matriz;
            nodeAux->nodeSon->nodeBrother->matriz = nodeAux->matriz;
            nodeAux->nodeSon->nodeBrother->nodeBrother->matriz = nodeAux->matriz;
            nodeAux->nodeSon->nodeBrother->nodeBrother->nodeBrother->matriz = nodeAux->matriz;
            searchSolution(size, flag, nodeAux->nodeSon);
      }

      if (nodeAux->nodeBrother != NULL) {
            //cout << "Irmão" << endl;
            searchSolution(size, flag, nodeAux->nodeBrother);
      }


}