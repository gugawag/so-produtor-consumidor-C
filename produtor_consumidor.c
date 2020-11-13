//
//  produtor_consumidor.c
//  
//
//  Created by Gustavo Wagner Diniz Mendes on 2/21/16.
//
//
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 10

typedef struct {
    int valor;
}item;

item buffer[BUFFER_SIZE];
int in = 0;
int out = 0;


//MAIN
int main(){
    
    item proximo_produzido;
    item proximo_consumido;
    int valor=1;
    
    pid_t pid=fork();
    if (pid<0){
        printf("Erro no fork!");
        return 1;
    }
    while (1) {
        if (pid>0) { //PRODUTOR
            fflush(stdout);
            printf("\n\n=== Produtor ===");
            /* produz um item e colocar em proximo_produzido */
            while (((in + 1) % BUFFER_SIZE) == out)
                ; /* buffer cheio. faz nada */
            proximo_produzido.valor=valor;
            buffer[in] = proximo_produzido;
            printf("\nProdutor: produzido item %d",valor++);
            in = (in + 1) % BUFFER_SIZE;
        }

        if (pid==0) { //CONSUMIDOR
            fflush(stdout);
            printf("\n\n=== Consumidor ===");
            while (in == out)
                ; /* faz nada */
            proximo_consumido = buffer[out];
            out = (out + 1) % BUFFER_SIZE;
            printf("\nConsumi item %d",proximo_consumido.valor);
            /* consome o item e coloca em proximo_consumido, depois incrementa o out */
        }
        
    }
}