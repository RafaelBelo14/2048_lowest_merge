#include <iostream>
#include <set>
using namespace std;

struct Node { 
      char slide;
      int numZeros;
      int level;
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

void inputMatrix(int ** matriz, int size);
void doTranspose(int ** matriz, int size);
void slide_left(int ** matriz, int size, int flag);
void push_line_left(int line[], int index, int size);
void slide_right(int ** matriz, int size, int flag);
void push_line_right(int line[], int index, int size);
void print_line(int line[], int size);
void print_tree(node * n, int nivel);
void printMatrix(int ** matrix, int size);

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

            nodeAux = insertNode('M', 0, NULL, NULL);
            nodeAux = buildTree(nodeAux, moves + 1, nodeAux->level, 0);
            //print_tree(nodeAux, size);

            int ** matriz = (int **)malloc(size * sizeof(int *));
            for (i = 0; i < size; ++i) {
                  matriz[i] = (int *)malloc(size * sizeof(int *));
            }
                  

            for (int j = 0; j < size; j++)
            {
                  for (int k = 0; k < size; k++)
                  {
                        cin >> matriz[j][k];
                  }
            }

            //printMatrix(matriz, size);

            while (nodeAux->nodeSon != NULL)
            {

                  if (nodeAux->nodeSon->slide == 'R')
                  {
                        slide_right(matriz, size, flag);
                  }

                  else if (nodeAux->nodeSon->slide == 'L')
                  {
                        slide_left(matriz, size, flag);
                  }

                  else
                  {
                        doTranspose(matriz, size);

                        if (nodeAux->nodeSon->slide == 'U')
                        {
                              slide_left(matriz, size, flag);
                        }

                        else{
                              slide_right(matriz, size, flag);
                        }

                        doTranspose(matriz, size);
                  }

                  nodeAux = nodeAux->nodeSon;
            }

            cout << "======= FINAL =========" << endl;

            printMatrix(matriz, size);
      }

      return 0;
}

void inputMatrix(int ** matriz, int size) {
      for (int j = 0; j < size; j++)
      {
            for (int k = 0; k < size; k++)
            {
                  cin >> matriz[j][k];
            }
      }
}

void doTranspose(int ** matriz, int size) {
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
}

void slide_left(int ** matriz, int size, int flag)
{
      for (int j = 0; j < size; j++) {
            for (int i = 0; i < size - 1; i++)
            {
                  if (matriz[j][i] == 0) {
                        push_line_left(matriz[j], i, size);
                        if (matriz[j][i + 1] != 0) {
                              print_line(matriz[j], size);
                              --i;
                        }
                  }
                  else if (matriz[j][i + 1] == 0)
                  {
                        push_line_left(matriz[j], i + 1, size);
                        if (matriz[j][i + 1] != 0) {
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
      
}

void slide_right(int ** matriz, int size, int flag) 
{
      for (int j = 0; j < size; j++) {
            for (int i = size - 1; i > 0; i--)
            {
                  if (matriz[j][i] == 0) {
                        push_line_right(matriz[j], i, size);
                        if (matriz[j][i - 1] != 0) {
                              ++i;
                        }
                  }
                  else if (matriz[j][i - 1] == 0)
                  {
                        push_line_right(matriz[j], i - 1, size);
                        if (matriz[j][i - 1] != 0) {
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

      print_tree(n->nodeSon, nivel+1);
      print_tree(n->nodeBrother, nivel);

      free(n);
 }

 void printMatrix(int ** matriz, int size) {
      for (int j = 0; j < size; j++)
      {
            for (int k = 0; k < size; k++)
            {
                  cout << matriz[j][k] << " ";
            }
            cout << endl;
      } 
 }