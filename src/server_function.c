#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "hwlib.h"
#include <netinet/in.h>
//#include <fcntl.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
//#include <sys/mman.h>
#include <arpa/inet.h>

#include "utility.h"

#include "highlevelDriversFPGA.h"
#include "lowlevelDriversFPGA.h"
#include "server_function.h"
#include "server.h"

// hpsserver.cpp

//Receive a single 32-bit word from socket
uint32_t receiveWordSocket(int socket){
  char msg[sizeof(uint32_t) * 8 + 1];
  char *ptr;
  if(read(socket, msg, sizeof(msg)) < 0){
    fprintf(stderr, "Error in reading the socket\n");
    return -1;
  }else{
    uint32_t data = strtoul(msg, &ptr, 16);
    printf("Received %08x\n", data);
    return data;
  }
}

//Send a string to socket
int sendSocket(int socket, void* msg, uint32_t len){
  int n;
  n = write(socket, msg, len);
  if(n < 0){
    fprintf(stderr, "Error in writing to the socket\n");
    return 1;
  }
  if (baseAddr.verbose > 1) printf("%s) Sent %d bytes\n", __METHOD_NAME__, n);
  return 0;
}

//Acquire a packet from the FPGA and forward it to the socket
void *high_priority(void *socket){
  uint32_t evt;
  int evtLen=0;
  int n;
  int sock = *(int *)socket;

  //Get an event from FPGA
  int evtErr = getEvent(&evt, &evtLen);
  if (baseAddr.verbose > 1) printf("getEvent result: %d\n", evtErr);

  //Send the event to the socket
  n = write(sock, &evt, evtLen);
  if(n < 0){
    perror("Error in writing an event to the socket\n");
  }else{
    if (baseAddr.verbose > 1) printf("Sent %d bytes\n", n);
  }

  //Kill the thread
  pthread_exit(NULL);
}

//Spawn a thread to send an event to socket
void GetEvent(int socket){
  pthread_t t;
  pthread_attr_t attr;
  int new_priority = 20;
  struct sched_param param;

  pthread_attr_init(&attr);
  pthread_attr_getschedparam(&attr, &param);
  param.sched_priority = new_priority;

  if (baseAddr.verbose > 1) printf("socket: %d\n", socket);
  if(pthread_create(&t, &attr, &high_priority, &socket) < 0){
    perror("Error in creating high_priority thread\n");
  }
  pthread_join(t, 0);

}

//------------------------------------------------------------------------

// hpsserver.cpp
// commento solo la receiver_comandi

