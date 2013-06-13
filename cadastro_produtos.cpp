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
void MenuProduto(void);
void Submenu(void);
void GravaDados(void);
void Cadastro(void);
void VisualizarCadastro(void);
void MostraCadastro(int, int);
int moveponteiro (void);
char role[2];

//Estrutura Produto
struct produtos
{
       long int id_fornecedor;
       char id_produto[50];
       char nome[50], num_nota[30], data_compra[10], tipo_unidade[5];
       char deletado;
       float preco;
}; 

struct produtos prod, consulta[99];

FILE *C; //ponteiro do arquivo
char getops;//Define a variavel de opção em mostrar cadastro seria usado para mover com , e. representando < >, mas não rolou ainda!!!
int i, PosFile = 0, deletado = 0;
char opDel;//variavel usada em opções do menu como teste de sim ou não!!!
int achou = -1;// VARIAVEL DE PESQUISA SETADA COMO -1 (QUANDO NÃO ACHA NADA NAO MUDA E RETORNA)

//Função para imprimir linha vazia perfumaria só pra fazer graça!!
void clearline(void)
{
       		for (i=0;i<80;i++)
				{
                	printf("%c",32); //IMPRIME LINHA EM BRANCO         
                }
     return;
}

void Frescurastela()// monta a parte superior do topo da pagina para enfeitar, tudo baseado com o código ASCII
{  
         printf("%c", 24);//Imprime uma seta pra cima baseado na tabela ASCII!!!
    
				for (i=0;i<77;i++)
				{
                printf("%c",61); //imprime  =  (SIMBOLO DE IGUAL)       
                }
                
    	 printf("%c", 24);//Imprime uma seta pra cima no fim do FOR!!!
}

void Frescuracadcli()// monta a parte superior do topo da pagina para enfeitar, tudo baseado com o código ASCII
{  
     printf("\t\t\t");
				for (i=0;i<30;i++)
				{
                printf("%c",95); //imprime     _  (SIMBOLO DE UNDERLINE)     
                }
	 printf("\n\n");
}

void Enfeite()// É a função do cabeçalho apenas para fazer toda a firula mencionada a cima deixando mais simpatico!!!
{
Frescurastela();
    printf("\n%c\t\t\t  Cadastro de Produtos\t\t\t\t      %c\n",24, 24);// Imprime o texto dando espaço igual aos demais textos, mais uma seta para cima para completar o quadrinho montado
Frescurastela();
}

//MENSAGEM DE ACESSO NEGADO
void Proibido()
{
    clrscr();//LIMPA TELA
    printf("Você não tem permissão para realizar esta ação!");
    getch();
    MenuProduto();
}

