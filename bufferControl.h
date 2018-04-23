struct buffer_data
{
    char data;
    struct timeval * timestamp;
};

/**
* Esta função é utilizada em client.c e em serverProgram.c pela função logInfo
* que é responsável por realizar a gravação nos arquivos de log: serverLog.txt e clientLog.txt 
*/
void insertValue(char data, struct timeval * timestamp);

struct buffer_data * waitFullBuffer (void);
