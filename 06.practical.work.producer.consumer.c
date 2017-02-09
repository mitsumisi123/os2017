#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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

int main(){

item a;
	a.type = '0';
	a.amount = 0;
	a.unit = '0';

item b;
	b.type = '1';
	b.amount = 1;
	b.unit = '1';

	printf("a: Type: %c   amount: %d   unit: %c  \n", a.type, a.amount, a.unit);
	printf("b: Type: %c   amount: %d   unit: %c \n",  b.type, b.amount, b.unit);

	produce(&a);
	printf("produce a: \n first value: %d  last : %d  \n", first, last);
	produce(&b);
	printf("produce b: \n first value: %d  last : %d  \n", first, last);

	consume();
	printf("Consume: \n first %d last : %d\n", first, last);

}


















