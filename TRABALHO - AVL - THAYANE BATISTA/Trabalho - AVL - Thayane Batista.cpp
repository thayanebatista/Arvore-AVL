///Trabalho de Arvores binarias
///Arvores AVL
///         Thayane Batista - RA 159049
///         Eng. de Computaçao





#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct no_avl
{
    int info;
    no_avl *Eprox,*Dprox;
    int bal;
};

no_avl *N = NULL; /// no N criado como variavel global para armazenar a raiz da arvore



/// Funcao para criar um novo no com o valor a ser inserido
no_avl* criaNo_AVL(no_avl *no, int x)
{
    no = new (no_avl); ///aloca o novo no

    if (no == NULL)
    {
        cout<<"\t\t\t OVERFLOW\n\n\n";
        return NULL;
    }
    else
    {
        no->info = x; // recebe o balor digitado pelo  usuario
        no->Eprox = NULL;
        no->Dprox = NULL;
        no->bal = 0;
        //aqui o no eh inserido como uma folha

        if( N == NULL)
        {
            N = no; // se a variavel de raiz estiver vazia, o novo no passa a ser a raiz
        }
        return no;
    }
}


/// rotacao para direita. simples e dupla
no_avl* rotaD(no_avl *no, bool &h)
{
    no_avl *d = no->Eprox;
    /// Rotacao simples
    if ( d != NULL )
    {
        if ( d->bal == -1)
        {
            no->Eprox = d->Dprox;
            d->Dprox  = no;
            no->bal = 0;
            no = d;
            if(d->Dprox == N)
            {
                N = d;
            }
        }
        else      /// rotacao dupla
        {
            no_avl *f = d->Dprox;
            d->Dprox = f->Eprox;
            f->Eprox = d;
            no->Eprox = f->Dprox;
            f->Dprox = no;

            if( f->bal ==0)
            {
                d->bal = 0;
                no->bal = 0;
            }
            else  if (f->bal == -1)
            {
                d->bal = 0;
                no->bal = 1;
            }
            else
            {
                d->bal = -1;
                no->bal = 0;
            }
            if (f->Dprox == N)
            {
                N = f;
                no = f;
            }

        }
        no->bal = 0;
        h = false;
        return no;
    }
}


/// rotacao para esquerda, simples e dupla

no_avl* rotaE(no_avl *no, bool &h)
{
    no_avl *z = no->Dprox;
    /// rotacao simples
    if ( z != NULL )
    {
        if ( z->bal ==1)
        {
            no->Dprox = z->Eprox;
            z->Eprox = no;
            no->bal = 0;
            no = z;
            if (z->Eprox == N)
            {
                N = z;
            }
        }
        else     /// rotacao dupla
        {
            no_avl *y = z->Eprox;
            z->Eprox = y->Dprox;
            y->Dprox = z;
            no->Dprox = y->Eprox;
            y->Eprox = no;

            if (y->bal == 1)
            {
                no->bal = -1;
                z->bal = 0;
            }
            else if (y->bal == 0)
            {
                z->bal = 0;
                no->bal = 0;
            }
            else
            {
                z->bal = 1;
                no->bal = 0;
            }
            no = y;

            if(y->Eprox == N)
            {
                N = y;
            }
        }
        no->bal = 0;
        h = false;
        return no;
    }
}


/// inserir um no na arvore verificando se sera raiz ou apenas filho
no_avl* inserir_avl (no_avl *no, int x, bool &h)
{
    if (no == NULL)
    {
        no  = criaNo_AVL(no, x);
        h = true;
    }
    else if(x< no->info)
    {
        no->Eprox = inserir_avl(no->Eprox,x,h);

        if (h)
        {
            switch (no->bal)
            {
            case 1:
                no->bal = 0;
                h  = false;
                break;
            case 0:
                no->bal = -1;
                break;
            case -1:
                no  =  rotaD(no,h);
                break;
            }
        }
    }
    else  if (x > no->info)
    {
        no->Dprox = inserir_avl(no->Dprox,x,h);

        if (h)
        {
            switch (no->bal)
            {
            case 1:
                no->bal  = 0;
                h  = false;
                break;
            case 0:
                no->bal = 0;
                h = false;
                break;
            case -1:
                no = rotaE(no,h);
                break;
            }
        }
    }
    else
    {
        cout<<"\t\t\tEste elemento ja existe...\n\n";
    }
    return  no;
}


