#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#define  BUFFER_SIZE 10	

sem_t semaphore;

int sem_wait(sem_t *s);

int sem_post(sem_t *s);

int sem_init(sem_t *sem, int pshared, unsigned int value);

int sem_destroy(sem_t *s);


typedef struct {
	char type; // 0=fried chicken, 1=French fries
	int amount; // pieces or weight
	char unit; // 0=piece, 1=gram
} item;
item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i) {
		while ((first + 1) % BUFFER_SIZE == last) {
		// do nothing -- no free buffer item
	    }
		sem_wait(&semaphore);
		memcpy(&buffer[first], i, sizeof(item));
		first = (first + 1) % BUFFER_SIZE;
		sem_post(&semaphore);
}

item* consume() {
		item *i = (item*)malloc(sizeof(item));
		while (first == last) {
		// do nothing -- nothing to consume
		}
		sem_wait(&semaphore);
		memcpy(i, &buffer[last], sizeof(item));
		last = (last + 1) % BUFFER_SIZE;
		sem_post(&semaphore);
		return i;
}

//Thread function to run 'produce'
void *produce_thread(){
	item it[3];
	//declare the items
	it[0].type = '1';
	it[0].amount = 2;
	it[0].unit = '1';

	it[1].type = '0';
	it[1].amount = 3;
	it[1].unit = '0';

	it[2].type = '1';
	it[2].amount = 5;
	it[2].unit = '0';
	//produce the items
	for (int i = 0; i < 3; ++i)
	{
		produce(&it[i]);
		printf("\nProduced item %d: %c, %d, %c\nfirst = %d, last = %d\n", i, it[i].type, it[i].amount, it[i].unit, first, last);
	}
}

//Thread function to run 'consume'
void *consume_thread(){
	item *consumed_item;
	//consume the items
	for (int i = 0; i < 3; ++i)
	{
		consumed_item = consume();
		printf("\nConsumed item %d: %c, %d, %c\nfirst = %d, last = %d\n", i, consumed_item->type, consumed_item->amount, consumed_item->unit, first, last);
	}
}

int main()
{
	sem_init(&semaphore, 0, 1);
	pthread_t tid, tid2;
	printf("Before consume: first = %d, last = %d\n", first, last); 
	pthread_create(&tid, NULL, produce_thread, NULL);		//create thread for producer
	printf("\nThread ID for produce_thread: %ld\n", tid);	//print out the Thread ID for producer
	pthread_create(&tid2, NULL, consume_thread, NULL);		//create thread for consumer
	printf("\nThread ID for consume_thread: %ld\n", tid2);	//print out the Thread ID for consumer 
	pthread_join(tid2, NULL);		//wait for thread to finish
	sem_destroy(&semaphore);
	return 0;
// I dont know why my code cant link with reference semaphore.h to highlight code but I can compile and run with :~$gcc -pthread
}
