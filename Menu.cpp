/*
  Nome: Menu
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



//Estrutura Funcionario a ser usada na verificação das senhas
struct Funcionario
{
       long int Identificacao;
       char Nome[30], Sobrenome[30], DataNascimento[10], Endereco[30], Cidade[30];
       char Estado[3], Cep[10], Telefone[13], Rg[13], Cpf[16], Funcao[3], Senha[10];
       char Deletado;
};

struct Funcionario Func; 

FILE *F; //ponteiro do arquivo
int i;//variavel global utilizada no no laço FOR da função de enfeite da tela

char role[2];

//Declaração das funções de firulas e enfeites do menu principal 
void Enfeite(void);
void Frescurastela(void);


int cairfora(void);

void Frescurastela()
{  // monta a parte superior do topo da pagina para enfeitar, tudo baseado com o código ASCII
         printf("%c", 24);//Imprime uma seta pra cima baseado na tabela ASCII!!!
    
      	for (i=0;i<77;i++)
			{
        		printf("%c",61); //imprime           
    		}
    	printf("%c", 24);//Imprime uma seta pra cima no fim do FOR!!!
   // printf("\n%c", 24);//Imprime uma seta pra cima no co!!!
     }

void Enfeite()
{// Função do cabeçalho apenas para fazer toda a firula mencionada a cima deixando mais simpatico!!!
    
Frescurastela();
    printf("\n%c\t\t\tSistema de Controle de Salão                          %c\n",24, 24);// Imprime o texto dando espaço igual aos demais textos, mais uma seta para cima para completar o quadrinho montado
Frescurastela();
    
}

 //Função menu principal 

//Função abre arquivo!!!          
void abre_arq()
{
          if((F = fopen("funcionarios.dat", "rb")) == NULL)//Se o arquivo não existir ou não puder ser aberto. Abre para leitura arquivo binário!!
        {
             clrscr();//limpa a tela
             printf("ERRO: O arquivo nao pode ser aberto!");//imprime caso o arquivo não possa ser aberto
             exit(1);/*Termina o processo normalmente, realizando a limpeza regular para terminar o programa.
              Comentario retirado do google para ficar melhor explicado*/
        }
}        
//Função fecha arquivo essa é bem frescura mesmo pq ficou maior que o comando em si!!
void fecha_arq()
{
fclose(F);
} 

