#pragma message("funcId_asm_inserted")
//
// File-system system calls.
// Mostly argument checking, since we don't trust
// user code, and calls into file.c and fs.c.
//

#include "types.h"
#include "defs.h"
#include "param.h"
#include "stat.h"
#include "mmu.h"
#include "proc.h"
#include "fs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "file.h"
#include "fcntl.h"

// Fetch the nth word-sized system call argument as a file descriptor
// and return both the descriptor and the corresponding struct file.
static int
argfd(int n, int *pfd, struct file **pf)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380000,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=23,column=1,abs_location_id=380000,funcName=argfd,srcFileId=38,locationId=0*/
  int fd;
  struct file *f;

  if(argint(n, &fd) < 0)
    return -1;
  if(fd < 0 || fd >= NOFILE || (f=myproc()->ofile[fd]) == 0)
    return -1;
  if(pfd)
    *pfd = fd;
  if(pf)
    *pf = f;
  return 0;
}

// Allocate a file descriptor for the given file.
// Takes over file reference from caller on success.
static int
fdalloc(struct file *f)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380001,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=42,column=1,abs_location_id=380001,funcName=fdalloc,srcFileId=38,locationId=1*/
  int fd;
  struct proc *curproc = myproc();

  for(fd = 0; fd < NOFILE; fd++){
    if(curproc->ofile[fd] == 0){
      curproc->ofile[fd] = f;
      return fd;
    }
  }
  return -1;
}

int
sys_dup(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380002,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=57,column=1,abs_location_id=380002,funcName=sys_dup,srcFileId=38,locationId=2*/
  struct file *f;
  int fd;

  if(argfd(0, 0, &f) < 0)
    return -1;
  if((fd=fdalloc(f)) < 0)
    return -1;
  filedup(f);
  return fd;
}

int
sys_read(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380003,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=71,column=1,abs_location_id=380003,funcName=sys_read,srcFileId=38,locationId=3*/
  struct file *f;
  int n;
  char *p;

  if(argfd(0, 0, &f) < 0 || argint(2, &n) < 0 || argptr(1, &p, n) < 0)
    return -1;
  return fileread(f, p, n);
}

int
sys_write(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380004,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=83,column=1,abs_location_id=380004,funcName=sys_write,srcFileId=38,locationId=4*/
  struct file *f;
  int n;
  char *p;

  if(argfd(0, 0, &f) < 0 || argint(2, &n) < 0 || argptr(1, &p, n) < 0)
    return -1;
  return filewrite(f, p, n);
}

int
sys_close(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380005,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=95,column=1,abs_location_id=380005,funcName=sys_close,srcFileId=38,locationId=5*/
  int fd;
  struct file *f;

  if(argfd(0, &fd, &f) < 0)
    return -1;
  myproc()->ofile[fd] = 0;
  fileclose(f);
  return 0;
}

int
sys_fstat(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380006,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=108,column=1,abs_location_id=380006,funcName=sys_fstat,srcFileId=38,locationId=6*/
  struct file *f;
  struct stat *st;

  if(argfd(0, 0, &f) < 0 || argptr(1, (void*)&st, sizeof(*st)) < 0)
    return -1;
  return filestat(f, st);
}

// Create the path new as a link to the same inode as old.
int
sys_link(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380007,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=120,column=1,abs_location_id=380007,funcName=sys_link,srcFileId=38,locationId=7*/
  char name[DIRSIZ], *new, *old;
  struct inode *dp, *ip;

  if(argstr(0, &old) < 0 || argstr(1, &new) < 0)
    return -1;

  begin_op();
  if((ip = namei(old)) == 0){
    end_op();
    return -1;
  }

  ilock(ip);
  if(ip->type == T_DIR){
    iunlockput(ip);
    end_op();
    return -1;
  }

  ip->nlink++;
  iupdate(ip);
  iunlock(ip);

  if((dp = nameiparent(new, name)) == 0)
    goto bad;
  ilock(dp);
  if(dp->dev != ip->dev || dirlink(dp, name, ip->inum) < 0){
    iunlockput(dp);
    goto bad;
  }
  iunlockput(dp);
  iput(ip);

  end_op();

  return 0;

bad:
  ilock(ip);
  ip->nlink--;
  iupdate(ip);
  iunlockput(ip);
  end_op();
  return -1;
}

