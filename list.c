#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* list=(List*)malloc(sizeof(List));
  list->head=NULL;
  list->tail=NULL;
  list->current=NULL;
     return list;
}

void * firstList(List * list) {
  if(!list->head){
    return NULL;
  }
  list->current=list->head;
  return(list->current->data);
}

void * nextList(List * list) {
  if(  !list->current || !list->current->next){ 
    return NULL;
  }
  list->current=list->current->next;
  return(list->current->data);
}

void * lastList(List * list) {
  if(!list->tail){
    return NULL;
  }
  list->current=list->tail;
  return(list->tail->data);
}

void * prevList(List * list) {
  if(!list->current || !list->current->prev){ 
    return NULL;
  }
  list->current=list->current->prev;
  return(list->current->data);
}

void pushFront(List * list, void * data) {
  Node* n = createNode(data);
  n->next= list->head;
  if(list->head==NULL){
    list->head = n;  
    list->tail=n;
  }
  else{
    list->head->prev=n;
  }
  list->head = n;
  n->prev=NULL;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node* n = createNode(data);
  n->data=list->head;
  if(list->head==NULL)
  {
    list->head=n;
    list->tail=n;
  }
  else{
    if(list->tail == list->current){
      list->tail=n;
      list->current->next=n;
      n->prev=list->current;
    }
    else{
      n->prev=list->current;
      list->current->next=n->next;
      n->next=list->current->next;
      list->current->prev->next=n;
      
      //list->current->next->prev=n;
      //n->prev=list->current;   
      //list->current->next=n; 
      //n->next=list->current->next;     
    }
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}