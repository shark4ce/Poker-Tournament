#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"

Sala CitireSala(const char *filename1) {

    FILE *fp;
    fp = fopen(filename1, "r");

    Sala room = NULL;
    int i,j;

    room = (Sala)malloc(sizeof(struct sala));
    room->nrLocCrt = 0;
    room->nrLocMax = 0;
    room->masa = NULL;
    fscanf(fp,"%d",&room->nrMese);

    for(i=0; i < room->nrMese; i++) {
        //
        TLista aux = NULL, ultim1 = NULL, p = NULL, ultim2 = NULL, p2 = NULL;
        Masa M = NULL;
        aux = (TLista)malloc(sizeof(Celula));
        if(!aux) return NULL;
        aux->urm = NULL;

        TLista s = NULL;
        s = (TLista)malloc(sizeof(Celula));
        if(!s) return NULL;
        s->urm = NULL;
        M = (Masa)malloc(sizeof(struct masa));
        M->jucatori = NULL;
        M->numeMasa = (char*)malloc(30*sizeof(char));
        fscanf(fp,"%s",M->numeMasa);
        fscanf(fp,"%d",&M->nrCrtJucatori);
        fscanf(fp,"%d",&M->nrMaxJucatori);
        room->nrLocCrt = room->nrLocCrt+M->nrCrtJucatori;
        room->nrLocMax = room->nrLocMax+M->nrMaxJucatori;
        for(j = 0; j < M->nrCrtJucatori; j++) {
            TLista temp = NULL;
            Jucator J;
            temp = (TLista)malloc(sizeof(Celula));
            if(!temp) return NULL;
            J = (Jucator)malloc(sizeof(struct jucator));
            if(!J) return NULL;
            J->nume = (char*)malloc(30*sizeof(char));
            if(!J->nume) {
                free(J);
                return NULL;
            }
            fscanf(fp,"%s",J->nume);
            fscanf(fp,"%d",&J->nrMaini);
            temp->info=J;
            if(s->urm==NULL) {
                s->urm=temp;
                temp->urm=s;
            } else {
                for(p2=s->urm; p2!=s ; ultim2=p2, p2=p2->urm);
                ultim2->urm=temp;
                temp->urm=s;
            }
        }
        M->jucatori=s;
        aux->info=M;
        //Introducere sfarsit de lista (lista a meselor)
        for(p=room->masa ; p!=NULL; ultim1=p, p = p->urm);
        if(ultim1==NULL) room->masa=aux;
        else ultim1->urm=aux;
    }
    fclose(fp);
    return room;
}


void AfisareSala(Sala room, const char *filename2) {
    TLista aux = NULL,temp = NULL;

    FILE *fd;
    fd = fopen(filename2,"a");
    if(room == NULL) {
        fprintf(fd,"Sala este inchisa!\n");
        fclose(fd);
        return;
    }

    for(aux = room->masa; aux != NULL; aux = aux->urm) {
        fprintf(fd,"%s:",((Masa)aux->info)->numeMasa);
        for(temp=((Masa)aux->info)->jucatori->urm;
                temp!=((Masa)aux->info)->jucatori; temp = temp->urm) {
            fprintf(fd," %s -",((Jucator)temp->info)->nume);
            if(temp->urm==((Masa)aux->info)->jucatori)
                fprintf(fd," %d.\n",((Jucator)temp->info)->nrMaini);
            else fprintf(fd," %d;",((Jucator)temp->info)->nrMaini);
        }
    }
    fclose(fd);
}

TLista CautareMasa(Sala room, char *numeMC) {
    TLista aux = NULL;
    for(aux = room->masa ; aux != NULL; aux = aux->urm) {
        if(strcmp(((Masa)aux->info)->numeMasa,numeMC)==0) return aux;
    }
    return NULL;
}


TLista CautareJucator(Sala room,char* numeMC,char* numeJC, char* file) {
    TLista aux = NULL,temp = NULL;
    aux=CautareMasa(room,numeMC);

    FILE *fj;
    fj = fopen(file,"a");
    if(aux == NULL) {
        fprintf(fj, "Masa %s nu exista!\n",numeMC);
        fclose(fj);
        return NULL;
    }
    for(temp = ((Masa)aux->info)->jucatori->urm;
            temp != ((Masa)aux->info)->jucatori;
            temp = temp->urm) {
        if(strcmp(((Jucator)temp->info)->nume,numeJC)==0) {
            return temp;
        }
    }
    fprintf(fj, "Jucatorul %s nu exista la masa %s!\n",numeJC,numeMC);
    fclose(fj);
    return NULL;
}

