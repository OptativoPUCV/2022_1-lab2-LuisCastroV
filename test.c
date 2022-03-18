#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.c"


char msg[300];
int test_id = -1;


int success(){
  printf("SUCCESS\n");
  exit(0);
}

void err_msg(char* msg){
    //if(test_id!=-1) return;
    printf("   [FAILED] ");
    printf("%s\n",msg);
    //print_trace();
}

void ok_msg(char* msg){
    //if(test_id!=-1) return;
    printf ("   [OK] ");
    printf("%s\n",msg);
}

void info_msg(char* msg){
    //if(test_id!=-1) return;
    printf ("   [ INFO ] %s\n",msg);
}

int test_suite(int(*test)(), char* msg, int max_score, int id, int req_id){
    if(test_id==-1 || test_id==id){
        printf("\n%s\n", msg);
        int score=test();

        if(id==req_id && score == max_score) success();

        printf("   partial_score: %d/%d\n", score, max_score); 
        
        return score;
    }
    return 0;
}


/*************  TESTS  ******************/
List* initialize_exList(){
     info_msg("Creando Lista:{0,2,4,6,8,10,12,14,16,18}");
     List * L = (List *)malloc(sizeof(List));
     int *j = (int*) malloc(sizeof(int));
     *j=0;
     L->head=L->tail=createNode(j);
     info_msg("llamando a firstList");
     L->current=L->head;

    int i; Node*n;
     for(i=1;i<10;i++){
         int *j = (int*) malloc(sizeof(int));
         *j=i*2;
         n = createNode(j) ;
         L->tail->next=n;
         n->prev=L->tail;
         L->tail=n;
         
    }
    return L;
}

List* initialize_emptyList(){
     info_msg("Creando Lista vacia (head=NULL)");
     List * L = (List *)malloc(sizeof(List));

     L->current=NULL;
     L->head=L->tail=NULL;

    return L;
}

int test_create(){
    List* L = createList();
    if(L==NULL){
        err_msg("createList retorna NULL");
        return 0;
    }
    if(L->head != NULL || L->tail !=NULL || L->current!=NULL){
        err_msg("Debes inicalizar los componentes de la lista");
        return 0;
    }

    ok_msg("createList");
    return 10;
}

int test_first_next(){
    List* L=initialize_exList();
    info_msg("llamando a firstList");
    int*j = firstList(L);
    if(j ==NULL){
        err_msg("firstList retorna NULL");
        return 0;
    }
    if(*j != 0){
        sprintf(msg,"firstList retorna %d",*j);
        err_msg(msg);
        return 0;
    }
    if(L->current == NULL){
        err_msg("firstList debe actualizar posicion del current");
        return 0;
    }
    if(L->current != L->head){
        err_msg("current debería apuntar al primer nodo");
        return 0;
    }

    L=initialize_emptyList();
    info_msg("llamando a firstList");
    j = firstList(L);
    if(j != NULL){
        err_msg("firstList deberia retornar NULL");
        return 0;
    }

    ok_msg("firstList");

    L=initialize_exList();

    info_msg("llamando a nextList");
    j = nextList(L);
    if(j ==NULL){
        err_msg("nextList retorna NULL");
        return 5;
    }
    if(*j != 2){
        sprintf(msg,"nextList retorna %d",*j);
        err_msg(msg);
        return 5;
    }
    if(L->current != L->head->next){
        err_msg("current deberia moverse al siguiente nodo");
        return 5;
    }
    ok_msg("nextList");
    info_msg("posicionando el current al final de la lista");
    L->current = L->tail;
    info_msg("llamando a nextList");
    j = nextList(L);
    if(j != NULL){
        err_msg("nextList deberia retornar NULL");
        return 5;
    }
    ok_msg("nextList");

    info_msg("modificando: current=NULL");
    L->current = NULL;
    info_msg("llamando a nextList");
    j = nextList(L);
    if(j != NULL){
        err_msg("nextList deberia retornar NULL");
        return 5;
    }
    ok_msg("nextList");

    return 15;
}

int test_last_prev(){
    List* L=initialize_exList();
    info_msg("llamando a lastList");
    int*j = lastList(L);
    if(j ==NULL){
        err_msg("lastList retorna NULL");
        return 0;
    }
    if(*j != 18){
        sprintf(msg,"lastList retorna %d",*j);
        err_msg(msg);
        return 0;
    }
    if(L->current == NULL){
        err_msg("lastList debe actualizar posicion del current");
        return 0;
    }
    if(L->current != L->tail){
        err_msg("current deberia apuntar al ultimo nodo");
        return 0;
    }
    ok_msg("lastList");

    info_msg("llamando a prevList");
    j = prevList(L);
    if(j ==NULL){
        err_msg("prevList retorna NULL");
        return 0;
    }
    if(*j != 16){
        sprintf(msg,"prevList retorna %d",*j);
        err_msg(msg);
        return 0;
    }
    if(L->current != L->tail->prev){
        err_msg("current deberia moverse al nodo anterior");
        return 0;
    }
    ok_msg("prevList");
    info_msg("posicionando el current al comienzo de la lista");
    L->current = L->head;
    info_msg("llamando a prevList");
    j = prevList(L);
    if(j != NULL){
        err_msg("prevList deberia retornar NULL");
        return 0;
    }
    ok_msg("nextList");

    info_msg("modificando: current=NULL");
    L->current = NULL;
    info_msg("llamando a prevList");
    j = prevList(L);
    if(j != NULL){
        err_msg("prevList deberia retornar NULL");
        return 0;
    }
    ok_msg("prevList");

    return 10;
}

