#include <stdio.h> 

int main(){
	int start, end;
	printf("Enter start year: "); 
	scanf("%d", &start); 
	printf("Enter finish year: "); 
	scanf("%d", &end); 
	printf("The leap years between %d and %d are: ", start, end);
	while(start<=end){
		if (start%4!=0){ 
		}else if(start%100!=0){
			printf("%d ", start);	
		}else if(start%400!=0){
		}else{
			printf("%d ", start);	
		}
		start ++;
	}
	printf("\n");
	return 42;
}
