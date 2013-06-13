/*
  Nome: Cadastro de Fornecedores
  Copyright: By Albino IT Services
  Autores: Fernando Albino
  Data: 01/11/12 14:50 
  Descrição: Cadastro/Pesquisa/ Edição de Arquivos Cadastro de 

Clientes 
  
*/
// Declaração das bibliotecas a serem usadas / ou não pelo 

código!!!!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <conio2.h>//Essa ta mais pela honra de conseguir fazer 

funcionar do que por ser usada mesmo, mas é bem legal para enfeitar 

mais o programa 
#include <locale.h>//para ajustar a linguagem
#include <windows.h>

#define clrscr() (system("CLS")) //Definição para limpar a tela


//Declaração das funções 
void MenuForncedores(void);
void Submenu(void);
void GravaDados(void);
void Cadastro(void);
void VisualizarCadastro(void);
void MostraCadastro(int, int);
int moveponteiro (void);
char role[2];//VARIAVEL DE CHECAGEM

//Estrutura Fornecedores
struct fornecedores
{
       char id_fornecedor[50];
       char nome[50], endereco[30], cidade[30];
       char estado[3], cep[10], telefone[13], CNPJ[13], cargo[30], 

permissao[2];// A ou V ou S;
       char deletado;
}; 
struct fornecedores forn, consulta[99];

FILE *C; //ponteiro do arquivo
char getops;//Define a variavel de opção em mostrar cadastro seria 

usado para mover com , e. representando < >, mas não rolou ainda!!!
int i, PosFile = 0, deletado = 0;
char opDel;//variavel usada em opções do menu como teste de sim ou 

não!!!
int achou = -1;

//Função para imprimir linha vazia perfumaria só pra fazer graça!!
void clearline(void){
     for (i=0;i<80;i++)
   {
                printf("%c",32); //imprime  =         
     }
     return;
}

void Frescurastela()
{  // monta a parte superior do topo da pagina para enfeitar, tudo 

baseado com o código ASCII
         printf("%c", 24);//Imprime uma seta pra cima baseado na 

tabela ASCII!!!
    
			for (i=0;i<77;i++)
			{
                printf("%c",61); //imprime  =         
            }
    	 printf("%c", 24);//Imprime uma seta pra cima no fim do 

FOR!!!
}
// monta a parte superior do topo da pagina para enfeitar, tudo 

baseado com o código ASCII
void Frescuracadcli()
{  
     printf("\t\t\t");
				for (i=0;i<30;i++)
				{
                	printf("%c",95); //imprime     _      
                }
	 printf("\n\n");
}
// É a função do cabeçalho apenas para fazer toda a firula 

