/*
    Title: Algorithm Design and Problem Solving(CMPU1001) Assignment

    Author: D22127506 Heeyeon Yoon

    Submission Date: 07/04/2024

    Program Description: This code performs 4 tasks given for aeronautical equipment produced on 4 production lines of an engineering company
                        The program has menu with 4 options, each option number performs the each task
                        (i.e., option1 => task1, option2 => task2, ...)
                        When the user selects one of the option numbers, the program will perform corresponding task, and 
                        user can exit the program by choose option number 0. 

    Task1: Display the sorted product logs in Product ID, Issue code, date & time order for each line ordered by date & time
    The algorithm used for Task1: Merge Sort as there are huge amounts of data stored and need to sorted the data, 
                                so the running time of the algorithm should be O(NLog(N)). 
                                Therefore, I used Merge sort which is divide-and-conquer paradigm.

    Task2: Display two single lists to report issue codes by each product Id and Line code order
    The algorithm used for Task2: Circular Queue as the algorithm's running time should be O(N). 
                                Therefore, I used a Circular Queue, which operates based on FIFO (First In First Out) principle

    Task3: Search the earliest occurrence of an issue code for a given product Id across all production lines
    The algorithm used for Task3: Binary Search, Merge Sort as there are huge amounts of data stored and need to sorted the data, 
                                so the running time of the algorithm should be O(Log(N))

    Task4: Display all the issues and count the number of issues for a given product Id across all production lines
    The algorithm used for Task4: Linear Search as the algorithm's running time should be O(N). 
                                Therefore, I used Linear Search, which is the most basic of search algorithms.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define NUM_LINE 4 // Number of production lines
#define NUM_PRODUCT 10 // Number of products in each production line
#define LENGTH 100 // Length for characters
#define MAX_LOGS 40 // Number of maximum QA logs



// Structure templates
// Data of QA logs
struct logs_data
{
    int line_code;
    int batch_code;
    int date_time;
    int prod_id;
    char issue[LENGTH];
    char resol[LENGTH];
    int employee_id;
};


/* Data consists of: Line code, Batch code, Batch Date & Time (order: date-hr-min), Product ID, 
Issue Code & description, Resolution code & description, Reporting employee ID */

// The data of 10 products in Production line 1
struct logs_data prod_line1[NUM_PRODUCT] = {
    {1, 330301, 211710, 1010, "011 - Engine Overheat", "101 - Engine Coolant System Upgrade", 2401},
    {1, 330301, 220710, 1010, "009 - Crack Found", "202 - Surface replacement", 2401},
    {1, 330301, 230810, 1010, "006 - Loose Mounting Bolts", "905 - Repair Mounting Bolts", 2401},
    {1, 330305, 210915, 1009, "002 - Electrical Short Circuit", "105 - Repair Wiring", 2405},
    {1, 330305, 220915, 1009, "009 - Crack Found", "105 - Repair Wiring", 2405},
    {1, 330305, 220915, 1009, "006 - Loose Mounting Bolts", "905 - Repair Mounting Bolts", 2405},
    {1, 330309, 231010, 1002, "003 - Fuel Pressure Variability", "109 - Repair Pumps", 2409},
    {1, 330309, 241111, 1002, "009 - Crack Found", "109 - Repair Pumps", 2409},
    {1, 330309, 251212, 1002, "006 - Loose Mounting Bolts", "905 - Repair Mounting Bolts", 2409},
    {2, 330302, 210710, 1012, "005 - Wing Surface Damage", "102 - Surface Repolishing", 2402}
};

// The data of 10 products in Production line 2
struct logs_data prod_line2[NUM_PRODUCT] = {
    {2, 330302, 210810, 1012, "009 - Crack Found", "202 - Surface replacement", 2402},
    {2, 330302, 220820, 1012, "006 - Loose Mounting Bolts", "905 - Repair Mounting Bolts", 2402},
    {2, 330302, 230830, 1012, "001 - System Failure", "302 - System Check and Replacement", 2402},
    {2, 330306, 251350, 1008, "006 - Loose Mounting Bolts", "905 - Repair Mounting Bolts", 2406},
    {2, 330306, 231440, 1008, "009 - Torn Section Found", "206 - Seat Replacement", 2406},
    {2, 330306, 241020, 1008, "306 - Backrest won't go down", "905 - Repair Mounting Bolts", 2406},
    {2, 330310, 211110, 1005, "004 - Slide Stuck", "110 - Lubricate slide", 2410},
    {2, 330310, 221220, 1005, "006 - Loose Mounting Bolts", "905 - Repair Mounting Bolts", 2410},
    {2, 330310, 231330, 1005, "009 - Torn Section Found", "906 - Slide Surface Replacement", 2410},
    {1, 330309, 220107, 1002, "002 - Electrical Short Circuit", "105 - Repair Wiring", 2409}
};

