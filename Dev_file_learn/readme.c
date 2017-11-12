/****************************************************************
Linux�������豸��ӳ������ļ�
�豸�ļ�һ��洢�� /dev Ŀ¼��
���ǿ���������ļ�һ����������
ls /dev �Cl
brw-rw----  1 root disk      8,   0 Dec 21 20:00 sda
crw--w----  1 root tty         4,   0 Dec 21 20:00 tty0
b ��ʾ���豸�ļ�
c  ��ʾ�ַ��豸�ļ�




�豸�ļ���������
�򿪣� fd = open(devName, O_RDWR)
���ݣ� ioctl(fd, TCGETA, &oldAttr); 
���ã� ioctl(fd,  TCSETA, &newAttr);
����     read(fd, buf, len);
д��     write(fd, buf, len);
�ָ��� ioctl(fd, TCSETA, &oldAttr);
�رգ� close(fd)



�ն��豸����
include<unistd.h>
ioctl(int fd, int cmd, struct termio *arg)
cmd ����
TCGETA        ��ȡ�ն���Ϣ
TCSETA        д���ն���Ϣ
TCSETAW     �Ƚ���ǰ������з�����ϣ���д������
TCSETAF      �Ƚ���ǰ���������գ���д������




�ն��豸����
include<termio.h>
struct termio
{
unsigned short c_iflag;   //�ն����뷽ʽ
unsigned short c_oflag;  //�ն������ʽ
unsigned short c_cflag;  //�ն˿��Ʒ�ʽ
unsigned short c_lflag;   //�й���ģʽ
char                  c_line;    
unsigned char  c_cc[NCC];  //�����ַ�
}



�ն��豸����
c_iflagֵ             ����
-------------------------------------------------------
IGNBRK     ����break������       (ignore break)
BRKINT     break ����sigint�ź� ��break sigint)
IGNPAR     ������żУ��         ��ignore parity��
PARMRK     ��¼��żУ�����       (parity mark)
INPCK      ������żУ��           (in parity check)
ISTRIP     �����ֽڵ�8λ�����ܴ�����  (strip)
INLCR      ת�� �����ַ�(NL) Ϊ �س��ַ� (CR)
IGNCR      ���Իس�               (ignore CR)
ICRNL              ת�� �س��ַ�(CR) Ϊ �����ַ�(NL)
IUCLC      ����Ĵ�дתСд   (upper char lower char)
IXON       ����������ֹͣ������ƣ��������������ֹͣ�ַ���������ж�������������
IXANY      �������������ַ������������
IXOFF      ����������ֹͣ�������
MAXBEL     ������ʱ��������ʾ         (max bell)


c_oflagֵ   ����
------------------------------------------------------
OPOST       �ַ�������ɺ����   (post)
OLCUC       �����Сд��ĸת��д (lower char upper char) 
ONLCR       ����� ����(NL) תΪ �س����� (CR, NL)
OCRNL       ����� �س�(CR) תΪ ����(NL)
ONOCR       ���Իس��ַ�
ONLRET      �ն��ϻ���ʱ(NL) ִ�лس� (CR) ����
OFDEL       �� DEL ������ (output fill del)


c_cflagֵ      ����
---------------------------------------------------
B[����]      ���� (��ʼֵ=B9600, B38400, B115200 ��)
             //�����ʺ;���ɷ��ȣ�����̫�󣬲������ù��ߵĲ�����  
CS[����]     �����ֽڳ��� (��ʼֵ=CS8, CS5,CS6,CS7��) 
CREAD        ���Խ����ַ�
HUPCL        �ر�ʱ���� (hup close)


�ն��豸����
Ĭ��ICANON������ģʽΪ��׼ģʽ���л���
����Ϊ ~ICANON��������ģʽΪԭʼ���룬�޻���

c_lflagֵ   ����
---------------------------
ISIG        �����źŴ���
ICANON      ���ܱ�׼����
XCASE       �������ִ�Сд��������
ECHO        �ַ�����
ECHOE       �˸�+�ո� �����ַ�
ECHOK       ɾ��һ�к���
ECHONL      ECHO�ر�ʱ�����Ի��з�
NOFLSH      �ն��˳���ˢ�� 


�ն��豸����
c_cc[NCC]            ����
----------------------------------------------------------------
c_cc[VMIN]           ��������ַ��ĸ�����0��ʾ���޶���
c_cc[VTIME]          ����ȴ�ʱ��       (50 ��ʾ�ȴ� 5�����к�������)



VMIN   VTIME    ����
----------------------------------------------
>0     >0       ���볤��ΪVMIN�ֽڣ�����VTIMEʱ�䵽(����1���ַ�)��read()����
>0     =0       ���볤��ΪVMIN�ֽڣ������ź��жϣ� read()����
=0     >0       ������read()�ͷ��أ� ����VTIME��ʱҲ����
                ����scanf() �����������ַ�(�س�����VTIMEʱ�䵽����)
=0     =0       read()��������



�ⲿ�豸����
���豸�����ò���
�򿪣�open      ���ڴ��ڣ���Ҫʹ�� O_NOCTTY ����
ԭʼģʽ����  ~ICANON, 
������   B9600, 
ÿ�ν���1���ַ� c_cc[VMIN]=1
������ ~ECHO
���������������CR-NLת��  ~ICRNL,~ONLCR
�ַ�������󣬲���ʱ��� TAB0  OPOST
****************************************************************/

        