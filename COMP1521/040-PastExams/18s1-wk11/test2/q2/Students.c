// Students.c ... implementation of Students datatype

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "Students.h"

typedef struct _stu_rec {
	int   id;
	char  name[20];
	int   degree;
	float wam;
} sturec_t;

typedef struct _students {
    int    nstu;
    StuRec recs;
} students_t;

// build a collection of student records from a file descriptor
Students getStudents(int in)
{
	// Create the Students object to return
	Students students = malloc(sizeof(students_t));
	if(students == NULL) return NULL;
	
	// Find the size of the file in bytes
	off_t fileSize = lseek(in, 0, SEEK_END);
	if(fileSize < 0) return NULL;
	
	// Number of students = tot_size/size_student
	int n_students = fileSize/sizeof(sturec_t);
	
	// Initialise the Students->StuRec array
	students->nstu = n_students;
	students->recs = malloc(n_students * sizeof(sturec_t));
	if(students->recs == NULL) return NULL;

	lseek(in, 0, SEEK_SET);
	// Read student records into the struct
	for(int i = 0; i < n_students; i++){
		int bytes_read = read(in, (void *) &students->recs[i], sizeof(sturec_t));
		if(bytes_read < sizeof(sturec_t)) return NULL;
	}

	return students;	
}

// show a list of student records pointed to by ss
void showStudents(Students ss)
{
	assert(ss != NULL);
	for (int i = 0; i < ss->nstu; i++)
		showStuRec(&(ss->recs[i]));
}

// show one student record pointed to by s
void showStuRec(StuRec s)
{
	printf("%7d %s %4d %0.1f\n", s->id, s->name, s->degree, s->wam);
}
