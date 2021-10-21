//Projeto 02 - Struct
//Aluno: Ricardo Alves de Lima Júnior | Matrícula: UC20102577
//Aluno: Luiz Gustavo da Costa Gonçalves | Matrícula: UC20201242

//Bibliotecas:
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAX_C 50 + 2

// Variaveis Struct:
typedef struct cadastro{
  int id;
  char nome_completo[MAX_C];
  char email[MAX_C];
  char genero[MAX_C];
  char endereco[MAX_C];
  double altura;
  bool vacina;
  int id_backup;
  char nome_backup[MAX_C];
  char email_backup[MAX_C];
  char genero_backup[MAX_C];
  char endereco_backup[MAX_C];
  double altura_backup;
  bool vacina_backup;
}pessoas;

//Funções do menu principal:
void configInicial();//Função que atribui valores iniciais para as variáveis.
void cadastraUsuario();//Função que cadastra um usuário.
void editarUsuario();//Função que edita um usuário.
void excluiUsuario();//Função que exclui um usuário.
void pesquisarCadastro(); //Função que pesquisa um cadastro pelo ID.
void pesquisarEmail();//Função que pesquisa um cadastro pelo email.
void listaCadastro(); //Função que mostra uma lista com todos os usuários cadastrados.
void backupCadastro(); //Função que faz o backup de todos os cadastros.
void restaurarCadastro(); //Função que restaura os cadastros a partir do backup.

//Funções de verificação:
void verificaNome(); //Função que verifica se o nome não é nulo.
void verificaEmail();   //Função que verifica se o email é valido.
void verificaGenero();   //Função que verifica se o gênero é válido.
void verificaAltura();   //Função que verifica se a altura é válida.
void verificaVacina();  //Função que verifica se o usuário é vacinado.
bool verificaID();    //Função que verifica se o ID existe.
//Outras funções:
void criacaoConta(); //Função que cria uma conta (necessária para fazer o backup).
void preencheId();   //Função que radomiza os IDs.
int pegaPosicaoID();  //Função que pega a posição do ID no vetor de IDs.

// Inicio do Algoritmo Principal:
int main (){
	
	
	
}