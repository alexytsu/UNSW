#include <stdio.h>

typedef struct employee_t{
    int employeeID;
    char name[64];
    char jobTitle[64];
}Employee;

void print_employee_id(Employee e);
int set_employee_id(Employee *e);

int main(void){
    Employee test_employee;
    set_employee_id(&test_employee);
    print_employee_id(test_employee);

    Employee accounting_department[500];
    for(int i = 0; i < 500; i ++){
        set_employee_id(&accounting_department[i]);
        //can implement functions here to read details from stdin or a file
    }
    for(int i = 0; i < 500; i ++){
        print_employee_id(accounting_department[i]);
        //can implement functions here to print other employee details
    }
    
    return 0;
}

int set_employee_id(Employee *e){
    //sets unique and sequential employee ID's for everyone
    static int id = 0;
    e->employeeID = id; 
    id ++;
    return 1;
}

void print_employee_id(Employee e){
    printf("ID: %d\n", e.employeeID); 
}