void MenuProduto()
{
    clrscr();//LIMPA TELA//limpa tela
    int op;//variavel opcao menu
    Enfeite();//Chama o embelezador do programa
    
    //LINHA EM BRANCO
    clearline();
    
    //MENU 
    printf("\t\t\t\t 1- Cadastrar novo produto\n\n");
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
      if((C = fopen("produtos.dat", "rb")) == NULL){
           clrscr();//LIMPA TELA//limpa tela
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
    while(fread(&prod, sizeof(prod), 1, C))
	{
         
         strcpy(consulta[cont].id_produto, prod.id_produto);
         strcpy(consulta[cont].nome, prod.nome);
         strcpy(consulta[cont].data_compra, prod.data_compra);
         strcpy(consulta[cont].tipo_unidade, prod.tipo_unidade);
         strcpy(consulta[cont].num_nota, prod.num_nota);
         
         consulta[cont].deletado = prod.deletado;
		 consulta[cont].preco = prod.preco;
         cont++;
    }
    fclose(C);//Fecha o arquivo
     
     
    int id_resultado = -1;//SETA/INICIA ID RESULTADO COMO -1
     
     //LE O VETOR CONSULTA
     for(temp = 0; temp <= cont; temp++ )
     {
         // FAZ A COMPARACAO NOS CAMPOS, ID, NOME E DOC PARA VER SE ACHOU ALGO
         if(strcmp(busca,consulta[temp].id_produto) == 0 || strcasecmp(busca,consulta[temp].nome) == 0 || strcmp(busca,consulta[temp].data_compra) == 0)
         {
             printf("ACHOU\n\n");
             //SE ACHOU< VERIFICA SE O REGISTRO FOI DELETADO
             if(consulta[temp].deletado == 'D')
             {
                 //SETA FLAG DE DELETADO COMO 1 / TRUE (VERDADEIRO)                      
                 deletado = 1;                   
             }
             
             //ARMAZENA POSICAO DO VETOR DO REGISTRO
             id_resultado = temp;
         }
     }
     
     int regAtual = 0;
     int ultimoRegistro = cont;
          
     //printf ("%d, %s",&regAtual, &cont);  //////////teste/////////
     //getch();
     
     //SE ACHOU O REGISTRO
     if(id_resultado > -1)
     {
         //SE FOI DELETADO, EXIBE MENSAGEM E VOLTA PARA O MENU            
         if(deletado == 1)
         {
            clrscr();//LIMPA TELA
            printf("\nRegistro excluido!");
            getch();
             
            //LIMPA A FLAG, SENAO TODOS OS OUTROS EXIBIRAO COMO DELETADO!!
            deletado = 0;
            MenuProduto(); 
         }
         //SENAO MOSTRA O REGISTRO
         else
         {
             MostraCadastro(id_resultado,cont);
         }
         
     }
}
//FUNCAO DELETAR REGISTRO
void DeletarRegistro(int Reg, int cont)
{
    if(strcmp(role, "A") ==0 || strcmp(role, "S") ==0 )//VERIFICA PERMISSAO APENAS AMINISTRADOR E SUPRVISOR ACESSAO
    {
      fclose(C);
      if((C = fopen("produtos.dat", "rb")) == NULL)
      {
           clrscr();//LIMPA TELA
           printf("ERRO: O arquivo nao pode ser aberto!");
           exit(1);
      }
      /*SETA POSFILE NO INICIO DO ARQUIVO*/
      fseek(C, PosFile, SEEK_SET);
      //Retorna para o inicio do arquivo
      rewind(C);
      //ENQUANTO NAO FOR FINAL DO ARQUIVO E ACHOU DIFERENTE DE -1
      while((!feof(C)) && achou == -1)
      {
			//LE OS ELEMENTOS DA STRUCT CADA UM COM UM TAMNAHO DE BYTES A PARTIR DO ARQUIVO E OS ARMAZENA
            fread(&prod, sizeof(produtos), 1, C); 
            //SE FOR DIFERENTE DO FINAL DE ARQUIVO
			if(!feof(C))
            {	//SE COMPARA 
                if(strcmp(prod.id_produto,consulta[Reg].id_produto) == 0)
                {
                    achou = 1;                                     
                }
                else
                {
                    PosFile++;  //SENAO CONDICAO A CIMA NAO ATINGIDA  INCREMENTA POSFILE
                }
            }
            else
            {
                 PosFile =-1; //SENAO NAO ENCONTROU SETA POSFILE EM -1    
            } 
      }
      
      if (achou==-1)// SE NAO ACHOU NADA 
      {
         PosFile = -1;//SETA POSFILE 
      }
      
       fclose(C);//FECHA ARQUIVO
       //SE ACHOU ALGO 
       if(PosFile != -1)
       {
           if((C = fopen("produtos.dat", "rb+")) == NULL)
           {
                clrscr();//LIMPA TELA
                printf("ERRO: ARQUIVO NAO PODE SER CRIADO \n");
                getch();
                exit(1);      
           }
           
           moveponteiro();// Chamada da função para mover ponteiro
           
           prod.deletado = 'D';// muda a flag do registro 
           // SE ESCREVE NO ARQUIVO
           if(fwrite(&prod, sizeof(prod),1, C)!=1)
           {
              printf("\nErro na exclusao...");
              getch();
           }
           else
           {
              clrscr();//LIMPA TELA//LIMPA TELA
              printf("\nExclusao feita com sucesso...");
              getch();
           }
       }
       
       fclose(C);     
    
    
    getch();
    MenuProduto();
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
        if((C = fopen("produtos.dat", "rb")) == NULL)
        {
           clrscr();//LIMPA TELA//limpa tela
           printf("ERRO: O arquivo nao pode ser aberto!");
           exit(1);
        }
        
        rewind(C);//Retorna para o inicio do arquivo
        
        //ENQUANTO NAO FOR O FINAL DO ARQUIVO OU achou == -1
        while((!feof(C)) && achou == -1)
        {
            /*Lê os elementos de contagem, cada um com um tamanho de bytes, 
            a partir do fluxo e armazena no bloco de memória especificado pelo ponteiro.*/
            
            fread(&prod, sizeof(produtos), 1, C);
            
            //SE NAO FOR O FINAL DO ARQUIVO
            if(!feof(C))
            {
                //VERIFICA SE OS REGISTROS SAO IGUAIS, SE SIM, SETA ACHOU como 1
                if(strcmp(prod.id_produto,consulta[Reg].id_produto) == 0)
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
        // SE NAO ACHOU NADA
        if (achou==-1) 
        {
         PosFile = -1;
        }
        
        fclose(C);//Fecha o arquivo
        printf("\n%d", PosFile);
        printf("\n%d", achou);
        getch();
        //SE ACHOU 
        if(PosFile != -1) 
        {
           if((C = fopen("produtos.dat", "rb+")) == NULL)
           {
                clrscr();//LIMPA TELA
                printf("ERRO: ARQUIVO NAO PODE SER CRIADO \n");
                getch();
                exit(1);      
           }
           moveponteiro();
           
           clrscr();//LIMPA TELA
           
           printf("Edicao de Cadastro \n\n"); fflush(stdin);
           printf("Codigo: %s  \n\n", prod.id_produto); fflush(stdin);
           printf("ID Fornecedor:"); fflush(stdin); scanf("%i",&prod.id_fornecedor);
           printf("Nome:"); fflush(stdin); gets(prod.nome);
           printf("Data da Compra:"); fflush(stdin); gets(prod.data_compra);
           printf("Tipo da Unidade:"); fflush(stdin); gets(prod.tipo_unidade);
           printf("Preço:"); fflush(stdin); scanf("%f", &prod.preco);;
           printf("Número Nota Fiscal"); fflush(stdin); gets(prod.num_nota);
        
           
           if(fwrite(&prod, sizeof(prod),1, C)!=1) 
           {
              clrscr();//LIMPA TELA
              printf("\nErro na gravação...");
              getch();
           }
           else
           {
              clrscr();//LIMPA TELA
              printf("\nEdicao feita com sucesso...");
              getch();
           }
           fclose(C);
        }
        
        getch();
        MenuProduto();
    }
    else
    {
        Proibido();
    }
}

void MostraCadastro(int Reg, int cont){
     
     
     clrscr();//LIMPA TELA//limpa tela
     printf("VISUALIZAÇÃO DE CADASTRO PRODUTOS\n\n");
     printf("Numero de ID: %s \n\n", consulta[Reg].id_produto);
     printf("Numero de ID do Fornecedor: %d \n\n", consulta[Reg].id_fornecedor);
     printf("Nome: %s \n\n", consulta[Reg].nome);
     printf("Data da Compra: %s \n\n", consulta[Reg].data_compra);
     printf("Tipo da Unidade: %s \n\n", consulta[Reg].tipo_unidade);
     printf("Preco: %.2f \n\n", consulta[Reg].preco);
     printf("Número Nota Fiscal %s \n\n", consulta[Reg].num_nota);
     
     
     if(strcmp(role, "A") ==0 || strcmp(role, "S") ==0 )
     {
         printf("Digite d para deletar o registro. \n");
         printf("Digite e para editar o registro. \n");            
     }
     
     
     
     printf("Para voltar ao MENU digite qualquer tecla. \n\n");
     fflush(stdin);
     getops = getch();
     
     
     switch(getops){
            case 'd':
                 fflush(stdin);
                  clrscr();//LIMPA TELA
                  printf("Deseja DELETAR o registro? (S/N)");
                  opDel = getch();
                  
                  if(opDel == 115 || opDel == 83)
                  {
                      DeletarRegistro(Reg, cont);
                      
                  }   
                  MenuProduto(); 
                  break;    
              
              //EDITAR
              case 'e':
                  fflush(stdin);
                  clrscr();//LIMPA TELA//limpa tela
                  printf("Voce deseja EDITAR este registro? (S/N)");
                  opDel = getch();
                  
                  if(opDel == 115 || opDel == 83)
                  {
                      EditarRegistro(Reg, cont);
                  }
                  MenuProduto(); break;//chama menu produto
              
          default:  
                    MenuProduto(); break;//força chamada menucliente
     }
}

int ProximoRegistro()
{
    int retorno = 0;
    
    //CRIA O ARQUIVO
      if((C = fopen("produtos.dat", "ab")) == NULL){
           clrscr();//LIMPA TELA//limpa tela
           printf("ERRO: O arquivo nao pode ser aberto!");
           getch();
           exit(1);
     }
     fclose(C);//Fecha o arquivo
     
     //ABRE O ARQUIVO PARA LEITURA
      if((C = fopen("produtos.dat", "rb")) == NULL){
           clrscr();//LIMPA TELA//limpa tela
           printf("ERRO: O arquivo nao pode ser aberto!");
           getch();
           exit(1);
     }

     
     fseek(C, 0, 0); //Move o ponteiro para uma posição especifica no arquivo, aqui no caso vai para posição inicial
     
     //Lê o arquivo e armazena no vetor Consulta
     while(fread(&prod, sizeof(prod), 1, C)){
         retorno = atoi(prod.id_produto);
     }
     
     fclose(C);//Fecha o arquivo
     retorno = retorno + 1;
     
     
     return retorno;
}

void Cadastro(){// Função de cadastro
     if(strcmp(role, "A") ==0 || strcmp(role, "S") ==0 )
     {
         clrscr();//LIMPA TELA//limpa tela
         Enfeite();//Chama o embelezador do programa
         
         int proximo = ProximoRegistro();
         char id[50];
         
         fflush(stdin);
         printf("\nNumero de ID: %d \n", proximo); fflush(stdin);
         //VALIDA ID
         itoa(proximo, id, 10);//CONVERTE INTEIRO PARA STRING BASE DECIMAL
                  
         strcpy(prod.id_produto, id);
         printf("ID Fornecedor:"); fflush(stdin); scanf("%i",&prod.id_fornecedor);
         printf("Nome:"); fflush(stdin); gets(prod.nome);
         printf("Data da Compra:"); fflush(stdin); gets(prod.data_compra);
         printf("Tipo da Unidade:"); fflush(stdin);  gets(prod.tipo_unidade);
         printf("Preço:"); fflush(stdin);  scanf("%f", &prod.preco);
         printf("Número Nota Fiscal"); fflush(stdin); gets(prod.num_nota);
                
        printf ("\t\t\n Os dados estão corretos \n     Sim: S | Não: N\n");
        opDel = getch();
        //115 = s e 83 = n na tabela ASCII
        if(opDel == 83)
        {
               Cadastro();
        }
        if (opDel == 115)
        { 
        GravaDados();//Chama função grava dados
        }
     }
     else
     {
        Proibido();
     }
}


void GravaDados(){
     if((C = fopen("produtos.dat", "ab")) == NULL) {//Testa e abre o arquivo
           printf("ERRO: ARQUIVO NAO PODE SER CRIADO \n");
           exit(1);      
     }
     if(fseek(C, 0, 2) != 0){
            printf("erro no fseek");     
     }
     else{
            fwrite(&prod, sizeof(produtos),1,C);
            
     }
     fclose(C);//Fecha o arquivo
     
     MenuProduto();
}

int moveponteiro()//Função para mover a posição do ponteiro no arquivo
{
	fseek(C,PosFile*sizeof(prod),SEEK_CUR);//Move o ponteiro para uma posição especifica no arquivo no caso posição atual do arquivo
	fread(&prod, sizeof(prod), 1, C);/*Lê os elementos de contagem, cada um com um tamanho de bytes, 
	a partir do fluxo e armazena no bloco de memória especificado pelo ponteiro.*/
	fseek(C,PosFile*sizeof(prod),SEEK_SET);//Move o ponteiro para uma posição especifica no arquivo no caso posição inicial do arquivo
}    


//Função principal - após todas para evitar qualuqer falha no compilador                          
int main(int argc, char * argv[]){//Função principal
    setlocale(LC_ALL,""); //Corrige acentuação definindo local (Região) 
    system("color 9F");//Configuração da Cor Tela e fonte
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
    MenuProduto();
    
    getch();
    return 0;
}                         
                        
                           
