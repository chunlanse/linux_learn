/****************************************************************
Linux把所有设备都映射成了文件
设备文件一般存储在 /dev 目录下
我们可以像操作文件一样操作他们
ls /dev –l
brw-rw----  1 root disk      8,   0 Dec 21 20:00 sda
crw--w----  1 root tty         4,   0 Dec 21 20:00 tty0
b 表示块设备文件
c  表示字符设备文件




设备文件操作流程
打开： fd = open(devName, O_RDWR)
备份： ioctl(fd, TCGETA, &oldAttr); 
设置： ioctl(fd,  TCSETA, &newAttr);
读：     read(fd, buf, len);
写：     write(fd, buf, len);
恢复： ioctl(fd, TCSETA, &oldAttr);
关闭： close(fd)



终端设备操作
include<unistd.h>
ioctl(int fd, int cmd, struct termio *arg)
cmd 参数
TCGETA        获取终端信息
TCSETA        写入终端信息
TCSETAW     先将当前输入队列发送完毕，再写入设置
TCSETAF      先将当前输入队列清空，再写入设置




终端设备操作
include<termio.h>
struct termio
{
unsigned short c_iflag;   //终端输入方式
unsigned short c_oflag;  //终端输出方式
unsigned short c_cflag;  //终端控制方式
unsigned short c_lflag;   //行规则模式
char                  c_line;    
unsigned char  c_cc[NCC];  //控制字符
}



终端设备操作
c_iflag值             描述
-------------------------------------------------------
IGNBRK     忽略break的输入       (ignore break)
BRKINT     break 产生sigint信号 （break sigint)
IGNPAR     忽略奇偶校验         （ignore parity）
PARMRK     记录奇偶校验错误       (parity mark)
INPCK      激活奇偶校验           (in parity check)
ISTRIP     忽略字节第8位，不能处理汉字  (strip)
INLCR      转换 换行字符(NL) 为 回车字符 (CR)
IGNCR      忽略回车               (ignore CR)
ICRNL              转换 回车字符(CR) 为 换行字符(NL)
IUCLC      输入的大写转小写   (upper char lower char)
IXON       运行启动和停止输出控制，把输入的启动和停止字符不读入队列而是做控制作用
IXANY      运行任意输入字符重新启动输出
IXOFF      运行启动和停止输入控制
MAXBEL     队列满时，响铃提示         (max bell)


c_oflag值   描述
------------------------------------------------------
OPOST       字符处理完成后输出   (post)
OLCUC       输出的小写字母转大写 (lower char upper char) 
ONLCR       输出的 换行(NL) 转为 回车换行 (CR, NL)
OCRNL       输出的 回车(CR) 转为 换行(NL)
ONOCR       忽略回车字符
ONLRET      终端上换行时(NL) 执行回车 (CR) 功能
OFDEL       以 DEL 填充输出 (output fill del)


c_cflag值      描述
---------------------------------------------------
B[数字]      设置 (初始值=B9600, B38400, B115200 等)
             //波特率和距离成反比，距离太大，不宜设置过高的波特率  
CS[数字]     传送字节长度 (初始值=CS8, CS5,CS6,CS7等) 
CREAD        可以接受字符
HUPCL        关闭时挂起 (hup close)


终端设备操作
默认ICANON，输入模式为标准模式，有缓冲
设置为 ~ICANON，则输入模式为原始输入，无缓冲

c_lflag值   描述
---------------------------
ISIG        接受信号处理
ICANON      接受标准输入
XCASE       接受区分大小写正则输入
ECHO        字符回显
ECHOE       退格+空格 擦除字符
ECHOK       删除一行后换行
ECHONL      ECHO关闭时，回显换行符
NOFLSH      终端退出后不刷新 


终端设备操作
c_cc[NCC]            描述
----------------------------------------------------------------
c_cc[VMIN]           定义读入字符的个数（0表示不限定）
c_cc[VTIME]          定义等待时间       (50 表示等待 5秒后进行后续处理)



VMIN   VTIME    作用
----------------------------------------------
>0     >0       输入长度为VMIN字节，或者VTIME时间到(至少1个字符)，read()返回
>0     =0       输入长度为VMIN字节，或者信号中断， read()返回
=0     >0       有输入read()就返回， 或者VTIME超时也返回
                对于scanf() 可以输入多个字符(回车或者VTIME时间到返回)
=0     =0       read()立即返回



外部设备操作
打开设备，常用参数
打开：open      对于串口，需要使用 O_NOCTTY 参数
原始模式输入  ~ICANON, 
波特率   B9600, 
每次接受1个字符 c_cc[VMIN]=1
不回显 ~ECHO
输入输出都不进行CR-NL转换  ~ICRNL,~ONLCR
字符处理完后，不延时输出 TAB0  OPOST
****************************************************************/

        