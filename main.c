#include "domino.h"

int main(){
    srand(time(NULL));
    int jogar = 1;
    int vez = 1;
    while(jogar){
        Lista* player1=criar();
        Lista* player2=criar();
        Lista* domino=criar();
        Lista* jogo=criar();
        int i, j;
        for(i=0; i<=6 ;i++){
           for(j=0; j<=i; j++)
                jogo=inserir(jogo, i, j);
        }

        for(i = 0; i < 7; i++){
            comprar(&jogo, &player1);
            comprar(&jogo, &player2);
        }
        i = jogo_jogado(jogo, player1, player2, domino, vez);
        system("pause");
        system("cls");
        if(i >= 1)
            printf("\n\nParabens! Voce ganhou!\n");
        else if(i <= -1)
            printf("\n\nVoce perdeu! Mais sorte na proxima!\n");
        else
            printf("\n\nEmpate!!\n");
        system("pause");
        system("cls");
        printf("Deseja jogar novamente?\n1.SIM\n2.NAO\n");
        scanf("%d", &jogar);
        jogar -= 2;
        vez = !vez;
    }
    return 0;
}
