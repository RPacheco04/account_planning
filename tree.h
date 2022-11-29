#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct tree {
  char *id;
  char *name;
  double value;
  int child_count;
  struct tree** childs;
} Tree;

/**
 * @brief Creates a new tree node
 * @return Tree* 
 */
Tree* _createEmptyTree() {
  Tree* tree = (Tree*) malloc(sizeof(Tree));
  tree->id = "0";
  tree->name = "Plano de contas";
  tree->value = 0;
  tree->child_count = 2;
  tree->childs = (Tree**) malloc(sizeof(Tree*) * 2);
  tree->childs[0] = (Tree*) malloc(sizeof(Tree));
  tree->childs[0]->id = "1";
  tree->childs[0]->name = "Receitas";
  tree->childs[0]->value = 0;
  tree->childs[0]->childs = NULL;
  tree->childs[0]->child_count = 0;
  tree->childs[1] = (Tree*) malloc(sizeof(Tree));
  tree->childs[1]->id = "2";
  tree->childs[1]->name = "Despesas";
  tree->childs[1]->value = 0;
  tree->childs[1]->childs = NULL;
  tree->childs[1]->child_count = 0;
  return tree;
}

void _deleteTree(Tree* tree) {
  for (int i = 0; i < tree->child_count; i++) {
    _deleteTree(tree->childs[i]);
  }
  free(tree);
}


double _calculateValue(Tree* tree) {
  double value = tree->value;
  for (int i = 0; i < tree->child_count; i++) {
    value += _calculateValue(tree->childs[i]);
  }
  return value;
}

/**
 * @brief Calculate the balance of the billings. Get the tree child of id 1 and subtract the tree child of id 2
 * @param tree 
 * @return double 
 */
double _calculateBalance(Tree* tree) {
  double balance = 0;
  for (int i = 0; i < tree->child_count; i++) {
    if (strcmp(tree->childs[i]->id, "1") == 0) 
      balance += _calculateValue(tree->childs[i]);
    else if (strcmp(tree->childs[i]->id, "2") == 0)
      balance -= _calculateValue(tree->childs[i]);
    
  }
  return balance;
}

void _showTree(Tree* t, int ident) {
  if (strcmp(t->id, "0") != 0) { // don't show root
    for (int i = 0; i < ident; i++) {
      printf("    ");
    };
    double value = _calculateValue(t);
    printf("%s. %s: R$%.2f \n\n", t->id, t->name, value);
  }
  for (int i = 0; i < t->child_count; i++) {
    _showTree(t->childs[i], ident+1);
  }
}

/**
 * @brief Receive the current tree object and the new tree object. 
 * Insert the new tree object in the current tree object as child of the node with the id passed as parameter
 * The received newTree has the id of the father.
 * The id of the newTree is setted with a concatenation of the id of the father and the next available index of the child.
 */
bool _insertChildOnId(Tree* currentTree, Tree* newTree, char* father_id) {
  if (strcmp(currentTree->id, father_id) == 0) {
    // Realloc childs
    currentTree->child_count++;
    currentTree->childs = (Tree**) realloc(currentTree->childs, sizeof(Tree*) * currentTree->child_count);
    // Set new id
    char* newId = (char*) malloc(sizeof(char) * 10);
    sprintf(newId, "%s.%d", currentTree->id, currentTree->child_count);
    newTree->id = newId;
    currentTree->childs[currentTree->child_count-1] = newTree;
    return true;
  }
  for (int i = 0; i < currentTree->child_count; i++) {
    if (_insertChildOnId(currentTree->childs[i], newTree, father_id)) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Get the user input data and create a new tree object with it
 */
void _addNode(Tree *current, char *father_id, char *name, double value) {
  Tree* newTree = (Tree*) malloc(sizeof(Tree));
  newTree->id = father_id;
  newTree->name = name;
  newTree->value = value;
  newTree->childs = NULL;
  newTree->child_count = 0;
  _insertChildOnId(current, newTree, father_id);
}

/**
 * @brief Remove the node with the id passed as parameter and all its childs from the tree
 * @param current
 * @param id
 */
void _removeNode(Tree *current, char *id) {
  for (int i = 0; i < current->child_count; i++) {
    if (strcmp(current->childs[i]->id, id) == 0) {
      _deleteTree(current->childs[i]);
      current->child_count--;
      current->childs[i] = current->childs[current->child_count];
      current->childs = (Tree**) realloc(current->childs, sizeof(Tree*) * current->child_count);
      return;
    }
  }
  for (int i = 0; i < current->child_count; i++) {
    _removeNode(current->childs[i], id);
  }
}

/**
 * @brief Set the value of the node of id passed as parameter to the value passed as parameter
 * @param current 
 * @param id 
 * @param value 
 */
void _insertValue(Tree *current, char *id, double value) {
  if (strcmp(current->id, id) == 0) {
    if (current->child_count == 0) {
      current->value = value;
    } else {
      printf("Não é possível inserir valor em um nó que possui filhos");
    }
  } else {
    for (int i = 0; i < current->child_count; i++) {
      _insertValue(current->childs[i], id, value);
    }
  }
}
