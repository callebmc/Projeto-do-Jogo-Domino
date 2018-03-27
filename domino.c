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

int comprar(Lista** l, Lista** p){//retira uma peça da lista l e adiciona a p
    int i, a, k = tamanho(*l);
    if(!k)//se não há peças para comprar retorna 0
        return 0;
    Lista* m = *l;
    a = rand()%k;//sorteia uma peça
    for(i = 0; i < a; i++)
        m = m->next;
    //retira a peça do monte e passa pro jogador
    *p = inserir(*p, m->ladoA, m->ladoB);
    *l = remover(*l, m->ladoA, m->ladoB);
    return 1;
}

void imprimir_pecas(Lista* l){//imprime as peças que estão na mesa
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
            imprimir_pecas(domino);//mostra as peças da mesa
            printf("\n\nPlayer 1:\n");
            imprimir_para_frente(player1);//mostra as peças do jogador
            Lista* m;
            //verifica se o jogador tem alguma peça que possa ser colocada na mesa
            m = player1;
            i = verifica(domino, m);
            while(!i){
                m = m->next;
                if(!m)
                    break;
                i = verifica(domino, m);
            }
            if(m){//escolhe qual peça quer jogar
                while(!jogou){
                    printf("\nEscolha o numero da peca a ser movida:\n");
                    scanf("%d", &escolhe);
                    if(escolhe > tamanho(player1))
                        escolhe = tamanho(player1);
                    for (i = 1, m = player1; i < escolhe; i++, m = m->next);//encontra a peça escolhida
                    if(!domino){//se a mesa está vazia, coloca a peça na mesa
                        jogou++;
                        domino = inserir(domino, m->ladoA, m->ladoB);
                        player1 = remover(player1, m->ladoA, m->ladoB);
                    }else{//senão verifica se a peça escolhida pode ser colocada
                        opcao = verifica(domino, m);
                        if(!opcao){//se não pode, escolhe outra peça
                            continue;
                        }
                        else{//se pode, verifica onde colocar a peça
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
            }else{//se não há peças para serem jogadas, tenta comprar uma peça
                jogou += comprar(&jogo, &player1);
                if(jogou)//se conseguiu comprar
                    printf("\n\nNao ha pecas para serem jogadas.\n\nVoce comprou uma peca.\n");
                else//se não haviam peças para serem compradas
                    printf("\n\nNao ha pecas para serem jogadas.\n\nVoce passou a vez.\n");
            }
            vez = !vez;
        }else//jogada do computador
            if(player1){
                jogou += jogada_pc(&jogo, &domino, &player2);
                vez = !vez;
            }
        if(!jogou && !jogo)//se não há peças para serem compradas, e nem peças na mão dos jogadores que possam ser jogadas
            break;//termina o jogo
    }
    int retorno;
    if(!player1)//Player 1 venceu
        retorno  = 1;
    else if(!player2)//Player 2 venceu
        retorno  = -1;
    else
        retorno = soma_pecas(player2) - soma_pecas(player1);//retorna a diferença entre o valor das peças dos jogadores

    liberar(jogo);
    liberar(player1);
    liberar(player2);
    liberar(domino);

    return retorno;//retorna o vencedor
}

int soma_pecas(Lista* p){//soma o valor das peças que estão na mão do jogador
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
    //encontra a primeira peça que possa ser jogada
    i = verifica(*d, m);
    while(!i){
        m = m->next;
        if(!m)
            break;
        i = verifica(*d, m);
    }
    if(!i){//caso não tenha peças para jogar tenta comprar
        i = comprar(j, p);
        if(i)
            printf("\n\nOponente comprou uma peca\n");
        else//se não tem mais peças para serem compradas passa a vez
            printf("\n\nOponente passou a vez\n");
        return i;
    }
    //joga a peça
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
    *p = remover(*p, m->ladoA, m->ladoB);//remove a peça do jogador
    return 1;
}


int verifica(Lista* domino, Lista* peca){//verifica se uma peça pode ser colocada na mesa
    if(!domino)//se não tem nada na mesa, qualquer peça pode ser jogada
        return 1;

    //aux será a última peça da mesa
    Lista* aux = domino;
    while(aux->next)
        aux = aux->next;

    if(domino->ladoA == peca->ladoB && aux->ladoB == peca->ladoA)
        return 3;//peça pode ir de qualquer lado
    if(domino->ladoA == peca->ladoA && aux->ladoB == peca->ladoB)
        return -3;//peça invertida pode ir de qualquer lado
    if(domino->ladoA == peca->ladoB)
        return 1;//peça vai no inicio
    if(domino->ladoA == peca->ladoA)
        return 2;//peca vai no inicio invertida
    if(aux->ladoB == peca->ladoA)
        return -1;//peça vai  no final
    if(aux->ladoB == peca->ladoB)
        return -2;//peça vai no final invertida
    return 0;//peça não pode ser encaixada
}