Sala noroc(Sala room, TLista poz,int PLMaini) {

    if(poz != NULL) {
        ((Jucator)poz->info)->nrMaini = ((Jucator)poz->info)->nrMaini + PLMaini;
    }
    return room;
}

void freeJucator(Jucator j){
    if(j == NULL) return;
    free(j->nume);
    free(j);
}

void freeMasa(Masa m){
    if(m == NULL) return;
    free(m->numeMasa);
    TLista l=NULL;
    for(l = m->jucatori->urm; l != m->jucatori;){
        freeJucator((Jucator)l->info);
        TLista l2 = l;
        l = l->urm;
        free(l2);
    }

    free(m->jucatori);
    free(m);
}

void freeSala(Sala s){
    if(s == NULL) return;

    TLista l=NULL;
    for(l = s->masa; l != NULL;){
        freeMasa((Masa)l->info);
        TLista l2 = l;
        l = l->urm;
        free(l2);
    }
    
    free(s);
}


Sala EliminareJucator(Sala room, TLista poz) {
    TLista p = NULL;

    for(p = poz; p->urm != poz; p = p->urm);
    p->urm = poz->urm;
    
    freeJucator((Jucator)poz->info);
    free(poz);

    room->nrLocCrt--;
    return room;
}

Sala EliminareMasa(Sala room,TLista aux) {
    TLista temp = NULL,ultima = NULL;
    for(temp = room->masa; temp != aux; ultima = temp, temp = temp->urm);
    if(ultima == NULL) room->masa = aux->urm;
    else ultima->urm=aux->urm;
    room->nrLocMax = room->nrLocMax - ((Masa)aux->info)->nrMaxJucatori;
    freeMasa(((Masa)aux->info));
    free(aux);
    room->nrMese--;

    return room;
}

Sala ghinion(Sala room,TLista poz,char *numeMC,int PLMaini) {
    TLista aux = NULL;
    if(poz != NULL) {
        ((Jucator)poz->info)->nrMaini=((Jucator)poz->info)->nrMaini - PLMaini;
        if( ((Jucator)poz->info)->nrMaini <= 0) {
            room=EliminareJucator(room,poz);
            aux=CautareMasa(room,numeMC);
            ((Masa)aux->info)->nrCrtJucatori--;
            if(((Masa)aux->info)->nrCrtJucatori == 0) {
                room=EliminareMasa(room,aux);
                if(room->nrMese == 0) {
                    freeSala(room);
                    room = NULL;
                    return NULL;
                }
            }
        }
    }
    return room;
}



Sala TURA(Sala room,char* numeMC,char* file) {
    TLista aux = NULL,prima = NULL,ultima = NULL,first = NULL;

    aux=CautareMasa(room,numeMC);
    if(aux == NULL) {
        FILE *fd;
        fd = fopen(file,"a");
        fprintf(fd, "Masa %s nu exista!\n",numeMC);
        fclose(fd);
        return room;
    }
    ultima = ((Masa)aux->info)->jucatori->urm;
    prima = ((Masa)aux->info)->jucatori->urm;
    //efectuarea rotatiei
    for(; ultima->urm != ((Masa)aux->info)->jucatori; ultima = ultima->urm);
    ultima->urm = prima;
    ((Masa)aux->info)->jucatori->urm = prima->urm;
    prima->urm = ((Masa)aux->info)->jucatori; //adresa santinelei
    //decrementare
    for(first = prima->urm->urm ; first != ((Masa)aux->info)->jucatori;  ) {
        TLista tmpfirst = first->urm;

        ((Jucator)first->info)->nrMaini--;
        if(((Jucator)first->info)->nrMaini <= 0) {
            room=EliminareJucator(room,first);
            ((Masa)aux->info)->nrCrtJucatori--;
            if(((Masa)aux->info)->nrCrtJucatori == 0) {
                room=EliminareMasa(room,aux);
                if(room->nrMese == 0) {
                    freeSala(room);
                    return NULL;
                }
                return room;
            }
        }

        first = tmpfirst;
    }

    return room;
}

Sala TuraCompleta(Sala room,char* file) {
    TLista aux=NULL;
    for(aux = room->masa; aux !=NULL;) {
        TLista tmpaux = aux->urm;
        room=TURA(room,((Masa)aux->info)->numeMasa,file);
        aux = tmpaux;
    }
    return room;
}

