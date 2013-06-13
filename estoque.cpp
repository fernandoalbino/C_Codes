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
void MenuEstoque(void);
void Submenu(void);
void GravaDados(void);
void Compra(void);
void Venda(void);
void Estoque(void);
void VisualizarCadastro(void);
void MostraEstoque(int);
int moveponteiro (void);
char role[2];

//Estrutura Cleintes
struct estoque{
       char id_produto[50], id_sequencial[50];
       char movimentacao;
       int quantidade;
       char obs[255], data[8];       
}; 

struct estoque est, consulta[99];

struct produto
{
       long int id_fornecedor;
       char id_produto[50];
       char nome[50], num_nota[30], data_compra[10], tipo_unidade[5];
       char deletado;
       float preco;
}; 

struct produto prod, consultap[99];

struct caixae{
       char movimentacao;
       float preco;
       char obs[255], data[8];       
}; 

struct caixae cai;

FILE *C; //ponteiro do arquivo
char getops;//Define a variavel de opção em mostrar cadastro seria usado para mover com , e. representando < >, mas não rolou ainda!!!
int i, PosFile = 0, deletado = 0;
char opDel;//variavel usada em opções do menu como teste de sim ou não!!!
int achou = -1;
int total_final_estoque = 0;
int total_itens_estoque = 0;

//Função para imprimir linha vazia perfumaria só pra fazer graça!!
void clearline(void)
{
     for (i=0;i<80;i++){
                printf("%c",32); //imprime  =         
                }
     return;
}
// monta a parte superior do topo da pagina para enfeitar, tudo baseado com o código ASCII
void Frescurastela()
{  
         printf("%c", 24);//Imprime uma seta pra cima baseado na tabela ASCII!!!
    
for (i=0;i<77;i++){
                printf("%c",61); //imprime  =         
                }
    printf("%c", 24);//Imprime uma seta pra cima no fim do FOR!!!
}
// monta a parte superior do topo da pagina para enfeitar, tudo baseado com o código ASCII
void Frescuracadcli()
{  
     printf("\t\t\t");
for (i=0;i<30;i++){
                printf("%c",95); //imprime     _      
                }printf("\n\n");
}
// É a função do cabeçalho apenas para fazer toda a firula mencionada a cima deixando mais simpatico!!!
void Enfeite()
{
Frescurastela();
    printf("\n%c\t\t\t  Controle de Estoque       \t\t\t      %c\n",24, 24);// Imprime o texto dando espaço igual aos demais textos, mais uma seta para cima para completar o quadrinho montado
Frescurastela();
}

//MENSAGEM DE ACESSO NEGADO
void Proibido()
{
    clrscr();//limpa tela
    printf("Você não tem permissão para realizar esta ação!");
    getch();
    MenuEstoque();
}

