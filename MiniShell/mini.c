#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <stdio.h>
#include <signal.h>

#define max 100
int exec=0;
int back=0;

void clean(char * params, int fim)  //funÃ§Ã£o para limpar string de argumentos
{
    for(int i=0; i<fim; i++)
    {
        params[i]=0;
    }
}

int isola(char ** params, char * cadeia)    ///funcao para separar varios argumentos 
{                                           //na mesma linha onde encontrar espaÃ§os
    int v=0;
    for(int i=0; i<9;i++)clean(params[i],25);   //chama funcao para limpar lixos na matriz de 
    int i,j;                                    //argumentos

    for(i=0, j=0 ; i<max; i++, j++)         ///interage ate o final da linha de comando
    {
        if(cadeia[i]==' ')                  ///se durante a varredura da linha do comando 
         {                                  ///ele encontrar ' ', executa...
             j=-1;                          //
             v++;                           //
             if(v>=10)                      //suporta somente 10 argumentos                  
             {
                 return 0;                  //se passar, para de ler codigos
             }
             if(strcmp(params[0],"exec")==0)//se o primeiro argumento for == "exec"
             {                              //ativa uma flag global que usamos para 
                 clean(params[0],10);       //chamar o codigo e depois morrer
                exec=1;
                v--;
             }

         }
         else{
             params[v][j]=cadeia[i];      //a medida que interamos em i e j , o argumento na posicao v
         }                                //vai receber este texto
    }
    if(strcmp(params[v],"&")==0)          //se no ultimo argumento 
    {                                     //encontrar  '&' ativa uma flag 
        back=1;                           //para desativar o wait do processo filho
        v--;
    }
    v++;
    while(v<10)
    {
        params[v]=0;                     //adiciona 0 na posicao do argumento na matriz
        v++;
    }
    return 1;
}


void trataSignal(int sig);



 int main(){
	signal(SIGINT,trataSignal);
    pid_t pid;           ///variavel para guardar id de processo

    for(;;)        //loop de interaÃ§Ã£o com o shell
    {
            char * linha= malloc(sizeof(char)*100);   ///variavel para receber a linha de comando
            char ** argumentos=malloc(sizeof(char*)*10);///matriz para receber argumentos de chamada de sistema
            for(int i=0; i<10; i++)argumentos[i]=malloc(sizeof(char)*15); /// faz parte declaraÃ§Ã£o da matrizz 
                                                        //onde vai guardar os argumentos
            clean(linha,100); 


            printf("%s haaa  estou rodandoooo# ",get_current_dir_name());
            scanf(" %[^\n]s", linha);


            setbuf(stdin, NULL);

             if(isola(argumentos,linha)==1)
            {  
                      if(strcmp(argumentos[0],"sair")==0 || strcmp(argumentos[0],"exit")==0
					  	 || strcmp(argumentos[0], "EXIT")==0)
                      {
                          break;
                      }
                      else if(strcmp(argumentos[0],"cd")==0)
                      {
                            
                             chdir(argumentos[1]);
                      }
                      else if(exec==1)    ///se a flag de exec estivar ativa
                      {                   //ele pula para salto, uma label declarada um pouco ante 
                            goto SALTO;    //da chamada do execvp para ser executada e depois morta
                      }
                    else{
                        pid=fork();     //id do processo filho 
                        if(pid==0)      //
                        {
                            SALTO:
                            if(execvp(argumentos[0],argumentos)==-1){
                                printf("comando invalido\n");
                                exit(0);
                            }
						}else if(back==0){
                            waitpid(pid,0,0);
                        }
					}                            
            }
            else printf("quantidade de parametros invalidos");

    }
    printf("estou morrendo");
}
void trataSignal(int sig) {
	char c;
	signal(sig, SIG_IGN);
	printf("\nCtrl-C? [s/n]");
	c = getchar();
	if(c=='s' || c=='S')
		exit(0);
	else
		main();
}