// The data of 10 products in Production line 3
struct logs_data prod_line3[NUM_PRODUCT] = {
    {2, 330306, 201350, 1008, "009 - Crack Found", "206 - Seat Replacement", 2406},
    {3, 330303, 201400, 1004, "006 - Loose Mounting Bolts", "905 - Repair Mounting Bolts", 2403},
    {3, 330303, 221640, 1004, "009 - Crack Found", "103 - Window Replacement", 2403},
    {3, 330303, 231300, 1004, "029 - Wind is Leaking", "103 - Window Replacement", 2403},
    {3, 330303, 201240, 1004, "039 - Cover won't go down", "113 - Cover Replacement", 2403},
    {3, 330311, 221030, 1013, "001 - System Failure", "302 - System Check and Replacement", 2411},
    {3, 330311, 231030, 1013, "021 - Broken Strap", "322 - Mask Replacement", 2411},
    {3, 330311, 241130, 1013, "031 - Lack of the Mask", "312 - Produce more mask", 2411},
    {3, 330311, 251131, 1013, "041 - Dirt on the Mask", "322 - Mask Replacement", 2411},
    {4, 330304, 251325, 1001, "010 - Landing Tire Wear", "104 - Tire Replacement", 2404}
};

// The data of 10 products in Production line 4
struct logs_data prod_line4[NUM_PRODUCT] = {
    {4, 330304, 200845, 1001, "110 - Flat Tire", "104 - Tire Replacement", 2404},
    {4, 330304, 220910, 1001, "009 - Crack Found", "104 - Tire Replacement", 2404},
    {4, 330304, 241030, 1001, "006 - Loose Mounting Bolts", "905 - Repair Mounting Bolts", 2404},
    {4, 330308, 230900, 1007, "008 - Gear Stuck Open", "108 - Repair Mechanism", 2408},
    {4, 330308, 241000, 1007, "001 - System Failure", "118 - System Check", 2408},
    {4, 330308, 251100, 1007, "006 - Loose Mounting Bolts", "905 - Repair Mounting Bolts", 2408},
    {4, 330312, 211530, 1011, "009 - Crack found", "112 - Replace Flooring Material", 2412},
    {4, 330312, 220930, 1011, "006 - Loose Mounting Bolts", "905 - Repair Mounting Bolts", 2412},
    {4, 330312, 230830, 1011, "939 - Dirt Section found", "333 - Clean", 2412},
    {3, 330311, 221445, 1003, "101 - Torn section found", "111 - Mask System Check and Replacement", 2411}
};

// Struct for a new single list to report issue codes by product Id and line Id for all production lines
struct logs_data all_log[MAX_LOGS];


// Struct for the Circular Queue
struct CircularQueue
{
    int head, tail, size;

    // nested structure
    struct logs_data c_array[MAX_LOGS];
};


// Function signatures
void combine_logs(struct logs_data *, int, int *);
void mergeSortByDate(struct logs_data *, int, int);
void mergeByDate(struct logs_data*, int, int, int);
void mergeSortByPID(struct logs_data *, int, int);
void mergeByPID(struct logs_data*, int, int, int);
void searchEarliestOccur(struct logs_data *, int, int);
void initializeQueue(struct CircularQueue *);
void enQueue(struct CircularQueue *, struct logs_data);
void printIssueCode(struct CircularQueue *);
void searchIssues(struct logs_data *, int, int);



