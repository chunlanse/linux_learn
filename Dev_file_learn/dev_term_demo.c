#include<stdio.h>
#include<unistd.h>
#include<termio.h>
#include<string.h>



/*********************TEST RESULT*****************************
hello
szBuf: hello
HELLO
szBuf: HELLO
*************************************************************/
void TestIflag()
{
    struct termio old,new;
    char szBuf[100];

    ioctl(STDIN_FILENO, TCGETA, &old);   //backup old attribute

    new = old;

    new.c_iflag |= IUCLC;  //set IUCLC flag

    ioctl(STDIN_FILENO, TCSETA, &new);  //set new attribute

    scanf("%s",szBuf);

    printf("szBuf: %s\n",szBuf);

    old.c_iflag &= ~IUCLC;
    ioctl(STDIN_FILENO, TCSETA, &old); //resume attribute

    scanf("%s",szBuf);

    printf("szBuf: %s\n",szBuf);
}

/*********************TEST RESULT*****************************
HELLO, WORLD!
Hello, world!
*************************************************************/
void TestOflag()
{
    struct termio old, new;

    ioctl(STDOUT_FILENO, TCGETA, &old);

    new = old;              //init 

    new.c_oflag |= OLCUC;  //set OLCUC bit to 1

    ioctl(STDOUT_FILENO, TCSETA, &new);

    printf("Hello, world!\n");

    ioctl(STDOUT_FILENO, TCSETA, &old);  //resume the attribute

    printf("Hello, world!\n");
}

/*********************TEST RESULT*****************************
1 -->49
2 -->50
3 -->51
a -->97
b -->98
c -->99

 -->10
*************************************************************/
//convert char to ascii
void PrintCharAscii()
{
    struct termio old,new;

    ioctl(STDIN_FILENO, TCGETA, &old);

    new = old;
    new.c_lflag &= ~ICANON;    //remove "ICANON" attribute

    ioctl(STDIN_FILENO, TCSETA, &new);

    char c = 0;
    while('\n' != c)
    {
        c = getchar();
        printf(" -->%d\n",c);
    }

    ioctl(STDIN_FILENO, TCSETA, &old);
}

/*********************TEST RESULT*****************************
Password:
Your passwd is: hello
*************************************************************/
void TestPasswd()
{
    struct termio old, new;

    ioctl(STDIN_FILENO, TCGETA, &old);

    new = old;
    new.c_lflag &= ~ECHO;
    new.c_lflag |= ECHONL;

    ioctl(STDIN_FILENO, TCSETA, &new);

    char szPass[100] = {};
    fprintf(stderr, "Password:");
    scanf("%s", szPass);

    printf("Your passwd is: %s\n", szPass);
    ioctl(STDIN_FILENO, TCSETA, &old);
}

/*********************TEST RESULT*****************************
test1:
[hello@localhost devlearn]$ ./dev_term_demo 
Input:1szBuf: 1                             //delay 5s
[hello@localhost devlearn]$ 
test2:
[hello@localhost devlearn]$ ./dev_term_demo 
Input:adcdrfgsfgszBuf: adcdrfgsfg           //only allow input 10 characters 
[hello@localhost devlearn]$ 
*************************************************************/
void testCCC()
{
    struct termio old, new;
    char szBuf[100] = {};

    ioctl(STDIN_FILENO, TCGETA, &old);

    new = old;
    new.c_lflag &= ~ICANON;

    new.c_cc[VMIN] = 10;
    new.c_cc[VTIME] = 50;   //50 ==> 5 second 

    ioctl(STDIN_FILENO, TCSETA, &new);

    fprintf(stderr, "Input:");

    read(STDIN_FILENO, szBuf, 100);

    printf("szBuf: %s\n", szBuf);

    ioctl(STDIN_FILENO, TCSETA, &old);
}




int main()
{
    TestIflag();
    TestOflag();
    PrintCharAscii();
    TestPasswd();
    testCCC();
    return 0;
}
 
 
 
 

 
 
 
 
 
 
 
 
 
 