int test_pushfront(){
    info_msg("Creando lista vacia");
    List * L = (List *)calloc(1,sizeof(List));

    int *j = (int*) malloc(sizeof(int));
    *j = rand()%100;
    
    sprintf(msg, "Insertando %d a la lista (pushfront)",*j);
    info_msg(msg);
    pushFront(L,j);

    if(L->head==NULL) {
        err_msg("head=NULL");
        return 0;
    }

    if(L->tail==NULL) {
        err_msg("tail=NULL");
        return 0;
    }

    if(L->head != L->tail){
        err_msg("head!=tail");
        return 0;
    }

    if(L->head->data != j){
        sprintf(msg,"head->data!=%d",*j);
        err_msg(msg);
        return 0;
    }

    L = initialize_exList();

    Node* aux=L->head;

    sprintf(msg, "pushFront(%d)",*j);
    info_msg(msg);
    pushFront(L,j);

    if(L->head->data != j){
        sprintf(msg,"head->data!=%d",*j);
        err_msg(msg);
        return 0;
    }

    if(L->head->next == NULL){
        err_msg("head->next=NULL");
        return 0;
    }

    if(L->head->next != aux){
        sprintf(msg,"head->next->data=%d (debe ser 0)",*(int*) L->head->next->data);
        err_msg(msg);
        return 0;
    }


    ok_msg("pushFront");
    return 10;

    //initialize_exList();

}

int test_pushcurrent(){
    List* L = initialize_exList();
    int *j = (int*) malloc(sizeof(int));
    *j = rand()%100;

    L->current=L->head;

    info_msg("Moviendo el current al primer nodo de la lista");

    sprintf(msg, "pushFront(%d)",*j);
    info_msg(msg);
    pushCurrent(L,j);

    if(L->head == NULL || L->head->next==NULL){
        err_msg("head o head->next es NULL");
        return 0;
    }

    if(L->head->next->data != j){
        sprintf(msg,"head->next->data!=%d",*j);
        err_msg(msg);
        return 0;
    }

    if(L->head->next->prev ==NULL){
        err_msg("el prev del nuevo nodo deberia apuntar a head");
        return 0;
    }

    L->current=L->tail;
    Node* aux=L->tail;
    info_msg("aux=L->tail");
    

    info_msg("Moviendo el current al ultimo nodo de la lista");
    pushCurrent(L,j);

    if(L->tail == NULL || L->tail->data != j){
        err_msg("tail deberia apuntar al nuevo nodo");
        return 0;
    }

    if(aux->next == NULL || aux->next!=L->tail){
        err_msg("aux->next deberia apuntar a nuevo tail");
        return 0;
    }

    if(L->tail->prev == NULL || L->tail->prev!=aux){
        err_msg("tail->prev deberia apuntar a aux");
        return 0;
    }

    ok_msg("pushCurrent");
    return 10;

    //initialize_exList();

}

int test_popcurrent(){
    List* L = initialize_exList();
    int *j = (int*) malloc(sizeof(int));
    *j = rand()%100;

    L->current=L->head;

    info_msg("Moviendo el current al primer nodo de la lista");

    info_msg("popCurrent()");;
    int* k = popCurrent(L);


    if(L->head == NULL || *(int*)L->head->data != 2){
        err_msg("El head es incorrecto");
        return 0;
    }

    if(L->head->prev != NULL){
        err_msg("head->prev deberia ser NULL");
        return 0;
    }

    if(*k != 0){
        sprintf(msg,"PopCurrent retorna %d",*k);
        err_msg(msg);
        return 0;
    }

    L->current=L->head->next;
    Node* aux=L->head->next->next;
    info_msg("L->current=L->head->next");
    info_msg("aux=L->head->next->next");
    
    info_msg("popCurrent()");;
    k=popCurrent(L);

    if(L->head->next == NULL || L->head->next!=aux){
        err_msg("L->head->next deberia apuntar a aux");
        return 0;
    }

    if(aux->prev != L->head){
        err_msg("aux->prev deberia apuntar a head");
        return 0;
    }

    if(*k != 4){
        sprintf(msg,"PopCurrent retorna %d",*k);
        err_msg(msg);
        return 0;
    }

    L->current=L->tail;
    aux=L->tail->prev;

    info_msg("L->current=L->tail");

    aux=L->tail->prev;
    info_msg("aux=L->tail->prev");
    
    info_msg("popCurrent()");;
    k = popCurrent(L);

    if(L->tail != aux){
        err_msg("tail deberia ser igual a aux");
        return 0;
    }

    if(L->tail->next != NULL){
        err_msg(">tail->next deberia apuntar a NULL");
        return 0;
    }

    if(*k != 18){
        sprintf(msg,"PopCurrent retorna %d",*k);
        err_msg(msg);
        return 0;
    }





    ok_msg("popCurrent");
    return 15;

    //initialize_exList();

}

int main( int argc, char *argv[] ) {
    
    if(argc>1) test_id=atoi(argv[1]);
    srand(time(NULL));

    int total_score=0;
    total_score+=test_suite(test_create, "Test Create...", 10, 0, test_id);
    total_score+=test_suite(test_first_next, "Test First y Next...", 15, 1, test_id);
    total_score+=test_suite(test_last_prev, "Test Last y Prev...", 10, 2, test_id);
    total_score+=test_suite(test_pushfront, "Test pushFront...", 10, 3, test_id);
    total_score+=test_suite(test_pushcurrent, "Test pushCurrent...", 10, 4, test_id);
    total_score+=test_suite(test_popcurrent, "Test popCurrent...", 15, 5, test_id);
    
    
    if(argc==1)
      printf("\ntotal_score: %d/70\n", total_score);

    

    return 0;
}