//Função principal 
int main(int argc, char * argv[])
{  
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
    
        setlocale(LC_ALL,""); //Corrige acentuação definindo local (Região) 
        system("mode 80, 40"); // determina tamanho da tela colunas/linhas 
        system("color fc"); // Seta cor
      
             
           char op, sair;
           int i;
           do{
               clrscr();//Limpa tela!!
               Enfeite();//Chama a função para deixar o sistema Lindio!!!
                
                printf("\n\n\t\t\t 1 - Funcionários\n\n");//da qui... 
                printf("\t\t\t 2 - Clientes\n\n");
                printf("\t\t\t 3 - Fornecedores\n\n");
                printf("\t\t\t 4 - Produtos\n\n");
                printf("\t\t\t 5 - Estoque\n\n");
                printf("\t\t\t 6 - Caixa\n\n");
                printf("\t\t\t 7 - Relatório\n\n");//...até aqui imprime o que está escrito ;) deixando tudo alinhado "Que supimpa!!"
                printf("\t\t\t 8 - Logout\n\n");
                printf("\t\t\t 9 - PARA SAIR\n\n");
                
                printf("Digite uma opção ");
    
                op=getch();//op = a tecla da opção definida caso seja precionado alguma tecla diferente das acima ... vai para default
    
                switch(op){ //Vai para a opção selecionada com base nas opções impressas a cima VERIFICANDO O NIVEL DE PERMISSAO 
                           
                  case '1': 
                       if(strcmp(role, "A") ==0)
                       {
                           system("cadastro_funcionarios.exe A");
                       }
                           
                       if(strcmp(role, "S") ==0)
                       {
                           system("cadastro_funcionarios.exe S");
                       }
                       
                       if(strcmp(role, "V") ==0)
                       {
                           system("cadastro_funcionarios.exe V");
                       }
                       
                       break;//Chama o arquivo cadastro de Funcionários
                  
                  case '2': 
                       if(strcmp(role, "A") ==0)
                       {
                           system("cadastro_clientes.exe A");
                       }
                           
                       if(strcmp(role, "S") ==0)
                       {
                           system("cadastro_clientes.exe S");
                       }
                       
                       if(strcmp(role, "V") ==0)
                       {
                           system("cadastro_clientes.exe V");
                       }
                       
                       
                       break;//Chama o arquivo cadastro de Clientes
                  
                  case '3': 
                       if(strcmp(role, "A") ==0)
                       {
                           system("cadastro_fornecedores.exe A");
                       }
                           
                       if(strcmp(role, "S") ==0)
                       {
                           system("cadastro_fornecedores.exe S");
                       }
                       
                       if(strcmp(role, "V") ==0)
                       {
                           system("cadastro_fornecedores.exe V");
                       }
                       break;//Chama o arquivo cadastro de Fornecedores
                  
                  case '4': 
                       if(strcmp(role, "A") ==0)
                       {
                           system("cadastro_produtos.exe A");
                       }
                           
                       if(strcmp(role, "S") ==0)
                       {
                           system("cadastro_produtos.exe S");
                       }
                       
                       if(strcmp(role, "V") ==0)
                       {
                           system("cadastro_produtos.exe V");
                       }
                       
                       break;//Chama o arquivo cadastro de Produtos
                  case '5': 
                        if(strcmp(role, "A") ==0)
                       {
                           system("estoque.exe A");
                       }
                           
                       if(strcmp(role, "S") ==0)
                       {
                           system("estoque.exe S");
                       }
                       
                       if(strcmp(role, "V") ==0)
                       {
                           system("estoque.exe V");
                       }
                       break;//Chama o arquivo estoque
                  
                  case '6': 
                       if(strcmp(role, "A") ==0)
                       {
                           system("caixa.exe A");
                       }
                           
                       if(strcmp(role, "S") ==0)
                       {
                           system("caixa.exe S");
                       }
                       
                       if(strcmp(role, "V") ==0)
                       {
                           system("caixa.exe V");
                       } 
                       break;//Chama o arquivo caixa
                  
                  case '7': 
                       if(strcmp(role, "A") ==0)
                       {
                           system("relatorios.exe A");
                       }
                           
                       if(strcmp(role, "S") ==0)
                       {
                           system("relatorios.exe S");
                       }
                       
                       if(strcmp(role, "V") ==0)
                       {
                           system("relatorios.exe V");
                       }
                       break;//Chama o arquivo relatorio
                   
                  case '8':
                       if(strcmp(role, "A") ==0)
                       {
                           system("MenuPrincipal.exe A");
                       }
                           
                       if(strcmp(role, "S") ==0)
                       {
                           system("MenuPrincipal.exe S");
                       }
                       
                       if(strcmp(role, "V") ==0)
                       {
                           system("MenuPrincipal.exe V");
                       }
                       break;//Chama o arquivo menuprincipal tela de login
                 
                  case '9':
						cairfora();
						exit(1);
                        break;//Chama funcao sair
		 		  
				   default:
						 printf ("Opcao Invalida\n"); 
						 break;//Chama o arquivo cadastro de Funcionários
               }
              
              printf("Deseja continuar? S/N\n");//imprime caso seja clicado em uma opção invalida 
              sair=getch();// Aguarda o digito de S ou N !!
              if (sair=='n'){
                             cairfora();//força a saída que por algum motivo a chamada a baixo trava no laço 
                             exit(1);
                             }
          }while(sair!='n');// continua o DO enquanto a opção for diferente de n    
}

int cairfora(void){
 clrscr();
 Enfeite();
 
 printf("\t\t\t\t             ,:,:,,,                         \n");            
printf("\t\t               ,issr::,,,,:irssr:                     \n");           
printf("\t\t            ,rs:                :rr                    \n");          
printf("\t\t          ,sr,   ::i,::i:         :ss                  \n");          
printf("\t\t         r2   ,B2;: :, ,iGr   :52r: ,Br                 \n");         
printf("\t\t        Hs    B: , ,B@r  :B   @r,:,@B,s@                \n");         
printf("\t\t       5i     2s,,  ii,,sB,   Xi  :B@i s@                \n");        
printf("\t\t      rr       :;:::, ,i,      ir:    ,:Bs                \n");       
printf("\t\t      M                           ,:;:,  5,               \n");       
printf("\t\t     Si                              ,   :s                \n");      
printf("\t\t     B                       :rrrr2  s@   M                \n");      
printf("\t\t     @             :,  ,:rs5ss:, sB   :   B                \n");      
printf("\t\t     M,            ,, :5r,     ,Gs       ,H                 \n");     
printf("\t\t     i2                        ,         s;                \n");      
printf("\t\t      G                                  B                 \n");      
printf("\t\t      ,G                                9,                   \n");    
printf("\t\t       ,9                              2i                    \n");    
printf("\t\t        ,X,                          ,Si                    \n");     
printf("\t\t          ss,                      ,s2                       \n");    
printf("\t\t           ,ss:                  :ss,                        \n");    
printf("\t\t              issr:,     2    :ir:,                          \n");    
printf("\t\t                 ,irrri:r@B@B@s:                                \n"); 
printf("\t\t                       s9  @  ,rsss,                            \n"); 
printf("\t\t                     2B:   s:      :B@                          \n"); 
printf("\t\t                    @,      @ ,s@B@B@BS                        \n");  
printf("\t\t                  ,@   i2@B2@@s2r,  s,                         \n");  
printf("\t\t                  @B@B@B5i, :H                                 \n");  
printf("\t\t                   B  :      S                               \n\n");              
    printf ("\n\t\t\t ATÉ MAIS!!!\n\n");
system ("hasta.mp3");
exit(1);
return 0;
}
