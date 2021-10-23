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

typedef struct
{
  int usuario;
  int quantidade_usuario;
  int menu;
  char login[MAX_C];
  char senha[MAX_C];
  int id_aux;
} outrasVariaveis;

// Funções do menu principal:
void configInicial(dados *pessoa, dados *backup);                             // Função que atribui valores iniciais para as variáveis.
void cadastraUsuario(dados *pessoa, outrasVariaveis codigo);                  // Função que cadastra um usuário.
void editarUsuario(dados *pessoa);                                            // Função que edita um usuário.
void excluiUsuario(dados *pessoa);                                            // Função que exclui um usuário.
void pesquisarCadastro(dados *pessoa, outrasVariaveis codigo);                // Função que pesquisa um cadastro pelo ID.
void pesquisarEmail(dados *pessoa, outrasVariaveis codigo);                   // Função que pesquisa um cadastro pelo email.
void listaCadastro(dados *pessoa, outrasVariaveis codigo);                    // Função que mostra uma lista com todos os usuários cadastrados.
void backupCadastro(dados *pessoa, outrasVariaveis codigo, dados *backup);    // Função que faz o backup de todos os cadastros.
void restaurarCadastro(dados *pessoa, outrasVariaveis codigo, dados *backup); // Função que restaura os cadastros a partir do backup.

// Funções de verificação:
void verificaNome(dados *pessoa, outrasVariaveis codigo);   // Função que verifica se o nome não é nulo.
void verificaEmail(dados *pessoa, outrasVariaveis codigo);  // Função que verifica se o email é valido.
void verificaGenero(dados *pessoa, outrasVariaveis codigo); // Função que verifica se o gênero é válido.
void verificaAltura(dados *pessoa, outrasVariaveis codigo); // Função que verifica se a altura é válida.
void verificaVacina(dados *pessoa, outrasVariaveis codigo); // Função que verifica se o usuário é vacinado.
bool verificaID(dados *pessoa, int id_aux);                 // Função que verifica se o ID existe.
// Outras funções:
void criacaoConta(outrasVariaveis codigo);              // Função que cria uma conta (necessária para fazer o backup).
void preencheId(dados *pessoa, outrasVariaveis codigo); // Função que radomiza os IDs.
int pegaPosicaoID(dados *pessoa, int id_aux);           // Função que pega a posição do ID no vetor de IDs.

// Inicio do Algoritmo Principal:
int main()
{
  setlocale(LC_ALL, "Portuguese"); // Função que habilita a formatação em Português para todos os printfs.
  srand((int)time(0));             // Função que dá a semente para o cálculo da função rand().

  dados pessoa[MAX];
  dados backup[MAX];
  outrasVariaveis codigo;

  // Atribuição de valores iniciais para as variáveis:
  configInicial(pessoa, backup);

  // Criação de conta:
  printf("Olá, seja bem-vindo ao cadastro online da Universidade Católica de Brasília.\n");
  printf("Crie sua conta...\n");
  criacaoConta(codigo);

  // Menu principal:
  do
  {
    system("cls");
    printf("-----------------\n");
    printf("MENU:\n");
    printf("1 - CADASTRO\n");
    printf("2 - EDITAR CADASTRO\n");
    printf("3 - EXCLUIR CADASTRO\n");
    printf("4 - PROCURAR CADASTRO VIA ID\n");
    printf("5 - PROCURAR CADASTRO VIA E-MAIL\n");
    printf("6 - LISTA DE CADASTROS\n");
    printf("7 - BACKUP DE CADASTROS\n");
    printf("8 - RESTAURAÇÃO (Backup necessário)\n");
    printf("9 - SAIR\n");
    printf("Escolha: ");
    scanf("%d", &codigo.menu);
    system("cls");
    getchar();
    //    codigo.usuario = pegaPosicaoID(pessoa->id, 0);
    switch (codigo.menu)
    {
    case 1: // Cadastro de usuário.
      cadastraUsuario(pessoa, codigo);
      codigo.quantidade_usuario++;
      break;
    case 2: // Edição de usuário.
      editarUsuario(pessoa);
      break;
    case 3: // Exclusão de usuário.
      excluiUsuario(pessoa);
      codigo.quantidade_usuario--;
      break;
    case 4: // Pesquisa de usuário pelo ID.
      pesquisarCadastro(pessoa, codigo);
      break;
    case 5: // Pesquisa de usuário pelo email.
      pesquisarEmail(pessoa, codigo);
      break;
    case 6: // Lista de usuários cadastrados.
      listaCadastro(pessoa, codigo);
      break;
    case 7: // Backup dos cadastros.
      backupCadastro(pessoa, codigo, backup);
      break;
    case 8: // Restauração dos cadastros.
      restaurarCadastro(pessoa, codigo, backup);
      break;
    default:
      printf("Opção inválida.\n");
      system("pause");
      break;
    }
  } while (codigo.menu != 9);
  return 0;
}
// Fim do algoritmo principal.

