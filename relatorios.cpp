/*
  Nome: Cadastro de Cliente
  Copyright: By Albino IT Services
  Autores: Fernando Albino
  Data: 01/11/12 14:50 
  Descrição: Cadastro/Pesquisa/ Edição de Arquivos Cadastro de Clientes 
  
*/
// Declaração das bibliotecas a serem usadas / ou não pelo código!!!!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <conio2.h>//Essa ta mais pela honra de conseguir fazer funcionar do que por ser usada mesmo, mas é bem legal para enfeitar mais o programa 
#include <locale.h>//para ajustar a linguagem
#include <windows.h>


#define clrscr() (system("CLS")) //Definição para limpar a tela


//Declaração das funções 
void MenuCliente(void);
void Submenu(void);
void GravaDados(void);
void Cadastro(void);
void RelatorioCliente(void);
void RelatorioFuncionario(void);
void RelatorioProduto(void);
void RelatorioFornecedor(void);
void MostraCadastro(int, int);
int moveponteiro (void);
char role[2];

//Estrutura Cleintes
struct clientes
{
       long int id_funcionario;
       char id_cliente[50];
       char nome[50], data_nascimento[10], endereco[30], cidade[30];
       char estado[3], cep[10], telefone[13], Doc[13];
       char deletado;
}; 

struct clientes cli, consulta[99];

struct funcionarios
{
       char id_funcionario[50];
       char nome[50], data_nascimento[10], endereco[30], cidade[30];
       char estado[3], cep[10], telefone[13], Doc[13], senha[30], salario[30], cargo[30], permissao[2];// A ou V ou S;
       char deletado;
}; 

struct funcionarios func;

struct produtos
{
       long int id_fornecedor;
       char id_produto[50];
       char nome[50], num_nota[30], data_compra[10], tipo_unidade[5];
       char deletado;
       float preco;
}; 

struct produtos prod;

struct fornecedores
{
       char id_fornecedor[50];
       char nome[50], endereco[30], cidade[30];
       char estado[3], cep[10], telefone[13], CNPJ[13], cargo[30], permissao[2];// A ou V ou S;
       char deletado;
}; 

struct fornecedores forn;

FILE *C; //ponteiro do arquivo
char getops;//Define a variavel de opção em mostrar cadastro seria usado para mover com , e. representando < >, mas não rolou ainda!!!
int i, PosFile = 0, deletado = 0;
char opDel;//variavel usada em opções do menu como teste de sim ou não!!!
int achou = -1;


//Função para imprimir linha vazia perfumaria só pra fazer graça!!
void clearline(void)
{
     for (i=0;i<80;i++)
  {
        printf("%c",32); //imprime  =         
    }
     return;
}
 // monta a parte superior do topo da pagina para enfeitar, tudo baseado com o código ASCII
void Frescurastela()
{ 
         printf("%c", 24);//Imprime uma seta pra cima baseado na tabela ASCII!!!
    
				for (i=0;i<77;i++)
				{		
					printf("%c",61); //imprime  =         
                }
    	 printf("%c", 24);//Imprime uma seta pra cima no fim do FOR!!!
}
// monta a parte superior do topo da pagina para enfeitar, tudo baseado com o código ASCII
void Frescuracadcli()
{  
     printf("\t\t\t");
			for (i=0;i<30;i++)
			{
                printf("%c",95); //imprime     _      
            }
	 printf("\n\n");
}
// É a função do cabeçalho apenas para fazer toda a firula mencionada a cima deixando mais simpatico!!!
void Enfeite()
{
	Frescurastela();
    	printf("\n%c\t\t\t  Relatorios\t\t\t\t\t      %c\n",24, 24);// Imprime o texto dando espaço igual aos demais textos, mais uma seta para cima para completar o quadrinho montado
	Frescurastela();
}

//MENSAGEM DE ACESSO NEGADO
void Proibido()
{
    clrscr();//limpa tela
    printf("Você não tem permissão para realizar esta ação!");
    getch();
    MenuCliente();
}

void MenuCliente()
{
    clrscr();//limpa tela
    int op;
    Enfeite();//Chama o embelezador do programa
    
    //LINHA EM BRANCO
    clearline();
    
    //CADASTRO
    printf("\t\t\t\t 1 - Clientes\n\n");
    Frescuracadcli();
    
	    
    printf("\t\t\t 2 - Funcionarios \n\n");
    Frescuracadcli();
    
    printf("\t\t\t 3 - Produtos \n\n");
    Frescuracadcli();

	printf("\t\t\t 4 - Fornecedores \n\n");
    Frescuracadcli();
    
    printf("\t\t\t 5 - Voltar \n\n");
    Frescuracadcli();
    
    
    
    scanf("%d", &op);
     switch(op){
        case 1: RelatorioCliente(); break;
        case 2: RelatorioFuncionario(); break;
		case 3: RelatorioProduto(); break;
		case 4: RelatorioFornecedor(); break;
		case 5: exit(1);
        
            /* REMOVIDO POIS ESTAVA CRIANDO DIVERSAS CHAMADAS PARA MENU 
			if(strcmp(role, "A") == 0)
              {
                  system ("Menu.exe A");
              } 
              
              if(strcmp(role, "S") == 0)
              {
                  system ("Menu.exe S");
              }
              
              if(strcmp(role, "V") == 0)
              {
                  system ("Menu.exe V");
              }
              */ 
             break;
      }
}
//funcao para visualizar cadastro 
void RelatorioCliente()
{
      //ABRE O ARQUIVO
      if((C = fopen("clientes.dat", "rb")) == NULL)
	  {
		clrscr();//limpa tela
           printf("Não há itens cadastrados!");
           getch();
           MenuCliente();
      }
     //Move o ponteiro para uma posição especifica no arquivo, aqui no caso vai para posição inicial 
     fseek(C, 0, 0); //PODERIA SER REWIND
     
     int cont = 0;//Contador
     int temp; // Contador temporario
     
     fflush(stdin);
     
     //Lê o arquivo e armazena no vetor Consulta
     clrscr();//limpa tela
     printf("VISUALIZAÇÃO DE CADASTRO CLIENTE\n\n");
     
     while(fread(&cli, sizeof(cli), 1, C))
	 {
         printf("ID: %s | ", cli.id_cliente);
         printf("Nome: %s \n", cli.nome);
         
         cont++;
     }
     fclose(C);//Fecha o arquivo
     
     printf("\n\nTotal de Clientes: %d", cont);
     getch();
     MenuCliente();
     
}