void MenuEstoque(){
    clrscr();//limpa tela
    int op;
    Enfeite();//Chama o embelezador do programa
    
    //LINHA EM BRANCO
    clearline();
    
    //CADASTRO
    printf("\t\t\t\t 1 - Compra\n\n");
    Frescuracadcli();
        
    printf("\t\t\t 2 - Venda \n\n");
    Frescuracadcli();
    
    printf("\t\t\t 3 - Estoque\n\n");
    Frescuracadcli();
    
    printf("\t\t\t 4 - Voltar\n\n");
    Frescuracadcli();
    
    scanf("%d", &op);
     switch(op){
        case 1: Compra(); break;
        case 2: Venda(); break;
        case 3: Estoque(); break;
        case 4: exit(1);
        
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

void MostraEstoque(int Total){
     
     
     clrscr();//limpa tela
     printf("VISUALIZAÇÃO DE PRODUTO EM ESTOQUE\n\n");
     
     int cont = 0;
     
     printf("PRODUTO | MOVIMENTACAO | QUANTIDADE | DATA |  OBS\n\n");
     
     for(cont = 0; cont < total_itens_estoque; cont++)
     {
         printf("%s | ", consulta[cont].id_produto);
         
         if(consulta[cont].movimentacao == 'E')
         {
             printf("%s  | ", "Entrada");
         }
         else
         {
             printf("%s  | ", "Saida");
         }
                 
         printf(" %i  |    ", consulta[cont].quantidade);
         printf(" %s  |    ", consulta[cont].data);
         printf(" %s  |  \n", consulta[cont].obs);
     }
     
     printf("\n\n");
     printf("Total em estoque: %d \n\n\n", total_final_estoque);
     
     
     printf("Para voltar ao MENU digite qualquer tecla. \n\n");
     getch();
     MenuEstoque();
     

}

//FUNCAO RESPONSAVEL PELA GERACAO DO PROXIMO NUMERO DE ID
int ProximoRegistro()
{
    int retorno = 0;
    
     //CRIA O ARQUIVO .. NECESSARIO CASO O ARQUIVO NAO EXISTA
     if((C = fopen("estoque.dat", "ab")) == NULL)
     {
           clrscr();//limpa tela
           printf("ERRO: O arquivo nao pode ser aberto!");
           getch();
           exit(1);
     }
     fclose(C);//Fecha o arquivo
     
     //ABRE O ARQUIVO PARA LEITURA
      if((C = fopen("estoque.dat", "rb")) == NULL){
           clrscr();//limpa tela
           printf("ERRO: O arquivo nao pode ser aberto!");
           getch();
           exit(1);
     }

     
     fseek(C, 0, 0); //Move o ponteiro para uma posição especifica no arquivo, aqui no caso vai para posição inicial
     
     //Lê o arquivo e armazena no vetor Consulta
     while(fread(&est, sizeof(est), 1, C)){
         retorno = atoi(est.id_produto); //RETORNO RECEBE A STRING CONVERTIDA PARA INT 
     }
     
     fclose(C);//Fecha o arquivo
     retorno = retorno + 1;//ICREMENTA O ID EM +1 APARTIR DOS DADOS LIDOS A CIMA
     
     //RETORNA
     return retorno;
}

// Função de Compra
void Compra()
{
     if(strcmp(role, "A") ==0 || strcmp(role, "S") ==0 )
     {
         clrscr();//limpa tela
         Enfeite();//Chama o embelezador do programa
         
         int proximo = ProximoRegistro();//VARIAVEL PARA RECEBER FUNCAO GERADORA DE CÓDIGO
         char id[50];
         
         fflush(stdin);
         printf("\nNumero de ID: %d \n", proximo); fflush(stdin);
         //VALIDA ID
         itoa(proximo, id, 10);
         
         //ARMAZENA O NUMERO DO ID GERADO PARA SALVAR NO ARQUIVO JUNTO COM O RESTO DOS CADASTRO A SER DIGITADO     
         strcpy(est.id_sequencial, id);
         printf("ID Produto:"); fflush(stdin); gets(est.id_produto);
         est.movimentacao = 'E';
         printf("Data:"); fflush(stdin); gets(est.data);
         printf("Quantidade:"); fflush(stdin); scanf("%d", &est.quantidade);
         printf("Observacoes:"); fflush(stdin); gets(est.obs);
         
        //CHECA AS INFORMACOES           
        printf ("\t\t\n Os dados estão corretos \n     Sim: S | Não: N\n");
        opDel = getch();//AGUARDA CONFIRMACAO
        
        if(opDel == 83)
        {
               Compra();
        }
        if (opDel == 115)
        { //115 = s e 83 = n na tabela ASCII
        	
        	//ABRE O ARQUIVO
		      if((C = fopen("produtos.dat", "rb")) == NULL){
		           clrscr();//limpa tela
		           printf("ERRO: O arquivo nao pode ser aberto!");
		           getch();
		           exit(1);
		     }
		     fseek(C, 0, 0);
		     
		     int cont = 0;
		     float total = 0;
		     
		     while(fread(&prod, sizeof(produto), 1, C)){
				if(strcmp(est.id_produto, prod.id_produto) == 0)
         		{
					strcpy(consultap[cont].id_produto, prod.id_produto);
		        	strcpy(consultap[cont].nome, prod.nome);
		         	strcpy(consultap[cont].data_compra, prod.data_compra);
		         	strcpy(consultap[cont].tipo_unidade, prod.tipo_unidade);
		         	strcpy(consultap[cont].num_nota, prod.num_nota);
		         
		         	consultap[cont].deletado = prod.deletado;
				 	consultap[cont].preco = prod.preco;
				 	
				 	
				 	printf("PRECO: %.2f \n", consultap[cont].preco);
				 	printf("QUANTIDADE: %d  |  ", est.quantidade);
		     		total = consultap[cont].preco * est.quantidade;
				 	
				 	printf("TOTAL: %.2f", total);
				 	getch();
		         	cont++;
				}
		         
		     }
		     fclose(C);//Fecha o arquivo
		     
		     
		     if(cont > 0)
		     {
					//ATUALIZA CAIXA
					cai.movimentacao = 'S';
					strcpy(cai.data, est.data);
					strcpy(cai.obs, est.obs);
					cai.preco = total;
			         
					if((C = fopen("caixa.dat", "ab")) == NULL) //Testa e abre o arquivo
					{
				           printf("ERRO: ARQUIVO NAO PODE SER CRIADO \n");
				           exit(1);      
				     }
				     if(fseek(C, 0, 2) != 0){
				            printf("erro no fseek");     
				     }
				     else{
				            fwrite(&cai, sizeof(caixae),1,C);
				            
				     }
				     fclose(C);//Fecha o arquivo
     
     				
     				
					GravaDados();
			 }
			 else
			 {
					clrscr();//limpa tela
				    printf("Produto inexistente, verifique o ID do produto!");
				    getch();
				    MenuEstoque();
			 }
		}     
    }
     else
     {         
        Proibido();
     }
}

// Função de Venda
void Venda()
{
     if(strcmp(role, "A") ==0 || strcmp(role, "S") ==0 ||strcmp(role, "V") ==0 )//CHECA PERMISSAO NO CASO TODOS PODEM VENDER
     {
         clrscr();//limpa tela
         Enfeite();//Chama o embelezador do programa
         
         int proximo = ProximoRegistro();//VARIAVEL PARA RECEBER FUNCAO GERADORA DE CÓDIGO
         char id[50];
         
         fflush(stdin);
         printf("\nNumero de ID: %d \n", proximo); fflush(stdin);
         //VALIDA ID
         itoa(proximo, id, 10);
         
         //ARMAZENA O NUMERO DO ID GERADO PARA SALVAR NO ARQUIVO JUNTO COM O RESTO DO CADASTRO A SER DIGITADO     
         strcpy(est.id_sequencial, id);
         printf("ID Produto:"); fflush(stdin); gets(est. id_produto);
         est.movimentacao = 'S';
         printf("Data:"); fflush(stdin); gets(est.data);
         printf("Quantidade:"); fflush(stdin); scanf("%d", &est.quantidade);
         printf("Observacoes:"); fflush(stdin); gets(est.obs);
         
        //CHECA AS INFORMACOES           
        printf ("\t\t\n Os dados estão corretos \n     Sim: S | Não: N\n");
        opDel = getch();//AGUARDA CONFIRMACAO
        
        if(opDel == 83)
        {
               Compra();
        }
        if (opDel == 115)
        { //115 = s e 83 = n na tabela ASCII
        	//ABRE O ARQUIVO
		      if((C = fopen("produtos.dat", "rb")) == NULL){
		           clrscr();//limpa tela
		           printf("ERRO: O arquivo nao pode ser aberto!");
		           getch();
		           exit(1);
		     }
		     fseek(C, 0, 0);
		     
		     int cont = 0;
		     float total = 0;
		     
		     while(fread(&prod, sizeof(produto), 1, C)){
				if(strcmp(est.id_produto, prod.id_produto) == 0)
         		{
					strcpy(consultap[cont].id_produto, prod.id_produto);
		        	strcpy(consultap[cont].nome, prod.nome);
		         	strcpy(consultap[cont].data_compra, prod.data_compra);
		         	strcpy(consultap[cont].tipo_unidade, prod.tipo_unidade);
		         	strcpy(consultap[cont].num_nota, prod.num_nota);
		         
		         	consultap[cont].deletado = prod.deletado;
				 	consultap[cont].preco = prod.preco;
				 	
				 	
				 	printf("PRECO: %.2f \n", consultap[cont].preco);
				 	printf("QUANTIDADE: %d   |  ", est.quantidade);
		     		total = consultap[cont].preco * est.quantidade;
				 	
				 	printf("TOTAL: %.2f", total);
				 	getch();
		         	cont++;
				}
		         
		     }
		     fclose(C);//Fecha o arquivo
		     
		     
		     if(cont > 0)
		     {
					//ATUALIZA CAIXA
					cai.movimentacao = 'E';
					strcpy(cai.data, est.data);
					strcpy(cai.obs, est.obs);
					cai.preco = total;
			         
					if((C = fopen("caixa.dat", "ab")) == NULL) //Testa e abre o arquivo
					{
				           printf("ERRO: ARQUIVO NAO PODE SER CRIADO \n");
				           exit(1);      
				     }
				     if(fseek(C, 0, 2) != 0){
				            printf("erro no fseek");     
				     }
				     else{
				            fwrite(&cai, sizeof(caixae),1,C);
				            
				     }
				     fclose(C);//Fecha o arquivo
     
     				
     				
					GravaDados();
			 }
			 else
			 {
					clrscr();//limpa tela
				    printf("Produto inexistente, verifique o ID do produto!");
				    getch();
				    MenuEstoque();
			 }
        }
     }
     else
     {
        Proibido();
     }
}


// Função de Estoque
void Estoque()
{
     //ABRE O ARQUIVO
      if((C = fopen("estoque.dat", "rb")) == NULL){
           clrscr();//limpa tela
           printf("ERRO: O arquivo nao pode ser aberto!");
           getch();
           exit(1);
     }
     fseek(C, 0, 0); //Move o ponteiro para uma posição especifica no arquivo, aqui no caso vai para posição inicial
     
     int cont = 0;//Contador
     int temp = 0; // Contador temporario
     char busca[50]; // vaeriavel para o campo de busca
     
     fflush(stdin);
     
     printf ("Digite o código do produto a ser buscado: "); 
     gets(busca);
     
     //Lê o arquivo e armazena no vetor apenas os registros com o id igual a busca!
     while(fread(&est, sizeof(estoque), 1, C)){
         
         if(strcmp(est.id_produto, busca) == 0 )
         {
              strcpy(consulta[cont].id_produto, est.id_produto);
              strcpy(consulta[cont].id_sequencial, est.id_sequencial);
              strcpy(consulta[cont].obs, est.obs);
              strcpy(consulta[cont].data, est.data);
              consulta[cont].movimentacao = est.movimentacao;
              consulta[cont].quantidade = est.quantidade;
              
              total_itens_estoque++;
              cont++;     
         }
         
         
     }
     fclose(C);//Fecha o arquivo
     
     //FAZ A SOMA DO ESTOQUE FINAL
     for(temp = 0; temp < cont; temp++)
     {
         if(consulta[temp].movimentacao == 'E')
         {
             total_final_estoque += consulta[temp].quantidade;
         }
         else
         {
             total_final_estoque -= consulta[temp].quantidade;
         }
         
     }
     
     //MONTA A TELA DE VISUALIZACAO
     MostraEstoque(total_final_estoque);
}

void GravaDados(){
     if((C = fopen("estoque.dat", "ab")) == NULL) //Testa e abre o arquivo
	 {
           printf("ERRO: ARQUIVO NAO PODE SER CRIADO \n");
           exit(1);      
     }
     //SE TESTA FSEEK
     if(fseek(C, 0, 2) != 0)
	 {
            printf("erro no fseek");     
     }
     //SENAO GRAVA NO ARQUIVO
     else
	 {
            fwrite(&est, sizeof(estoque),1,C);
            
     }
     fclose(C);//Fecha o arquivo
     
     MenuEstoque();
}

int moveponteiro(){//Função para mover a posição do ponteiro no arquivo
                           fseek(C,PosFile*sizeof(est),SEEK_CUR);//Move o ponteiro para uma posição especifica no arquivo no caso posição atual do arquivo
                           fread(&est, sizeof(est), 1, C);/*Lê os elementos de contagem, cada um com um tamanho de bytes, 
                            a partir do fluxo e armazena no bloco de memória especificado pelo ponteiro.*/
                           fseek(C,PosFile*sizeof(est),SEEK_SET);//Move o ponteiro para uma posição especifica no arquivo no caso posição inicial do arquivo
                           }    


//Função principal - após todas para evitar qualuqer falha no compilador                          
int main(int argc, char * argv[]){//Função principal
    setlocale(LC_ALL,""); //Corrige acentuação definindo local (Região) 
    system("color 8F");//Configuração da Cor Tela e fonte
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
    
    
    MenuEstoque();//Chamada da função menu funcionario
    
    getch();
    return 0;
}                         
                        
                   
