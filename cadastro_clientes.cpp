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
void VisualizarCadastro(void);
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

void Frescurastela()
{  // monta a parte superior do topo da pagina para enfeitar, tudo baseado com o código ASCII
         printf("%c", 24);//Imprime uma seta pra cima baseado na tabela ASCII!!!
    
				for (i=0;i<77;i++)
				{		
					printf("%c",61); //imprime  =         
                }
    	 printf("%c", 24);//Imprime uma seta pra cima no fim do FOR!!!
}

void Frescuracadcli()// monta a parte superior do topo da pagina para enfeitar, tudo baseado com o código ASCII
{  
     printf("\t\t\t");
			for (i=0;i<30;i++)
			{
                printf("%c",95); //imprime     _      
            }
	 printf("\n\n");
}
void Enfeite()
{// É a função do cabeçalho apenas para fazer toda a firula mencionada a cima deixando mais simpatico!!!
	Frescurastela();
    	printf("\n%c\t\t\t  Cadastro de Clientes\t\t\t\t      %c\n",24, 24);// Imprime o texto dando espaço igual aos demais textos, mais uma seta para cima para completar o quadrinho montado
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
    printf("\t\t\t\t 1- Cadastrar novo cliente\n\n");
    Frescuracadcli();
        
    printf("\t\t\t 2- Visualizar/Editar cadastro \n\n");
    Frescuracadcli();
    
    printf("\t\t\t 3- Voltar ao menu principal\n\n");
    Frescuracadcli();
    
    
    scanf("%d", &op);
     switch(op){
        case 1: Cadastro(); break;
        case 2: VisualizarCadastro(); break;
        case 3: exit(1);
        
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
void VisualizarCadastro()
{
      //ABRE O ARQUIVO
      if((C = fopen("clientes.dat", "rb")) == NULL)
	  {
		clrscr();//limpa tela
           printf("ERRO: O arquivo nao pode ser aberto!");
           getch();
           exit(1);
      }
     fseek(C, 0, 0); //Move o ponteiro para uma posição especifica no arquivo, aqui no caso vai para posição inicial
     
     int cont = 0;//Contador
     int temp; // Contador temporario
     char busca[50]; // vaeriavel para o campo de busca
     
     fflush(stdin);
     
      printf ("Digite o código, nome ou documento: "); 
      gets(busca);
     
     //Lê o arquivo e armazena no vetor Consulta
     
     while(fread(&cli, sizeof(cli), 1, C))
	 {
         
         strcpy(consulta[cont].id_cliente, cli.id_cliente);
         strcpy(consulta[cont].nome, cli.nome);
         strcpy(consulta[cont].data_nascimento, cli.data_nascimento);
         strcpy(consulta[cont].endereco, cli.endereco);
         strcpy(consulta[cont].cidade, cli.cidade);
         strcpy(consulta[cont].estado, cli.estado);
         strcpy(consulta[cont].cep, cli.cep);
         strcpy(consulta[cont].telefone, cli.telefone);
         strcpy(consulta[cont].Doc, cli.Doc);
         
         consulta[cont].deletado = cli.deletado;

         cont++;
     }
     fclose(C);//Fecha o arquivo
     
     
     int id_resultado = -1;
     
     //LE O VETOR CONSULTA
     for(temp = 0; temp <= cont; temp++ )
     {
         // FAZ A COMPARACAO NOS CAMPOS, ID, NOME E DOC PARA VER SE ACHOU ALGO
         if(strcmp(busca,consulta[temp].id_cliente) == 0 || strcasecmp(busca,consulta[temp].nome) == 0 || strcmp(busca,consulta[temp].Doc) == 0)
         {
             printf("ACHOU\n\n");
             //SE ACHOU< VERIFICA SE O REGISTRO FOI DELETADO
             if(consulta[temp].deletado == 'D')
             {
                 //SETA FLAG DE DELETADO COMO 1 / TRUE                       
                 deletado = 1;                   
             }
             
             //ARMAZENA POSICAO DO VETOR DO REGISTRO
             id_resultado = temp;
         }
     }
     
     int regAtual = 0;
     int ultimoRegistro = cont;
     char menu;
     
	 //SE ACHOU O REGISTRO
     if(id_resultado > -1)
     {
         //SE FOI DELETADO, EXIBE MENSAGEM E VOLTA PARA O MENU            
         if(deletado == 1)
         {
            clrscr();
            printf("\nRegistro excluido!");
            getch();
             
            //LIMPA A FLAG, SENAO TODOS OS OUTROS EXIBIRAO COMO DELETADO!!
            deletado = 0;
            MenuCliente(); 
         }
         //SENAO MOSTRA O REGISTRO
         else
         {
             MostraCadastro(id_resultado,cont);
         }
         
     }
}

void DeletarRegistro(int Reg, int cont)
{
    if(strcmp(role, "A") ==0 || strcmp(role, "S") ==0 )
    {
      if((C = fopen("clientes.dat", "rb")) == NULL)
      {
           clrscr();
           printf("ERRO: O arquivo nao pode ser aberto!");
           exit(1);
      }
      fseek(C, PosFile, SEEK_SET);
      rewind(C);//Retorna para ao inicio do arquivo
      
      while((!feof(C)) && achou == -1)
      {
            fread(&cli, sizeof(clientes), 1, C);
            if(!feof(C))
            {
                if(strcmp(cli.id_cliente,consulta[Reg].id_cliente) == 0)
                {
                    achou = 1;                                     
                }
                else
                {
                    PosFile++;    
                }
            }
            else
            {
                 PosFile =-1;    
            } 
      }
      
      if (achou==-1)
      {
         PosFile = -1;
      }
      
       fclose(C);
      
       if(PosFile != -1)
       {
           if((C = fopen("clientes.dat", "rb+")) == NULL)
           {
                clrscr();
                printf("ERRO: ARQUIVO NAO PODE SER CRIADO \n");
                getch();
                exit(1);      
           }
           
           moveponteiro();// Chamada da função para mover ponteiro
           
           cli.deletado = 'D';// muda a flag do registro 
           
           if(fwrite(&cli, sizeof(cli),1, C)!=1)
           {
              printf("\nErro na exclusao...");
              getch();
           }
           else
           {
              clrscr();
              printf("\nExclusao feita com sucesso...");
              getch();
           }
       }
       
       fclose(C);     
    
    
    getch();
    MenuCliente();
    }
    else
    {
        Proibido();
    }
}

void EditarRegistro(int Reg, int cont)
{
    if(strcmp(role, "A") ==0 || strcmp(role, "S") ==0 )
    {
        fclose(C);//Fecha o arquivo
        //Testa o arquivo
        if((C = fopen("clientes.dat", "rb")) == NULL)
        {
           clrscr();//limpa tela
           printf("ERRO: O arquivo nao pode ser aberto!");
           exit(1);
        }
        
        rewind(C);//Retorna para o inicio do arquivo
        
        //ENQUANTO NAO FOR O FINAL DO ARQUIVO OU achou == -1
        while((!feof(C)) && achou == -1)
        {
            /*Lê os elementos de contagem, cada um com um tamanho de bytes, 
            a partir do fluxo e armazena no bloco de memória especificado pelo ponteiro.*/
            
            fread(&cli, sizeof(clientes), 1, C);
            
            //SE NAO FOR O FINAL DO ARQUIVO
            if(!feof(C))
            {
                //VERIFICA SE OS REGISTROS SAO IGUAIS, SE SIM, SETA ACHOU como 1
                
                if(strcmp(cli.id_cliente,consulta[Reg].id_cliente) == 0)
                {
                    achou = 1;                                     
                }
                //SENAO, ANDA O PONTEIRO
                else
                {
                    PosFile++;    
                }
            } 
        }
        
        if (achou==-1) //SE ACHOU = -1 NÃO ACHOU NADA NO ARQUIVO
        {
         PosFile = -1;// SETA POSICAO COMO -1 
        }
        
        fclose(C);//Fecha o arquivo
        getch();
        
        if(PosFile != -1) 
        {
           if((C = fopen("clientes.dat", "rb+")) == NULL)
           {
                clrscr();//limpa tela
                printf("ERRO: ARQUIVO NAO PODE SER CRIADO \n");
                getch();
                exit(1);      
           }
           moveponteiro();
           
           clrscr();//limpa tela
           
           printf("Edicao de Cadastro \n\n"); fflush(stdin);
           printf("Codigo: %s  \n\n", cli.id_cliente); fflush(stdin);
           printf("Nome:"); fflush(stdin); gets(cli.nome);
           printf("Data de Nascimento:"); fflush(stdin); gets(cli.data_nascimento);
           printf("Endereco:"); fflush(stdin); gets(cli.endereco);
           printf("Cidade:"); fflush(stdin); gets(cli.cidade);
           printf("Estado:"); fflush(stdin); gets(cli.estado);
           printf("Cep:"); fflush(stdin); gets(cli.cep);
           printf("Telefone:"); fflush(stdin); gets(cli.telefone);
           printf("Documento:"); fflush(stdin); gets(cli.Doc);
        
           
           if(fwrite(&cli, sizeof(cli),1, C)!=1) 
           {
              clrscr();
              printf("\nErro na gravação...");
              getch();
           }
           else
           {
              clrscr();
              printf("\nEdição feita com sucesso...");
              getch();
           }
           fclose(C);
        }
        
        getch();
        MenuCliente();
    }
    else
    {
        Proibido();// SENAO A PERMISSAO PARA EDITAR E SUPERVISOR OU ADMINISTRADOR CHAMA A FUNCAO DE MENSAGEM PROIBIDO
    }
}

void MostraCadastro(int Reg, int cont)// MOSTRA CADASTRO PESQUISADO
{
     clrscr();//limpa tela
     printf("VISUALIZAÇÃO DE CADASTRO CLIENTE\n\n");
     printf("Numero de ID: %s \n\n", consulta[Reg].id_cliente);
     printf("Numero de ID do funcionario: %s \n\n", consulta[Reg].id_funcionario);
     printf("Nome: %s \n\n", consulta[Reg].nome);
     printf("Data de Nascimento: %s \n\n", consulta[Reg].data_nascimento);
     printf("Documento: %s \n\n", consulta[Reg].Doc);
     printf("Endereco: %s \n\n", consulta[Reg].endereco);
     printf("Cidade: %s \n\n", consulta[Reg].cidade);
     printf("Estado: %s \n\n", consulta[Reg].estado);
     printf("Cep: %s \n\n", consulta[Reg].cep);
     printf("Telefone: %s \n\n", consulta[Reg].telefone);
    
     
     if(strcmp(role, "A") ==0 || strcmp(role, "S") ==0 )// SE AS PERMISSOES FOREM VALIDAS IMPRIME NA TELA
     {
         printf("Digite d para deletar o registro. \n");
         printf("Digite e para editar o registro. \n");            
     }
     
     
     
     printf("Para voltar ao MENU digite qualquer tecla. \n\n");
     fflush(stdin);
     getops = getch();
     
     
     switch(getops)
	 {
            case 'd':
                 fflush(stdin);
                  clrscr();
                  printf("Deseja DELETAR o registro? (S/N)");
                  opDel = getch();
                  
                  if(opDel == 115 || opDel == 83)
                  {
                      DeletarRegistro(Reg, cont);
                      
                  }   
                  MenuCliente(); 
                  break;    
              
              //EDITAR
              case 'e':
                  fflush(stdin);
                  clrscr();//limpa tela
                  printf("Voce deseja EDITAR este registro? (S/N)");
                  opDel = getch();
                  
                  if(opDel == 115 || opDel == 83)
                  {
                      EditarRegistro(Reg, cont);
                  }
                  MenuCliente(); break;//chama menu cliente
              
          default:  
                    MenuCliente(); break;//força chamada menucliente
     }
}

int ProximoRegistro()
{
    int retorno = 0;
    
    //CASO NÃO EXITA CRIA O ARQUIVO
    if((C = fopen("clientes.dat", "ab")) == NULL)
	{
           clrscr();//limpa tela
           printf("ERRO: O arquivo nao pode ser aberto!");
           getch();
           exit(1);
    }
     fclose(C);//Fecha o arquivo
     
     //ABRE O ARQUIVO PARA LEITURA
    if((C = fopen("clientes.dat", "rb")) == NULL)
	{
           clrscr();//limpa tela
           printf("ERRO: O arquivo nao pode ser aberto!");
           getch();
           exit(1);
    }

     
     fseek(C, 0, 0); //Move o ponteiro para uma posição especifica no arquivo, aqui no caso vai para posição inicial
     
     //Lê o arquivo e armazena no vetor Consulta
    while(fread(&cli, sizeof(cli), 1, C))
	{
         retorno = atoi(cli.id_cliente); //CONVERTE CHAR PARA INT PARA INCREMENTAR ID NO RETORNO 
    }
     
     fclose(C);//Fecha o arquivo
     retorno = retorno + 1;// INCREMENTA RETORNO APARTIR DO ULTIMO ID SALVO NO ARQUIVO
     
     
     return retorno;//RETORNA VALOR 
}

// Função de cadastro
void Cadastro()
{
     if(strcmp(role, "A") ==0 || strcmp(role, "S") ==0 )//VERIFICA PERMISSOES SOMENTE ADMIM E SUPERVISOR PODEM CADASTRAR
     {
         clrscr();//limpa tela
         Enfeite();//Chama o embelezador do programa
         
         int proximo = ProximoRegistro();
         char id[50];
         
         fflush(stdin);
         printf("\nNumero de ID: %d \n", proximo); fflush(stdin);
         //VALIDA ID
         itoa(proximo, id, 10);
         //ARMAZENA ID PARA GRAVACAO AO FINAL DO ARQUIVO
         strcpy(cli.id_cliente, id);
         printf("Nome:"); fflush(stdin); gets(cli.nome);
         printf("Data de Nascimento:"); fflush(stdin); gets(cli.data_nascimento);
         printf("Documento:"); fflush(stdin); gets(cli.Doc);
         printf("Endereco:"); fflush(stdin); gets(cli.endereco);
         printf("Cidade:"); fflush(stdin); gets(cli.cidade);
         printf("Estado:"); fflush(stdin);  gets(cli.estado);
         printf("Cep:"); fflush(stdin); gets(cli.cep);
         printf("Telefone:"); fflush(stdin); gets(cli.telefone);
        
        printf ("\t\t\n Os dados estão corretos \n     Sim: S | Não: N\n");
        opDel = getch();
        
        if(opDel == 83)
        {
               Cadastro();
        }
        if (opDel == 115)
        { //115 = s e 83 = n na tabela ASCII
        GravaDados();//Chama função grava dados
        }
     }
     else
     {
        Proibido();// SENAO CHAMA FUNCAO D
     }
}


void GravaDados(){
     if((C = fopen("clientes.dat", "ab")) == NULL) 
	 {//Testa e abre o arquivo
           printf("ERRO: ARQUIVO NAO PODE SER CRIADO \n");
           exit(1);      
     }
     if(fseek(C, 0, 2) != 0)
	 {
            printf("erro no fseek");     
     }
     else{
            fwrite(&cli, sizeof(clientes),1,C);
            
     }
     fclose(C);//Fecha o arquivo
     
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
    system("color cf");//Configuração da Cor Tela e fonte
    system("mode 80, 40");//Configuração de colunas e linhas do programa
    
    //VERIFICA SE ESTA LOGADO PARA EXECUTAR O PROGRAMA
    if(argv[1] == NULL)
    {// SE NAO ESTIVER LOGADO
        clrscr();//LIMPA TELA
        printf("Você precisa estar logado!");
        getch();
        exit(1);
    }
    //SE ESTIVER LOGADO
    else
    {
        strcpy(role,  argv[1]);
    }
    //CHAMA A FUNCAO
    MenuCliente();
    
    getch();
    return 0;
}                         
                        
                           
