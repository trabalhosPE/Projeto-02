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
  int aux_posicao;
  int id_aux;
  char login[MAX_C];
  char senha[MAX_C];
} outrasVariaveis;

// Funções do menu principal:
void configInicial(dados *pessoa, dados *backup);                             // Função que atribui valores iniciais para as variáveis.
void cadastraUsuario(dados *pessoa, outrasVariaveis codigo);                  // Função que cadastra um usuário.
void editarUsuario(dados *pessoa, outrasVariaveis codigo);                    // Função que edita um usuário.
void excluiUsuario(dados *pessoa, outrasVariaveis codigo);                    // Função que exclui um usuário.
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
bool verificaID(dados *pessoa, outrasVariaveis codigo);     // Função que verifica se o ID existe.
// Outras funções:
void criacaoConta(outrasVariaveis codigo);                // Função que cria uma conta (necessária para fazer o backup).
void preencheId(dados *pessoa, outrasVariaveis codigo);   // Função que radomiza os IDs.
int pegaPosicaoID(dados *pessoa, outrasVariaveis codigo); // Função que pega a posição do ID no vetor de IDs.

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
      editarUsuario(pessoa, codigo);
      break;
    case 3: // Exclusão de usuário.
      excluiUsuario(pessoa,codigo);
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
    fgets(pessoa[codigo.usuario].nome_completo, MAX_C, stdin);
    verificaNome(pessoa, codigo);
    printf("Nome cadastrado com sucesso!\n\n");
    printf("Informe o seu email: ");
    fgets(pessoa[codigo.usuario].email, MAX_C, stdin);
    verificaEmail(pessoa, codigo);
    printf("Email cadastrado com sucesso!\n\n");
    printf("Informe o seu gênero. [\"Feminino\", \"Masculino\" ou \"Não Declarar\"]: ");
    fgets(pessoa[codigo.usuario].genero, MAX_C, stdin);
    verificaGenero(pessoa, codigo);
    printf("Gênero cadastrado com sucesso!\n\n");
    printf("Informe o endereço [CEP]: ");
    scanf("%[^\n]", pessoa[codigo.usuario].endereco.cep);
    getchar();
    printf("Informe o endereço [ESTADO]: ");
    scanf("%[^\n]", pessoa[codigo.usuario].endereco.estado);
    getchar();
    printf("Informe o endereço [CIDADE]: ");
    scanf("%[^\n]", pessoa[codigo.usuario].endereco.cidade);
    getchar();
    printf("Informe o endereço [BAIRRO]: ");
    scanf("%[^\n]", pessoa[codigo.usuario].endereco.bairro);
    getchar();
    printf("Informe o endereço [RUA]: ");
    scanf("%[^\n]", pessoa[codigo.usuario].endereco.rua);
    getchar();
    printf("Endereço cadastrado com sucesso!\n\n");
    printf("Informe a sua altura: ");
    scanf("%lf", &pessoa[codigo.usuario].altura);
    verificaAltura(pessoa, codigo);
    getchar();
    printf("Altura cadastrada com sucesso.\n\n");
    printf("Você se vacinou? Escreva \"Sim\" ou \"Não\": ");
    verificaVacina(pessoa, codigo);
    printf("Vacina cadastrada com sucesso!\n\n");
  }
  else
  {
    system("cls");
    printf("A capacidade máxima de usuários cadastrados já foi atingida.\n");
  }
  system("pause");
}
void editarUsuario(dados *pessoa, outrasVariaveis codigo)
{
  int menu_aux;
  printf("Para editar, primeiro informe o seu ID: ");
  scanf("%d", &codigo.id_aux);
  getchar();
  if (verificaID(pessoa, codigo) == true)
  {
    codigo.aux_posicao = pegaPosicaoID(pessoa, codigo);
    do
    {
      system("cls");
      printf("Dados cadastrados:\n");
      printf("ID: %d \n", pessoa[codigo.aux_posicao].id);
      printf("1 - Nome completo: %s", pessoa[codigo.aux_posicao].nome_completo);
      printf("2 - Email: %s", pessoa[codigo.aux_posicao].email);
      printf("3 - Gênero: %s", pessoa[codigo.aux_posicao].genero);
      printf("4 - Endereço: %s", pessoa[codigo.aux_posicao].endereco);
      printf("5 - Altura: %.2lf metros\n", pessoa[codigo.aux_posicao].altura);
      ((pessoa[codigo.aux_posicao].vacina == true) ? (printf("6 - Vacinado(a): Sim\n")) : (printf("6 - Vacinado(a): Não\n")));
      printf("7 - Sair\n");
      printf("Escolha: ");
      scanf("%d", &menu_aux);
      getchar();
      switch (menu_aux)
      {
      case 1:
        printf("Informe o seu nome completo: ");
        fgets(pessoa[codigo.aux_posicao].nome_completo, MAX_C, stdin);
        verificaNome(pessoa, codigo);
        printf("Nome editado com sucesso!\n\n");
        break;
      case 2:
        printf("Informe o seu email: ");
        fgets(pessoa[codigo.aux_posicao].email, MAX_C, stdin);
        verificaEmail(pessoa, codigo);
        printf("Email editado com sucesso!\n\n");
        break;
      case 3:
        printf("Informe o seu gênero. Escreva \"Feminino\", \"Masculino\" ou \"Não Declarar\": ");
        fgets(pessoa[codigo.aux_posicao].genero, MAX_C, stdin);
        verificaGenero(pessoa, codigo);
        printf("Gênero editado com sucesso!\n\n");
        break;
      case 4:
        printf("Informe o seu endereço: ");
        printf("Informe o endereço [CEP]: ");
        scanf("%[^\n]", pessoa[codigo.aux_posicao].endereco.cep);
        getchar();
        printf("Informe o endereço [ESTADO]: ");
        scanf("%[^\n]", pessoa[codigo.aux_posicao].endereco.estado);
        getchar();
        printf("Informe o endereço [CIDADE]: ");
        scanf("%[^\n]", pessoa[codigo.aux_posicao].endereco.cidade);
        getchar();
        printf("Informe o endereço [BAIRRO]: ");
        scanf("%[^\n]", pessoa[codigo.aux_posicao].endereco.bairro);
        getchar();
        printf("Informe o endereço [RUA]: ");
        scanf("%[^\n]", pessoa[codigo.aux_posicao].endereco.rua);
        getchar();
        printf("Endereço editado com sucesso!\n\n");
        break;
      case 5:
        printf("Informe a sua altura: ");
        scanf("%lf", &pessoa[codigo.aux_posicao].altura);
        verificaAltura(pessoa, codigo);
        getchar();
        printf("Altura editada com sucesso.\n\n");
        break;
      case 6:
        printf("Você se vacinou? Escreva \"Sim\" ou \"Não\": ");
        verificaVacina(pessoa, codigo);
        printf("Vacina editada com sucesso!\n\n");
        break;
      default:
        printf("Opção inválida.\n");
        system("pause");
        break;
      }
    } while (menu_aux != 7);
  }
  else
    printf("O ID informado não existe.\n");
  system("pause");
}
void excluiUsuario(dados *pessoa, outrasVariaveis codigo)
{
  printf("Para excluir um cadastro informe o ID: ");
  scanf("%d", &codigo.id_aux);
  getchar();
  if (verificaID(pessoa, codigo) == true)
  {
    codigo.aux_posicao = pegaPosicaoID(pessoa, codigo);
    pessoa[codigo.aux_posicao].id = 0;
    pessoa[codigo.aux_posicao].altura = 0;
    pessoa[codigo.aux_posicao].vacina = false;
    for (int i = 0; i < MAX_C; i++)
    {
      pessoa[codigo.aux_posicao].nome_completo[i] = '\0';
      pessoa[codigo.aux_posicao].email[i] = '\0';
      pessoa[codigo.aux_posicao].genero[i] = '\0';
      pessoa[codigo.aux_posicao].endereco.rua[i] = '\0';
      pessoa[codigo.aux_posicao].endereco.bairro[i] = '\0';
      pessoa[codigo.aux_posicao].endereco.estado[i] = '\0';
      pessoa[codigo.aux_posicao].endereco.cidade[i] = '\0';
      pessoa[codigo.aux_posicao].endereco.cep[i] = '\0';
    }
    printf("Usuário excluido com sucesso!\n");
  }
  else
    printf("O ID informado não existe.\n");
  system("pause");
}
