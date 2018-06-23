#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;


void sair(int sig) // função de saída
{
    (void) signal(SIGINT, SIG_DFL);
}

void data(char *comando);
void mudar(char *comando1, char *comando2, char *buffer);
void listar(char *comando, char *buffer);

int main()
{
    int status;
    pid_t pid;
    char cwd[4096];
    char entrada[100];
    char comando1[100];
    char comando2[100];
    char comando3[100];
    int comandoBg;
    char *saida = "sair";


    (void) signal(SIGINT, sair); // interrupção do Mini-Shell



    do{ // execução Mini-Shell

        for(int i = 0; i < 100; i++) // inicia os vetores de char com \0, para preenchimento posterior
        {
            entrada[i] = '\0';
            comando1[i] = '\0';
            comando2[i] = '\0';
            comando3[i] = '\0';
        }

        cout<<"\n<MINI-SHELL>";

        scanf(" %[^\n]", entrada); // leitura do vetor entrada após um enter

        if(entrada[strlen(entrada)-1] == '&'){ // Indentificar entrada '&' no final da linha de comando
            comandoBg = 1;
            entrada[strlen(entrada)-2] = '\0';
        }

        for(int i = 0; i < strlen(entrada); i++)
        {
            if(entrada[i] == ' ')
            {

                entrada[i] = '\0'; // converte espaços para \0
                strcpy(comando1,entrada); // copia as informações da entrada para o comando1
                strcpy(comando2,entrada+i+1); // copia as informações da direita para o comando2
                printf("%s", comando2);
                for(int j = 0; j < strlen(comando2); j++){
                    if(comando2[j] == ' '){
                        comando2[j] = '\0';
                        strcpy(comando3, comando2+j+1); // copia as informações da direita para o comando3
                    }
                }
            }
        }


        strcpy(comando1,entrada);

        if (!strcmp (comando1, "exec")){ // compara o comando um com a função exec

            if(strcmp(comando2,saida)) // copia o conteúdo da saída para comando 2
            {

                pid = fork(); // cria o processo

                if(pid==0)
                {
                    if(strlen(comando3) == 0) // compara se o comando 3 possui argumentos
                    {
                        execlp(comando2,comando2,(void*)0,(void*)0);
                        exit(-1);
                    }
                    else
                    {
                        execlp(comando2,comando2,comando3,(void*)0);
                        exit(-1);
                    }
                }

                else

                {
                    if(wait(&status) != pid);
                    // finaliza o processo
                }

            }
        }

       listar(comando1, cwd);
       mudar(comando1, comando2, cwd);
    }while(strcmp(comando1,saida)); // condição de parada
    return  0;
}

void mudar(char *comando1, char *comando2, char *buffer){
    if(strcmp(comando1, "mudar") == 0){
        if(chdir(comando2) < 0){
            printf("Não foi possivel executar o comando!\n");
        }else{
            if (getcwd(buffer, 4096) == NULL)
                perror("Não foi possivel obter o diretorio");
        }
    }
}

void listar(char *comando, char *buffer){
    if(strcmp(comando, "pasta") == 0){
            if(getcwd(buffer,sizeof(buffer)) == NULL){
                printf("Não foi possivel executar o comando!\n");
            }
    }
}