int main() 
{
    // Array of pointers to struct logs_data to store pointers to each production line
    struct logs_data *lines[NUM_LINE] = {prod_line1, prod_line2, prod_line3, prod_line4};
    int option_selec = 1;

    // Initialize the total number of logs to 0
    // Will pass it by address through combine_logs() function
    int total_logs = 0;

    // Combine(Merge) logs data of each production lines for task 3 and 4
    for (int i = 0; i < NUM_LINE; i++) 
    {
        combine_logs(lines[i], NUM_PRODUCT, &total_logs);
    }
    

    printf("\n\n\t  << QA logs data for the manufacturing process >>\n\n");


    do{

        printf("\n\t\t\t--- Main Menu ---\n");
        printf("\n0. End the program\n");
        printf("\n1. Order the product logs by Product ID, Issue code, and date & time (display date & time order)\n");
        printf("\n2. Display a single list to report issue codes by product Id and line Id all production lines\n");
        printf("\n3. Show the earliest occurrence of an issue code for a given product id across all production lines\n");
        printf("\n4. Show all the issues for a given product id and count the number of issues\n");

        scanf("%d", &option_selec);

        switch (option_selec) {

            case 1:
                {
                    printf("\n\n------------------------------------------------------------------------------\n");
                    printf("\n\nDisplay the product logs in Product id, Issue code, date & time order \n");
                    printf("(Ordered by date & time)\n\n\n");


                    // Call the function to order the product logs in date & time orde
                    for (int i = 0; i < NUM_LINE; i++)
                    {
                        mergeSortByDate(lines[i], 0, NUM_PRODUCT - 1);
                    }
                    

                    // Display the Ordered logs 
                    for (int i = 0; i < NUM_LINE; i++) {
                        printf("Production Line %d:\n", i + 1);
                        for (int j = 0; j < NUM_PRODUCT; j++) {
                            printf("%d, %s, %d\n", lines[i][j].prod_id, lines[i][j].issue, lines[i][j].date_time);
                        }
                        printf("\n");
                    }

                    printf("\n\n------------------------------------------------------------------------------\n\n");

                }
                
                break;

            case 2:
                {
                    // create a circular queue
                    struct CircularQueue queue;
                    initializeQueue(&queue);

                    // Enqueue all data into the circular queue
                    for (int i = 0; i < NUM_PRODUCT; i++) 
                    {
                        enQueue(&queue, prod_line1[i]);
                        enQueue(&queue, prod_line2[i]);
                        enQueue(&queue, prod_line3[i]);
                        enQueue(&queue, prod_line4[i]);
                    }
            
                    // Display a single list to report issue codes by product Id and Line code
                    printf("\n\n---------------------------------------------------------------------------------------------\n");
                    printf("\n\nDisplay two single lists to report issue codes by each product Id order and Line code order\n");
                    printIssueCode(&queue);
                
                }

                break;

            case 3:
                {
                    int input_id;

                    // Ask user to enter the product id
                    printf("\n\n------------------------------------------------------------------------------\n\n");
                    printf("\nEnter the product id:");
                    scanf("%d", &input_id);

                    // Function call for searching the earliest occurence of issuce code for the given product id
                    searchEarliestOccur(all_log, MAX_LOGS, input_id);
                }

                break;

            case 4:
                {
                    int user_inp_id;

                    // Ask user to enter the product id
                    printf("\n\n------------------------------------------------------------------------------\n\n");
                    printf("\nEnter the product id:");
                    scanf("%d", &user_inp_id);
                    printf("\n");

                    // Function call for searching all the issues for the user entered product id and count them
                    searchIssues(all_log, MAX_LOGS, user_inp_id);
                }

                break;

            default:

            break;
        }

    }while(option_selec != 0);


    return 0;
}


// Function for ordering the production line logs by date & time using Merge sort
void mergeSortByDate(struct logs_data *arr, int left, int right) 
{
    // Check if there are at least two elements to sort (if the size of array is bigger than one)
    if (left < right) 
    {
        // Calculate the middle index
        int mid = left + (right - left) / 2;

        // Sort the first half of the array
        mergeSortByDate(arr, left, mid);

        // Sort the right half of the array
        mergeSortByDate(arr, mid + 1, right);

        // Merge the sorted halves
        mergeByDate(arr, left, mid, right);
    }
} 

