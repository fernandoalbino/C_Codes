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
void MenuCaixa(void);
void Submenu(void);
void GravaDados(void);
void Entrada(void);
void Saida(void);
void Caixa(void);
void VisualizarCadastro(void);
void MostraCaixa(int);
int moveponteiro (void);
char role[2];

//Estrutura Cleintes
struct caixa{
       char movimentacao;
       float preco;
       char obs[255], data[8];       
}; 

struct caixa cai, consulta[99];

FILE *C; //ponteiro do arquivo
char getops;//Define a variavel de opção em mostrar cadastro seria usado para mover com , e. representando < >, mas não rolou ainda!!!
int i, PosFile = 0, deletado = 0;
char opDel;//variavel usada em opções do menu como teste de sim ou não!!!
int achou = -1;
float total_final_caixa = 0.00;
int total_itens_caixa = 0;
 

//Função para imprimir linha vazia perfumaria só pra fazer graça!!
void clearline(void){
     for (i=0;i<80;i++){
                printf("%c",32); //imprime  =         
                }
     return;
}

void Frescurastela(){  // monta a parte superior do topo da pagina para enfeitar, tudo baseado com o código ASCII
         printf("%c", 24);//Imprime uma seta pra cima baseado na tabela ASCII!!!
    
for (i=0;i<77;i++){
                printf("%c",61); //imprime  =         
                }
    printf("%c", 24);//Imprime uma seta pra cima no fim do FOR!!!
}

void Frescuracadcli(){  // monta a parte superior do topo da pagina para enfeitar, tudo baseado com o código ASCII
     printf("\t\t\t");
for (i=0;i<30;i++){
                printf("%c",95); //imprime     _      
                }printf("\n\n");
}
void Enfeite(){// É a função do cabeçalho apenas para fazer toda a firula mencionada a cima deixando mais simpatico!!!
Frescurastela();
    printf("\n%c\t\t\t\t  Caixa\t\t\t\t\t      %c\n",24, 24);// Imprime o texto dando espaço igual aos demais textos, mais uma seta para cima para completar o quadrinho montado
Frescurastela();
}

//MENSAGEM DE ACESSO NEGADO
void Proibido()
{
    clrscr();//limpa tela
    printf("Você não tem permissão para realizar esta ação!");
    getch();
    MenuCaixa();
}