// Is the directory dp empty except for "." and ".." ?
static int
isdirempty(struct inode *dp)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380008,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=170,column=1,abs_location_id=380008,funcName=isdirempty,srcFileId=38,locationId=8*/
  int off;
  struct dirent de;

  for(off=2*sizeof(de); off<dp->size; off+=sizeof(de)){
    if(readi(dp, (char*)&de, off, sizeof(de)) != sizeof(de))
      panic("isdirempty: readi");
    if(de.inum != 0)
      return 0;
  }
  return 1;
}

//PAGEBREAK!
int
sys_unlink(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380009,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=186,column=1,abs_location_id=380009,funcName=sys_unlink,srcFileId=38,locationId=9*/
  struct inode *ip, *dp;
  struct dirent de;
  char name[DIRSIZ], *path;
  uint off;

  if(argstr(0, &path) < 0)
    return -1;

  begin_op();
  if((dp = nameiparent(path, name)) == 0){
    end_op();
    return -1;
  }

  ilock(dp);

  // Cannot unlink "." or "..".
  if(namecmp(name, ".") == 0 || namecmp(name, "..") == 0)
    goto bad;

  if((ip = dirlookup(dp, name, &off)) == 0)
    goto bad;
  ilock(ip);

  if(ip->nlink < 1)
    panic("unlink: nlink < 1");
  if(ip->type == T_DIR && !isdirempty(ip)){
    iunlockput(ip);
    goto bad;
  }

  memset(&de, 0, sizeof(de));
  if(writei(dp, (char*)&de, off, sizeof(de)) != sizeof(de))
    panic("unlink: writei");
  if(ip->type == T_DIR){
    dp->nlink--;
    iupdate(dp);
  }
  iunlockput(dp);

  ip->nlink--;
  iupdate(ip);
  iunlockput(ip);

  end_op();

  return 0;

bad:
  iunlockput(dp);
  end_op();
  return -1;
}

static struct inode*
create(char *path, short type, short major, short minor)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380010,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=243,column=1,abs_location_id=380010,funcName=create,srcFileId=38,locationId=10*/
  struct inode *ip, *dp;
  char name[DIRSIZ];

  if((dp = nameiparent(path, name)) == 0)
    return 0;
  ilock(dp);

  if((ip = dirlookup(dp, name, 0)) != 0){
    iunlockput(dp);
    ilock(ip);
    if(type == T_FILE && ip->type == T_FILE)
      return ip;
    iunlockput(ip);
    return 0;
  }

  if((ip = ialloc(dp->dev, type)) == 0)
    panic("create: ialloc");

  ilock(ip);
  ip->major = major;
  ip->minor = minor;
  ip->nlink = 1;
  iupdate(ip);

  if(type == T_DIR){  // Create . and .. entries.
    dp->nlink++;  // for ".."
    iupdate(dp);
    // No ip->nlink++ for ".": avoid cyclic ref count.
    if(dirlink(ip, ".", ip->inum) < 0 || dirlink(ip, "..", dp->inum) < 0)
      panic("create dots");
  }

  if(dirlink(dp, name, ip->inum) < 0)
    panic("create: dirlink");

  iunlockput(dp);

  return ip;
}