// Funções:
void configInicial(dados *pessoa, dados *backup)
{
  for (int i = 0; i < MAX; i++)
  {
    pessoa[i].id = 0;
    backup[i].id = 0;
    pessoa[i].altura = 0;
    backup[i].altura = 0;
    pessoa[i].vacina = false;
    backup[i].vacina = false;
    for (int j = 0; j < MAX_C; j++)
    {
      pessoa[i].nome_completo[j] = '\0';
      backup[i].nome_completo[j] = '\0';
      pessoa[i].email[j] = '\0';
      backup[i].email[j] = '\0';
      pessoa[i].genero[j] = '\0';
      backup[i].genero[j] = '\0';
      pessoa[i].endereco.rua[j] = '\0';
      backup[i].endereco.rua[j] = '\0';
      pessoa[i].endereco.bairro[j] = '\0';
      backup[i].endereco.bairro[j] = '\0';
      pessoa[i].endereco.estado[j] = '\0';
      backup[i].endereco.estado[j] = '\0';
      pessoa[i].endereco.cidade[j] = '\0';
      backup[i].endereco.cidade[j] = '\0';
      pessoa[i].endereco.cep[j] = '\0';
      backup[i].endereco.cep[j] = '\0';
    }
  }
}
void cadastraUsuario(dados *pessoa, outrasVariaveis codigo)
{
  if (codigo.quantidade_usuario < MAX)
  {
//    preencheId(pessoa->id, codigo);
    printf("O seu ID é \"%d\".\n\n", pessoa[codigo.usuario].id);
    printf("Informe o seu nome completo: ");
    /*fgets(nome_completo[usuario], MAX_C, stdin);
    verificaNome(nome_completo, usuario);
    printf("Nome cadastrado com sucesso!\n\n");
    printf("Informe o seu email: ");
    fgets(email[usuario], MAX_C, stdin);
    verificaEmail(email, usuario);
    printf("Email cadastrado com sucesso!\n\n");
    printf("Informe o seu gênero. [\"Feminino\", \"Masculino\" ou \"Não Declarar\"]: ");
    fgets(genero[usuario], MAX_C, stdin);
    verificaGenero(genero, usuario);
    printf("Gênero cadastrado com sucesso!\n\n");
    printf("Informe o seu endereço: ");
    fgets(endereco[usuario], MAX_C, stdin);
    printf("Endereço cadastrado com sucesso!\n\n");
    printf("Informe a sua altura: ");
    scanf("%lf", &altura[usuario]);
    verificaAltura(altura, usuario);
    getchar();
    printf("Altura cadastrada com sucesso.\n\n");
    printf("Você se vacinou? Escreva \"Sim\" ou \"Não\": ");
    verificaVacina(vacina, usuario);
    printf("Vacina cadastrada com sucesso!\n\n");*/
  }
  else
  {
    system("cls");
    printf("A capacidade máxima de usuários cadastrados já foi atingida.\n");
  }
  system("pause");
}














