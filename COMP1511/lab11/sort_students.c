// starting point for COMP1511 lab 11

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_STUDENT_NAME_LENGTH 128
#define MAX_GRADE_STRING_LENGTH 22
#define MAX_LAB_NAME_LENGTH 32
#define MAX_LINE_LENGTH 4096

struct student {
    int              zid;
    char             name[MAX_STUDENT_NAME_LENGTH + 1];
    char             lab_name[MAX_LAB_NAME_LENGTH + 1];
    char             lab_grades[MAX_GRADE_STRING_LENGTH + 1];
    struct student   *next;
};

struct student *read_students_file(char filename[]);
struct student *read_student(FILE *stream);

double grades2labmark(char grades[]){
    double mark = 0;

    for(int i = 0; grades[i] != '\0'; i ++){
        switch (grades[i]){
            case 'A':
                mark+=1.0;
                break;
            case '+':
                mark+=0.2;
                break;
            case 'B':
                mark+=0.8;
                break;
            case 'C':
                mark+=0.5;
                break;
        }
    }
    if(mark > 10) return 10.0;
    return mark;
}

int sorted_zid(int zid_1, int zid_2){
	if(zid_1 < zid_2){
		return 1;
	}
	return 0;
}

void printlist(struct student *head){
    for(struct student *n = head; n != NULL; n = n->next){
        printf("%d %-30s %-12s %-22s %4.1lf\n", n->zid, n->name, n->lab_name, n->lab_grades, grades2labmark(n->lab_grades));
    }
}

int sorted_name(char *name1, char *name2){
	if((*name1 == '\0' || *name1 == ' ')&& (*name2 == '\0' || *name2 == ' ')){
		return 2;
	}

	if(*name1 == '\0' || *name1 == ' '){
		return 1;
	} else if(*name2 == '\0'){
		return 0;
	}

	if(*name1 < *name2){
		return 1;
	} else if(*name1 > *name2){
		return 0;
	} else {
		return sorted_name(name1+1, name2+1);
	}
}


int unsorted(struct student *stu1, struct student *stu2){
    char *lastname1, *firstname1;
    firstname1 = stu1->name;
    lastname1 = strchr(stu1->name, ' ');
    lastname1 ++;
    char *lastname2, *firstname2;
    firstname2 = stu2->name;
    lastname2 = strchr(stu2->name, ' ');
    lastname2 ++;

    int sortlast = sorted_name(lastname1, lastname2);
    if(sortlast == 1){
        return 0;
    }else if(sortlast == 2){
        int sortfirst = sorted_name(firstname1, firstname2);
        if(sortfirst ==1){
            return 0;
        }else if(sortfirst == 2){
            int sortzid = sorted_zid(stu1->zid,stu2->zid);
            if(sortzid == 1){
                return 0;
            }else{
                return 1;
            }
        }else{
            return 1;
        }
    }else{
        return 1;
    }
    return 0;
}

/*struct student *insert(struct student *student, struct student *sorted){
    if(sorted==NULL){
        sorted = student;
        sorted->next = NULL;
        return sorted;
    }

    struct student *previous = NULL;
    struct student *n = sorted;
    
    printf("student: %p, n: %p\n\n\n", student, n);
    
    //while(unsorted(student, n)){
    while(student->zid > n->zid){
        previous = n;
        n = n->next;
        if(n==NULL) break;
        if(n->next == NULL) break;
    }

    if(previous==NULL){
        student->next = sorted;
        return student;
    }

    if(previous->next==NULL){
        student->next=NULL;
        sorted->next=student;
        return student;
    }
    previous->next = student;
    student->next = n;
    return sorted;

}
*/

struct student *insert(struct student* node, struct student *head){
    struct student *previous = NULL;
    struct student *n = head;
    while(n!=NULL && unsorted(node, n)){
    //while(n!=NULL && node->zid>n->zid){
        previous = n;
        n = n->next;
    }

    if(previous == NULL){
        head = node;
    }else {
        previous->next = node;
    }

    node->next = n;
    return head;
}

int main(int argc, char *argv[]) {
    // CHANGE THIS CODE

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <marks-file>\n", argv[0]);
        return 1;
    }

    struct student *student_list = read_students_file(argv[1]);
    struct student *head = NULL;
    while(student_list!=NULL){
        struct student *next = student_list->next;
        head = insert(student_list, head);
        student_list = next;
    }
    printlist(head);
    return 0;
}

// DO NOT CHANGE THE CODE BELOW HERE - DO NOT CHANGE read_students_file

// read_students_file reads a file where line contains information for 1 student
// it creates a linked of student structs containing the information
// it returns a pointer to the head of the list

struct student *read_students_file(char filename[]) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr,"warning file %s could not  be opened for reading\n", filename);
        return NULL;
    }

    struct student *first_student = NULL;
    struct student *last_student = NULL;
    struct student *s;
    while ((s = read_student(fp)) != NULL) {
        if (last_student == NULL) {
            first_student = s;
            last_student = s;
        } else {
            last_student->next = s;
            last_student = s;
        }
    }

    fclose(fp);
    return first_student;
}

// DO NOT CHANGE read_student

// read_student mallocs a student struct
// and reads a line in this format:
//
// 5099703 Tsun Bordignon thu13-sitar A+A+CABAB..A.
//
// stores the values in the struct field
// and returns a pointer to the struct

struct student *read_student(FILE *stream) {
    char line[MAX_LINE_LENGTH];

    struct student *s = malloc(sizeof (struct student));
    assert(s);

    if (fgets(line, MAX_LINE_LENGTH, stream) == NULL) {
        free(s);
        return NULL;
    }

    char *newline_ptr = strchr(line, '\n');
    assert(newline_ptr);
    *newline_ptr = '\0';

    char *space_ptr = strrchr(line, ' ');
    assert(space_ptr);
    strncpy(s->lab_grades, space_ptr + 1, MAX_GRADE_STRING_LENGTH);
    s->lab_grades[MAX_GRADE_STRING_LENGTH] = '\0';
    *space_ptr = '\0';

    space_ptr = strrchr(line, ' ');
    assert(space_ptr);
    strncpy(s->lab_name, space_ptr + 1, MAX_LAB_NAME_LENGTH);
    s->lab_name[MAX_LAB_NAME_LENGTH] = '\0';
    *space_ptr = '\0';

    space_ptr = strchr(line, ' ');
    assert(space_ptr);
    strncpy(s->name, space_ptr + 1, MAX_STUDENT_NAME_LENGTH);
    s->name[MAX_STUDENT_NAME_LENGTH] = '\0';
    *space_ptr = '\0';

    s->zid = atoi(line);
    s->next = NULL;
    return s;
}
