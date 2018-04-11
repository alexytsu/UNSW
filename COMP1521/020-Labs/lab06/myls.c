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

#define MAXDIRNAME 100
#define MAXFNAME   200
#define MAXNAME    20

char *rwxmode(mode_t, char *);
char *username(uid_t, char *);
char *groupname(gid_t, char *);

int main(int argc, char *argv[])
{
   // string buffers for various names
   char dirname[MAXDIRNAME];
   char uname[MAXNAME+1]; // UNCOMMENT this line
   char gname[MAXNAME+1]; // UNCOMMENT this line
   char mode[MAXNAME+1]; // UNCOMMENT this line

   // collect the directory name, with "." as default
   if (argc < 2)
      strlcpy(dirname, ".", MAXDIRNAME);
   else
      strlcpy(dirname, argv[1], MAXDIRNAME);

   // check that the name really is a directory
   struct stat info;
   if (stat(dirname, &info) < 0)
      { perror(argv[0]); exit(EXIT_FAILURE); }
   if ((info.st_mode & S_IFMT) != S_IFDIR)
      { fprintf(stderr, "%s: Not a directory\n",argv[0]); exit(EXIT_FAILURE); }

   // open the directory to start reading
   DIR *df;
   df = opendir(dirname);

   // read directory entries
   struct dirent *entry; // UNCOMMENT this line
   while ((entry = readdir(df)) != NULL) {
      
      if(entry->d_name[0] == '.') continue;

      struct stat Object;
      mode_t ModeInfo = Object.st_mode;
      lstat(entry->d_name, &Object);
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

   // finish up
   closedir(df); // UNCOMMENT this line
   return EXIT_SUCCESS;
}

// convert octal mode to -rwxrwxrwx string
char *rwxmode(mode_t mode, char *str)
{

   str[11] = 0;
   for(int i = 0; i < 9; i++){
      str[9-i] = ( (mode>>i) && 1 ) ? 'a':'b';
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
