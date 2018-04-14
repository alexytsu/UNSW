// myls.c ... my very own "ls" implementation

#include <stdlib.h>
#include <stdio.h>
#include <bsd/string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>

#define MAXDIRNAME 100
#define MAXFNAME   200
#define MAXNAME    20

char *rwxmode(mode_t, char *);
char *username(uid_t, char *);
char *groupname(gid_t, char *);

typedef struct QueueNode {
    char * name;
    struct QueueNode * next;
} QueueNode;

QueueNode * newQueueNode(char *name){
    QueueNode * new;
    new = malloc(sizeof(QueueNode));
    new->name = name;
    new->next = NULL;
    return new;
}

int sorted(char *name1, char *name2){
    if(*name1 == '\0'&& *name2 == '\0'){
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
        return sorted(name1+1, name2+1);
    }
}

char *strlwr(char *string){
    char *newStr = malloc(1000 * sizeof(char));
    int i;
    for(i = 0; i < strlen(string); i ++){
        newStr[i] = tolower(string[i]);
    }
    newStr[strlen(string)] = 0;
    return newStr;
}

void printQueue(QueueNode * head){
    QueueNode * it = head;
    while(it != NULL){
        printf("%s\n", it->name);
        it = it->next;
    }
}


int main(int argc, char *argv[])
{
    // string buffers for various names
    char dirname[MAXDIRNAME];
    char uname[MAXNAME+1];
    char gname[MAXNAME+1];
    char mode[MAXNAME+1];

    // collect the directory name, with "." as default
    if (argc < 2)
        strlcpy(dirname, ".", MAXDIRNAME);
    else
        strlcpy(dirname, argv[1], MAXDIRNAME);

   // check that the name really is a directory
    struct stat info;
    if (stat(dirname, &info) < 0){
        perror(argv[0]); exit(EXIT_FAILURE);
    }
    if ((info.st_mode & S_IFMT) != S_IFDIR){ 
        fprintf(stderr, "%s: Not a directory\n",argv[0]); exit(EXIT_FAILURE);
    }

    // open the directory to start reading
    DIR *df;
    df = opendir(dirname);

    // read directory entries
    struct dirent *entry; 

    QueueNode *head = NULL;

    while ((entry = readdir(df)) != NULL) {

        if(entry->d_name[0] == '.') continue;

        QueueNode *tmp = newQueueNode(entry->d_name);
        QueueNode *it = NULL;
        QueueNode *it2 = NULL;
        if(head == NULL){
            head = tmp;
        }else{
            it = head;
            it2 = it;
            while(it != NULL){
                if(sorted(strlwr(tmp->name), strlwr(it->name))) break;
                it2 = it;
                it = it->next;
            }

            if(it2 == it){
                tmp->next = head;
                head = tmp;
            }else{            
                it2->next = tmp;
                tmp->next = it;
            }

        }


        struct stat Object;
        lstat(entry->d_name, &Object);
        mode_t ModeInfo = Object.st_mode;
        uid_t OwnerUID = (uid_t) Object.st_uid;
        gid_t GroupGID = (gid_t) Object.st_gid;
        long long ObjectSize = Object.st_size;

        printf("%s  %-8.8s %-8.8s %8lld  %s\n",
           rwxmode(ModeInfo, mode),
           username(OwnerUID, uname),
           groupname(GroupGID, gname),
           (long long) ObjectSize,
           entry->d_name);
    }

    printQueue(head);
    // finish up
    closedir(df); // UNCOMMENT this line
    return EXIT_SUCCESS;
}

// convert octal mode to -rwxrwxrwx string
char *rwxmode(mode_t mode, char *str)
{
    str[10] = 0;
    for(int i = 0; i < 9; i++){
        // if the bit is 1 set the appropriate letter
        if( (mode >> i) & 1){
            if( i %3 == 0){
                str[9-i] = 'x';
            }else if(i % 3 == 1){
                str[9-i] = 'w';          
            }else if(i % 3 == 2){
                str[9-i] = 'r';          
            }
        }else{ // otherwise default to -
            str[9-i] = '-';
        }
}

switch ((unsigned long)mode & S_IFMT) {
 case S_IFBLK:  str[0] = '?';                         break;
 case S_IFCHR:  str[0] = '?';                         break;
 case S_IFDIR:  str[0] = 'd';                         break;
 case S_IFIFO:  str[0] = '?';                         break;
 case S_IFLNK:  str[0] = 'l';                         break;
 case S_IFREG:  str[0] = '-';           break;
 case S_IFSOCK: str[0] = '?';               break;
 default:       str[0] = '?';               break;
}


return str;
}

// convert user id to user name
char *username(uid_t uid, char *name)
{
   struct passwd *uinfo = getpwuid(uid);
   if (uinfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)uid);
  else
      snprintf(name, MAXNAME, "%s", uinfo->pw_name);
  return name;
}

// convert group id to group name
char *groupname(gid_t gid, char *name)
{
   struct group *ginfo = getgrgid(gid);
   if (ginfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)gid);
  else
      snprintf(name, MAXNAME, "%s", ginfo->gr_name);
  return name;
}
