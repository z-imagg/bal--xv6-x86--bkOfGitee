> 原git仓库 [xv6-x86(xv6-public)](https://github.com/mit-pdos/xv6-public.git) 

> 文档 [mit 6.828/2023/](https://pdos.csail.mit.edu/6.828/2023/)


> 文档 [MIT 6.828/2018/xv6/book-rev11.pdf](https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf)


> [原readme](https://github.com/mit-pdos/xv6-public/blob/master/README)

> 注：  
-  xv6-x86(xv6-public) 已经被放弃了, 原作者转向了[xv6-riscv](https://github.com/mit-pdos/xv6-riscv.git)
-  xv6-x86文档来源:[mit-pdos/xv6-book.git](https://github.com/mit-pdos/xv6-book.git), 它需要 heirloom-doctools 来编译成pdf，但 heirloom-doctools太旧了 ，估计要ubuntu16或14能编译此pdf？猜测 编译出来的pdf就是  [MIT 6.828/2018/xv6/book-rev11.pdf](https://pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf)，因此不需要自己编译pdf了

# 环境
```bash
uname -a
#Linux xx 5.15.0-56-generic #62-Ubuntu SMP Tue Nov 22 19:54:14 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux


cat /etc/issue
#Linux Mint 21.1 Vera \n \l


cat /etc/debian_version
#bookworm/sid
```

# 准备
```shell
sudo  apt install    qemu-system-x86

```

```shell
 make -nB qemu
```

> [make_-nB_qemu.log](https://gitcode.net/crk/xv6-public/-/blob/main/study/make_-nB_qemu.log)



> [展开的Makefile比对: xv6-x86 和 xv6-riscv （仅kernel部分）](https://gitcode.net/crk/xv6-public/-/raw/main/study/xv6--x86-cmp-riscv.png)

# 在ubuntu23.04 x64下编译 xv6-x86代码, make时各种报错. 需要转移到老版本ubuntu14.04 i386下编译xv6-x86
> 比如
```
z@mm:/crk/xv6-x86$ make qemu

gcc -fno-pic -static -fno-builtin -fno-strict-aliasing -O2 -Wall -MD -ggdb -m32 -Werror -fno-omit-frame-pointer -fno-stack-protector -fno-pie -no-pie   -c -o sh.o sh.c
sh.c: In function ‘runcmd’:
sh.c:58:1: error: infinite recursion detected [-Werror=infinite-recursion]


gcc -fno-pic -static -fno-builtin -fno-strict-aliasing -O2 -Wall -MD -ggdb -m32 -Werror -fno-omit-frame-pointer -fno-stack-protector -fno-pie -no-pie   -c -o sh.o sh.c
sh.c:57:1: error: attributes should be specified before the declarator in a function definition
   57 | void
      | ^~~~
sh.c: In function ‘main’:
sh.c:168:7: error: implicit declaration of function ‘runcmd’ [-Werror=implicit-function-declaration]
  168 |       runcmd(parsecmd(buf));


gcc -fno-pic -static -fno-builtin -fno-strict-aliasing -O2 -Wall -MD -ggdb -m32 -Werror -fno-omit-frame-pointer -fno-stack-protector -fno-pie -no-pie   -c -o mp.o mp.c
In function ‘mpconfig’,
    inlined from ‘mpinit’ at mp.c:101:14:
mp.c:83:10: error: array subscript -48806446 is outside array bounds of ‘void[2147483647]’ [-Werror=array-bounds]
   83 |   if(conf->version != 1 && conf->version != 4)

```

# ubuntu14.04 i386 @docker

## docker安装
> 省略

## docker镜像加速
```shell
cat /etc/docker/daemon.json 
{
"registry-mirrors":"https://xxxx.mirror.aliyuncs.com"
}

#登陆阿里云官网 --->  docker镜像加速 ---> https://xxxx.mirror.aliyuncs.com  （xxxx是每个个人阿里云账户不同）
```

## xxx
### ubuntu 14.04 docker镜像
> 在这里找到了 ubuntu 14.04 docker镜像名： [hub.docker ](https://hub.docker.com/r/i386/ubuntu/tags?page=1&name=14.04)
```shell
sudo docker pull i386/ubuntu:14.04
sudo docker run --name ubuntu-1404-i386-a -itd -v /crk:/crk i386/ubuntu:14.04
```

### ubuntu 14.04 docker实例 内 编译 xv6-x86
#### 进入docker实例终端
>进入docker该实例终端```sudo docker exec -it  ubuntu-1404-i386-a bash```：


#### apt国内源配置

> apt国内源:
```shell
# https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/
echo '清华ubunt14.04 apt源' >  /etc/apt/sources.list
apt update
```

#### 安装 gcc、gdb、qemu
```shell
apt install build-essential gdb
apt install qemu-system-x86
```

#### 编译、运行
```shell
cd /crk/xv6-x86/
make clean
make qemu-nox
#正常编译, 正常启动qemu

#备注:  qemu-nox: 即 -nographic 
```

#### 调试
##### 准备
```shell
echo 'add-auto-load-safe-path /crk/xv6-x86/.gdbinit' >   /root/.gdbinit
```

##### gdb调试
> 详见：[两窗口调试：gdb-server、gdb ](https://gitcode.net/crk/xv6-riscv/-/raw/main/pic/gdb01.png)

> 以下简单描述 '两窗口调试：gdb-server、gdb'
1. gdb-server窗口
```shell
cd /crk/xv6-x86/
make qemu-nox-gdb
#gdb-server在25000端口等待
```


2. gdb窗口
```shell

cd /crk/xv6-x86/
gdb
#即连接到25000端口的gdb-server，可以开始正常调试


#备注:  /crk/xv6-x86/.gdbinit 中配置了 连接25000端口
```


# 学习
> 调用流程01：bootasm.S-->bootmain.c-->entry.S-->main.c 
> ![调用流程01：bootasm.S-->bootmain.c-->entry.S-->main.c](https://gitcode.net/crk/xv6-x86/-/raw/main/study/call_flow_01.png)


# addFuncIdByClangPlugin
```shell
make clean;  make addFuncIdByClangPlugin; make x86.o
```