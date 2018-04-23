#include <stdio.h>    /* Standard input/output definitions */
#include <stdlib.h> 
#include <stdint.h>   /* Standard types */
#include <string.h>   /* String function definitions */
#include <unistd.h>   /* UNIX standard function definitions */
#include <fcntl.h>    /* File control definitions */
#include <errno.h>    /* Error number definitions */
#include <termios.h>  /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <getopt.h>
#include <time.h>
#include "serialReader.h"

#define NSEC_PER_SEC (1000000000) /* The number of nsecs per sec. */

int serialport_init(const char* serialport, int baud);
int serialport_writebyte(int fd, uint8_t b);
int serialport_write(int fd, const char* str);
int serialport_read_until(int fd, char* buf, char until);

/*Esta função é responsável pela escrita de bytes*/
int serialport_writebyte( int fd, uint8_t b){
    int n = write(fd,&b,1);
    if( n!=1)
        return -1;
    return 0;
}

/*Função responsável pela escrita e pelo cálculo do tamanho da string*/
int serialport_write(int fd, const char* str) {
    int len = strlen(str);
    int n = write(fd, str, len);
    if( n!=len ) 
        return -1;
    return 0;
}

/* Esta função é responsável pela leitura de dados. 
* Parâmetros:   
*    int fd: abre o arquivo
*    char * buf: dado a ser lido
*    char until: utilizado para a marcação do último caractere
*/
int serialport_read_until(int fd, char* buf, char until) {
    int infoReaderPeriod = 100;
    struct timespec infoReaderClock;
    clock_gettime(CLOCK_MONOTONIC ,&infoReaderClock);

    char b[1];
    int i=0;
    int readStarted = 0;
    int n;

       while( readStarted == 0 || b[0] != until ) {
            n = read(fd, b, 1);    //Ler um char de cada vez
            if( n==-1) {
              usleep( 10 * 1000 ); //Se ocorreu erro, aguarda
                continue;
            }
            if( n==0 ) {
               usleep( 10 * 1000 ); //Aguarda 10 msec e tenta novamente
                continue;

            }
            
            if (b[0] == 'I') {
                readStarted = 1;  //Se o primeiro caractere recebido for I, inicia a leitura
                usleep( 10 * 1000 ); 
            }
            
            if (readStarted == 1 && b[0] != 'I') {
               buf[i] = b[0]; 
               i++;
            }
        } 
        buf[i] = 0;  // null terminate the string

       return 0;
    }

/*Esta função é responsável iniciar a transmissão de dados
* binários. Utiliza os parâmetros: 
*     const char* serialport: string com o nome da porta serial
*     int baud: taxa de transmissão (bps) (velocidade da conexão)
*/
int serialport_init(const char* serialport, int baud){
    int fd;
       
    fd = open(serialport, O_RDONLY); // open: abre o arquivo especificado pelo nome do caminho
                                     // O_RDONLY: somente leitura  
    if (fd == -1)  {
        perror("init_serialport: Unable to open port ");
        return -1;
    } 
}