//Functie de alocare pentru crearea listei sortate
TLista ALocareCEL(void *ae) {

    TLista aux=NULL;

    aux=(TLista)malloc(sizeof(Celula));
    if (!aux) return NULL;
    aux->info = ae;
    aux->urm = NULL;
    return aux;

}



void sortedInsert(TLista* L, TLista new_elem)
{
    TLista current = NULL, aux = NULL;

    //Tratarea cazului de lucru cu inceputul listei
    if (*L == NULL || ((Jucator)(*L)->info)->nrMaini <= ((Jucator)new_elem->info)->nrMaini)
    {
        if(*L != NULL) {
            if(((Jucator)(*L)->info)->nrMaini == ((Jucator)new_elem->info)->nrMaini) {
                if(*L!= NULL && (*L)->urm == NULL) { // avem un element in lista_sortata
                    if(strcmp(((Jucator)(*L)->info)->nume,((Jucator)new_elem->info)->nume) <= 0) {
                        aux=ALocareCEL(new_elem->info);
                        aux->urm=*L;
                        *L=aux;
                    } else if(strcmp(((Jucator)(*L)->info)->nume,((Jucator)new_elem->info)->nume) > 0) {
                        aux=ALocareCEL(new_elem->info);
                        aux->urm=(*L)->urm;
                        (*L)->urm=aux;
                    }

                } else if (*L!= NULL && (*L)->urm != NULL) { //avem mai multe elemente, dar cel care in introducem e mai mare ca primul din lista
                    TLista temp=NULL, u=NULL;
                    temp=*L;

                    for( temp = *L; temp != NULL &&
                            (((Jucator)temp->info)->nrMaini == ((Jucator)new_elem->info)->nrMaini)
                            &&
                            (strcmp(((Jucator)temp->info)->nume,((Jucator)new_elem->info)->nume) > 0);
                            u=temp, temp = temp->urm);
                    if( u!=NULL) {
                        aux=ALocareCEL(new_elem->info);
                        aux->urm = u->urm;
                        u->urm = aux;
                    } else {
                        aux=ALocareCEL(new_elem->info);
                        aux->urm=(*L);
                        *L=aux;
                    }

                }

            } else {
                aux=ALocareCEL(new_elem->info);
                aux->urm = *L;
                *L = aux;

            }

        } else {
            aux = ALocareCEL(new_elem->info);
            *L=aux;
        }

    } else {
        current = *L;
        while ( ((current->urm!=NULL)
                &&
                (((Jucator)current->urm->info)->nrMaini==((Jucator)new_elem->info)->nrMaini)
                &&
                (strcmp(((Jucator)current->urm->info)->nume,((Jucator)new_elem->info)->nume) > 0))
                ||
                (current->urm!=NULL
                &&
                (((Jucator)current->urm->info)->nrMaini > ((Jucator)new_elem->info)->nrMaini))  )
        {
            current = current->urm;
        }
        aux = ALocareCEL(new_elem->info);
        aux->urm = current->urm;
        current->urm = aux;
    }
}


void stergere_lista_sortata(TLista sorted) {
    TLista aux = NULL;
    while(sorted) {
        aux = sorted;
        sorted = aux->urm;
        free(aux);
    }

}



void insertionSort(TLista *L, char *file,char* numeMC)
{

    TLista sorted = NULL,temp = NULL;

    TLista current = (*L)->urm;
    while (current != (*L))
    {
        TLista next = current->urm;

        sortedInsert(&sorted, current);
        current = next;
    }

    if(sorted != NULL) {
        FILE *fd;
        fd = fopen(file,"a");
        fprintf(fd, "Clasament %s:\n",numeMC );
        for( temp = sorted; temp != NULL; temp = temp->urm) {
            fprintf(fd,"%s %d\n",((Jucator)temp->info)->nume,((Jucator)temp->info)->nrMaini);
        }
        fclose(fd);

        stergere_lista_sortata(sorted);
    }

}

void clasament(Sala room,char* numeMC,char* file) {
    TLista aux = NULL,poz = NULL;
    aux=CautareMasa(room,numeMC);
    if(aux == NULL) {
        FILE *fd;
        fd = fopen(file,"a");
        fprintf(fd, "Masa %s nu exista!\n",numeMC);
        fclose(fd);
        return;
    }
    poz = ((Masa)aux->info)->jucatori; //adresa listei de jucatori(adresa santinelei)
    insertionSort(&poz,file,numeMC);
}

