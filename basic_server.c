#include "pipe_networking.h"

static void sighandler(int signo){
  if (signo == SIGINT){
    remove("WKP");
    exit(1);
  }
}

int main() {

  signal(SIGINT, sighandler);

  int to_client;
  int from_client;
  char proc[BUFFER_SIZE];

  while (1) {

  	from_client = server_handshake( &to_client );
    
    if (from_client) {

        while(read(from_client, proc, sizeof(proc))) {
            printf("Subserver[%d] received %s from client\n", getpid(), proc );
            int i = 0;
            for (; i <strlen(proc); i++) {
                proc[i] += 1;
            }
            proc[i] = '\0';
            printf("Subserver[%d] sent [%s]\n", getpid(), proc);
            write(to_client, proc, strlen(proc));
        }
        break;
  	}

  }
  return 0;
}
