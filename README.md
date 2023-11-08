> xv6-x86(xv6-public) 已经被放弃了, 原作者转向了[xv6-riscv](https://github.com/mit-pdos/xv6-riscv.git)
> xv6-x86(xv6-public)文档 [mit 6.828/2023/](https://pdos.csail.mit.edu/6.828/2023/)

> [原readme](https://gitcode.net/crk/xv6-public/-/blob/master/README)

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

> [make_-nB_qemu.log](https://gitcode.net/crk/xv6-public/-/blob/master/study/make_-nB_qemu.log)



> [展开的Makefile比对: xv6-x86 和 xv6-riscv （仅kernel部分）](https://gitcode.net/crk/xv6-public/-/raw/main/study/xv6--x86-cmp-riscv.png)