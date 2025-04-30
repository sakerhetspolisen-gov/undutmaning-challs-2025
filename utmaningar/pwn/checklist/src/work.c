#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

#define FLAG "__NOT_THE_REAL_FLAG__(or_is_it? [It is not] )"
#define wow 1234


#define MAX_INPUT 128

#define WORK_SIZE 128
#define WORK_ITEMS 32
struct work;
typedef void (*work_func_t)(struct work *);
struct work { 
    work_func_t formater;
    char str_data[WORK_SIZE-sizeof(void*)];
};


struct context {
    struct work work_queue[WORK_ITEMS];
    void * pad; //TODO FIXME: Consider removing this padding allowin the index to changed as a red herring
    size_t index;
};
struct context ctx = {0};

size_t counter = 0; 

void handle_normal();
void normal_print(struct work * work  ) {
    printf("%s\n", work->str_data);
}

void print_the_flag(struct work * work ){
    char * flag = getenv("LAUNCH_CODE");
    printf("The launch code is %s .\n", flag);
}

void print_bar(struct work * work ){
    printf("====================================================\n");
}

void print_deferred(struct work * work ){
    printf("[DEFERRED LINE TEMPLATE]");
}



void __attribute__((noinline)) print_info(void){
    printf("\nTake an action, write a number\n");
    printf("We currently have %lu  out of %lu items in the checklist.\n", ctx.index, WORK_ITEMS);
    printf("1. Add a bar ========= \n");
    printf("2. Add a line\n");
    printf("3. Add a deferred line.\n");
    printf("4. Populate deferred lines.\n");
    printf("5. Add Launch code [RESTRICTED]\n");
    printf("7. Reset list\n");
    printf("8. Print list\n");
    printf("99. Exit!\n");

}

void __attribute__((noinline)) handle_normal(){
    if (!(ctx.index < WORK_ITEMS)){
        printf("The checklist is full can not add any more items! Print it?\n");
        return;
    }
    printf("Write the checklist item to be added!\n");
    struct work * item = &ctx.work_queue[ctx.index++];

    item->formater = normal_print;

    (void)fgets(item->str_data, sizeof(struct work), stdin);
}

void __attribute__((noinline)) handle_deferred(){
    if (!(ctx.index < WORK_ITEMS)){
        printf("The checklist is full can not add any more items! Print it?\n");
        return;
    }
    struct work * item = &ctx.work_queue[ctx.index++];

    item->formater = print_deferred;
}



void __attribute__((noinline)) handle_priv(){
    if (!(ctx.index < WORK_ITEMS)){
        printf("The checklist is full can not add any more items! Print it?\n");
        return;
    }

    char * auth = getenv("LAUNCH_ALLOWED");
    if(!auth || strcmp(auth, "yes")){
        printf("Adding the launch codes is not allowed!\n");
        return;
    }
    struct work * item = &ctx.work_queue[ctx.index++];

    item->formater = print_the_flag;
}


void __attribute__((noinline)) handle_populate(void){
    int count = 0;
    for(int i = 0; i < ctx.index; i++){
        struct work * item  = &ctx.work_queue[i];
        if(item->formater == print_deferred){
            count++;
            printf("Update the deferred item to be added!\n");
            struct work * item = &ctx.work_queue[i];

            item->formater = normal_print;

            (void)fgets(item->str_data, sizeof(struct work), stdin);    
        }
    }
    printf("Updated %d deferred lines...\n", count);
}

void __attribute__((noinline)) handle_print(void){
    for(int i = 0; i < ctx.index; i++){
        printf("%d: ", i+1);
        struct work * item = &ctx.work_queue[i];
        item->formater(item);
    }
}


void __attribute__((noinline)) add_bar(void){
    if (!(ctx.index < WORK_ITEMS)){
        printf("The checklist is full can not add any more items! Print it?\n");
        return;
    }
    struct work * item = &ctx.work_queue[ctx.index++];
    item->formater = print_bar;
}



void alarmHandler(int pass) {
    printf("TIMEOUT!\n");
    exit(1);
}

// Point to alarmHandler for SIGALRM and
// disable buffering on I/O
void setup() {
    struct sigaction act;
    act.sa_handler = alarmHandler;
    sigaction(SIGALRM, &act, NULL);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    alarm(300);
}

int main (void )
{
    

    char input[MAX_INPUT];
    setup();
    printf("Welcome the main list maker at star address 0x%lx \n", (((uint64_t) main) & 0xffffffffff000000)); //24

  while (1) {
    print_info();
    printf("# ");
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
      printf("Error reading input.\n");
      continue;
    }
    int action = atoi(input);
    switch (action) {
        case 1: {
            add_bar();
            break;
        }
        case 2: {
            handle_normal();
            break;
        }
        case 3: {
            handle_deferred();
            break;
        }
        case 4: {
            handle_populate();
            break;
        }
        case 5: {
            handle_priv();
            break;
        }
        case  7 : {
            ctx.index = 0;
            break;
        }
        case 8: {
            handle_print();
            break;
        } 
        case 99:
        {
            exit(0);
        }
        default : 
            continue;
    }

  }

    
}
