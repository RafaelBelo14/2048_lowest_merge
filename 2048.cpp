#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

int limite;

struct Node
{
      char slide;
      int numZeros;
      int level;
      int **matriz;
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

node *buildTree(node *raiz, int level, int nodeLevel, int brotherCount)
{

      node *auxNode;

      if (nodeLevel == level)
      {
            return auxNode;
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

void inputMatrix(int **matriz, int size);
void doTranspose(int **matriz, int size);
int checkDuplicates(int **matriz, int size);
bool slide_left(int **matriz, int size, int flag, bool moveOcurred);
bool slide_right(int **matriz, int size, int flag, bool moveOcurred);
bool push_line_left(int line[], int index, int size);
bool push_line_right(int line[], int index, int size);
void print_line(int line[], int size);
void print_tree(node *n, int nivel);
void printMatrix(int **matrix, int size);
bool checkSlide(int **matriz, int size, int flag, node *nodeAux, bool moveOcurred);
void searchSolution(int size, int flag, node *nodeAux);

int main()
{
      int reps, size;
      int flag = 0;
      int duplicates;
      node *nodeAux;
      string move;
      cin >> reps;

      for (int i = 0; i < reps; i++)
      {
            cin >> size;
            cin >> limite;

            nodeAux = insertNode('M', 0, NULL, NULL);
            nodeAux = buildTree(nodeAux, limite + 1, nodeAux->level, 0);

            int **matriz = (int **)malloc(size * sizeof(int *));
            for (i = 0; i < size; ++i)
            {
                  matriz[i] = (int *)malloc(size * sizeof(int *));
            }

            inputMatrix(matriz, size);
            //print_tree(nodeAux, limite);

            // TODO: VERIFICAR ZEROS E REPETIDOS
            nodeAux->matriz = matriz;
            duplicates = checkDuplicates(nodeAux->matriz, size);

            if (duplicates == 1)
            {
                  cout << "Não há elementos iguais ou é tudo zeros!" << endl;
                  return 0;
            }
            else if (duplicates == 2)
            {
                  cout << "Ganhou!" << endl;
                  limite = nodeAux->nodeSon->level;
                  return 0;
            }

            searchSolution(size, flag, nodeAux);

            //printMatrix(matriz, size);

            cout << "======= FINAL =========" << endl;

            printMatrix(matriz, size);
      }

      return 0;
}

void inputMatrix(int **matriz, int size)
{
      for (int j = 0; j < size; j++)
      {
            for (int k = 0; k < size; k++)
            {
                  cin >> matriz[j][k];
            }
      }
}

void doTranspose(int **matriz, int size)
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
}

int checkDuplicates(int **matriz, int size)
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

bool slide_left(int **matriz, int size, int flag, bool moveOcurred)
{
      bool changes;

      for (int j = 0; j < size; j++)
      {
            for (int i = 0; i < size - 1; i++)
            {
                  if (matriz[j][i] == 0)
                  {
                        changes = push_line_left(matriz[j], i, size);
                        if (matriz[j][i + 1] != 0)
                        {
                              --i;
                        }

                        if (moveOcurred == false && changes == true)
                        {
                              moveOcurred = true;
                        }
                  }
                  else if (matriz[j][i + 1] == 0)
                  {
                        changes = push_line_left(matriz[j], i + 1, size);
                        if (matriz[j][i + 1] != 0)
                        {
                              --i;
                        }

                        if (moveOcurred == false && changes == true)
                        {
                              moveOcurred = true;
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
                              moveOcurred = true;
                        }
                        else
                        {
                              flag = 0;
                        }
                  }
            }
            flag = 0;
      }

      return moveOcurred;
}

bool slide_right(int **matriz, int size, int flag, bool moveOcurred)
{
      bool changes;

      for (int j = 0; j < size; j++)
      {
            for (int i = size - 1; i > 0; i--)
            {
                  if (matriz[j][i] == 0)
                  {
                        changes = push_line_right(matriz[j], i, size);
                        if (matriz[j][i - 1] != 0)
                        {
                              ++i;
                        }

                        if (moveOcurred == false && changes == true)
                        {
                              moveOcurred = true;
                        }
                  }
                  else if (matriz[j][i - 1] == 0)
                  {
                        changes = push_line_right(matriz[j], i - 1, size);
                        if (matriz[j][i - 1] != 0)
                        {
                              ++i;
                        }

                        if (moveOcurred == false && changes == true)
                        {
                              moveOcurred = true;
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
                              moveOcurred = true;
                        }
                        else
                        {
                              flag = 0;
                        }
                  }
            }
            flag = 0;
      }

      return moveOcurred;
}

bool push_line_left(int line[], int index, int size)
{

      bool changes = false;

      for (int j = index; j < size; j++)
      {
            for (int i = j + 1; i < size; i++)
            {
                  if (line[i] != 0)
                  {
                        line[j] = line[i];
                        line[i] = 0;
                        changes = true;
                        break;
                  }
            }
      }

      return changes;
}

bool push_line_right(int line[], int index, int size)
{
      bool changes = false;

      for (int j = index; j > 0; j--)
      {
            for (int i = j - 1; i >= 0; i--)
            {
                  if (line[i] != 0)
                  {
                        line[j] = line[i];
                        line[i] = 0;
                        changes = true;
                        break;
                  }
            }
      }

      return changes;
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

void print_tree(node *n, int nivel)
{
      if (n == NULL)
            return;
      for (int i = 0; i < nivel; ++i)
      {
            cout << "..";
      }
      cout << n->slide << endl;

      print_tree(n->nodeSon, nivel + 1);
      print_tree(n->nodeBrother, nivel);

      free(n);
}

void printMatrix(int **matriz, int size)
{
      for (int j = 0; j < size; j++)
      {
            for (int k = 0; k < size; k++)
            {
                  cout << matriz[j][k] << " ";
            }
            cout << endl;
      }
}

bool checkSlide(int **matriz, int size, int flag, node *nodeAux, bool moveOcurred)
{

      if (nodeAux->slide == 'R')
      {
            moveOcurred = slide_right(matriz, size, flag, moveOcurred);
      }

      else if (nodeAux->slide == 'L')
      {
            moveOcurred = slide_left(matriz, size, flag, moveOcurred);
      }

      else
      {
            doTranspose(matriz, size);

            if (nodeAux->slide == 'U')
            {
                  moveOcurred = slide_left(matriz, size, flag, moveOcurred);
            }

            else
            {
                  moveOcurred = slide_right(matriz, size, flag, moveOcurred);
            }

            doTranspose(matriz, size);
      }
      return moveOcurred;
}

void searchSolution(int size, int flag, node *nodeAux)
{

      bool moveOcurred = false;
      int duplicates;

      cout << "NOVO - slide: " << nodeAux->slide << " | limite: " << nodeAux->level << endl;

      if (nodeAux->level == limite)
      {

            cout << "ÚLTIMO - slide: " << nodeAux->slide << " | limite: " << nodeAux->level << endl;

            moveOcurred = checkSlide(nodeAux->matriz, size, flag, nodeAux, moveOcurred);
            duplicates = checkDuplicates(nodeAux->matriz, size);

            if (duplicates == 2)
            {
                  // TODO: ATUALIZAR LIMITE
                  cout << "GANHEI E SOU - slide: " << nodeAux->slide << " | limite: " << nodeAux->level << endl;
                  limite = nodeAux->level;
                  return;
            }

            if (nodeAux->nodeBrother != NULL)
            {
                  cout << "TENHO IRMÃO QUE É - slide: " << nodeAux->nodeBrother->slide << " | limite: " << nodeAux->nodeBrother->level << endl;
                  searchSolution(size, flag, nodeAux->nodeBrother);
                  return;
            }
      }

      if (nodeAux->nodeSon != NULL)
      {
            cout << "TENHO FILHO QUE É - slide: " << nodeAux->nodeSon->slide << " | limite: " << nodeAux->nodeSon->level << endl;
            nodeAux->nodeSon->matriz = nodeAux->matriz;
            nodeAux->nodeSon->nodeBrother->matriz = nodeAux->matriz;
            nodeAux->nodeSon->nodeBrother->nodeBrother->matriz = nodeAux->matriz;
            nodeAux->nodeSon->nodeBrother->nodeBrother->nodeBrother->matriz = nodeAux->matriz;

            moveOcurred = checkSlide(nodeAux->nodeSon->matriz, size, flag, nodeAux->nodeSon, moveOcurred);
            duplicates = checkDuplicates(nodeAux->nodeSon->matriz, size);
            printMatrix(nodeAux->nodeSon->matriz, size);
            printMatrix(nodeAux->nodeSon->nodeBrother->matriz, size);

            // ====================================================== VERIFICAÇÕES

            if (duplicates == 1 || !moveOcurred)
            {

                  if (nodeAux->nodeSon->nodeBrother != NULL)
                  {

                        cout << "MERDA MAS IRMÃO QUE É - slide: " << nodeAux->nodeSon->nodeBrother->slide << " | limite: " << nodeAux->nodeSon->nodeBrother->level << endl;

                        moveOcurred = checkSlide(nodeAux->nodeSon->nodeBrother->matriz, size, flag, nodeAux->nodeSon->nodeBrother, moveOcurred);
                        duplicates = checkDuplicates(nodeAux->nodeSon->nodeBrother->matriz, size);
                        printMatrix(nodeAux->nodeSon->nodeBrother->matriz, size);

                        // ====================================================== VERIFICAÇÕES

                        if (duplicates == 1 || !moveOcurred)
                        {
                              cout << "ACABEI E SOU - slide: " << nodeAux->nodeSon->nodeBrother->slide << " | limite: " << nodeAux->nodeSon->nodeBrother->level << endl;
                              //cout << "Não há elementos iguais ou é tudo zeros!" << endl;
                              return;
                        }
                        else if (duplicates == 2)
                        {
                              cout << "GANHEI E SOU - slide: " << nodeAux->nodeSon->nodeBrother->slide << " | limite: " << nodeAux->nodeSon->nodeBrother->level << endl;
                              limite = nodeAux->nodeSon->level;
                              return;
                        }

                        // =====================================================

                        searchSolution(size, flag, nodeAux->nodeSon->nodeBrother);
                  }
            }

            else if (duplicates == 2)
            {
                  cout << "GANHEI - slide: " << nodeAux->nodeSon->slide << " | limite: " << nodeAux->nodeSon->level << endl;
                  limite = nodeAux->nodeSon->level;
                  return;
            }

            else
            {
                  searchSolution(size, flag, nodeAux->nodeSon);
                  cout << "Vou sair do tenho filho - slide: " << nodeAux->slide << " | limite: " << nodeAux->level << endl;
            }
      }

      if (nodeAux->nodeBrother != NULL)
      {
            printMatrix(nodeAux->nodeBrother->matriz, size);
            cout << "TENHO IRMÃO QUE É - slide: " << nodeAux->nodeBrother->slide << " | limite: " << nodeAux->nodeBrother->level << endl;

            moveOcurred = checkSlide(nodeAux->nodeBrother->matriz, size, flag, nodeAux->nodeBrother, moveOcurred);
            duplicates = checkDuplicates(nodeAux->nodeBrother->matriz, size);

            // ====================================================== VERIFICAÇÕES

            if (duplicates == 1 || !moveOcurred)
            {
                  cout << "ACABEI E SOU - slide: " << nodeAux->nodeBrother->slide << " | limite: " << nodeAux->nodeBrother->level << endl;
                  return;
            }
            else if (duplicates == 2)
            {
                  cout << "GANHEI E SOU - slide: " << nodeAux->nodeBrother->slide << " | limite: " << nodeAux->nodeBrother->level << endl;
                  limite = nodeAux->nodeBrother->level;
                  return;
            }

            // =====================================================

            searchSolution(size, flag, nodeAux->nodeBrother);
      }

      print_tree(nodeAux, limite);
}