//Funções de verificação:
//Verificação de Nome
void verificaNome(dados *pessoa, outrasVariaveis codigo) 
{
  if (strcmp(pessoa[codigo.usuario].nome_completo, "\n") == 0)
    do
    {
      system("cls");
      printf("O nome não pode ser nulo.\n");
      printf("Informe o seu nome completo: ");
      fgets(pessoa[codigo.usuario].nome_completo, MAX_C, stdin);
    } while (strcmp(pessoa[codigo.usuario].nome_completo, "\n") == 0);
}
// Verificação do Email
void verificaEmail(dados *pessoa, outrasVariaveis codigo)
{
  if (strchr(pessoa[codigo.usuario].email, '@') == NULL)
    do
    {
      system("cls");
      printf("O email deve conter um \"@\".\n");
      printf("Informe o seu email: ");
      fgets(pessoa[codigo.usuario].email, MAX_C, stdin);
    } while (strchr(pessoa[codigo.usuario].email, '@') == NULL);
}
// Verificação de genero
void verificaGenero(dados *pessoa, outrasVariaveis codigo) 
{
  for (int i = 0; i < strlen(pessoa[codigo.usuario].genero); i++)
    pessoa[codigo.usuario].genero[i] = tolower(pessoa[codigo.usuario].genero[i]);
  if (strcmp(pessoa[codigo.usuario].genero, "masculino\n") == 0)
    strcpy(pessoa[codigo.usuario].genero, "Masculino\n");
  else if (strcmp(pessoa[codigo.usuario].genero, "feminino\n") == 0)
    strcpy(pessoa[codigo.usuario].genero, "Feminino\n");
  else if (strcmp(pessoa[codigo.usuario].genero, "não declarar\n") == 0 || strcmp(pessoa[codigo.usuario].genero, "nÃo declarar\n") == 0)
    strcpy(pessoa[codigo.usuario].genero, "Não declarado\n");
  else
  {
    system("cls");
    printf("O gênero deve ser Feminino, Masculino ou Não Declarar.\n");
    printf("Informe o seu gênero: ");
    fgets(pessoa[codigo.usuario].genero, MAX_C, stdin);
    verificaGenero(pessoa,codigo);
  }
}
// Verificação Altura: 
void verificaAltura(dados *pessoa, outrasVariaveis codigo)
{
  if (pessoa[codigo.usuario].altura < 1 || pessoa[codigo.usuario].altura > 2)
    do
    {
      system("cls");
      printf("A altura deve ser entre 1 e 2 metros.\n");
      printf("Informe a sua altura: ");
      scanf("%lf", &pessoa[codigo.usuario].altura);
    } while (pessoa[codigo.usuario].altura < 1 || pessoa[codigo.usuario].altura > 2);
}
//Verificação Vacina:

void verificaVacina(dados *pessoa, outrasVariaveis codigo)
{
  char aux[4 + 2];
  fgets(aux, 4 + 2, stdin);
  for (int i = 0; i < strlen(aux); i++)
    aux[i] = tolower(aux[i]);
  if (strcmp(aux, "sim\n") == 0)
    pessoa[codigo.usuario].vacina = true;
  else if (strcmp(aux, "não\n") == 0 || strcmp(aux, "nÃo\n") == 0)
    pessoa[codigo.usuario].vacina = false;
  else
  {
    if (strchr(aux, '\n') == NULL)
      while (getchar() != '\n')
        ;
    system("cls");
    printf("Você deve escrever apenas \"Sim\" ou \"Não\".\n");
    printf("Você se vacinou? ");
    verificaVacina(pessoa,codigo);
  }
}
//Verificação de ID:

bool verificaID(dados *pessoa, outrasVariaveis codigo)
{
  for (int i = 0; i < MAX; i++)
    if (codigo.id_aux == pessoa[i].id)
      return true;
  return false;
}

// Outras Funções:
//Função de Criação de conta:
void criacaoConta(outrasVariaveis codigo)
{
  system("pause");
  system("cls");
  printf("Crie o seu login: ");
  fgets(codigo.login, MAX_C, stdin);
  printf("Crie a sua senha: ");
  fgets(codigo.senha, MAX_C, stdin);
}

//Função Preencher ID: OBS: erro no while (verificaID(pessoa.id, numero_randomico) == true);

void preencheId(dados *pessoa, outrasVariaveis codigo)
{
  int numero_randomico;
  do
  {
    numero_randomico = (1 + rand() % MAX);
  } while (verificaID(pessoa.id, numero_randomico) == true);
  pessoa[codigo.usuario].id = numero_randomico;
}

//Função Posição ID:
int pegaPosicaoID(dados *pessoa, outrasVariaveis codigo)
{
  int i = 0;
  while (pessoa[i].id != codigo.id_aux)
    i++;
  return i;
}
