//necessary directives
#include <stdio.h> //printf() and scanf()
#include <stdlib.h> //dynamic memory allocation
#include <string.h> //strcpy() and strcmp()
#include <stdbool.h> //boolean operations

//create a structure for employee data
struct Employee {
    char name[30]; //employee name
    int emp_id; //employee ID
    int years_of_experience; //years of experience
};

// Function prototypes
void createEmployee(struct Employee employees[], int *count); //reflect the changes
void displayEmployees(struct Employee employees[], int count); //pass by value
void updateEmployee(struct Employee employees[], int count); //pass by value
void deleteEmployee(struct Employee employees[], int *count); //reflect the changes
bool isNameExist(struct Employee employees[], int count, const char *name); //const as pointer is used
bool isEmployeeIdExist(struct Employee employees[], int count, int emp_id); //by default value is passed

int main() {
    struct Employee employees[50];  // Array to store employee records
    int count = 0;  // Variable to keep track of number of employees
    int choice; //declaration of menu variable
    
    do {
        // Menu
        printf("\n--- Employee Information System ---\n");
        printf("1. Create Employee\n");
        printf("2. Display Employee(s)\n");
        printf("3. Update Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice(1-5): ");
        scanf("%d", &choice);

        //menu to function mapping
        switch (choice) {
            case 1:
                createEmployee(employees, &count);
                break;
            case 2:
                displayEmployees(employees, count);
                break;
            case 3:
                updateEmployee(employees, count);
                break;
            case 4:
                deleteEmployee(employees, &count);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 to 5.\n");
        }
    } while (choice != 5);//exit control condition

    return 0;
}

// Function to check if a name already exists
bool isNameExist(struct Employee employees[], int count, const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(employees[i].name, name) == 0) {
            return true;
        }
    }
    return false;
}

// Function to check if an employee ID already exists
bool isEmployeeIdExist(struct Employee employees[], int count, int emp_id) {
    for (int i = 0; i < count; i++) {
        if (employees[i].emp_id == emp_id) {
            return true;
        }
    }
    return false;
}

// Function to create a new employee
void createEmployee(struct Employee employees[], int *count) {
    if (*count >= 50) { //checking allocated memory
        printf("Cannot add more employees. Array is full.\n");
        return;
    }
    printf("Create an Employee\n");
    struct Employee newEmployee;
    printf("Enter name: ");
    scanf(" %[^\n]s", newEmployee.name);  // Read name with spaces

    // Check if name already exists
    if (isNameExist(employees, *count, newEmployee.name)) {
        printf("Employee with the same name already exists.\n");
        return;
    }

    printf("Enter employee ID: ");
    scanf("%d", &newEmployee.emp_id);

    // Check if employee ID already exists
    if (isEmployeeIdExist(employees, *count, newEmployee.emp_id)) {
        printf("Employee with the same ID already exists.\n");
        return;
    }

    printf("Enter years of experience: ");
    scanf("%d", &newEmployee.years_of_experience);

    employees[*count] = newEmployee; //add the details to structure variable
    (*count)++; //incrementing 

    printf("Employee added successfully.\n"); //prompt message
}

// Function to display employees
void displayEmployees(struct Employee employees[], int count) {
    if (count == 0) {
        printf("No employees to display.\n");
        return;
    }

    int choice;
    printf("\n--- Display Options ---\n");
    printf("1. Display All Employees\n");
    printf("2. Display Specific Employee\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("\nList of Employees:\n");
            for (int i = 0; i < count; i++) {
                printf("Employee %d:\n", i + 1);
                printf("Name: %s\n", employees[i].name);
                printf("Employee ID: %d\n", employees[i].emp_id);
                printf("Years of Experience: %d\n", employees[i].years_of_experience);
                printf("\n");
            }
            break;
        case 2:
            {
                int emp_id;
                printf("Enter employee ID of the employee to display: ");
                scanf("%d", &emp_id);

                int found = 0;
                for (int i = 0; i < count; i++) {
                    if (employees[i].emp_id == emp_id) {
                        printf("\nEmployee Details:\n");
                        printf("Name: %s\n", employees[i].name);
                        printf("Employee ID: %d\n", employees[i].emp_id);
                        printf("Years of Experience: %d\n", employees[i].years_of_experience);
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("Employee with ID %d not found.\n", emp_id);
                }
            }
            break;
        default:
            printf("Invalid choice.\n");
    }
}

// Function to update employee details
void updateEmployee(struct Employee employees[], int count) {
    if (count == 0) {
        printf("No employees to update.\n");
        return;
    }
    printf("Update an employee\n");
    int emp_id;
    printf("Enter employee ID of the employee to update: ");
    scanf("%d", &emp_id);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (employees[i].emp_id == emp_id) {
            int choice;
            printf("Which detail to update?\n");
            printf("1. Name\n");
            printf("2. Years of Experience\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter updated name: ");
                    scanf(" %[^\n]s", employees[i].name);
                    printf("Name updated successfully.\n");
                    break;
                case 2:
                    printf("Enter updated years of experience: ");
                    scanf("%d", &employees[i].years_of_experience);
                    printf("Years of experience updated successfully.\n");
                    break;
                default:
                    printf("Invalid choice.\n");
            }

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", emp_id);
    }
}

// Function to delete an employee
void deleteEmployee(struct Employee employees[], int *count) {
    if (*count == 0) {
        printf("No employees to delete.\n");
        return;
    }

    int emp_id;
    printf("Enter employee ID of the employee to delete: ");
    scanf("%d", &emp_id);

    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (employees[i].emp_id == emp_id) {
            // Delete the employee record
            for (int j = i; j < *count - 1; j++) {
                employees[j] = employees[j + 1];
            }
            (*count)--;
            printf("Employee with ID %d deleted successfully.\n", emp_id);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", emp_id);
    }
}
