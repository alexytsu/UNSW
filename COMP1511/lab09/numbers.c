#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	FILE *fp;
	if(argc!=4){
		fprintf(stderr, "you dun fucked up. pls give me three argumetns ok thankstry agina beter lcuk next time. fool me once. shame on you. read my man page. like and scubscribe. youtube.come/watch=id&rickroll.com.au. fllow my soundcloud @ sund.coul.dcom/djmixtape.com\n");
		return 1;
	}
	fp = fopen(argv[3], "w");
	if(fp != NULL){
		int lower = atoi(argv[1]);
		int upper = atoi(argv[2]);
		for(int i = lower; i <= upper; i++){
			fprintf(fp, "%d\n", i);
		}
		fclose(fp);
	}else{
		fprintf(stderr, "uh oh you frickin moron. you have just opened the file of luck. decompile your os in nlog(n) time or you will never compile on your first go again\n");
	}
	return 0;
}