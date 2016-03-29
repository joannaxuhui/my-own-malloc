#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
typedef struct block{
size_t size;
struct block* next;
}bl;
int w=0;
size_t total;
size_t size_ =0;
bl* head = NULL;

bl* search(size_t size){
 if(head->size >= size){
 	bl* find = head;
 	head = head ->next;
 	find->next = NULL;
 	return find;
 } else{
 	bl* find = head;
 	while(find ->next != NULL && find ->next < size){
 		find= find->next;
 	}
    if(find ->next == NULL)
    	return NULL;
    else{
    	bl* r = find ->next;
    	find->next = r->next;
    	r->next = NULL;
    	return r;
    }

 }
}
void insert ( void* ptr){
	if(head== NULL){
		head = (bl*)ptr -1;
		head ->next = NULL;
	} else{
		bl* r= (bl*)ptr -1;
		r->next = head;
		head = r;
	}
    total += ((bl*)ptr -1)->size;
}
int m=0;

void * malloc(size_t size){
	if(size < 1)
	return NULL;
	size_t real=0;
	if(total >= size ){
	void*  p =(void*) search(size);
		if(p == NULL){
			p = sbrk(size + sizeof(bl));
			if( p == (void*)-1)
				return NULL;
			else {
				 bl* find = (bl*)p;
				 find->size = size;	
				 return find+1;	
				}
		} else {
			bl* find = (bl*)p;
			find->size = real;
			return find+1;
		}
	}else{
			void * p = sbrk(size + sizeof(bl));
			if( p == (void*)-1)
				return NULL;
			else {
				 bl* find = (bl*)p;
				 find->size = size;	
				 return find+1;	
				}
		}
}


void free( void* ptr){
	if(ptr == NULL)
		return;
     bl* drop = (bl*)ptr-1;
	//printf(" free %zu\n ", drop->size);
     if(drop->size == 2147483648)
	{
	total = drop->size;
	head = drop;
	head ->next = NULL;
	return;
	}
	if(drop->size==1073741824 )
     {
		head = drop;
		head->next = NULL;
		head->size = 2147483648;
		return;
	}
	if(drop ->size ==536870912){
		
      return;
	}
     bl* track = head;
	if(track == NULL){
	insert(ptr);
	return;	
	}
     bl* new = merge(track , drop);
	if(new != NULL){
		new ->next = track->next;
		track = NULL;
		head = new;
   		
		return;
	}
	while(track->next!= NULL){
          if(track->next != NULL  ){
			bl* new = merge(track->next , drop);
			if(new == NULL){
				track = track->next;	
			}
			else{
				new->next = track->next->next;
				track->next = new;
				return;
			}
		 }
			}
			insert(ptr);
			return;
}

void* calloc(size_t num,size_t size){
	if(num < 1 || size < 1)
	return NULL;
	size_t ok = num * size;
	void* p = malloc(ok);
	if(p ==NULL)
		return NULL;
	else{
		memset(p, 0, ok);
		return p;	
	}
}
void* realloc(void* ptr, size_t size){
	if(ptr == NULL)
	return malloc(size);
	if(size == 0){
	free(ptr);
	return NULL;
	}
	void * p = malloc(size);
	size_t ok = 0;
	size_t orig = ((bl*)ptr-1)->size;
	if(size < orig)
		ok =size;
	else
		ok = orig;
	memcpy(p, ptr, ok);
	free(ptr);
	return p;
}


