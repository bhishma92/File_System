/*
  FUSE: Filesystem in Userspace
  This is the adress where I am initializing my filesystem
  /home/yashi/fuse-2.9.3/example/plz/fusedata
  Please use replace all to replace this with your adress     before running.
getattr,init,mkdir and readdir is working as per my own logic and code;rest of the functions are working as per the logic of other examples I refered.
gcc -Wall yashi2.c `pkg-config fuse --cflags --libs` -o yashi2

*/

#define FUSE_USE_VERSION 26

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef linux
#define _XOPEN_SOURCE 700
#endif

#include <fuse.h>
#include <fuse_common.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#ifdef HAVE_SETXATTR
#include <sys/xattr.h>
#endif






static int code_getattr(const char *path, struct stat *stbuf)
{
	int res;
        memset(stbuf,0,sizeof(struct stat));
        if(strcmp(path,"/")==0)
        {
    stbuf->st_size;//=0;
    stbuf->st_mode;// =16877;
    stbuf->st_uid;//=1000;
    stbuf->st_gid;//=1000;
    stbuf->st_atime;//=1323630836;
    stbuf->st_ctime;//=1323630836;
    stbuf->st_mtime;//=1323630836;
    stbuf->st_nlink;//=4;
    
}
res = lstat(path, stbuf);
	if (res == -1)
		return -errno;
else 

	return (0);
}
   



static int code_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(path);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;

      filler(buf,".",NULL,0);
      filler(buf,"..",NULL,0);
      filler(buf,path+1,NULL,0);
       
		if (filler(buf, de->d_name, &st, 0))
			break;
	}

	closedir(dp);
	return 0;	
}



	
static int code_mkdir(const char *path, mode_t mode)
{
	int res;
char txt[2];
FILE *file;
char *token;
char *a;
char filename[50];
const char s[2] = ",";

file = fopen("fusedata.1.txt","r");

if(file)
{
while(fscanf(file,"%s",txt)!=EOF)
{
token = strtok(txt, s);//gettinh the first free block
while(token != NULL)
{
a = token;
FILE *next;
sprintf(filename,"/home/yashi/fuse-2.9.3/example/plz/fusedata.%s",a);
next = fopen(filename, "w+");
//writing in the free block
fprintf (next, "size:%d, uid:%d,gid:%d, blocksize:%ld, mode:%ld, atime:%d, ctime:%d, mtime:%d,nlink:%d", stbuf.st_size, stbuf.st_uid,stbuf.st_gid,stbuf.st_blksize,stbuf.st_mode,stbuf.st_mode,stbuf.st_atime,
stbuf.st_ctime,stbuf.st_mtime,stbuf.st_nlink);



//printf("%s\n",a);
token = strtok(NULL, s);
}

fclose(file);
}


	res = mkdir(path, mode);
	if (res == -1)
		return -errno;
       

	return (0);
}
}
static int code_unlink(const char *path)
{
	int res;

	res = unlink(path);
	if (res == -1)
		return -errno;

	return 0;
}




static int code_rename(const char *from, const char *to)
{
	int res;

	res = rename(from, to);
	if (res == -1)
		return -errno;

	return 0;
}

static int code_link(const char *from, const char *to)
{
	int res;

	res = link(from, to);
	if (res == -1)
		return -errno;

	return 0;
}







static int code_open(const char *path, struct fuse_file_info *fi)
{
	int res;

	res = open(path, fi->flags);
	if (res == -1)
		return -errno;

	close(res);
	return 0;
}