int
sys_open(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380011,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=287,column=1,abs_location_id=380011,funcName=sys_open,srcFileId=38,locationId=11*/
  char *path;
  int fd, omode;
  struct file *f;
  struct inode *ip;

  if(argstr(0, &path) < 0 || argint(1, &omode) < 0)
    return -1;

  begin_op();

  if(omode & O_CREATE){
    ip = create(path, T_FILE, 0, 0);
    if(ip == 0){
      end_op();
      return -1;
    }
  } else {
    if((ip = namei(path)) == 0){
      end_op();
      return -1;
    }
    ilock(ip);
    if(ip->type == T_DIR && omode != O_RDONLY){
      iunlockput(ip);
      end_op();
      return -1;
    }
  }

  if((f = filealloc()) == 0 || (fd = fdalloc(f)) < 0){
    if(f)
      fileclose(f);
    iunlockput(ip);
    end_op();
    return -1;
  }
  iunlock(ip);
  end_op();

  f->type = FD_INODE;
  f->ip = ip;
  f->off = 0;
  f->readable = !(omode & O_WRONLY);
  f->writable = (omode & O_WRONLY) || (omode & O_RDWR);
  return fd;
}

int
sys_mkdir(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380012,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=337,column=1,abs_location_id=380012,funcName=sys_mkdir,srcFileId=38,locationId=12*/
  char *path;
  struct inode *ip;

  begin_op();
  if(argstr(0, &path) < 0 || (ip = create(path, T_DIR, 0, 0)) == 0){
    end_op();
    return -1;
  }
  iunlockput(ip);
  end_op();
  return 0;
}

int
sys_mknod(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380013,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=353,column=1,abs_location_id=380013,funcName=sys_mknod,srcFileId=38,locationId=13*/
  struct inode *ip;
  char *path;
  int major, minor;

  begin_op();
  if((argstr(0, &path)) < 0 ||
     argint(1, &major) < 0 ||
     argint(2, &minor) < 0 ||
     (ip = create(path, T_DEV, major, minor)) == 0){
    end_op();
    return -1;
  }
  iunlockput(ip);
  end_op();
  return 0;
}

int
sys_chdir(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380014,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=373,column=1,abs_location_id=380014,funcName=sys_chdir,srcFileId=38,locationId=14*/
  char *path;
  struct inode *ip;
  struct proc *curproc = myproc();
  
  begin_op();
  if(argstr(0, &path) < 0 || (ip = namei(path)) == 0){
    end_op();
    return -1;
  }
  ilock(ip);
  if(ip->type != T_DIR){
    iunlockput(ip);
    end_op();
    return -1;
  }
  iunlock(ip);
  iput(curproc->cwd);
  end_op();
  curproc->cwd = ip;
  return 0;
}

int
sys_exec(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380015,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=398,column=1,abs_location_id=380015,funcName=sys_exec,srcFileId=38,locationId=15*/
  char *path, *argv[MAXARG];
  int i;
  uint uargv, uarg;

  if(argstr(0, &path) < 0 || argint(1, (int*)&uargv) < 0){
    return -1;
  }
  memset(argv, 0, sizeof(argv));
  for(i=0;; i++){
    if(i >= NELEM(argv))
      return -1;
    if(fetchint(uargv+4*i, (int*)&uarg) < 0)
      return -1;
    if(uarg == 0){
      argv[i] = 0;
      break;
    }
    if(fetchstr(uarg, &argv[i]) < 0)
      return -1;
  }
  return exec(path, argv);
}

int
sys_pipe(void)
{__asm__  __volatile__ (   "jmp 0f \n\t"    "or $0xFFFFFFFF,%%edi \n\t"    "or $380016,%%edi \n\t"    "0: \n\t" : : ); /*filePath=sysfile.c,line=424,column=1,abs_location_id=380016,funcName=sys_pipe,srcFileId=38,locationId=16*/
  int *fd;
  struct file *rf, *wf;
  int fd0, fd1;

  if(argptr(0, (void*)&fd, 2*sizeof(fd[0])) < 0)
    return -1;
  if(pipealloc(&rf, &wf) < 0)
    return -1;
  fd0 = -1;
  if((fd0 = fdalloc(rf)) < 0 || (fd1 = fdalloc(wf)) < 0){
    if(fd0 >= 0)
      myproc()->ofile[fd0] = 0;
    fileclose(rf);
    fileclose(wf);
    return -1;
  }
  fd[0] = fd0;
  fd[1] = fd1;
  return 0;
}