mencionada a cima deixando mais simpatico!!!
void Enfeite()
{
	Frescurastela();
		// Imprime o texto dando espaço igual aos demais 

textos, mais uma seta para cima para completar o quadrinho montado	
      	printf("\n%c\t\t\t  Cadastro de Fornecedores\t\t\t      %c

\n",24, 24);
	Frescurastela();
}

//MENSAGEM DE ACESSO NEGADO
void Proibido()
{
    clrscr();//limpa tela
    printf("Você não tem permissão para realizar esta ação!");
    getch();
    MenuForncedores();
}

void MenuForncedores()
{
    clrscr();//limpa tela
    int op;
    Enfeite();//Chama o embelezador do programa
    
    //LINHA EM BRANCO
    clearline();
    
    //MENU fornecedor
    printf("\t\t\t\t 1- Cadastrar novo Fornecedor\n\n");
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
        
            /* REMOVIDO POIS ESTAVA CRIANDO DIVERSAS CHAMADAS PARA 

MENU 
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
 
void VisualizarCadastro(){//funcao para visualizar cadastro
      //ABRE O ARQUIVO
      if((C = fopen("fornecedores.dat", "rb")) == NULL)
	  {
           clrscr();//limpa tela
           printf("ERRO: O arquivo nao pode ser aberto!");
           getch();
           exit(1);
      }
     fseek(C, 0, 0); //Move o ponteiro para uma posição especifica 

no arquivo, aqui no caso vai para posição inicial
     
     int cont = 0;//Contador
     int temp; // Contador temporario
     char busca[50]; // vaeriavel para o campo de busca
     
     fflush(stdin);
     
      printf ("Digite o código, nome ou documento: "); 
      gets(busca);
     
     //Lê o arquivo e armazena no vetor Consulta
     while(fread(&forn, sizeof(forn), 1, C))
	 {
         
         strcpy(consulta[cont].nome, forn.nome);
         strcpy(consulta[cont].endereco, forn.endereco);
         strcpy(consulta[cont].cidade, forn.cidade);
         strcpy(consulta[cont].estado, forn.estado);
         strcpy(consulta[cont].cep, forn.cep);
         strcpy(consulta[cont].telefone, forn.telefone);
         strcpy(consulta[cont].CNPJ, forn.CNPJ);
         
         
         consulta[cont].deletado = forn.deletado;

         cont++;
     }
     fclose(C);//Fecha o arquivo
     
    int id_resultado = -1;
     
     //LE O VETOR CONSULTA
     for(temp = 0; temp <= cont; temp++ )
     {
         // FAZ A COMPARACAO NOS CAMPOS, ID, NOME E DOC PARA VER SE 

ACHOU ALGO
         if(strcmp(busca,consulta[temp].id_fornecedor) == 0 || 

strcasecmp(busca,consulta[temp].nome) == 0 || strcmp

(busca,consulta[temp].CNPJ) == 0)
         {                                                     

//STRCASECMP PARA TIRAR O CASE     
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
             
            //LIMPA A FLAG, SENAO TODOS OS OUTROS EXIBIRAO COMO 

DELETADO!!
            deletado = 0;
            MenuForncedores(); 
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
    //CHECA AS PERMISSOES 
    if(strcmp(role, "A") ==0 || strcmp(role, "S") ==0 )
    {
      fclose(C);
      if((C = fopen("fornecedores.dat", "rb")) == NULL)
      {
           clrscr();
           printf("ERRO: O arquivo nao pode ser aberto!");
           exit(1);
      }
      fseek(C, PosFile, SEEK_SET);
      rewind(C);//Retorna para o inicio do arquivo
      
      while((!feof(C)) && achou == -1)
      {
            fread(&forn, sizeof(fornecedores), 1, C);
            if(!feof(C))
            {
                if(strcmp(forn.id_fornecedor,consulta

[Reg].id_fornecedor) == 0)
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
           if((C = fopen("fornecedores.dat", "rb+")) == NULL)
           {
                clrscr();
                printf("ERRO: ARQUIVO NAO PODE SER CRIADO \n");
                getch();
                exit(1);      
           }
           
           moveponteiro();// Chamada da função para mover ponteiro
           
           forn.deletado = 'D';// muda a flag do registro 
           
           if(fwrite(&forn, sizeof(forn),1, C)!=1)
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
    MenuForncedores();
    }
    else
    {
        Proibido();
    }
}

void EditarRegistro(int Reg, int cont)
{
    //CHECA AS PERMISSOES 
    if(strcmp(role, "A") ==0 || strcmp(role, "S") ==0 )
    {
        //Fecha o arquivo
	    fclose(C);
	    
        //Testa o arquivo
        if((C = fopen("fornecedores.dat", "rb")) == NULL)
        {
           clrscr();//limpa tela
           printf("ERRO: O arquivo nao pode ser aberto!");
           exit(1);
        }
        //Retorna para o inicio do arquivo
        rewind(C);
        
        //ENQUANTO NAO FOR O FINAL DO ARQUIVO OU achou == -1
        while((!feof(C)) && achou == -1)
        {
            /*Lê os elementos de contagem, cada um com um tamanho 

de bytes, 
            a partir do fluxo e armazena no bloco de memória 

especificado pelo ponteiro.*/
            fread(&forn, sizeof(fornecedores), 1, C);
            
            //SE NAO FOR O FINAL DO ARQUIVO
            if(!feof(C))
            {
                //VERIFICA SE OS REGISTROS SAO IGUAIS, SE SIM, SETA 

ACHOU como 1
                
                if(strcmp(forn.id_fornecedor,consulta

[Reg].id_fornecedor) == 0)
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
        
        if (achou==-1) 
        {
         PosFile = -1;
        }
        //Fecha o arquivo
        fclose(C);
       
        if(PosFile != -1) 
        {
           if((C = fopen("fornecedores.dat", "rb+")) == NULL)
           {    //limpa tela
                clrscr();
                printf("ERRO: ARQUIVO NAO PODE SER CRIADO \n");
                getch();
                exit(1);      
           }
           moveponteiro();
           
           clrscr();//limpa tela
           
           printf("Edição de Cadastro \n\n"); fflush(stdin);
           printf("Código: %s  \n\n", forn.id_fornecedor); fflush

(stdin);
           printf("Nome:"); fflush(stdin); gets(forn.nome);
           printf("Endereço:"); fflush(stdin); gets(forn.endereco);
           printf("Cidade:"); fflush(stdin); gets(forn.cidade);
           printf("Estado:"); fflush(stdin); gets(forn.estado);
           printf("Cep:"); fflush(stdin); gets(forn.cep);
           printf("Telefone:"); fflush(stdin); gets(forn.telefone);
           printf("CNPJ:"); fflush(stdin); gets(forn.CNPJ);
           
           
           if(fwrite(&forn, sizeof(forn),1, C)!=1) 
           {
              clrscr();
              printf("\nErro na gravação...");
              getch();
           }
           else
           {
              clrscr();
              printf("\nEdicao feita com sucesso...");
              getch();
           }
           fclose(C);
        }
        
        getch();
        MenuForncedores();
    }
    else
    {
        Proibido();
    }
}

void MostraCadastro(int Reg, int cont){
     
     
     clrscr();//limpa tela
     printf("VISUALIZAÇÃO DE CADASTRO FORNECEDOR\n\n");
     printf("Numero de ID: %s \n\n", consulta[Reg].id_fornecedor);
     printf("Nome: %s \n\n", consulta[Reg].nome);
     printf("CNPJ: %s \n\n", consulta[Reg].CNPJ);
     printf("Endereço: %s \n\n", consulta[Reg].endereco);
     printf("Cidade: %s \n\n", consulta[Reg].cidade);
     printf("Estado: %s \n\n", consulta[Reg].estado);
     printf("Cep: %s \n\n", consulta[Reg].cep);
     printf("Telefone: %s \n\n", consulta[Reg].telefone);
    
     //CHECA O TIPO DE PERMISSAO
     if(strcmp(role, "A") ==0 || strcmp(role, "S") ==0 )
     {
         printf("Digite d para deletar o registro. \n");
         printf("Digite e para editar o registro. \n");            
     }
     
     
     
     printf("Para voltar ao MENU digite qualquer tecla. \n\n");
     fflush(stdin);
     getops = getch();
     
     
     switch(getops)
	 {      //DELETAR
            case 'd':
                  fflush(stdin);
                  clrscr();
                  printf("Deseja DELETAR o registro? (S/N)");
                  opDel = getch();
                  //AGUARDA A OPCAO SER DIGITADA
                  if(opDel == 115 || opDel == 83)
                  {
                      //CHAMA A FUNCAO PARA DELETAR O CAFASTRO    
                      DeletarRegistro(Reg, cont);
                      
                  }   
                  MenuForncedores(); 
                  break;    
              
              //EDITAR
              case 'e':
                  fflush(stdin);
                  clrscr();//limpa tela
                  printf("Voce deseja EDITAR este registro? 

(S/N)");
                  opDel = getch();
                  //AGUARDA A OPCAO SER DIGITADA
                  if(opDel == 115 || opDel == 83)
                  {
                      //CHAMA A FUNCAO PARA EDITAR O CADASTRO     
                      EditarRegistro(Reg, cont);
                  }
                  MenuForncedores(); 
                  break;//chama menu fornecedor
              
          default:  
                    MenuForncedores(); 
					break;//força chamada menu 

fornecedor
     }
}
//FUNCAO RESPONSAVEL PELA GERACAO DO PROXIMO NUMERO DE ID
int ProximoRegistro()
{
    int retorno = 0;
    
     //CRIA O ARQUIVO .. NECESSARIO CASO O ARQUIVO NAO EXISTA
     if((C = fopen("fornecedores.dat", "ab")) == NULL)
     {
           clrscr();//limpa tela
           printf("ERRO: O arquivo nao pode ser aberto!");
           getch();
           exit(1);
     }
     //Fecha o arquivo
     fclose(C);
     
     //ABRE O ARQUIVO PARA LEITURA
      if((C = fopen("fornecedores.dat", "rb")) == NULL)
	  {
           clrscr();//limpa tela
           printf("ERRO: O arquivo nao pode ser aberto!");
           getch();
           exit(1);
      }

     //Move o ponteiro para uma posição especifica no arquivo, aqui 

no caso vai para posição inicial
     fseek(C, 0, 0); //PODIA SER REWIND
     
     //Lê o arquivo e armazena no vetor Consulta
     while(fread(&forn, sizeof(forn), 1, C)){
         retorno = atoi(forn.id_fornecedor); //RETORNO RECEBE A 

STRING CONVERTIDA PARA INT 
     }
     
     fclose(C);//Fecha o arquivo
     retorno = retorno + 1;//ICREMENTA O ID EM +1 APARTIR DOS DADOS 

LIDOS A CIMA
     
     //RETORNA
     return retorno;
}

// Função de cadastro
void Cadastro()
{
     if(strcmp(role, "A") ==0 || strcmp(role, "S") ==0 )
     {   //limpa tela 
         clrscr();
         Enfeite();//Chama o embelezador do programa
         //VARIAVEL PARA RECEBER FUNCAO GERADORA DE CÓDIGO
         int proximo = ProximoRegistro();//VALIDA ID
         char id[50];
         
         fflush(stdin);
         printf("\nNumero de ID: %d \n", proximo); fflush(stdin);
         //VALIDA ID
         itoa(proximo, id, 10);
         
         //ARMAZENA O NUMERO DO ID GERADO PARA SALVAR NO ARQUIVO 

JUNTO COM O RESTO DOS CADASTRO A SER DIGITADO     
         strcpy(forn.id_fornecedor, id);
         printf("Nome:"); fflush(stdin); gets(forn.nome);
         printf("CNPJ:"); fflush(stdin); gets(forn.CNPJ);
         printf("Endereco:"); fflush(stdin); gets(forn.endereco);
         printf("Cidade:"); fflush(stdin); gets(forn.cidade);
         printf("Estado:"); fflush(stdin);  gets(forn.estado);
         printf("Cep:"); fflush(stdin); gets(forn.cep);
         printf("Telefone:"); fflush(stdin); gets(forn.telefone);
         
        //CHECA AS INFORMACOES           
        printf ("\t\t\n Os dados estão corretos \n     Sim: S | 

Não: N\n");
        opDel = getch();//AGUARDA CONFIRMACAO
        
        if(opDel == 83)
        {
               Cadastro();//CHAMA FUNCAO CADASTRO
        }
        if (opDel == 115)
        { //115 = s e 83 = n na tabela ASCII
        GravaDados();//Chama função grava dados
        }
     }
     else
     {
        Proibido();//FUNCAO NEGA ACESSO DE ACORDO COM O 
     }
}


void GravaDados(){
     if((C = fopen("fornecedores.dat", "ab")) == NULL) {//Testa e 

abre o arquivo
           printf("ERRO: ARQUIVO NAO PODE SER CRIADO \n");
           exit(1);      
     }
     if(fseek(C, 0, 2) != 0){
            printf("erro no fseek");     
     }
     else{
            fwrite(&forn, sizeof(fornecedores),1,C);
            
     }
     fclose(C);//Fecha o arquivo
     
     MenuForncedores();
}

int moveponteiro()
{//Função para mover a posição do ponteiro no arquivo
	fseek(C,PosFile*sizeof(forn),SEEK_CUR);//Move o ponteiro 

para uma posição especifica no arquivo no caso posição atual do 

arquivo
	fread(&forn, sizeof(forn), 1, C);/*Lê os elementos de 

contagem, cada um com um tamanho de bytes, 
	a partir do fluxo e armazena no bloco de memória 

especificado pelo ponteiro.*/
	fseek(C,PosFile*sizeof(forn),SEEK_SET);//Move o ponteiro 

para uma posição especifica no arquivo no caso posição inicial do 

arquivo
}    


//Função principal - após todas para evitar qualuqer falha no 

compilador                          
int main(int argc, char * argv[]){//Função principal
    setlocale(LC_ALL,""); //Corrige acentuação definindo local 

(Região) 
    system("color F9");//Configuração da Cor Tela e fonte
    system("mode 80, 40");//Configuração de colunas e linhas do 

programa
    
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
    MenuForncedores();
    
    getch();
    return 0;
}                         
                        
                           
