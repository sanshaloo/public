#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif
#include <errno.h>
#include <libgen.h>
#include <locale.h>
#include <limits.h>


int main( int argc, char **argv ) {
  DIR *cd, *tgt ;
  struct dirent *dirinfo;
  struct dirent *tgtinfo;
  int filecount = 0;
  struct stat SrcInfo;
  struct stat fileinfo;
  struct stat DirChk ;
  char *fullname, *name;
  off_t size ;
  char *SrcDir = "new" ;
  char *TgtDir = "edit" ;
  char *tgtpath, *srcpath ;
  int i, elem ;
  char cwd[PATH_MAX];

  if ( argc == 3 ) {
    SrcDir = (char *)argv[1] ;
    TgtDir = (char *)argv[2] ;
  }

  if ( argc == 2 ) {
    SrcDir = "new";
    TgtDir = (char *)argv[1] ;
  }


  stat(TgtDir, &DirChk) ;


  printf ("ARGS = %d Source dir = %s, Target dir = %s\n", argc, SrcDir, TgtDir) ;

  i=elem=0;
  cd = opendir(SrcDir);
  // chdir("/home/sas/reco") ;

  tgt = opendir(TgtDir) ;

  if (!cd) {
    perror("could not chdir to \n" );
    return 0;
  }

  while ((dirinfo = readdir(cd)) != NULL) { 
    if ( strcmp(dirinfo->d_name,"..") == 0 ) continue ;
    if ( strcmp(dirinfo->d_name,".") == 0 ) continue ;
    // printf ("Filename = %s\n", dirinfo->d_name) ;
    tgtpath = malloc ( strlen(dirinfo->d_name) + strlen (TgtDir) + 2 ) ; /* Path + / + \0 + \n*/
    srcpath = malloc ( strlen(dirinfo->d_name) + strlen (SrcDir) + 2 ) ; /* Path + / + \0 + \n*/
    memcpy(tgtpath,"\0", sizeof(tgtpath) -1 );

    strcat(srcpath,SrcDir) ;
    strcat(srcpath,"/") ;
    strcat(srcpath,dirinfo->d_name) ;
    stat(srcpath, &SrcInfo ) ;

    strcat(tgtpath,TgtDir) ;
    strcat(tgtpath,"/") ;
    strcat(tgtpath,dirinfo->d_name) ;
    // printf ("Target Path = %s\n", tgt_path);

    if ( stat(tgtpath, &fileinfo ) < 0 ) {
          continue ;
          printf ( "File Not found %s/%s\n", TgtDir,dirinfo->d_name ) ;
    } else {
      printf ( "Both dirs:: %s :: Source size = %ld MB  Destination Size = %ld MB\n", srcpath, SrcInfo.st_size/1024/1024, fileinfo.st_size/1024/1024 ) ;

    }
    free(tgtpath) ;
    free(srcpath) ;

  }

return(0) ;
}