static int code_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
	int fd;
	int res;

	(void) fi;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static int code_write(const char *path, const char *buf, size_t size,
		     off_t offset, struct fuse_file_info *fi)
{
	int fd;
	int res;

	(void) fi;
	fd = open(path, O_WRONLY);
	if (fd == -1)
		return -errno;

	res = pwrite(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static int code_statfs(const char *path, struct statvfs *stbuf)
{
	int res;

	res = statvfs(path, stbuf);
	if (res == -1)
		return -errno;

	return 0;
}

static int code_release(const char *path, struct fuse_file_info *fi)
{
	
	(void) path;
	(void) fi;
	return 0;
}


static void *code_init(struct fuse_conn_info *conn)
{

struct superblock
{

long int creationTime;
int mounted;
int devID;
int freestart;
int freeEnd;
int root;
long maxBlocks;
};



struct superblock sb;
sb.creationTime = 1376483073;
sb.mounted;
sb.devID =20;
sb.freestart =1;
sb.freeEnd =25;
sb.root = 26;
sb.maxBlocks =10000;

mount++; //mount will increment everytime this init is called

//Writing in Superblock
FILE *infile;
infile = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.0.txt", "w+");
fprintf (infile, "creationTime:%ld, mounted:%d,devID:%d, freestart:%d, freeEnd:%d, root:%d, maxBlocks:%ld",sb.creationTime,sb.mounted, sb.devID,sb.freestart,sb.freeEnd,sb.root,sb.maxBlocks);
fclose(infile);





//now creating free block list

const int MAX1=400,MAX2=800,MAX3=1200,MAX4=1600,MAX5=2000,MAX6=2400,
MAX7 =2800,MAX8=3200,MAX9=3600, MAX10=4000, MAX11=4400,MAX12=4800,
MAX13=5200,MAX14=5600, MAX15=6000,MAX16=6400,MAX17=6800,MAX18=7200,
MAX19=7600,MAX20=8000,MAX21=8400,MAX22=8800,MAX23=9200,MAX24=9600,
MAX25=10000;


FILE *input;
int var1[MAX1],var2[MAX2],var3[MAX3],var4[MAX4],var5[MAX5],var6[MAX6],var7[MAX7],var8[MAX8],var9[MAX9],var10[MAX10],var11[MAX11],var12[MAX12],var13[MAX13],var14[MAX14],var15[MAX15],var16[MAX16],var17[MAX17],var18[MAX18],var19[MAX19],var20[MAX20],var21[MAX21],var22[MAX22],var23[MAX23],var24[MAX24],var25[MAX25]; 
int i;
char str[]="Free Block List:";
//FROM 27 to 399
for(i=27;i<MAX1;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.1.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=27;i<MAX1;i++)
{

fprintf(input,"%d,",i,var1[i]);
}
fclose(input);

}

//from 400 to 799
for(i=400;i<MAX2;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.2.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=400;i<MAX2;i++)
{

fprintf(input,"%d,",i,var2[i]);
}
fclose(input);

}

//from 800 to 1199
for(i=800;i<MAX3;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.3.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=800;i<MAX3;i++)
{

fprintf(input,"%d,",i,var3[i]);
}
fclose(input);

}

//from 1200 to 1599
for(i=1200;i<MAX4;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.4.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=1200;i<MAX4;i++)
{

fprintf(input,"%d,",i,var4[i]);
}
fclose(input);

}



//from 1600 to 1999
for(i=1600;i<MAX5;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.5.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=1600;i<MAX5;i++)
{

fprintf(input,"%d,",i,var5[i]);
}
fclose(input);

}
// from 2000 to 2400
for(i=2000;i<MAX6;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.6.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=2000;i<MAX6;i++)
{

fprintf(input,"%d,",i,var6[i]);
}
fclose(input);

}
//from 2400 to 2799
for(i=2400;i<MAX7;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.7.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=2400;i<MAX7;i++)
{

fprintf(input,"%d,",i,var7[i]);
}
fclose(input);
}

//FROM 2800 TO 3199
for(i=2800;i<MAX8;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.8.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=2800;i<MAX8;i++)
{

fprintf(input,"%d,",i,var8[i]);
}
fclose(input);
}

//From 3200 to 3599
for(i=3200;i<MAX9;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.9.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=3200;i<MAX9;i++)
{

fprintf(input,"%d,",i,var9[i]);
}
fclose(input);
}

//from 3600 to 3999

for(i=3600;i<MAX10;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.10.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=3600;i<MAX10;i++)
{

fprintf(input,"%d,",i,var10[i]);
}
fclose(input);
}

//from 4000 to 4399

for(i=4000;i<MAX11;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.11.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=4000;i<MAX11;i++)
{

fprintf(input,"%d,",i,var11[i]);
}
fclose(input);
}

//from 4400 to 4799

for(i=4400;i<MAX12;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.12.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=4400;i<MAX12;i++)
{

fprintf(input,"%d,",i,var12[i]);
}
fclose(input);
}

//from 4800 to 5199

for(i=4800;i<MAX13;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.13.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=4800;i<MAX13;i++)
{

fprintf(input,"%d,",i,var13[i]);
}
fclose(input);
}