// Function to merge two sorted subarrays into one array by date & time order
void mergeByDate(struct logs_data *arr, int left, int mid, int right) 
{
    // Calculate the sizes of the left and right subarrays
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Make temporary arrays to hold the left and right subarrays
    struct logs_data L[n1], R[n2];


    // Copy data from the original array to the temporary left array (L)
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
        
    // Copy data from the original array to the temporary right array (R)
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }


    // Initialize indices for merging process
    int i = 0; // Index for the left subarray
    int j = 0; // Index for the right subarray
    int k = left; // Index for the merged array


    while (i < n1 && j < n2) 
    {
        // Check if the elements of date_time in the left side of array is faster(smaller) than the elements in the right side of array
        if (L[i].date_time <= R[j].date_time) 
        {
            // Store the element from the left subarray into the main array
            arr[k] = L[i];
            i++;

        } else 
        {
            // Store the element from the right subarray into the main array
            arr[k] = R[j];
            j++;
        }

        // increase k (move k to right side)
        k++;

    }

    while (i < n1) 
    {
        // copy any remaining elements from the left subarray to the main array
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) 
    {
        // copy ant remaining elements from the right subarray to the main array
        arr[k] = R[j];
        j++;
        k++;
    }

}

// Function for ordering the production line logs by Product ID using Merge sort
void mergeSortByPID(struct logs_data *arr, int left, int right) 
{
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort the first half side
        mergeSortByPID(arr, left, mid);

        // Sort the second half side
        mergeSortByPID(arr, mid + 1, right);

        // Merge the sorted halves
        mergeByPID(arr, left, mid, right);
    }
} 


// Function to merge two sorted subarrays into one array by product id order
void mergeByPID(struct logs_data *arr, int left, int mid, int right) 
{
    // Calculate the sizes of the left and right subarrays
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // make temporary array to hold the subarrays
    struct logs_data L[n1], R[n2];


    // Copy data from the original(main) array to the left array (L)
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
        
    // Copy data from the original(main) array to the right array (R)
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }


    int i = 0;
    int j = 0;
    int k = left;
    

    while (i < n1 && j < n2) 
    {
        // Check if the elements of date_time in the left side of array is faster(smaller) than the elements in the right side of array
        if (L[i].prod_id <= R[j].prod_id) 
        {
            // Store the elements from the left array into the entire array sequentially from the left
            arr[k] = L[i];
            i++;

        } else 
        {
            // Store the elements from the right array into the entire array sequentially from the left
            arr[k] = R[j];
            j++;
        }

        // increase k (move k to right side)
        k++;

    }

    while (i < n1) 
    {
        // copy any remaining elements from the left subarray to the main array
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) 
    {
        // copy any remaining elements from the right subarray to the main array
        arr[k] = R[j];
        j++;
        k++;
    }

}

// Function to initialize Circular Queue
void initializeQueue(struct CircularQueue *queue)
{
    // initialize head, tail pointer to indicate the queue is empty
    queue->head = -1; // = (*queue).head = -1;
    queue->tail = -1;
    // initialize the size of the queue to 0 since it’s empty
    queue->size = 0;
}


// Function to enqueue an element into Circular Queue
void enQueue(struct CircularQueue *queue, struct logs_data prod_data)
{
    if (queue->size == 0)
    {
        // If the queue is empty, set the head to 0 to start from the beginning
        queue->head = 0;
    }

    // Calculate the position where the new element will be added in a queue 
    queue->tail = (queue->tail + 1) % (MAX_LOGS);
    // Add the new data to the queue in c_array
    queue->c_array[queue->tail] = prod_data;
    // Increment the size of the queue due to the addition of a new data
    queue->size++;
}
    