void MenuCaixa(){
    clrscr();//limpa tela
    int op;
    Enfeite();//Chama o embelezador do programa
    
    //LINHA EM BRANCO
    clearline();
    
    //CADASTRO
    printf("\t\t\t\t 1- Entrada\n\n");
    Frescuracadcli();
        
    printf("\t\t\t 2- Saida \n\n");
    Frescuracadcli();
    
    printf("\t\t\t 3- Fluxo de Caixa\n\n");
    Frescuracadcli();
    
    printf("\t\t\t 4- Voltar\n\n");
    Frescuracadcli();
    
    scanf("%d", &op);
     switch(op){
        case 1: Entrada(); break;
        case 2: Saida(); break;
        case 3: Caixa(); break;
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

void MostraCaixa(int Total){
     
     
     clrscr();//limpa tela
     printf("VISUALIZAÇÃO DE FLUXO DE CAIXA\n\n");
     
     int cont = 0;
     
     printf("PRODUTO | MOVIMENTACAO | QUANTIDADE | DATA |  OBS\n\n");
     
     for(cont = 0; cont < total_itens_caixa; cont++)
     {
         
         if(consulta[cont].movimentacao == 'E')
         {
             printf("%s   |  ", "Entrada");
         }
         else
         {
             printf("%s  |  ", "Saida");
         }
                 
         printf("%.2f  |  ", consulta[cont].preco);
         printf("%s  |  ", consulta[cont].data);
         printf("%s  |  \n", consulta[cont].obs);
     }
     
     printf("\n\n");
     printf("Total em caixa: %.2f \n\n\n", total_final_caixa);
     
     
     printf("Para voltar ao MENU digite qualquer tecla. \n\n");
     getch();
     MenuCaixa();
}

// Função de Compra
void Entrada()
{
     if(strcmp(role, "A") ==0 || strcmp(role, "S") ==0 )
     {
         clrscr();//limpa tela
         Enfeite();//Chama o embelezador do programa

         cai.movimentacao = 'E';
         printf("Data:"); fflush(stdin); gets(cai.data);
         printf("Preço:"); fflush(stdin); scanf("%f", &cai.preco);
         printf("Observacoes:"); fflush(stdin); gets(cai.obs);
         
        //CHECA AS INFORMACOES           
        printf ("\t\t\n Os dados estão corretos \n     Sim: S | Não: N\n");
        opDel = getch();//AGUARDA CONFIRMACAO
        
        if(opDel == 83)
        {
               Entrada();
        }
        if (opDel == 115)
        { //115 = s e 83 = n na tabela ASCII
        GravaDados();//Chama função grava dados
        }
     }
     else
     {
        Proibido();
     }
}

// Função de Venda
void Saida()
{
     if(strcmp(role, "A") ==0 || strcmp(role, "S") ==0 )
     {
         clrscr();//limpa tela
         Enfeite();//Chama o embelezador do programa
         
         cai.movimentacao = 'S';
         printf("Data:"); fflush(stdin); gets(cai.data);
         printf("Preço:"); fflush(stdin); scanf("%f", &cai.preco);
         printf("Observacoes:"); fflush(stdin); gets(cai.obs);
         
        //CHECA AS INFORMACOES           
        printf ("\t\t\n Os dados estão corretos \n     Sim: S | Não: N\n");
        opDel = getch();//AGUARDA CONFIRMACAO
        
        if(opDel == 83)
        {
               Entrada();
        }
        if (opDel == 115)
        { //115 = s e 83 = n na tabela ASCII
        GravaDados();//Chama função grava dados
        }
     }
     else
     {
        Proibido();
     }
}


// Função de Caixa
void Caixa()
{
     //ABRE O ARQUIVO
      if((C = fopen("caixa.dat", "rb")) == NULL){
           clrscr();//limpa tela
           printf("Não há nenhuma entrada cadastrada!");
           getch();
           MenuCaixa();
     }
     fseek(C, 0, 0); //Move o ponteiro para uma posição especifica no arquivo, aqui no caso vai para posição inicial
     
     int cont = 0;//Contador
     int temp = 0; // Contador temporario
     
     //Lê o arquivo e armazena no vetor apenas os registros com o id igual a busca!
     while(fread(&cai, sizeof(caixa), 1, C)){

		strcpy(consulta[cont].obs, cai.obs);
		strcpy(consulta[cont].data, cai.data);
		consulta[cont].movimentacao = cai.movimentacao;
		consulta[cont].preco = cai.preco;
		
		
		printf("%.2f", cai.preco);
		getch();
		total_itens_caixa++;
		cont++;     
         
     }
     fclose(C);//Fecha o arquivo
     
     //FAZ A SOMA DO ESTOQUE FINAL
     for(temp = 0; temp < cont; temp++)
     {
         if(consulta[temp].movimentacao == 'E')
         {
             total_final_caixa += consulta[temp].preco;
         }
         else
         {
             total_final_caixa -= consulta[temp].preco;
         }
         
     }
     
     //MONTA A TELA DE VISUALIZACAO
     MostraCaixa(total_final_caixa);
}

void GravaDados(){
     if((C = fopen("caixa.dat", "ab")) == NULL) {//Testa e abre o arquivo
           printf("ERRO: ARQUIVO NAO PODE SER CRIADO \n");
           exit(1);      
     }
     if(fseek(C, 0, 2) != 0){
            printf("erro no fseek");     
     }
     else{
            fwrite(&cai, sizeof(caixa),1,C);
            
     }
     fclose(C);//Fecha o arquivo
     
     MenuCaixa();
}
//Função para mover a posição do ponteiro no arquivo
int moveponteiro()
{
	fseek(C,PosFile*sizeof(cai),SEEK_CUR);//Move o ponteiro para uma posição especifica no arquivo no caso posição atual do arquivo
	fread(&cai, sizeof(cai), 1, C);/*Lê os elementos de contagem, cada um com um tamanho de bytes, 
	a partir do fluxo e armazena no bloco de memória especificado pelo ponteiro.*/
	fseek(C,PosFile*sizeof(cai),SEEK_SET);//Move o ponteiro para uma posição especifica no arquivo no caso posição inicial do arquivo
                           }    


//Função principal - após todas para evitar qualuqer falha no compilador                          
int main(int argc, char * argv[]){//Função principal
    setlocale(LC_ALL,""); //Corrige acentuação definindo local (Região) 
    system("color F8");//Configuração da Cor Tela e fonte
    system("mode 80, 40");//Configuração de colunas e linhas do programa

    //strcpy(role,  "A");   //PARA ABRIR SEM LOGAR COMENTE O IF E O ELSE E DESCOMENTE ISSO
    
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
    
    
    MenuCaixa();//Chamada da função menu funcionario
    
    getch();
    return 0;
}                         
                        
                           
