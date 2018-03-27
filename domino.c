#include "domino.h"

Lista* criar (void)
{
    return NULL;
}

Lista* inserir (Lista* lista, int elemA, int elemB)
{
    Lista* novo =(Lista*)malloc(sizeof(Lista));
    novo->ladoA = elemA;
    novo->ladoB = elemB;
    novo->next = lista;
    novo->prev = NULL;
    if (lista != NULL)
        lista->prev = novo;
    return novo;
}

Lista* inserir_fim(Lista* lista, int elemA, int elemB)
{
    Lista* novo = (Lista*)malloc(sizeof(Lista));
    novo->ladoA = elemA;
    novo->ladoB = elemB;
    novo->next = NULL;
    if(lista){
        Lista* aux = lista;
        while(aux->next)
            aux = aux->next;
        aux->next = novo;
        novo->prev = aux;
        return lista;
    }
    novo->prev = NULL;
    return novo;
}

void imprimir_para_frente (Lista *lista)
{
    Lista *v;
    int i;
    printf("\n");
    for (i = 1, v = lista; v != NULL; i++, v = v->next)
    {
        printf("Peca %d:\t%d | %d\n", i, v->ladoA, v->ladoB);
    }
}

void liberar (Lista *lista)
{
    while (lista != NULL)
    {
        Lista *aux = lista->next;
        free (lista);
        lista = aux;
    }
}

Lista* procurar(Lista* lista, int elemA, int elemB)
{
    while(lista!=NULL)
    {
        if(lista->ladoA == elemA && lista->ladoB == elemB)
        {
            return lista;
        }
        else
            lista=lista->next;
    }
    return NULL;
}

Lista* remover (Lista *lista, int elemA, int elemB)
{

    Lista* v = procurar(lista, elemA, elemB);
    if(!v)
        v = procurar(lista, elemB, elemA);

    if(v){
        if(v->prev==NULL)
        {
            lista = v->next;
            if(lista)
                lista->prev = NULL;
            else
                lista = NULL;
        }
        else if(v->next==NULL)
            v->prev->next=NULL;
        else
        {
            v->prev->next=v->next;
            v->next->prev=v->prev;
        }

        free(v);
    }
    return lista;
}

int tamanho(Lista* l){
    int i;
    for(i = 0; l != NULL; i++)
        l = l->next;
    return i;
}

int comprar(Lista** l, Lista** p){//retira uma pe�a da lista l e adiciona a p
    int i, a, k = tamanho(*l);
    if(!k)//se n�o h� pe�as para comprar retorna 0
        return 0;
    Lista* m = *l;
    a = rand()%k;//sorteia uma pe�a
    for(i = 0; i < a; i++)
        m = m->next;
    //retira a pe�a do monte e passa pro jogador
    *p = inserir(*p, m->ladoA, m->ladoB);
    *l = remover(*l, m->ladoA, m->ladoB);
    return 1;
}

void imprimir_pecas(Lista* l){//imprime as pe�as que est�o na mesa
    Lista *v;
    printf("\n");
    for (v = l; v != NULL; v = v->next)
    {
        printf(" %d|%d ", v->ladoA, v->ladoB);
    }
    printf("\n");
}

