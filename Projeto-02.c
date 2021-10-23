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
bool verificaID(dados *pessoa, int tmp);                    // Função que verifica se o ID existe.

// Outras funções:
void criacaoConta(outrasVariaveis *codigo); // Função que cria uma conta.
void preencheId(dados *pessoa, int tmp);    // Função que radomiza os IDs.
int pegaPosicaoID(dados *pessoa, int tmp);  // Função que pega a posição do ID no vetor de IDs.

// Inicio do Algoritmo Principal:
int main()
{
  setlocale(LC_ALL, "Portuguese"); // Função que habilita a formatação em Português para todos os printfs.
  srand((int)time(0));             // Função que dá a semente para o cálculo da função rand().

  dados pessoa[MAX];
  dados backup[MAX];
  outrasVariaveis codigo;

  // Criação de conta:
  printf("Olá, seja bem-vindo ao cadastro online da Universidade Católica de Brasília.\n");
  printf("Crie sua conta...\n");
  criacaoConta(&codigo);

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
    codigo.usuario = pegaPosicaoID(pessoa, 0);
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
      excluiUsuario(pessoa, codigo);
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
void cadastraUsuario(dados *pessoa, outrasVariaveis codigo)
{
  if (codigo.quantidade_usuario < MAX)
  {
    preencheId(pessoa, codigo.usuario);
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
  if (verificaID(pessoa, codigo.id_aux) == true)
  {
    codigo.aux_posicao = pegaPosicaoID(pessoa, codigo.id_aux);
    do
    {
      system("cls");
      printf("Dados cadastrados:\n");
      printf("ID: %d \n", pessoa[codigo.aux_posicao].id);
      printf("1 - Nome completo: %s", pessoa[codigo.aux_posicao].nome_completo);
      printf("2 - Email: %s", pessoa[codigo.aux_posicao].email);
      printf("3 - Gênero: %s", pessoa[codigo.aux_posicao].genero);
      printf("4 - Endereço: %s, ", pessoa[codigo.aux_posicao].endereco.cep);
      printf("%s ", pessoa[codigo.aux_posicao].endereco.rua);
      printf("%s, ", pessoa[codigo.aux_posicao].endereco.bairro);
      printf("%s - ", pessoa[codigo.aux_posicao].endereco.cidade);
      printf("%s\n", pessoa[codigo.aux_posicao].endereco.estado);
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
  if (verificaID(pessoa, codigo.id_aux) == true)
  {
    codigo.aux_posicao = pegaPosicaoID(pessoa, codigo.id_aux);
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
void pesquisarCadastro(dados *pessoa, outrasVariaveis codigo)
{
  char continua;
  do
  {
    system("cls");
    printf("Informe o seu ID para continuar: ");
    scanf("%d", &codigo.id_aux);
    getchar();
    system("cls");
    if (verificaID(pessoa, codigo.id_aux) == true)
    {
      codigo.aux_posicao = pegaPosicaoID(pessoa, codigo.id_aux);
      printf("ID: %d \n", pessoa[codigo.aux_posicao].id);
      printf("1 - Nome completo: %s", pessoa[codigo.aux_posicao].nome_completo);
      printf("2 - Email: %s", pessoa[codigo.aux_posicao].email);
      printf("3 - Gênero: %s", pessoa[codigo.aux_posicao].genero);
      printf("4 - Endereço: %s, ", pessoa[codigo.aux_posicao].endereco.cep);
      printf("%s ", pessoa[codigo.aux_posicao].endereco.rua);
      printf("%s, ", pessoa[codigo.aux_posicao].endereco.bairro);
      printf("%s - ", pessoa[codigo.aux_posicao].endereco.cidade);
      printf("%s\n", pessoa[codigo.aux_posicao].endereco.estado);
      printf("5 - Altura: %.2lf metros\n", pessoa[codigo.aux_posicao].altura);
      ((pessoa[codigo.aux_posicao].vacina == true) ? (printf("6 - Vacinado(a): Sim\n")) : (printf("6 - Vacinado(a): Não\n")));
    }
    else
      printf("O ID informado não existe.\n");
    system("pause");
    printf("\nDeseja fazer uma nova pesquisa? [S/N]: ");
    scanf(" %c", &continua);
  } while (continua == 'S' || continua == 's');
}
void pesquisarEmail(dados *pessoa, outrasVariaveis codigo)
{
  bool cadastroRetorno = false;
  char continua, cadastroPesquisa[MAX_C];
  do
  {
    printf("Informe o seu Email para continuar: ");
    fgets(cadastroPesquisa, MAX_C, stdin);
    for (int i = 0; i < MAX; i++)
      if (strcmp(pessoa[codigo.usuario].email, cadastroPesquisa) == 0)
      {
        system("cls");
        printf("ID: %d \n", pessoa[codigo.usuario].id);
        printf("1 - Nome completo: %s", pessoa[codigo.usuario].nome_completo);
        printf("2 - Email: %s", pessoa[codigo.usuario].email);
        printf("3 - Gênero: %s", pessoa[codigo.usuario].genero);
        printf("4 - Endereço: %s, ", pessoa[codigo.usuario].endereco.cep);
        printf("%s ", pessoa[codigo.usuario].endereco.rua);
        printf("%s, ", pessoa[codigo.usuario].endereco.bairro);
        printf("%s - ", pessoa[codigo.usuario].endereco.cidade);
        printf("%s\n", pessoa[codigo.usuario].endereco.estado);
        printf("5 - Altura: %.2lf metros\n", pessoa[codigo.usuario].altura);
        ((pessoa[codigo.usuario].vacina == true) ? (printf("6 - Vacinado(a): Sim\n")) : (printf("6 - Vacinado(a): Não\n")));
        cadastroRetorno = true;
      }
    if (cadastroRetorno == false)
      printf("Email não encontrado.\n");
    printf("\nDeseja fazer uma nova pesquisa? [S/N]: ");
    scanf(" %c", &continua);
  } while (continua == 'S' || continua == 's');
}
void listaCadastro(dados *pessoa, outrasVariaveis codigo)
{
  printf("**Lista de cadastros**\n");
  if (codigo.quantidade_usuario == 0)
  {
    printf("Lista vazia!\n");
    system("pause");
  }
  else
  {
    system("cls");
    for (int i = 0; i < MAX; i++)
      if (pessoa[codigo.usuario].id > 0)
      {
        printf("ID: %d \n", pessoa[codigo.usuario].id);
        printf("1 - Nome completo: %s", pessoa[codigo.usuario].nome_completo);
        printf("2 - Email: %s", pessoa[codigo.usuario].email);
        printf("3 - Gênero: %s", pessoa[codigo.usuario].genero);
        printf("4 - Endereço: %s, ", pessoa[codigo.usuario].endereco.cep);
        printf("%s ", pessoa[codigo.usuario].endereco.rua);
        printf("%s, ", pessoa[codigo.usuario].endereco.bairro);
        printf("%s - ", pessoa[codigo.usuario].endereco.cidade);
        printf("%s\n", pessoa[codigo.usuario].endereco.estado);
        printf("5 - Altura: %.2lf metros\n", pessoa[codigo.usuario].altura);
        ((pessoa[codigo.usuario].vacina == true) ? (printf("6 - Vacinado(a): Sim\n")) : (printf("6 - Vacinado(a): Não\n")));
      }
    system("pause");
  }
}
void backupCadastro(dados *pessoa, outrasVariaveis codigo, dados *backup)
{
  if (codigo.quantidade_usuario == 0)
  {
    printf("O backup não foi concluido.");
    system("pause");
  }
  else
  {
    for (int i = 0; i < codigo.quantidade_usuario; i++)
    {
      backup[i].id = pessoa[i].id;
      strcpy(backup[i].nome_completo, pessoa[i].nome_completo);
      strcpy(backup[i].email, pessoa[i].email);
      strcpy(backup[i].endereco.bairro, pessoa[i].endereco.bairro);
      strcpy(backup[i].endereco.cep, pessoa[i].endereco.cep);
      strcpy(backup[i].endereco.cidade, pessoa[i].endereco.cidade);
      strcpy(backup[i].endereco.estado, pessoa[i].endereco.estado);
      strcpy(backup[i].endereco.rua, pessoa[i].endereco.rua);
      strcpy(backup[i].genero, pessoa[i].genero);
      backup[i].altura = pessoa[i].altura;
      backup[i].vacina = pessoa[i].vacina;
    }
    printf("Backup concluido!!\n");
    system("pause");
  }
}
void restaurarCadastro(dados *pessoa, outrasVariaveis codigo, dados *backup)
{
  if (codigo.quantidade_usuario == 0)
  {
    printf("A restauração não foi concluida.\n");
    system("pause");
  }
  else
  {
    for (int i = 0; i < codigo.quantidade_usuario; i++)
    {
      pessoa[i].id = backup[i].id;
      strcpy(pessoa[i].nome_completo, backup[i].nome_completo);
      strcpy(pessoa[i].email, backup[i].email);
      strcpy(pessoa[i].endereco.bairro, backup[i].endereco.bairro);
      strcpy(pessoa[i].endereco.cep, backup[i].endereco.cep);
      strcpy(pessoa[i].endereco.cidade, backup[i].endereco.cidade);
      strcpy(pessoa[i].endereco.estado, backup[i].endereco.estado);
      strcpy(pessoa[i].endereco.rua, backup[i].endereco.rua);
      strcpy(pessoa[i].genero, backup[i].genero);
      pessoa[i].altura = backup[i].altura;
      pessoa[i].vacina = backup[i].vacina;
    }
    printf("Restauração concluida!\n");
    system("pause");
  }
}
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
    verificaGenero(pessoa, codigo);
  }
}
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
    verificaVacina(pessoa, codigo);
  }
}
bool verificaID(dados *pessoa, int tmp)
{
  for (int i = 0; i < MAX; i++)
    if (tmp == pessoa[i].id)
      return true;
  return false;
}
void criacaoConta(outrasVariaveis *codigo)
{
  system("pause");
  system("cls");
  printf("Crie o seu login: ");
  fgets(codigo->login, MAX_C, stdin);
  printf("Crie a sua senha: ");
  fgets(codigo->senha, MAX_C, stdin);
}
void preencheId(dados *pessoa, int tmp)
{
  int numero_randomico;
  do
  {
    numero_randomico = (1 + rand() % MAX);
  } while (verificaID(pessoa, numero_randomico) == true);
  pessoa[tmp].id = numero_randomico;
}
int pegaPosicaoID(dados *pessoa, int tmp)
{
  int i = 0;
  while (pessoa[i].id != tmp)
    i++;
  return i;
}