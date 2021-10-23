// Projeto 02 - Struct
// Aluno: Ricardo Alves de Lima Júnior | Matrícula: UC20102577
// Aluno: Luiz Gustavo da Costa Gonçalves | Matrícula: UC20201242

// Bibliotecas:
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Constantes:
#define MAX 1000     // MAX é número máximo de usuários que serão cadastrados.
#define MAX_C 50 + 2 // MAX_C é número máximo de caracteres que cada variável char pode ler.

// Variaveis Struct:
typedef struct
{
  char rua[MAX_C];
  char bairro[MAX_C];
  char estado[MAX_C];
  char cidade[MAX_C];
  char cep[11];
} localizacao;

typedef struct cadastro
{
  int id;
  char nome_completo[MAX_C];
  char email[MAX_C];
  char genero[MAX_C];
  localizacao endereco;
  double altura;
  bool vacina;
} dados;

// Funções do menu principal:
void configInicial();     // Função que atribui valores iniciais para as variáveis.
void cadastraUsuario();   // Função que cadastra um usuário.
void editarUsuario();     // Função que edita um usuário.
void excluiUsuario();     // Função que exclui um usuário.
void pesquisarCadastro(); // Função que pesquisa um cadastro pelo ID.
void pesquisarEmail();    // Função que pesquisa um cadastro pelo email.
void listaCadastro();     // Função que mostra uma lista com todos os usuários cadastrados.
void backupCadastro();    // Função que faz o backup de todos os cadastros.
void restaurarCadastro(); // Função que restaura os cadastros a partir do backup.

// Funções de verificação:
void verificaNome();   // Função que verifica se o nome não é nulo.
void verificaEmail();  // Função que verifica se o email é valido.
void verificaGenero(); // Função que verifica se o gênero é válido.
void verificaAltura(); // Função que verifica se a altura é válida.
void verificaVacina(); // Função que verifica se o usuário é vacinado.
bool verificaID();     // Função que verifica se o ID existe.
// Outras funções:
void criacaoConta(); // Função que cria uma conta (necessária para fazer o backup).
void preencheId();   // Função que radomiza os IDs.
int pegaPosicaoID(); // Função que pega a posição do ID no vetor de IDs.

// Inicio do Algoritmo Principal:
int main()
{
  dados pessoa[MAX];
  dados backup[MAX];
  return 0;
}