/// funcao para remocao de um no na arvore
no_avl* remove_avl (no_avl *A, int x,bool &h){
    if(A != NULL){
        //Sub-arvore à direita
        if(x > A->info){
            A->Dprox = remove_avl(A->Dprox,x,h);
            if(h){
                if(A != NULL){
                    switch (A->bal){
                        case 1:
                            A->bal = 0;
                            h = false;
                        break;

                        case 0:
                            A->bal = -1;
                        break;

                        case -1:
                            A->Eprox->bal = -1;
                            A = rotaD(A,h);
                        break;
                    }
                }
            }
        }
        //Sub-arvore à esquerda
        else if (x < A->info){
            A->Eprox = remove_avl(A->Eprox,x,h);
            if(h){
                if (A != NULL){
                    switch (A->bal){
                        case 1:
                            A->bal = 0;
                            h = false;
                        break;

                        case 0:
                            A->Dprox->bal = 1;
                            A = rotaE(A,h);
                        break;

                        case -1:
                            A->bal = 1;
                        break;
                    }
                }
            }
        }
        else{
            if (A->Dprox == NULL){
                if(A == N){
                    N = A->Eprox;
                    A = A->Eprox;
                    h = true;
                }
            }
            else{
                if (A->Eprox == NULL){
                    if (A == N){
                        N = A->Dprox;
                        A = A->Dprox;
                        h = true;
                    }
                }
                else{
                    no_avl *s;
                    s = A;
                    h = true;
                    no_avl *v;
                    v = s;
                    s = s->Dprox;
                    while(s->Eprox != NULL){
                        v = s;
                        s = s->Eprox;
                    }
                    A->info = s->info;
                    if(A == v){
                        v->Dprox = s->Dprox;
                    }
                    else{
                        v->Eprox = s->Dprox;
                    }
                    if(h){
                        if(A != NULL){
                            switch (A->bal){
                                case 1:
                                    A->bal = 0;
                                    h = false;
                                break;

                                case 0:
                                    A->bal = -1;
                                break;

                                case -1:
                                    A->Eprox->bal = -1;
                                    A = rotaD(A,h);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    else {
        cout<<"Elemento nao encontrado!\n";
    }
    return A;
}




///busca de um no recursivamente, primeiro pelo lado esquerdo, depois pelo direito, verificando se é a raiz
no_avl* buscar_avl (no_avl *no, int x)
{
    if (no == NULL)
    {
        return NULL;
    }
    else if ( x < no->info)
    {
        return buscar_avl(no->Eprox,x);///busca nos nos da esquerda
    }
    else if ( x > no->info)
    {
        return buscar_avl(no->Dprox,x);///busca nos nos da direita
    }
    else
    {
        return no;
    }
}


/// funcao para imprimir a arvore de maneira recursiva

void imprime_avl (no_avl *no, int level)
{
    if (no!=NULL)
    {
        imprime_avl(no->Dprox, level + 1);
        printf("\n");
        for (int i = 0; i < level && no != N; i++)
            cout<<"        ";
        cout<<no->info;
        imprime_avl(no->Eprox, level + 1);
    }




//    if(no != NULL)
//    {
//        imprime_avl(no->Dprox, altura+1);
//        for (int i=0; i < altura ; i++)
//        {
//            cout<<"---";
//        }
//        cout<<no->info<<endl;
//        imprime_avl(no->Eprox, altura+1);
//    }
}

int main()
{
    int op = -1, valor = -1;
    bool h = false;
    while ( op != 0 )
    {
        system("cls");
        cout<<"\t\t\t::::: MENU ARVORE AVL :::::\t\t\t\n\n\n";
        cout<<"\t\t 1: INSERIR um no na Arvore AVL\t\n";
        cout<<"\t\t 2: REMOVER um no na Arvore AVL\t\n";
        cout<<"\t\t 3: BUSCAR um no na Arvore AVL\t\n";
        cout<<"\t\t 4: MOSTRAR Arvore AVL balanceada\t\n\n";
        cout<<"\t\t 0: SAIR\t\n\n\n";
        cout<<"\t\t\t   Digite sua opcao: \t";
        cin>>op;
        switch (op)
        {
        case 1:
            system("cls");
            cout<<"\t\t\t::::: MENU ARVORE AVL :::::\t\t\t\n\n";
            cout<<"\t\tDigite um valor a ser inserido na arvore: ";
            cin>>valor;
            //chamada da funcao para inserir o no na arvore
            inserir_avl(N,valor,h);
            cout<<"\n\n\t\tValor inserido com sucesso!!\n\n";
            system("pause");
            break;
        case 2:
            system("cls");
            cout<<"\t\t\t::::: MENU ARVORE AVL :::::\t\t\t\n\n";
            cout<<"\t\tDigite um valor a ser removido na arvore: ";
            cin>>valor;
            //chamada da funcao para remover o no na arvore
            remove_avl(N,valor,h);
            cout<<endl;
            system("pause");
            break;
        case 3:
            system("cls");
            cout<<"\t\t\t::::: MENU ARVORE AVL :::::\t\t\t\n\n";
            cout<<"\t\tDigite um valor a ser buscado na arvore: ";
            cin>>valor;
            //chamada da funcao para buscar o no na arvore
            buscar_avl(N,valor);
            cout<<endl;
            system("pause");
            break;

        case 4:
            system("cls");
            cout<<"\t\t\t::::: ARVORE AVL BALANCEADA :::::\t\t\t\n\n";
            //chamada da funcao para MOSTRAR A ARVORE
            imprime_avl(N,0);
            cout<<endl<<endl<<endl;
            system("pause");
            break;
        case 0:
            system("cls");
            cout<<"\t\t\t SAINDO \t\t\t\n\n";
            cout<<"\t\t\t Obrigada!\t\t\t\n\n";
            system("pause");
            break;
        default:
            system("cls");
            cout<<"\t\t\t Opcao invalida\t\t\t\n\n\n";
        }

    }
}