// from 5200 to 5600
for(i=5200;i<MAX14;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.14.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=5200;i<MAX14;i++)
{

fprintf(input,"%d,",i,var14[i]);
}
fclose(input);
}

// from 5600 to 5999

for(i=5600;i<MAX15;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.15.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=5600;i<MAX15;i++)
{

fprintf(input,"%d,",i,var15[i]);
}
fclose(input);
}

//from 6000 to 6399

for(i=6000;i<MAX16;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.16.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=6000;i<MAX16;i++)
{

fprintf(input,"%d,",i,var16[i]);
}
fclose(input);
}

//from 6400 to 6799

for(i=6400;i<MAX17;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.17.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=6400;i<MAX17;i++)
{

fprintf(input,"%d,",i,var17[i]);
}
fclose(input);
}

//from 6800 to 7199
for(i=6800;i<MAX18;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.18.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=6800;i<MAX18;i++)
{

fprintf(input,"%d,",i,var18[i]);
}
fclose(input);
}

//from 7200 to 7599
for(i=7200;i<MAX19;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.19.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=7200;i<MAX19;i++)
{

fprintf(input,"%d,",i,var19[i]);
}
fclose(input);
}

// from 7600 to 7999

for(i=7600;i<MAX20;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.20.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=7600;i<MAX20;i++)
{

fprintf(input,"%d,",i,var20[i]);
}
fclose(input);
}

// from 8000 to 8399

for(i=8000;i<MAX21;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.21.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=8000;i<MAX21;i++)
{

fprintf(input,"%d,",i,var21[i]);
}
fclose(input);
}

// from 8400 to 8800

for(i=8400;i<MAX22;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.22.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=8400;i<MAX22;i++)
{

fprintf(input,"%d,",i,var22[i]);
}
fclose(input);
}

// from 8800 to 9200

for(i=8800;i<MAX23;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.23.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=8800;i<MAX23;i++)
{

fprintf(input,"%d,",i,var23[i]);
}
fclose(input);
}

 //from 9200 to 9600

for(i=9200;i<MAX24;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.24.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=9200;i<MAX24;i++)
{

fprintf(input,"%d,",i,var24[i]);
}
fclose(input);
}

// from 9600 to 10000

for(i=9600;i<MAX25;i++)
{
input = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.25.txt", "w+");
//fwrite(str,1,sizeof(str),input);
for(i=9600;i<MAX25;i++)
{

fprintf(input,"%d,",i,var25[i]);
}
fclose(input);
}

// Root 
struct stat stbuf;
stbuf.st_size;
    stbuf.st_mode;
    stbuf.st_uid;
    stbuf.st_gid;
    stbuf.st_blksize=4096;
    stbuf.st_atime;
    stbuf.st_ctime;
    stbuf.st_mtime;
    stbuf.st_nlink;




FILE *root;

root = fopen("/home/yashi/fuse-2.9.3/example/plz/fusedata.26.txt", "w+");

fprintf (root, "size:%d, uid:%d,gid:%d, blocksize:%ld, mode:%ld, atime:%d, ctime:%d, mtime:%d,nlink:%d", stbuf.st_size, stbuf.st_uid,stbuf.st_gid,stbuf.st_blksize,stbuf.st_mode,stbuf.st_mode,stbuf.st_atime,
stbuf.st_ctime,stbuf.st_mtime,stbuf.st_nlink);
fclose(root);

//initializing the free blocks from 27 to 10000
char file_name[50];
int j;
FILE *in;
char str1[]= " ";
for(j=27;j<10000;j++)
{

sprintf(file_name, "/home/yashi/fuse-2.9.3/example/plz/fusedata.%d",j);
in = fopen(file_name, "w+");
fwrite(str1,1,sizeof(str),in);
//fprintf (input, "%d", 0);
fclose(in);
}


return (0);
}






 







static struct fuse_operations code_oper = {
        
        .init           = code_init,
	.getattr	= code_getattr,
	.readdir	= code_readdir,
	.mkdir		= code_mkdir,
	.unlink		= code_unlink,
	.rename		= code_rename,
	.link		= code_link,
	.open		= code_open,
	.read		= code_read,
	.write		= code_write,
	.statfs		= code_statfs,
	.release	= code_release,
	
};

int main(int argc, char *argv[])
{


	umask(0);
	return fuse_main(argc, argv, &code_oper, NULL);
}
