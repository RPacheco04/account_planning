
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"

enum Options {
  EXIT = 0,
  ADD = 1,
  REMOVE,
  INSERTVALUE,
  PRINT,
  BALANCE,
  INFO,
};

/**
 * @brief Print the user menu options
 */
void printMenu() {
  printf("Escolha uma opção: \n");
  printf("1 - Adicionar nova conta \n");
  printf("2 - Remover conta \n");
  printf("3 - Inserir valor em conta \n");
  printf("4 - Imprimir plano de contas \n");
  printf("5 - Calcular saldo \n");
  printf("6 - Informações do sistema \n");
  printf("0 - Sair \n");
}

/**
 * @brief Print the first messages to the user
 * @return bool If the user choose to use the custom template
 */
bool printWelcome() {
  int option;
  printf("================================================================================================\n");
  printf("Bem-vindo ao simulador de Plano de Contas Contábil. \n\n");
  printf("Você irá criar o Plano de Contas do seu negócio.\n");
  printf("Plano de Contas é criado com o Plano de Contas Predefinido, com contas sugeridas .\n");
  printf("Você pode editá-lo do jeito que desejar, ou criar um plano customizado do zero. \n\n");
  printf("1 - Sim \n");
  printf("2 - Não \n");
  printf("Deseja usar o Plano de Contas Predefinido? ");
  scanf("%d", &option);
  bool useTemplate = option == 1;
  if (useTemplate) 
    printf("Você escolheu usar o Plano de Contas Predefinido. \n");
  else 
    printf("Você escolheu criar um Plano de Contas customizado. \n");
  return useTemplate;
}

/**
 * @brief Print the system information
 */
void showSystemInfo() {
  printf("================================================================================================\n");
  printf("Informações do sistema: \n");
  printf("Este programa foi desenvolvido com o objetivo de implementar um Plano de Contas Contábil facilitado para empreendedores. \n");
  printf("O programa foi desenvolvido em C, utilizando estrutura em Árvores para armazenar as contas. \n\n");

  printf("Estrutua do plano de contas: \n");
  printf("O plano de contas básico é dividido entre Receitas e Despesas.\n");
  printf("Todos as entradas de valor devem ser armazenadas e informadas em Receitas, enquanto as saídas de valor, em Despesas\n\n");

  printf("Plano de Contas Predefinido: \n");
  printf("O plano de contas predefinido foi criado por nós a partir de análises dos Planos de Contas criados para empresas de pequeno e médio porte.\n");
  printf("É composto por 4 grupos de Receitas e 5 grupos de Despesas, sendo eles: \n");
  printf("1 - Receitas \n");
  printf("    1.1 - Fontes de renda direta\n");
  printf("        1.1.1 - Vendas\n");
  printf("        1.1.2 - Mensalidades\n");
  printf("        1.1.3 - Outras receitas\n");
  printf("    1.2 - Investimentos\n");
  printf("        1.2.1 - Investimentos externos\n");
  printf("        1.2.2 - Retorno de investimentos (ROI)\n");
  printf("        1.2.3 - Empréstimos bancários\n");
  printf("    1.3 - Recebimentos\n");
  printf("        1.3.1 - Recebimentos de clientes\n");
  printf("    1.4 - Outras receitas \n");
  printf("2 - Despesas \n");
  printf("    2.1 - Custos em produtos \n");
  printf("        2.1.1 - Materia prima \n");
  printf("        2.1.2 - Promoções e descontos \n");
  printf("        2.1.3 - Infraestrutura de produtos \n");
  printf("        2.1.4 - Outros custos em produtos \n");
  printf("    2.2 - Custos de recursos humanos \n");
  printf("        2.2.1 - Salários de funcionários \n");
  printf("        2.2.2 - Benefícios de funcionários \n");
  printf("    2.3 - Manutenção \n");
  printf("        2.3.1 - Manutenção de equipamentos \n");
  printf("        2.3.2 - Manutenção de instalações \n");
  printf("    2.4 - Administração \n");
  printf("        2.4.1 - Água \n");
  printf("        2.4.2 - Aluguel \n"); 
  printf("        2.4.3 - Energia elétrica \n");
  printf("        2.4.4 - Internet e Telefone \n");
  printf("        2.4.5 - Publicidade e marketing \n");
  printf("        2.4.6 - Pagamentos de empréstimos\n");
  printf("    2.5 - Outras despesas \n\n");
  
  printf("O programa foi desenvolvido por: \n");
  printf(" - Ricardo Pacheco \n");
  printf(" - Yago Leão \n");
  printf(" - João Felipe Kessler \n");
  printf("================================================================================================\n");
}

/**
 * @brief Print the current tree structure
 * @param tree 
 */
void showCurrentTree(Tree * tree) {
  printf("\n");
  printf("================================================================================================\n");
  printf("Plano de Contas atual: \n\n");
  _showTree(tree, 0);
  printf("================================================================================================\n");
  printf("\n");
}

/**
 * @brief Get user input to create a new account. Calls _addNode
 * @param current 
 */
