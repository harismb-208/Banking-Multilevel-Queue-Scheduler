#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Define transaction structure
typedef struct {
    int transaction_id;
    int priority;
    int processing_time;
    int arrival_time;
    int wait_time;
    int turn_around_time;
    int completion_time;
    int remaining_time;
    char transaction_type[30];
} Transaction;

// Define queue structure
typedef struct {
    Transaction *transactions;
    int front, rear, size, capacity;
    char name[30];
    int time_quantum;
} Queue;

// Function prototypes
Queue* createQueue(int capacity, const char *name, int time_quantum);
void enqueue(Queue* queue, Transaction transaction);
Transaction dequeue(Queue* queue);
void processTransactions(Queue* highPriorityQueue, Queue* mediumPriorityQueue, Queue* lowPriorityQueue, Transaction* transactions, int n);
void calculateTimes(Transaction* transactions, int n);
void displayGanttChart(Transaction* transactions, int n);
void displayTransactionTable(Transaction* transactions, int n);
void displayAverages(Transaction* transactions, int n);

int main() {
    int n, i, priorityChoice;
    int samePriority = 0;

    printf("Do you want all transactions to have the same priority level?\n(1 = Yes, 0 = No):");
    scanf("%d", &samePriority);

    if (samePriority == 1) {
        printf("\nSelect priority level: \n1 - High (Cash Withdrawal, Transfer)\n2 - Medium (Bill Payment, Balance Check)\n3 - Low (Loan Processing, Account Creation)\n\nEnter choice: ");
        scanf("%d", &priorityChoice);
    }

    Queue* highPriorityQueue = createQueue(10, "High Priority", 2);
    Queue* mediumPriorityQueue = createQueue(10, "Medium Priority", 0);
    Queue* lowPriorityQueue = createQueue(10, "Low Priority", 0);

    printf("\nEnter number of transactions:");
    scanf("%d", &n);
    printf("\n");
    Transaction transactions[n];

    for (i = 0; i < n; i++) {
        transactions[i].transaction_id = i + 1;

        if (samePriority) {
            transactions[i].priority = priorityChoice;
        } else {
            printf("Enter priority (1-High, 2-Medium, 3-Low) for transaction %d: ", transactions[i].transaction_id);
            scanf("%d", &transactions[i].priority);
        }
        
        printf("Enter processing time and arrival time for transaction %d: ", transactions[i].transaction_id);
        scanf("%d %d", &transactions[i].processing_time, &transactions[i].arrival_time);
        printf("\n");

        transactions[i].remaining_time = transactions[i].processing_time;
        transactions[i].wait_time = 0;
        transactions[i].turn_around_time = 0;
        transactions[i].completion_time = 0;

        if (transactions[i].priority == 1) {
            strcpy(transactions[i].transaction_type, "Cash Withdrawal/Fund Transfer");
            enqueue(highPriorityQueue, transactions[i]);
        } else if (transactions[i].priority == 2) {
            strcpy(transactions[i].transaction_type, "Bill Payment/Balance Check");
            enqueue(mediumPriorityQueue, transactions[i]);
        } else {
            strcpy(transactions[i].transaction_type, "Loan Processing/Account Creation");
            enqueue(lowPriorityQueue, transactions[i]);
        }
    }

    printf("\nProcessing transactions...\n\n");

    processTransactions(highPriorityQueue, mediumPriorityQueue, lowPriorityQueue, transactions, n);
    calculateTimes(transactions, n);
    displayGanttChart(transactions, n);
    displayTransactionTable(transactions, n);
    displayAverages(transactions, n);

    return 0;
}

// Function definitions
Queue* createQueue(int capacity, const char *name, int time_quantum) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->transactions = (Transaction*)malloc(queue->capacity * sizeof(Transaction));
    strcpy(queue->name, name);
    queue->time_quantum = time_quantum;
    return queue;
}

void enqueue(Queue* queue, Transaction transaction) {
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->transactions[queue->rear] = transaction;
    queue->size += 1;
}

Transaction dequeue(Queue* queue) {
    if (queue->size == 0) {
        printf("Error: Queue is empty!\n");
        exit(1);
    }
    Transaction transaction = queue->transactions[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size -= 1;
    return transaction;
}

void processTransactions(Queue* highPriorityQueue, Queue* mediumPriorityQueue, Queue* lowPriorityQueue, Transaction* transactions, int n) {
    int current_time = 0;
    int gantt_chart[n], completion_times[n], index = 0;

    while (highPriorityQueue->size > 0) {
        Transaction t = dequeue(highPriorityQueue);
        gantt_chart[index++] = t.transaction_id;
        sleep(t.processing_time);
        current_time += t.processing_time;
        completion_times[t.transaction_id - 1] = current_time;
    }

    while (mediumPriorityQueue->size > 0) {
        Transaction t = dequeue(mediumPriorityQueue);
        gantt_chart[index++] = t.transaction_id;
        sleep(t.processing_time);
        current_time += t.processing_time;
        completion_times[t.transaction_id - 1] = current_time;
    }

    while (lowPriorityQueue->size > 0) {
        Transaction t = dequeue(lowPriorityQueue);
        gantt_chart[index++] = t.transaction_id;
        sleep(t.processing_time);
        current_time += t.processing_time;
        completion_times[t.transaction_id - 1] = current_time;
    }

    for (int i = 0; i < n; i++) {
        transactions[i].completion_time = completion_times[i];
    }
}

// Function to display Gantt Chart
void displayGanttChart(Transaction* transactions, int n) {
    printf("\nGantt Chart:\n");

    // Top Border
    for (int i = 0; i < n; i++) {
        printf("------");
    }
    printf("\n");

    // Transaction IDs
    for (int i = 0; i < n; i++) {
        printf("| T%d ", transactions[i].transaction_id);
    }
    printf("|\n");

    // Bottom Border
    for (int i = 0; i < n; i++) {
        printf("------");
    }
    printf("\n");

    // Time Line
    int time = 0;
    printf("0    ");
    for (int i = 0; i < n; i++) {
        time = transactions[i].completion_time;
        printf("%d    ", time);
    }
    printf("\n");
}

void calculateTimes(Transaction* transactions, int n) {
    for (int i = 0; i < n; i++) {
        transactions[i].turn_around_time = abs(transactions[i].completion_time - transactions[i].arrival_time);
        transactions[i].wait_time = abs(transactions[i].turn_around_time - transactions[i].processing_time);
    }
}


void displayTransactionTable(Transaction* transactions, int n) {
    printf("\nTransaction Table:\n");
    printf("ID\tAT\tPT\tCT\tTAT\tWT\tType\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%s\n", transactions[i].transaction_id, transactions[i].arrival_time, transactions[i].processing_time, transactions[i].completion_time, transactions[i].turn_around_time, transactions[i].wait_time, transactions[i].transaction_type);
    }
}

void displayAverages(Transaction* transactions, int n) {
    float total_tat = 0, total_wt = 0;
    
    for (int i = 0; i < n; i++) {
        total_tat += transactions[i].turn_around_time;
        total_wt += transactions[i].wait_time;
    }

    printf("\nAverage Turnaround Time: %.2f seconds\n", total_tat / n);
    printf("Average Waiting Time: %.2f seconds\n", total_wt / n);
}
