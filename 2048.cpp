#include <iostream>
#include <set>
using namespace std;

struct Node { 
      char slide;
      int numZeros;
      int level;
      //int size;
      //int matriz[size][size];
      Node *nodeFather; 
      Node *nodeBrother; 
      Node *nodeSon;
}; 

typedef struct Node node;

node * insertNode(char slide, int level, node * nodeFather, node * nodeSon)
{
      node * auxNode = (node *)malloc(sizeof(node));
      auxNode->slide = slide;
      auxNode->level = level;
      auxNode->nodeFather = nodeFather;
      auxNode->nodeSon = nodeSon;
      auxNode->nodeBrother = NULL;

      return auxNode;
}

node * buildTree(node * raiz, int level, int nodeLevel, int brotherCount) { 

      node * auxNode;

      if (nodeLevel == level) {
            //cout << "Acabei aqui!" << endl;
            return auxNode;
      }

      if (raiz->nodeSon == NULL && raiz->level + 1 != level) {
            auxNode = insertNode('L', raiz->level + 1, raiz, NULL);
            raiz->nodeSon = buildTree(auxNode, level, auxNode->level, 0);
      }

      if (raiz->nodeFather != NULL) {
            auxNode = insertNode('R', raiz->level, NULL, NULL);
            raiz->nodeBrother = buildTree(auxNode, level, auxNode->level, 1);
            brotherCount = 0;
      }

      else if (raiz->nodeFather == NULL && brotherCount != 3 && raiz->level != 0) {
            if (raiz->slide == 'L') {
                  auxNode = insertNode('R', raiz->level, NULL, NULL);
            }
            else if (raiz->slide == 'R') {
                  auxNode = insertNode('U', raiz->level, NULL, NULL);
            }
            if (raiz->slide == 'U') {
                  auxNode = insertNode('D', raiz->level, NULL, NULL);
            }

            raiz->nodeBrother = buildTree(auxNode, level, auxNode->level, ++brotherCount);
      }

      return raiz;
} 

void slide_left(int line[], int size, int flag);
void push_line_left(int line[], int index, int size);

void slide_right(int line[], int size, int flag);
void push_line_right(int line[], int index, int size);

void print_line(int line[], int size);
void print_tree(node * n, int nivel);

int main()
{
      int reps, size, moves, aux;
      int flag = 0;
      node * nodeAux;
      string move;
      cin >> reps;

      for (int i = 0; i < reps; i++)
      {
            cin >> size;
            cin >> moves;
            int matriz[size][size];
            nodeAux = insertNode('M', 0, NULL, NULL);
            nodeAux = buildTree(nodeAux, size, nodeAux->level, 0);
            print_tree(nodeAux, size);

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

void print_tree(node * n, int nivel) {
      if(n==NULL) return;
      for(int i = 0; i < nivel; ++i) {
            cout << "..";
      }
      cout << n->slide << endl;

      //imprime filhos primeiro
      print_tree(n->nodeSon, nivel+1);
      //imprime irmaos
      print_tree(n->nodeBrother, nivel);
 }