struct record {
 char data;
 struct timeval * timestamp;
};

/**
*Função utilizada em serverProgram.c e client.c para manipulação de dados da lista circular
* e também em channelClient.c na função listenServer. 
*/
void insertRecord(char data, struct timeval * timestamp);

struct record * readRecord(struct record * recordValue);
