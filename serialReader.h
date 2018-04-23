/*Funções utilizadas em serverProgram.c e em serialReader.c*/
int serialport_init(const char* serialport, int baud);

int serialport_read_until(int fd, char* buf, char until);