void insertNewNode(Tree *current) {
  char *id = malloc(sizeof(char) * 100);
  char *name = malloc(sizeof(char) * 100);
  double value;
  printf("Digite o ID do pai onde deseja inserir: ");
  scanf("%s", id);
  printf("Digite o nome da nova conta: ");
  scanf("%s", name);
  printf("Digite o valor da nova conta: ");
  scanf(" %lf", &value);
  _addNode(current, id, name, value);
  printf("Conta adicionada com sucesso! \n");
  showCurrentTree(current);
}

/** Get the id of the node to delete from user input and calls _removeNode */
void removeNode(Tree *current) {
  char *id = malloc(sizeof(char) * 100);
  printf("Digite o ID da conta que deseja remover: ");
  scanf("%s", id);
  if (strcmp(id, "1") == 0 || strcmp(id, "2") == 0) {
    printf("\n================================================================================================\n");
    printf("Não é permitido deletar as contas Receitas e Despesas\n");
    printf("================================================================================================\n\n");
    return;
  } else {
    _removeNode(current, id);
    printf("Conta removida com sucesso! \n");
    showCurrentTree(current);
  }
}

/**
 * @brief Get user input of node id and new value. Calls _insertValue
 * 
 */
void insertValue(Tree *current) {
  char *id = malloc(sizeof(char) * 100);
  printf("Digite o ID da conta onde deseja inserir o valor: ");
  scanf("%s", id);
  double value;
  printf("Digite o valor a ser inserido: ");
  scanf("%lf", &value);
  _insertValue(current, id, value);
  printf("Valor inserido com sucesso na conta \n");
  showCurrentTree(current);
}


/**
 * @brief Calculate the balance of the billings (Receitas - Despesas)
 * @param current 
 */
void calculateBalance(Tree *current) {
  printf("\n================================================================================================\n");
  printf("Calculando o balanço do plano de contas atual: \n");
  double balance = _calculateBalance(current);
  printf("O balanço do plano de contas atual é: R$ %.2lf \n", balance);
  printf("================================================================================================\n");

}

/**
 * @brief Create the pre-defined tree structure
 * @return tree
 */
Tree* implementsBaseTree(Tree* tree) {
  // Receitas
  _addNode(tree, "1", "Fontes de renda direta", 0);
  _addNode(tree, "1.1", "Vendas", 0);
  _addNode(tree, "1.1", "Mensalidades", 0);
  _addNode(tree, "1.1", "Outras receitas", 0);
  _addNode(tree, "1", "Investimentos", 0);
  _addNode(tree, "1.2", "Investimentos externos", 0);
  _addNode(tree, "1.2", "Retorno de investimentos (ROI)", 0);
  _addNode(tree, "1.2", "Empréstimos bancários", 0);
  _addNode(tree, "1", "Recebimentos", 0);
  _addNode(tree, "1.3", "Recebimentos de clientes", 0);
  _addNode(tree, "1", "Outras receitas", 0);

  // Despesas
  _addNode(tree, "2", "Custos em produtos", 0);
  _addNode(tree, "2.1", "Materia prima", 0);
  _addNode(tree, "2.1", "Promoções e descontos", 0);
  _addNode(tree, "2.1", "Infraestrutura de produtos", 0);
  _addNode(tree, "2.1", "Outros custos em produtos", 0);
  _addNode(tree, "2", "Custos de recursos humanos", 0);
  _addNode(tree, "2.2", "Salários de funcionários", 0);
  _addNode(tree, "2.2", "Benefícios de funcionários", 0);
  _addNode(tree, "2", "Manutenção", 0);
  _addNode(tree, "2.3", "Manutenção de equipamentos", 0);
  _addNode(tree, "2.3", "Manutenção de instalações", 0);
  _addNode(tree, "2", "Administração", 0);
  _addNode(tree, "2.4", "Água", 0);
  _addNode(tree, "2.4", "Aluguel", 0);
  _addNode(tree, "2.4", "Energia elétrica", 0);
  _addNode(tree, "2.4", "Internet e Telefone", 0);
  _addNode(tree, "2.4", "Publicidade e marketing", 0);
  _addNode(tree, "2.4", "Pagamentos de empréstimos", 0);
  _addNode(tree, "2", "Outras despesas", 0);
  return tree;
}

int main() {
  bool useBaseTemplate = printWelcome();
  Tree * tree = _createEmptyTree();
  if (useBaseTemplate) tree = implementsBaseTree(tree);
  showCurrentTree(tree);

  int option = 1;
  while (option != EXIT) {
    printMenu();
    scanf("%d", &option);
    switch (option) {
      
      case ADD:
        insertNewNode(tree);
        break;
      case REMOVE:
        removeNode(tree);
        break;
      case INSERTVALUE:
        insertValue(tree);
        break;
      case PRINT:
        showCurrentTree(tree);
        break;
      case BALANCE:
        calculateBalance(tree);
        break;
      case INFO:
        showSystemInfo();
        break;
      case EXIT:
        break;
      default:
        printf("Opção inválida. \n");
        break;
    }
  }
}
