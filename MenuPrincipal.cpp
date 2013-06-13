/*
  Nome: Menu Principal
  Copyright: By Albino IT Services
  Autores: Fernando Albino RA: 6309036 
  Data: 01/11/12 14:50 
  Descrição: Cadastro/Pesquisa/ Edição de Arquivos Cadastro de Clientes 
  
*/

// Declaração das bibliotecas a serem usadas / ou não pelo código!!!!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <conio2.h>//Essa ta mais pela honra de conseguir fazer funcionar do que por ser usada mesmo, mas é bem legal para enfeitar mais o programa 
#include <locale.h>
#include <windows.h>

#define clrscr() (system("CLS")) //Definição para limpar a tela



//Declaração das funções que realmente importão!!!
void Menu(void);
void Login(void);
int cairfora(void); //para forçar saída
//Declaração das funções de firulas e enfeites do menu principal 
void Enfeite(void);
void Frescurastela(void);

//Declaração das funções abrir e fechar arquivo 
void abre_arq(void);
void fecha_arq(void);

//Estrutura Funcionario a ser usada na verificação das senhas
struct Funcionario
{
       char id_funcionario[50];
       char nome[50], data_nascimento[10], endereco[30], cidade[30];
       char estado[3], cep[10], telefone[13], Doc[13], senha[30], salario[30], cargo[30], permissao[2];// A ou V ou S;
       char deletado;
};

struct Funcionario Func; 

struct Logon
{
       char Nome[30];
       char Permissao; //A = Administrador /  S = Supervisor / U= Usuario
} log;


FILE *F; //ponteiro do arquivo
int i;//variavel global utilizada no no laço FOR da função de enfeite da tela
char role[2];

// função principal
int main()
{
      setlocale(LC_ALL,""); //Corrige acentuação definindo local (Região) 
      system("mode 80, 25"); // determina tamanho da tela colunas/linhas 
      system("color fc");// determina a cor fundo e texto do menu 
      
      
      
      Login();//chama a função de login!! OH!!!
           
      getch();//aguarda que sejá precionado uma tecla, pra falar a verdade nem sei se ta usando, mas gosto de para o programa em varios pontos para teste
}
// monta a parte superior do topo da pagina para enfeitar, tudo baseado com o código ASCII
void Frescurastela()
{  
         printf("%c", 24);//Imprime uma seta pra cima baseado na tabela ASCII!!!
    
    for (i=0;i<77;i++){
                printf("%c",61); //imprime           
                }
    printf("%c", 24);//Imprime uma seta pra cima no fim do FOR!!!
}

void Enfeite(){// Função do cabeçalho apenas para fazer toda a firula mencionada a cima deixando mais simpatico!!!
    
Frescurastela();
    printf("\n%c\t\t\tSistema de Controle de Salão                          %c\n",24, 24);// Imprime o texto dando espaço igual aos demais textos, mais uma seta para cima para completar o quadrinho montado
Frescurastela();
    
}

void Login()
{
     
     
    char senha[6] = "0000";//Define a senha do admistrador 
    char exit[4] = "0";
    char senhaentrada[90],s;//veriavel para armazenar a senha digitada e fazer a verificação
    int achou = 0; // Define achou = 0 utilizado na busca das senhas no arquivo de funcionários
    char vetor[8] = ""; // INICIA A STRING EM BRANCO, SENAO A VARIAVEL VETOR VAI FICAR COM SUJEIRA NOS ULTIMOS CARACTERES, DAI A SENHA NAO BATE NUNCA
  int i, controle;

    Enfeite();//chama a função enfeite montando todo o cabeçalho "Que lindo"
    printf("\n\n\t\t\t Digite a senha de acesso\n\n");
    printf("\n\n\t\t\t SENHA DE ADMINISTRADOR: 0000");
    printf("\n\n\t\t\t SENHA: ");//imprime o texto e aguarda a senha ser digitada
    
    //DESSE JEITO, ESTA TRAVANDO A SENHA OBRIGATORIAMENTE A TER 4 CARACTERES, SE TIVER MENOS OU MAIS, ELA VAI FORÇAR
    //O USUÁRIO A DIGITAR SEMPRE 4 CARACTERES
    // O USUARIO ESTA OBRIGADO A DIGITAR 4 CARACTERES
    // OBRIGATORIAMENTE 4 DIGITOS!
	for(i=0;i<4;i++)
	{
        fflush(stdin);            
		vetor[i]=getch();
		printf("*");
	} 	
	
    getch();
	strcpy(senhaentrada,vetor);
    
  
    if(strcmp(senha,senhaentrada) == 0)
	{//verifica se a senha é do administrador!!
        //LOGADO COM SUCESSO!   
        clrscr();//limpa a tela
        strcpy(role, "A");
        Menu();//chama o menu
        
    }
    else
    {//se não for a senha do adimistrador verifica as senhas dos funcionarios cadastrados no arquivo de funcionarios
         abre_arq();//Chama a função para abrir o arquivo
         rewind(F);//Retorna o ponteiro para o inicio do arquivo
        
          while((!feof(F)))// Faz a leitura do arquivo de funcionarios 
		  {
                fread(&Func, sizeof(Funcionario), 1, F);//Ler o bloco de dados de fluxo
                
                if(!feof(F))//Verifica se é diferente do final do arquivo
				{
                                   
                    if(strcmp(Func.senha,senhaentrada) == 0)// Compara as senhas dos funcionarios salvas no arquivo com a senha digitada  
                    {                        
                        if(Func.deletado != 'D')// Verifica se cadastro do funcionario foi deletado
                        {
                             achou = 1;
                             strcpy(role, Func.permissao); //Compara permissao
                        }
                        
                    }
                }
          }
       fecha_arq();//chama função para fechar o arquivo
       
       
       if(achou > 0 )//Faz a verificação se encontrou!!!
	   {
           clrscr();//Limpa a tela 
           Menu();//Chama a função menu
       }
       else//Caso não encontre uma senha compativel...
	   {
            clrscr();//limpa a tela
            Enfeite();//chama a função que monta o cabeçalho!
            printf("\n\n\t\t\t Senha Incorreta\n\n");//Imprime a mensagem se não houver senhas compativeis
            getch();//aguarda ser precionada alguma tecla
            clrscr();//Limpa a tela 
            main();//Chama a função principal 
       }
    }
}

void Menu()// Chama o Menu
{ 
  if(strcmp(role, "A") == 0)// Se permissao == a A abre executa como admin
  {
      system ("Menu.exe A"); 
  } 
  
  if(strcmp(role, "S") == 0)// Se permissao == a S abre executa como Suervisor
  {
      system ("Menu.exe S");
  }
  
  if(strcmp(role, "V") == 0)// Se permissao == a V abre executa como Vendedor
  {
      system ("Menu.exe V");
  }  
  
}
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
int cairfora(void)
{
    exit(1);
    return 0;
}