// Function to print issue codes by Product ID order and Line Code order
void printIssueCode(struct CircularQueue *queue)
{
    printf("\n\n  --- Issue codes by Product ID order ---\n\n");

    // Create an array to store issue codes based on product ID and line code order
    struct logs_data issueCodes[MAX_LOGS];
    int index = 0;

    // Store issue codes in the array
    int i = queue->head;
    int count = queue->size;

    while (count > 0)
    {
        // Retrieve issue code at position i and store it into array of issueCodes
        issueCodes[index++] = queue->c_array[i];
        // Move to the next position in the queue
        i = (i+1) % (MAX_LOGS);
        count--;
    }

    
    // Sort the array based on product ID
    for (int i = 0; i < (MAX_LOGS); i++)
    {
        for (int j = i + 1; j < (MAX_LOGS); j++)
        {
            if (issueCodes[i].prod_id > issueCodes[j].prod_id)
            {
                struct logs_data temp = issueCodes[i];
                issueCodes[i] = issueCodes[j];
                issueCodes[j] = temp;
            }   
        }
    }


    // Print the sorted issue codes by product Id order
    printf("\nProduct ID\tIssue Code & Description\n\n");
    for (int i = 0; i < MAX_LOGS; i++)
    {
        printf("%d\t\t%s\n", issueCodes[i].prod_id, issueCodes[i].issue);
    }


    printf("\n\n------------------------------------------------------------------------------\n");
    printf("\n\n  --- Issue codes by Line Code order ---\n\n");
    

    // Sort the array based on Line code
    for (int i = 0; i < (MAX_LOGS); i++)
    {
        for (int j = i + 1; j < (MAX_LOGS); j++)
        {
            if (issueCodes[i].line_code > issueCodes[j].line_code)
            {
                struct logs_data temp = issueCodes[i];
                issueCodes[i] = issueCodes[j];
                issueCodes[j] = temp;
            }   
        }
    }

    // Print the sorted issue codes line code order            
    printf("\nLine Code\tIssue Code & Description\n\n");
    for (int i = 0; i < MAX_LOGS; i++)
    {
        printf("%d\t\t%s\n", issueCodes[i].line_code, issueCodes[i].issue);
    }

    
    printf("\n\n------------------------------------------------------------------------------\n");


}


// Function for copying all the logs data from each production lines to the single list
void combine_logs(struct logs_data *prod_logs, int num_logs, int *total_logs) 
{
    for (int i = 0; i < num_logs; i++) 
    {
        all_log[*total_logs] = prod_logs[i];
        (*total_logs)++;
    }
}


// Function for searching the earliest occurrence of an issue code for a given product id 
void searchEarliestOccur(struct logs_data *logs, int size, int inp_prod_id) 
{
    // Sort the array logs for binary search
    mergeSortByPID(logs, 0, size - 1);
    

    // Initialize the earliestIndex to -1, in case the product id that user entered is not found in the logs
    int earliestIndex = -1;
    int low = 0;
    int high = size -1;


    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (logs[mid].prod_id == inp_prod_id)
        {
            // Store the index of the earliest occurrence
            earliestIndex = mid;
            high = mid - 1; // continue search at the left side

        } 
        else if (logs[mid].prod_id < inp_prod_id)
        {
           low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
        
    }

    // If the earliestIndex is not equal to -1, that means it has the issue code for user entered product id
    // If the earliestIndex is equal to -1, that means it doesn't have the issue code for user entered product id
    if (earliestIndex != -1) 
    {
        // Traverse backwards from the earliestIndex to find the first occurrence of the product id
        while (earliestIndex > 0 && logs[earliestIndex - 1].prod_id == inp_prod_id)
        {
            earliestIndex--;
        }

        printf("\n\nData of the earliest occurrence of issue code for product id %d\n\n", inp_prod_id);
        printf("Line Code: %d\n", logs[earliestIndex].line_code);
        printf("Batch Code: %d\n", logs[earliestIndex].batch_code);
        printf("Date & Time: %d\n", logs[earliestIndex].date_time);
        printf("Issue: %s\n", logs[earliestIndex].issue);

        printf("\n\n------------------------------------------------------------------------------\n\n");

    } 
    else 
    {
        printf("\nIssue code for product id %d not found in the logs.\n", inp_prod_id);

    }
}


// Function for searching all the issues for given product id and count them
void searchIssues(struct logs_data *logs, int size, int inp_id)
{
    int count = 0;

    // Initialize the searchPdID to -1, in case the product id that user entered is not found in the logs
    int searchPdID = -1;

    for (int i = 0; i < size; i++)
    {
        if (logs[i].prod_id == inp_id)
        {
            count++;
            printf("\nIssue %d: %s\n", count, logs[i].issue);

            searchPdID = i;
        }
    }

    if (searchPdID == -1)
    {
        printf("\nProduct id %d not found in the logs.\n", inp_id);

    }
    else
    {
        printf("\n\nThe total number of issues reported for a product id %d: %d\n", inp_id, count);
    }
    
    printf("\n\n------------------------------------------------------------------------------\n\n");

}   