void RelatorioFuncionario()
{//funcao para visualizar cadastro
      //ABRE O ARQUIVO
      if((C = fopen("funcionarios.dat", "rb")) == NULL)
	  {
		clrscr();//limpa tela
           printf("Não há itens cadastrados!");
           getch();
           MenuCliente();
      }
     fseek(C, 0, 0); //Move o ponteiro para uma posição especifica no arquivo, aqui no caso vai para posição inicial
     
     int cont = 0;//Contador
     int temp; // Contador temporario
     
     fflush(stdin);
     
     //Lê o arquivo e armazena no vetor Consulta
     clrscr();//limpa tela
     printf("RELATORIOS DE FUNCIONARIOS\n\n");
     
     while(fread(&func, sizeof(func), 1, C))
	 {
         printf("ID: %s | ", func.id_funcionario);
         printf("Nome: %s \n", func.nome);
         
         cont++;
     }
     fclose(C);//Fecha o arquivo
     
     printf("\n\nTotal de Funcionarios: %d", cont);
     getch();
     MenuCliente();
     
}

void RelatorioProduto()
{//funcao para visualizar cadastro
      //ABRE O ARQUIVO
      if((C = fopen("produtos.dat", "rb")) == NULL)
	  {
		clrscr();//limpa tela
           printf("Não há itens cadastrados!");
           getch();
           MenuCliente();
      }
     fseek(C, 0, 0); //Move o ponteiro para uma posição especifica no arquivo, aqui no caso vai para posição inicial
     
     int cont = 0;//Contador
     int temp; // Contador temporario
     
     fflush(stdin);
     
     //Lê o arquivo e armazena no vetor Consulta
     clrscr();//limpa tela
     printf("RELATORIOS DE PRODUTOS\n\n");
     
     while(fread(&prod, sizeof(prod), 1, C))
	 {
         printf("ID: %s | ", prod.id_produto);
         printf("Nome: %s | ", prod.nome);
         printf("Preço: %.2f \n", prod.preco);
         
         cont++;
     }
     fclose(C);//Fecha o arquivo
     
     printf("\n\nTotal de Produtos: %d", cont);
     getch();
     MenuCliente();
     
}

void RelatorioFornecedor()
{//funcao para visualizar cadastro
      //ABRE O ARQUIVO
      if((C = fopen("fornecedores.dat", "rb")) == NULL)
	  {
		clrscr();//limpa tela
           printf("Não há itens cadastrados!");
           getch();
           MenuCliente();
      }
     fseek(C, 0, 0); //Move o ponteiro para uma posição especifica no arquivo, aqui no caso vai para posição inicial
     
     int cont = 0;//Contador
     int temp; // Contador temporario
     
     fflush(stdin);
     
     //Lê o arquivo e armazena no vetor Consulta
     clrscr();//limpa tela
     printf("RELATORIOS DE FORNECEDORES\n\n");
     
     while(fread(&forn, sizeof(forn), 1, C))
	 {
         printf("ID: %s | ", forn.id_fornecedor);
         printf("Nome: %s \n", forn.nome);
         
         cont++;
     }
     fclose(C);//Fecha o arquivo
     
     printf("\n\nTotal de Fornecedores: %d", cont);
     getch();
     MenuCliente();
     
}

int moveponteiro()
{//Função para mover a posição do ponteiro no arquivo
       fseek(C,PosFile*sizeof(cli),SEEK_CUR);//Move o ponteiro para uma posição especifica no arquivo no caso posição atual do arquivo
       fread(&cli, sizeof(cli), 1, C);/*Lê os elementos de contagem, cada um com um tamanho de bytes, 
       a partir do fluxo e armazena no bloco de memória especificado pelo ponteiro.*/
       fseek(C,PosFile*sizeof(cli),SEEK_SET);//Move o ponteiro para uma posição especifica no arquivo no caso posição inicial do arquivo
}    


//Função principal - após todas para evitar qualquer falha no compilador                          
int main(int argc, char * argv[])
{
    setlocale(LC_ALL,""); //Corrige acentuação definindo local (Região) 
    system("color FC");//Configuração da Cor Tela e fonte
    system("mode 80, 40");//Configuração de colunas e linhas do programa
    //VERIFICA SE ESTA LOGADO PARA EXECUTAR O PROGRAMA    
    if(argv[1] == NULL)
    {// SE NAO ESTIVER LOGADO
        clrscr();//limpa tela
        printf("Você precisa estar logado!");
        getch();
        exit(1);
    }
    //SE ESTIVER LOGADO
    else
    {
        strcpy(role,  argv[1]);
    }
    
    MenuCliente();//Chamada da função menu cliente
    
    getch();
    return 0;
}                         
                        
                           