void *receiver_slow_control(void *args){

  int len, rc, on = 1;
  int listen_sd = -1, new_sd = -1;
  char buffer[80];
  struct sockaddr_in addr;
  int timeout;
  struct pollfd fds[200];
  int nfds = 1, current_size = 0;
  char *port = (char*)args;
  int porta = atoi(port);

  listen_sd = socket(AF_INET, SOCK_STREAM, 0);
  if(listen_sd < 0){

    perror("socket() fallita");
    exit(-1);
  }

  rc = setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
  if(rc < 0){

    perror("setopt() fallita");
    close(listen_sd);
    exit(-1);
  }

  rc = ioctl(listen_sd, FIONBIO, (char *)&on);
  if(rc < 0){

    perror("ioctl() fallita");
    close(listen_sd);
    exit(-1);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(porta);

  rc = bind(listen_sd, (struct sockaddr *)&addr, sizeof(addr));
  if(rc < 0){

    perror("bind() fallita");
    close(listen_sd);
    exit(-1);
  }

  rc = listen(listen_sd, 32);
  if(rc < 0){

    perror("listen() fallita");
    close(listen_sd);
    exit(-1);
  }

  memset(fds, 0, sizeof(fds));

  fds[0].fd = listen_sd;
  fds[0].events = POLLIN;

  timeout = (3 * 60* 1000);

  while(1){

    printf("faccio poll\n");
    rc = poll(fds, nfds, timeout);
    if(rc < 0){

      perror("errore poll()");
      close(listen_sd);
      exit(-1);
    }

    current_size = nfds;
    printf("Current size %d\n", current_size);
    if(fds[0].revents & POLLIN){

      struct sockaddr_in cliaddr;
      int addrlen = sizeof(cliaddr);
      new_sd = accept(listen_sd, (struct sockaddr *)&cliaddr, (socklen_t * __restrict__ )&addrlen);
      printf("connessione da parte di %d accettata\n", new_sd);
      for(int i = 0; i < 200; i++){

	if(fds[i].fd == 0){

	  fds[i].fd = new_sd;
	  fds[i].events = POLLIN;
	  nfds++;
	  break;
	}
      }
    }

    for(int i = 1; i < 200; i++){

      if(fds[i].fd > 0 && fds[i].revents & POLLIN){

	rc = read(fds[i].fd, buffer, sizeof(buffer));
	if(rc < 0){

	  perror("errore poll()");
	  exit(-1);
	}else if(rc == 0){

	  close(fds[i].fd);
	  fds[i].fd = -1;
	  continue;
	}

	len = rc;
	printf("[SERVER] ho ricevuto %d bytes, da %d:: %s\n", len, fds[i].fd, buffer);

	rc = write(fds[i].fd, buffer, len);
	if(rc < 0){

	  perror("errore write()");
	  exit(-1);
	}



      }
    }
  }

  pthread_exit(NULL);
}

int sockOpener(void* args, int* sockIn) {
  // questa parte diventa un banale
  // hpsserver* hsrv = new hpsserver(bla, bla, bla)
  // dare controllata che tutta 'sta roba sia, uguale, nel costruttore di tcpserver
  // in teoria si' perche' io da qui ho copiato
  // ma sicuramente almeno manca il pezzo committato da Nicolo' dopo:
  // https://github.com/PerugiaOverNetDAQ/oca/commit/b8daee0873b71e149a75e278ae9f00c0b8d2b702

  char* port = (char*)args;
  int porta = atoi(port);
  struct sockaddr_in server_addr;
  int n =0;

  printf("TCP/IP socket: Opening... ");
  *sockIn = socket(AF_INET , SOCK_STREAM , 0);
  if(*sockIn < 0){
    perror("Error in socket creation...\n");
    return 1;
  }

  //Avoid "Address already in use" issue at server startup
  if (setsockopt(*sockIn , SOL_SOCKET, SO_REUSEADDR,&n, sizeof(int)) == -1) {
    perror("setsockopt failed...\n");
    //exit(1);
    return 2;
  }
  printf("ok\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(porta);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  printf("TCP/IP socket: binding... ");
  if(bind(*sockIn, (struct sockaddr *) &server_addr , sizeof(server_addr)) < 0){
    perror("Error\n");
    //exit(EXIT_FAILURE);
    return EXIT_FAILURE;
  }else{
    printf("ok\n");
    fflush(stdout);
  }

  printf("TCP/IP socket: listening... ");
  if(listen(*sockIn, 1) < 0){
    perror("Error\n");
    //exit(EXIT_FAILURE);
    return EXIT_FAILURE;
  }
  printf("ok\n");

  return 0;
}

void* receiver_comandi(int* sockIn){
  int addrLen, openConn;
  struct sockaddr_in client_addr;

  addrLen = sizeof(client_addr);
  printf("Waiting for a client to connect...\n");
  openConn = accept(*sockIn, (struct sockaddr *) &client_addr, (socklen_t *) &addrLen);
  if(openConn < 0){
    perror("Error in accepting socket connection\n");
  }else{
    uint32_t trash;
    printf("%s) Connection open: (socket number %d, %s:%d)\n", __METHOD_NAME__, openConn, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    printf("\nRegister array initial content:\n");
    for(int j=0; j<32; j++){
      ReadReg(j, &trash);
    }
    printf("\n");
  }

  //-----------------------------------------------------
  // questa parte sara' un metodo di hpsserver

  //------------------------------------------------------
  // questa parte sarà il Listen() (di tcpserver)
  // che a sua volta chiama il
  // virtual void ProcessMsgReceived(char* msg);
  // che e' specializzato/implementato in hpsserver

  char msg[256]="";
  int bytesRead=0;
  bool kControl = true;
  while(kControl) {
    char replyStr[256];

    bytesRead=read(openConn, msg, sizeof(msg));
    if(bytesRead < 0) {
      // Error: check for specific errors
      if (EAGAIN==errno || EWOULDBLOCK==errno) {
        printf("%s) errno: %d\n", __METHOD_NAME__, errno);
      }
      else {
        printf("%s) Read error (%d)\n", __METHOD_NAME__, bytesRead);
        perror("Read error");
      }
    }
    else if (bytesRead==0) {
      kControl=false;
      printf("%s) Client closed the connection\n", __METHOD_NAME__);
    }
    else {
      if(strcmp(msg, "init") == 0){
        uint32_t regsContent[14];

        sprintf(replyStr, "%s", "[SERVER] Starting Init. Send data...");
        printf("%s\n", replyStr);
        sendSocket(openConn, replyStr, strlen(replyStr));

        //Receive the whole content (apart from reg rGOTO_STATE)
        for(int ii = 0; ii < 7; ii++){
          regsContent[ii*2]   = receiveWordSocket(openConn);
          regsContent[ii*2+1] = (uint32_t)ii;
        }

        Init(regsContent, 14);
      }
      else if(strcmp(msg, "readReg") == 0){
        uint32_t regAddr = receiveWordSocket(openConn);
        uint32_t regContent;

        printf("Send read request...\n");
        ReadReg(regAddr, &regContent);

        sprintf(replyStr, "%08x", regContent);
        sendSocket(openConn, replyStr, strlen(replyStr));
      }
      else if((strcmp(msg, "set delay")==0)||(strcmp(msg, "OverWriteDelay")==0)){
        uint32_t delay = receiveWordSocket(openConn);

        SetDelay(delay);

        sprintf(replyStr, "%08x", delay);
        sendSocket(openConn, replyStr, strlen(replyStr));
      }
      else if(strcmp(msg, "set mode") == 0){
        uint32_t mode = receiveWordSocket(openConn);
        SetMode(mode);
        sprintf(replyStr, "%08x", mode);
        sendSocket(openConn, replyStr, strlen(replyStr));
      }
      else if(strcmp(msg, "get event number") == 0){
        uint32_t extTrigCount, intTrigCount;

        GetEventNumber(&extTrigCount, &intTrigCount);

        sprintf(replyStr, "%08u %08u", extTrigCount, intTrigCount);
        sendSocket(openConn, replyStr, strlen(replyStr));
      }
      else if(strcmp(msg, "print all event number") == 0){
        uint32_t extTrigCount, intTrigCount;

        GetEventNumber(&extTrigCount, &intTrigCount);

        sprintf(replyStr, "%08u %08u", extTrigCount, intTrigCount);
        printf("%s\n",replyStr);
        sendSocket(openConn, replyStr, strlen(replyStr));
      }
      else if(strcmp(msg, "event reset") == 0){
        EventReset();
        sprintf(replyStr, "%08x", 1);
        sendSocket(openConn, replyStr, strlen(replyStr));
      }
      else if(strcmp(msg, "Calibrate") == 0){
        uint32_t calib = receiveWordSocket(openConn);

        Calibrate(calib);

        sprintf(replyStr, "%08x", calib);
        sendSocket(openConn, replyStr, strlen(replyStr));
      }
      else if(strcmp(msg, "WriteCalibPar") == 0){
        sprintf(replyStr, "%08x", 0);
        sendSocket(openConn, replyStr, strlen(replyStr));
      }
      else if(strcmp(msg, "SaveCalibrations") == 0){
        sprintf(replyStr, "%08x", 0);
        sendSocket(openConn, replyStr, strlen(replyStr));
      }
      else if(strcmp(msg, "intTriggerPeriod") == 0){
        uint32_t period = receiveWordSocket(openConn);

        intTriggerPeriod(period);

        sprintf(replyStr, "%08x", period);
        sendSocket(openConn, replyStr, strlen(replyStr));
      }
      else if(strcmp(msg, "selectTrigger") == 0){
        uint32_t intTrig = receiveWordSocket(openConn);

        selectTrigger(intTrig);

        sprintf(replyStr, "%08x", intTrig);
        sendSocket(openConn, replyStr, strlen(replyStr));
      }
      else if(strcmp(msg, "configureTestUnit") == 0){
        uint32_t tuCfg = receiveWordSocket(openConn);
        char testUnitCfg = ((tuCfg&0x300)>>8);
        char testUnitEn  = ((tuCfg&0x2)>>1);

        configureTestUnit(tuCfg);

        sprintf(replyStr, "%08x %08u", testUnitCfg, testUnitEn);
        sendSocket(openConn, replyStr, strlen(replyStr));
      }
      else if(strcmp(msg, "get event") == 0){
        uint32_t* evt = NULL;
        int evtLen=0;

        //Get an event from FPGA
        int evtErr = getEvent(evt, &evtLen);
        if (baseAddr.verbose > 1) printf("getEvent result: %d\n", evtErr);

        //Send the event to the socket
        sendSocket(openConn, evt, evtLen);
      } else if (strcmp(msg, "quit") == 0) {
        printf("FIX ME: Close connection and socket...\n");
        //kControl=false;
      }
      else {
        char c[strlen(msg)+32]="";
        printf("%s) Unkown message: %s\n", __METHOD_NAME__, msg);
        sprintf(c, "%08x", 0x000cacca);
        sendSocket(openConn, c, strlen(c));
      }
    }

    bzero(msg, sizeof(msg));
    sleep(1);

  }

  //-------------------------------------------------

  //pthread_exit(NULL);
  void* pippo;
  return pippo;
}