int jogo_jogado(Lista* jogo, Lista* player1, Lista* player2, Lista* domino, int vez){
    int opcao, escolhe, i, jogou;
    while(player1 && player2){//
        jogou = 0;
        if(vez){
            system("pause");
            system("cls");
            printf("Pecas colocadas:\n");
            imprimir_pecas(domino);//mostra as pe�as da mesa
            printf("\n\nPlayer 1:\n");
            imprimir_para_frente(player1);//mostra as pe�as do jogador
            Lista* m;
            //verifica se o jogador tem alguma pe�a que possa ser colocada na mesa
            m = player1;
            i = verifica(domino, m);
            while(!i){
                m = m->next;
                if(!m)
                    break;
                i = verifica(domino, m);
            }
            if(m){//escolhe qual pe�a quer jogar
                while(!jogou){
                    printf("\nEscolha o numero da peca a ser movida:\n");
                    scanf("%d", &escolhe);
                    if(escolhe > tamanho(player1))
                        escolhe = tamanho(player1);
                    for (i = 1, m = player1; i < escolhe; i++, m = m->next);//encontra a pe�a escolhida
                    if(!domino){//se a mesa est� vazia, coloca a pe�a na mesa
                        jogou++;
                        domino = inserir(domino, m->ladoA, m->ladoB);
                        player1 = remover(player1, m->ladoA, m->ladoB);
                    }else{//sen�o verifica se a pe�a escolhida pode ser colocada
                        opcao = verifica(domino, m);
                        if(!opcao){//se n�o pode, escolhe outra pe�a
                            continue;
                        }
                        else{//se pode, verifica onde colocar a pe�a
                            jogou++;
                            if(opcao == 3 || opcao == -3){//jogador deve escolher se vai no inicio ou no fim
                                int pos;
                                printf("\nEscolha onde deseja colocar a peca\n1.Inicio\n2.Fim\n");
                                scanf("%d", &pos);
                                if(pos == 1)
                                    if(opcao == 3)//vai no inicio
                                        domino = inserir(domino, m->ladoA, m->ladoB);
                                    else//vai invertida no inicio
                                        domino = inserir(domino, m->ladoB, m->ladoA);
                                else
                                    if(opcao == 3)//vai no fim
                                        domino = inserir_fim(domino, m->ladoA, m->ladoB);
                                    else//vai invertida no fim
                                        domino = inserir_fim(domino, m->ladoB, m->ladoA);
                            }else if(opcao == 1)//vai no inicio
                                domino = inserir(domino, m->ladoA, m->ladoB);
                            else if(opcao == 2)//vai invertida no inicio
                                domino = inserir(domino, m->ladoB, m->ladoA);
                            else if(opcao == -1)//vai no fim
                                domino = inserir_fim(domino, m->ladoA, m->ladoB);
                            else if(opcao == -2)//vai invertida no fim
                                domino = inserir_fim(domino, m->ladoB, m->ladoA);
                            player1 = remover(player1, m->ladoA, m->ladoB);
                        }
                    }
                }
            }else{//se n�o h� pe�as para serem jogadas, tenta comprar uma pe�a
                jogou += comprar(&jogo, &player1);
                if(jogou)//se conseguiu comprar
                    printf("\n\nNao ha pecas para serem jogadas.\n\nVoce comprou uma peca.\n");
                else//se n�o haviam pe�as para serem compradas
                    printf("\n\nNao ha pecas para serem jogadas.\n\nVoce passou a vez.\n");
            }
            vez = !vez;
        }else//jogada do computador
            if(player1){
                jogou += jogada_pc(&jogo, &domino, &player2);
                vez = !vez;
            }
        if(!jogou && !jogo)//se n�o h� pe�as para serem compradas, e nem pe�as na m�o dos jogadores que possam ser jogadas
            break;//termina o jogo
    }
    int retorno;
    if(!player1)//Player 1 venceu
        retorno  = 1;
    else if(!player2)//Player 2 venceu
        retorno  = -1;
    else
        retorno = soma_pecas(player2) - soma_pecas(player1);//retorna a diferen�a entre o valor das pe�as dos jogadores

    liberar(jogo);
    liberar(player1);
    liberar(player2);
    liberar(domino);

    return retorno;//retorna o vencedor
}

int soma_pecas(Lista* p){//soma o valor das pe�as que est�o na m�o do jogador
    int soma = 0;
    while(p){
        soma += p->ladoA + p->ladoB;
        p = p->next;
    }
    return soma;
}

int jogada_pc(Lista** j, Lista** d, Lista** p){
    Lista* m = *p;
    int i;
    //encontra a primeira pe�a que possa ser jogada
    i = verifica(*d, m);
    while(!i){
        m = m->next;
        if(!m)
            break;
        i = verifica(*d, m);
    }
    if(!i){//caso n�o tenha pe�as para jogar tenta comprar
        i = comprar(j, p);
        if(i)
            printf("\n\nOponente comprou uma peca\n");
        else//se n�o tem mais pe�as para serem compradas passa a vez
            printf("\n\nOponente passou a vez\n");
        return i;
    }
    //joga a pe�a
    if(i == 1)
        *d = inserir(*d, m->ladoA, m->ladoB);
    else if(i == 2)
        *d = inserir(*d, m->ladoB, m->ladoA);
    else if(i == 3){
        i = rand()%2;
        if(i)
            *d = inserir(*d, m->ladoA, m->ladoB);
        else
            *d = inserir_fim(*d, m->ladoA, m->ladoB);
    }
    else if(i == -1)
        *d = inserir_fim(*d, m->ladoA, m->ladoB);
    else if(i == -2)
        *d = inserir_fim(*d, m->ladoB, m->ladoA);
    else if(i == -3){
        i = rand()%2;
        if(i)
            *d = inserir(*d, m->ladoB, m->ladoA);
        else
            *d = inserir_fim(*d, m->ladoB, m->ladoA);
    }
    printf("\n\nOponente jogou a peca %d | %d\n", m->ladoA, m->ladoB);
    *p = remover(*p, m->ladoA, m->ladoB);//remove a pe�a do jogador
    return 1;
}


int verifica(Lista* domino, Lista* peca){//verifica se uma pe�a pode ser colocada na mesa
    if(!domino)//se n�o tem nada na mesa, qualquer pe�a pode ser jogada
        return 1;

    //aux ser� a �ltima pe�a da mesa
    Lista* aux = domino;
    while(aux->next)
        aux = aux->next;

    if(domino->ladoA == peca->ladoB && aux->ladoB == peca->ladoA)
        return 3;//pe�a pode ir de qualquer lado
    if(domino->ladoA == peca->ladoA && aux->ladoB == peca->ladoB)
        return -3;//pe�a invertida pode ir de qualquer lado
    if(domino->ladoA == peca->ladoB)
        return 1;//pe�a vai no inicio
    if(domino->ladoA == peca->ladoA)
        return 2;//peca vai no inicio invertida
    if(aux->ladoB == peca->ladoA)
        return -1;//pe�a vai  no final
    if(aux->ladoB == peca->ladoB)
        return -2;//pe�a vai no final invertida
    return 0;//pe�a n�o pode ser encaixada
}
