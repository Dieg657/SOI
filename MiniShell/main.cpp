#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <string.h>

using namespace std;




void data(pid_t pid);
void mudar(char *comando1, char *comando2, char *buffer);
void listar(string argumentos);
void ps(pid_t pid);
void apagar(pid_t pid);
void pasta(pid_t pid);
void sair();

const char * ObtenhaParamentrosDeEntrada(vector<char*>entrada){
    entrada.erase(entrada.begin());
    string retorno = "";
    for(char * value:entrada)
        retorno += string(" ")+string(value);
    return retorno.c_str();
}

int main()
{
    pid_t pid;
    char entrada[500];
    do{

        *entrada = 0;
        cout<<"\n<MINI-SHELL>";
        scanf(" %[^\n]", entrada); // leitura do vetor entrada após um enter
        vector<char*>comandos;
        char* aux = strtok(entrada, " ");
        while(aux != 0){
            comandos.push_back(aux);
            aux = strtok(0, " ");
        }


        if(strcmp(comandos[0],"sair") == 0){
            sair();
        }

        if(strcmp(comandos[0],"hoje") == 0){
            pid = fork();
            data(pid);
        }else

        if(strcmp(comandos[0],"processo") == 0){
            pid = fork();
            ps(pid);
        }else

        if(strcmp(comandos[0],"listar") == 0){
            listar(ObtenhaParamentrosDeEntrada(comandos));
        }else

        if(strcmp(comandos[0],"apagar") == 0){
            pid = fork();
            apagar(pid);
        }else
        if(strcmp(comandos[0],"pasta") == 0){
            pid = fork();
            pasta(pid);
        }else{
            printf("Comando desconhecido\n");
        }

    }while(1);
    return  0;
}

void listar(string parametros){
    string comando = "ls";
    comando += string(" ")+ parametros;
    system(comando.c_str());
}

void data(pid_t pid){
    if(pid == 0)
    execlp("/bin/date", "date", 0);

}

void ps(pid_t pid){
    if(pid == 0)
    execlp("/bin/ps", "ps", 0);
}

void apagar(pid_t pid){
    if(pid == 0)
    execlp("/usr/bin/clear", "clear", 0);
}

void pasta(pid_t pid){
    if(pid == 0)
    execlp("/bin/pwd", "pwd", 0);
}

void sair() // função de saída
{
    exit(0);
}
