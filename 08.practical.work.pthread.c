#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define BUFFER_SIZE 10


typedef struct{

  char type;           // 0=fried chicken, 1=French fries

  int amount;          // pieces or weight   

  char unit;          // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];

int first = 0;

int last = 0;

void produce(item *i) {
	while ((first + 1) % BUFFER_SIZE == last) {
		// do nothing -- no free buffer item
	}
	
	memcpy(&buffer[first], i, sizeof(item));
	
	first = (first + 1) % BUFFER_SIZE;
}


item *consume() {
   item *i = malloc(sizeof(item));

   while(first == last) {
   // do nothing -- nothing to consume
                        }

   memcpy(i, &buffer[last],sizeof(item));

   last = (last + 1) % BUFFER_SIZE;

   return i;
}

void setItem(item i, char t, int a , char u){
	i.type = t;
	i.amount = a;
	i.unit = u;
}

void show(int n,item I[]){
	for(int i=0;i<n;i++){
    printf("I[%d]: Type: %c   amount: %d   unit: %c  \n",i, I[i].type, I[i].amount, I[i].unit);
}
}
void *produce_thread(int n,item I[]){
	for(int i=0;i<n;i++){
	produce(&I[i]);
	printf("produce I[%d]:: \n first value: %d  last : %d  \n",i, first, last);
}
}

void *consume_thread(int n){
	for(int i=0;i<n;i++){
		consume();
	printf("Consume: \n first %d last : %d\n", first, last);
}
}



int main(){
item I[3];
setItem(I[0],'0',1,'0');
setItem(I[1],'1',1,'0');
setItem(I[2],'0',1,'1');    

show(3,I);
	
pthread_t tid_produce;
pthread_t tid_consume;
	
	pthread_create(&tid_produce,NULL,produce_thread(3,I),NULL);
	pthread_create(&tid_consume,NULL,consume_thread(2),NULL);
	
pthread_join(tid_produce, NULL);
pthread_join(tid_consume, NULL);

}


