Sala inchide_masa(Sala room,char* numeMC,char* file) {
    TLista aux = NULL,temp = NULL;
    int loc_disp_sala,loc_disp_masa,i,l,z;
    aux=CautareMasa(room,numeMC); //am gasit pozitia mesei
    FILE *fd;
    fd = fopen(file,"a");
    if(aux == NULL) {
        fprintf(fd, "Masa %s nu exista!\n",numeMC);
        fclose(fd);
        return room;
    }
    loc_disp_sala = room->nrLocMax-room->nrLocCrt-((Masa)aux->info)->nrMaxJucatori+((Masa)aux->info)->nrCrtJucatori;
    z = ((Masa)aux->info)->nrMaxJucatori;
    ((Masa)aux->info)->nrMaxJucatori = ((Masa)aux->info)->nrCrtJucatori; // egalam ca sa neutralizam masa ca avand locuri indisponibile

    if( ((Masa)aux->info)->nrCrtJucatori > loc_disp_sala) {
        fprintf(fd, "Nu exista suficiente locuri in sala!\n");
        fclose(fd);
        ((Masa)aux->info)->nrMaxJucatori = z;
        return room;
    } else {
        for( l = ((Masa)aux->info)->nrCrtJucatori; l > 0 ; l--) {
            for(temp = room->masa ; temp != NULL; temp = temp->urm) {
                loc_disp_masa = ( ((Masa)temp->info)->nrMaxJucatori - ((Masa)temp->info)->nrCrtJucatori);
                if( loc_disp_masa > 0)
                {
                    for (i = 0 ; i < loc_disp_masa  ; i++)
                    {
                        if(((Masa)aux->info)->jucatori->urm == ((Masa)aux->info)->jucatori)
                        {
                            ((Masa)aux->info)->nrMaxJucatori = z;
                            room = EliminareMasa(room,aux);
                            return room;
                        }

                        TLista aux1 = NULL, z = NULL;
                        for(aux1 = ((Masa)temp->info)->jucatori->urm;
                            aux1 != ((Masa)temp->info)->jucatori;
                            z=aux1, aux1 = aux1->urm );

                        TLista a = NULL,s = NULL;
                        s = ((Masa)aux->info)->jucatori;
                        a = s->urm;
                        if(a->urm == ((Masa)aux->info)->jucatori)
                        {
                            a->urm=z->urm;
                            z->urm = a;
                            s->urm = s;
                            ((Masa)temp->info)->nrCrtJucatori++;

                        } else
                        {
                            s->urm = a->urm;
                            a->urm = z->urm;
                            z->urm = a;
                            ((Masa)temp->info)->nrCrtJucatori++;
                        }
                    }

                } else continue;

            }
        }
        ((Masa)aux->info)->nrMaxJucatori = z;
        room = EliminareMasa(room,aux);
    }
    return room;
}


int main(int argc, char **argv)
{
    Sala room = NULL;
    TLista poz = NULL;
    FILE *ft;
    char ev[300];
    char numeMC[300];
    char numeJC[300];
    int PLMaini;

    room = CitireSala(argv[1]);

    //citire evenimente
    ft = fopen(argv[2],"r");
    while(fscanf(ft,"%s",ev) != EOF) {
        if(strcmp(ev,"print") == 0) {
            AfisareSala(room,argv[3]);
        }
        if(strcmp(ev,"noroc") == 0) {
            fscanf(ft,"%s",numeMC);
            fscanf(ft,"%s",numeJC);
            fscanf(ft,"%d",&PLMaini);
            poz = CautareJucator(room,numeMC,numeJC,argv[3]);
            room = noroc(room,poz,PLMaini);
        }
        if(strcmp(ev,"ghinion") == 0) {
            fscanf(ft,"%s",numeMC);
            fscanf(ft,"%s",numeJC);
            fscanf(ft,"%d",&PLMaini);
            poz=CautareJucator(room,numeMC,numeJC,argv[3]);
            room = ghinion(room,poz,numeMC,PLMaini);
        }
        if(strcmp(ev,"tura")==0) {
            fscanf(ft,"%s",numeMC);
            room=TURA(room,numeMC,argv[3]);

        }
        if(strcmp(ev,"tura_completa") ==0 ) {
            room = TuraCompleta(room,argv[3]);
        }
        if(strcmp(ev,"clasament") ==0 ) {
            fscanf(ft,"%s",numeMC);
            clasament(room,numeMC,argv[3]);
        }
        if(strcmp(ev,"inchide") == 0) {
            fscanf(ft,"%s",numeMC);
            inchide_masa(room,numeMC,argv[3]);

        }

    }


    fclose(ft);

    freeSala(room);

    return 0;
}
