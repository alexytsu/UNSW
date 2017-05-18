#include <stdio.h>

int sorted_name(char *name1, char *name2){
	if(*name1 == '\0'&& *name2 == '\0\){
		return 2;
	}

	if(*name1 == '\0'){
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

int sorted_zid(int zid_1, int zid_2){
	if(zid_1 < zid_2){
		return 0;	
	}
	return 1;
}

typedef struct student *Student

Student makeStudent(char *line){
	char * zid, *firstname, *lab, *grads, *lastname;

	zid = line;
	firstname = strchr(zid, ' ');
	firstname[0] = '\0';
	firstname++;
    
    lastname = strchr(firstname, ' ');
    lastname[0] = '\0';
    lastname++;

	lab = strchr(lastname, ' ' );
	*lab = '\0';
	lab++;

	grads = strchr(lab, ' ');

	*grads = '\0';
	grads++;

	Student s = malloc(sizeof(struct student));

	s->zid = atoi(zid);
	strcpy(s->name, lastname);
	strcpy(s->labname, lab);
	strcpy(s->grades, grads);

	s->next = NULL;
	return s;
	
}
