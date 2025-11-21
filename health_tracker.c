#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Data Structure Definitions ---

/**
 * @brief Structure to hold the health metrics for a single day.
 */
typedef struct HealthMetric {
    char date[11];      // Date in YYYY-MM-DD format (10 chars + null terminator)
    int steps;          // Step count
    int calories_burned; // Calories burned
    float sleep_hours;  // Hours of sleep
} Metric;

/**
 * @brief Node structure for the Doubly Linked List.
 * This is the core Data Structure (DSA) component.
 */
typedef struct RecordNode {
    Metric data;
    struct RecordNode *prev;
    struct RecordNode *next;
} RecordNode;

// Global head and tail pointers for the Doubly Linked List
RecordNode *head = NULL;
RecordNode *tail = NULL;

// --- Utility Functions ---

/**
 * @brief Generates a new Doubly Linked List Node and allocates memory.
 * @param newMetric The Metric data to store in the node.
 * @return A pointer to the newly created node.
 */
RecordNode* createNode(Metric newMetric) {
    RecordNode *newNode = (RecordNode*)malloc(sizeof(RecordNode));
    if (newNode == NULL) {
        printf("\n[ERROR] Memory allocation failed! Exiting.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = newMetric;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

/**
 * @brief Inserts a new metric record at the end of the Doubly Linked List.
 * This ensures chronological order.
 * @param newMetric The Metric data to be inserted.
 */
void insertRecord(Metric newMetric) {
    RecordNode *newNode = createNode(newMetric);

    if (head == NULL) {
        // List is empty
        head = newNode;
        tail = newNode;
    } else {
        // Append to the end
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    printf("\n[SUCCESS] Record for %s successfully added.\n", newMetric.date);
}

// --- Core Functionality ---

/**
 * @brief Prompts the user for metric data and inserts it into the list.
 */
void addNewRecord() {
    Metric newMetric;
    char date_input[100];
    
    printf("\n--- Add New Health Record ---\n");
    
    // Auto-generate current date for convenience
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(newMetric.date, sizeof(newMetric.date), "%Y-%m-%d", tm);
    
    printf("Enter Date (YYYY-MM-DD) [Default: %s]: ", newMetric.date);
    if (scanf("%99s", date_input) != 1) { /* error handling */ return; }
    // If the user entered nothing, use the default date
    if (strcmp(date_input, newMetric.date) != 0) {
        strncpy(newMetric.date, date_input, 10);
        newMetric.date[10] = '\0'; // Ensure null termination
    }

    printf("Enter Step Count: ");
    if (scanf("%d", &newMetric.steps) != 1) { printf("[ERROR] Invalid input.\n"); return; }
    
    printf("Enter Calories Burned: ");
    if (scanf("%d", &newMetric.calories_burned) != 1) { printf("[ERROR] Invalid input.\n"); return; }
    
    printf("Enter Sleep Hours (e.g., 7.5): ");
    if (scanf("%f", &newMetric.sleep_hours) != 1) { printf("[ERROR] Invalid input.\n"); return; }
    
    insertRecord(newMetric);
}

/**
 * @brief Displays all stored health records by traversing the Doubly Linked List.
 */
void displayRecords() {
    if (head == NULL) {
        printf("\n[INFO] No records found. Add some data first.\n");
        return;
    }
    
    printf("\n--- Historical Health Records ---\n");
    printf("| %-10s | %-8s | %-12s | %-8s |\n", "Date", "Steps", "Calories", "Sleep (h)");
    printf("|------------|----------|--------------|----------|\n");
    
    RecordNode *current = head;
    while (current != NULL) {
        printf("| %-10s | %-8d | %-12d | %-8.1f |\n", 
               current->data.date, 
               current->data.steps, 
               current->data.calories_burned, 
               current->data.sleep_hours);
        current = current->next;
    }
    printf("|------------|----------|--------------|----------|\n");
}

/**
 * @brief Calculates and prints a summary (total and average) of all metrics.
 */
void calculateSummary() {
    if (head == NULL) {
        printf("\n[INFO] No records found to calculate summary.\n");
        return;
    }
    
    long long totalSteps = 0;
    long long totalCalories = 0;
    float totalSleepHours = 0.0f;
    int count = 0;
    
    // Variables for min/max
    int maxSteps = -1;
    int minSteps = 99999999;
    char dateMaxSteps[11] = "";
    char dateMinSteps[11] = "";

    RecordNode *current = head;
    while (current != NULL) {
        totalSteps += current->data.steps;
        totalCalories += current->data.calories_burned;
        totalSleepHours += current->data.sleep_hours;
        count++;

        // Find Max Steps
        if (current->data.steps > maxSteps) {
            maxSteps = current->data.steps;
            strcpy(dateMaxSteps, current->data.date);
        }
        // Find Min Steps
        if (current->data.steps < minSteps) {
            minSteps = current->data.steps;
            strcpy(dateMinSteps, current->data.date);
        }
        
        current = current->next;
    }

    printf("\n--- Health Metrics Summary (%d Days) ---\n", count);
    
    // Average Calculations
    printf("\n[Average Metrics]\n");
    printf("  Average Steps:         %.2f\n", (float)totalSteps / count);
    printf("  Average Calories Burned: %.2f\n", (float)totalCalories / count);
    printf("  Average Sleep Hours:   %.2f\n", totalSleepHours / count);
    
    // Total Calculations
    printf("\n[Total Metrics]\n");
    printf("  Total Steps Tracked:     %lld\n", totalSteps);
    printf("  Total Calories Tracked:  %lld\n", totalCalories);
    printf("  Total Sleep Hours Tracked: %.1f\n", totalSleepHours);

    // Min/Max Analysis
    printf("\n[Performance Analysis]\n");
    printf("  Best Step Day: %d steps on %s\n", maxSteps, dateMaxSteps);
    printf("  Worst Step Day: %d steps on %s\n", minSteps, dateMinSteps);
}

/**
 * @brief Provides a simple text-based bar chart visualization for Steps.
 * This demonstrates basic data visualization using C.
 */
void visualizeSteps() {
    if (head == NULL) {
        printf("\n[INFO] No records found for visualization.\n");
        return;
    }

    printf("\n--- Text Visualization: Step Count ---\n");
    
    RecordNode *current = head;
    int maxSteps = 0;
    
    // First pass: Find the maximum step count for scaling
    while (current != NULL) {
        if (current->data.steps > maxSteps) {
            maxSteps = current->data.steps;
        }
        current = current->next;
    }
    
    if (maxSteps == 0) {
        printf("\n[INFO] All step counts are zero.\n");
        return;
    }
    
    // Second pass: Print the chart
    current = head;
    printf("Scale: One '#' represents approx. %d steps.\n\n", maxSteps / 50 + 1);
    
    while (current != NULL) {
        int barLength = (current->data.steps * 50) / maxSteps; // Scale to fit in max 50 characters
        
        printf("%s | %-5d | ", current->data.date, current->data.steps);
        
        for (int i = 0; i < barLength; i++) {
            printf("#");
        }
        printf("\n");
        
        current = current->next;
    }
    printf("\n");
}


/**
 * @brief Frees all memory allocated for the Doubly Linked List nodes.
 */
void cleanup() {
    RecordNode *current = head;
    RecordNode *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
    tail = NULL;
    printf("\n[INFO] All memory successfully freed. Exiting program.\n");
}

// --- Main Program and Menu ---

int main() {
    int choice;

    // Set up initial dummy data for testing the visualization and summary
    Metric day1 = {"2025-01-01", 12500, 2500, 7.5};
    Metric day2 = {"2025-01-02", 7800, 1800, 6.0};
    Metric day3 = {"2025-01-03", 15200, 3000, 8.2};
    insertRecord(day1); // Insertion adds data and links nodes
    insertRecord(day2);
    insertRecord(day3);
    
    // Main Menu Loop
    do {
        printf("\n============================================\n");
        printf("  Personal Health Metrics Tracker (DSA Project)\n");
        printf("============================================\n");
        printf("1. Add New Daily Record (Steps, Calories, Sleep)\n");
        printf("2. View All Historical Records\n");
        printf("3. Calculate and View Summary Statistics (Averages/Totals/Min/Max)\n");
        printf("4. Visualize Step Count (Text Bar Chart)\n");
        printf("5. Exit and Cleanup\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            // Handle non-integer input to prevent infinite loop
            while (getchar() != '\n'); 
            choice = 0;
            printf("\n[ERROR] Invalid input. Please enter a number from the menu.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addNewRecord();
                break;
            case 2:
                displayRecords();
                break;
            case 3:
                calculateSummary();
                break;
            case 4:
                visualizeSteps();
                break;
            case 5:
                cleanup();
                break;
            default:
                printf("\n[WARNING] Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}