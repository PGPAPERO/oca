#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>

#include "hps_0.h"
#include "user_avalon_fifo_regs.h"
#include "lowlevelDriversFPGA.h"
#include "server.h"
#include "utility.h"

//Atomic FIFO methods

uint32_t readFifoLevel (uint32_t* fifoLevelAddr) {
	return *fifoLevelAddr;
}

bool readFifoFull (uint32_t* fifoStatusAddr) {
	return (*fifoStatusAddr & ALTERA_AVALON_FIFO_STATUS_F_MSK) && 1;
}

bool readFifoAFull (uint32_t* fifoStatusAddr) {
	return (*fifoStatusAddr & ALTERA_AVALON_FIFO_STATUS_AF_MSK) && 1;
}

bool readFifoEmpty (uint32_t* fifoStatusAddr) {
	return (*fifoStatusAddr & ALTERA_AVALON_FIFO_STATUS_E_MSK) && 1;
}

bool readFifoAEmpty (uint32_t* fifoStatusAddr) {
	return (*fifoStatusAddr & ALTERA_AVALON_FIFO_STATUS_AE_MSK) && 1;
}

// FIFO initialization: Set aFull and aEmpty thresholds, disable interrupts,
// and reset events register
int InitFifo(int FIFO_TYPE, uint32_t aEmptyThr, uint32_t aFullThr, uint8_t interruptEn) {
	uint32_t *lw_fifo_event_reg_addr;
	uint32_t *lw_fifo_almostfull_reg_addr;
	uint32_t *lw_fifo_almostempty_reg_addr;
	uint32_t *lw_fifo_ienable_reg_addr;

	//Select the proper FIFO
	if (FIFO_TYPE == CONFIG_FIFO){
		lw_fifo_event_reg_addr = baseAddr.configFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_EVENT_REG;
		lw_fifo_almostfull_reg_addr = baseAddr.configFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_ALMOSTFULL_REG;
		lw_fifo_almostempty_reg_addr = baseAddr.configFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_ALMOSTEMPTY_REG;
		lw_fifo_ienable_reg_addr = baseAddr.configFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_IENABLE_REG;
	}
	else if (FIFO_TYPE == HK_FIFO){
		lw_fifo_event_reg_addr = baseAddr.hkFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_EVENT_REG;
		lw_fifo_almostfull_reg_addr = baseAddr.hkFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_ALMOSTFULL_REG;
		lw_fifo_almostempty_reg_addr = baseAddr.hkFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_ALMOSTEMPTY_REG;
		lw_fifo_ienable_reg_addr = baseAddr.hkFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_IENABLE_REG;
	}
	else if (FIFO_TYPE == DATA_FIFO){
		lw_fifo_event_reg_addr = baseAddr.FastFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_EVENT_REG;
		lw_fifo_almostfull_reg_addr = baseAddr.FastFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_ALMOSTFULL_REG;
		lw_fifo_almostempty_reg_addr = baseAddr.FastFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_ALMOSTEMPTY_REG;
		lw_fifo_ienable_reg_addr = baseAddr.FastFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_IENABLE_REG;
	}
	else
		return (1);

	//Reset events and set values
	*lw_fifo_event_reg_addr			 	= ALTERA_AVALON_FIFO_EVENT_ALL_MSK;
	*lw_fifo_almostempty_reg_addr	= aEmptyThr;
	*lw_fifo_almostfull_reg_addr	= aFullThr;
	*lw_fifo_ienable_reg_addr 		= interruptEn & ALTERA_AVALON_FIFO_IENABLE_ALL_MSK;

	return (0);
}

// Funzione di scrittura della FIFO.
int WriteFifo(int FIFO_TYPE, uint32_t *data){		// (Selezione della FIFO, puntatore alla Word da inviare alla FIFO)

	if (FIFO_TYPE != CONFIG_FIFO){
		return (1);
	}

	if (readFifoFull(baseAddr.configFifoStatus)) //Check if Full before writing
		return (2);
	else{
		*baseAddr.configFifo = *data;
		return (0);
	}
}

// Funzione di scrittura della FIFO con un burst di dati.
int WriteFifoBurst(int FIFO_TYPE, uint32_t *data, int length_burst){// (Selezione della FIFO, Indirizzo di partenza dell'array di dati da inviare alla FIFO, Numero di dati che costituisce la raffica)

  if (FIFO_TYPE != CONFIG_FIFO){
    return (1);
  }

  if (readFifoFull(baseAddr.configFifoStatus)) //FIX ME: Should check the A-Full before writing
    return (2);
  else
    {// Altrimenti, carica la FIFO con i dati a partire dall'indirizzo "data" e restituisci il valore "0".
      for (int i=0; i<length_burst; i++){
	*baseAddr.configFifo = data[i];
      }

      return (0);
    }
}


// Funzione di lettura della FIFO.
int ReadFifo(int FIFO_TYPE, uint32_t *data){		// (Selezione della FIFO, puntatore alla Word letta dalla FIFO)
	uint32_t *f2h_lw_fifo_status_reg_addr;
	uint32_t *f2h_lw_fifo_output_addr;

	// Selezione della FIFO
	if (FIFO_TYPE == CONFIG_FIFO)
		return (-1);
	else if (FIFO_TYPE == HK_FIFO){
		f2h_lw_fifo_output_addr = baseAddr.hkFifo;
		f2h_lw_fifo_status_reg_addr = baseAddr.hkFifoStatus;
	}
	else if (FIFO_TYPE == DATA_FIFO){
		f2h_lw_fifo_output_addr = baseAddr.FastFifo;
		f2h_lw_fifo_status_reg_addr = baseAddr.FastFifoStatus;
	}
	else
		return (-1);

	if (readFifoEmpty(f2h_lw_fifo_status_reg_addr)) //Check if Empty before reading
		return (-2);
	else{
		*data = *f2h_lw_fifo_output_addr;
		return (1);
	}
}

// Funzione per la lettura di un burst di dati dalla FIFO.
int ReadFifoBurst(int FIFO_TYPE, uint32_t* data, int length_burst, bool flush){		// (Selezione della FIFO, Indirizzo a partire del quale depositare i dati letti dalla FIFO, Numero di dati che costituisce la raffica)
  uint32_t fifo_level = 0;
  uint32_t *f2h_lw_fifo_level_reg_addr = nullptr;
  uint32_t *f2h_lw_fifo_output_addr = nullptr;
  int readLen = length_burst;

  // Selezione della FIFO
  if (FIFO_TYPE == CONFIG_FIFO)
    return (-1);
  else if (FIFO_TYPE == HK_FIFO){
    f2h_lw_fifo_output_addr = baseAddr.hkFifo;
    f2h_lw_fifo_level_reg_addr = baseAddr.hkFifoLevel;
  }
  else if (FIFO_TYPE == DATA_FIFO){
    f2h_lw_fifo_output_addr = baseAddr.FastFifo;
    f2h_lw_fifo_level_reg_addr = baseAddr.FastFifoLevel;
  }
  else
    return (-1);

  fifo_level = readFifoLevel(f2h_lw_fifo_level_reg_addr);		// Lettura del livello di riempimento della FIFO.
  if (flush == true) {
    readLen = (uint32_t)fifo_level;
  }
  if ((uint32_t)readLen > fifo_level) {// Se il livello è minore della lunghezza della raffica, termina la funzione con un errore.
    if(baseAddr.verbose > 3){
      printf("We tried to read %d, while the fifo level was %d\n", readLen, (int)(fifo_level));
      uint32_t regContent;
      ReadReg(21, &regContent);
      printf("Register 21: %08x\n", regContent);
      ReadReg(22, &regContent);
      printf("Register 22: %08x\n", regContent);
      //      sleep(3);
    }
    return (-2);
  }
  else{											// Altrimenti, leggi dalla FIFO "length_burst" dati e restituisci il valore "0".
    for (int i=0; i<readLen; i++){
      data[i] = *f2h_lw_fifo_output_addr;
    }

    return (readLen);
  }
}

// Funzione di lettura dello stato della FIFO.
int StatusFifo(int FIFO_TYPE, uint32_t *fifo_level, uint32_t *fifo_full, uint32_t *fifo_empty, uint32_t *fifo_almostfull, uint32_t *fifo_almostempty, uint32_t *almostfull_setting, uint32_t *almostempty_setting){
	uint32_t *lw_fifo_level_reg_addr;
	uint32_t *lw_fifo_status_reg_addr;
	uint32_t *lw_fifo_almostfull_reg_addr;
	uint32_t *lw_fifo_almostempty_reg_addr;

	// Selezione della FIFO
	if (FIFO_TYPE == CONFIG_FIFO){
		lw_fifo_level_reg_addr = baseAddr.configFifoLevel;
		lw_fifo_status_reg_addr = baseAddr.configFifoStatus;
		lw_fifo_almostfull_reg_addr = baseAddr.configFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_ALMOSTFULL_REG;
		lw_fifo_almostempty_reg_addr = baseAddr.configFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_ALMOSTEMPTY_REG;
	}
	else if (FIFO_TYPE == HK_FIFO){
		lw_fifo_level_reg_addr = baseAddr.hkFifoLevel;
		lw_fifo_status_reg_addr = baseAddr.hkFifoStatus;
		lw_fifo_almostfull_reg_addr = baseAddr.hkFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_ALMOSTFULL_REG;
		lw_fifo_almostempty_reg_addr = baseAddr.hkFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_ALMOSTEMPTY_REG;
	}
	else if (FIFO_TYPE == DATA_FIFO){
		lw_fifo_level_reg_addr = baseAddr.FastFifoLevel;
		lw_fifo_status_reg_addr = baseAddr.FastFifoStatus;
		lw_fifo_almostfull_reg_addr = baseAddr.FastFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_ALMOSTFULL_REG;
		lw_fifo_almostempty_reg_addr = baseAddr.FastFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_ALMOSTEMPTY_REG;
	}
	else
		return (1);

	*fifo_level = readFifoLevel(lw_fifo_level_reg_addr);
	*fifo_full = readFifoFull(lw_fifo_status_reg_addr);
	*fifo_empty = readFifoEmpty(lw_fifo_status_reg_addr);
	*fifo_almostfull = readFifoAFull(lw_fifo_status_reg_addr);
	*fifo_almostempty = readFifoAEmpty(lw_fifo_status_reg_addr);
	*almostfull_setting = *lw_fifo_almostfull_reg_addr;
	*almostempty_setting = *lw_fifo_almostempty_reg_addr;

	/* printf("%s-%d) %u %u %u %u %u %u %u\n", __METHOD_NAME__, __LINE__, */
	/*        *fifo_level, */
	/*        *fifo_full, */
	/*        *fifo_empty, */
	/*        *fifo_almostfull, */
	/*        *fifo_almostempty, */
	/*        *almostfull_setting, */
	/*        *almostempty_setting); */

	return (0);
}

// Funzione che stampa a video lo stato della FIFO.
int ShowStatusFifo(int FIFO_TYPE){		// (Selezione della FIFO)
	int error;
	char fifoName[13];
	int fifoDepth;
	uint32_t fifo_level;
	uint32_t fifo_full;
	uint32_t fifo_empty;
	uint32_t fifo_almostfull;
	uint32_t fifo_almostempty;
	uint32_t almostfull_setting;
	uint32_t almostempty_setting;

	// Selezione della FIFO
	if (FIFO_TYPE == CONFIG_FIFO){
		strcpy(fifoName,"Config");
		fifoDepth = FIFO_HPS_TO_FPGA_IN_CSR_FIFO_DEPTH;
	}
	else if (FIFO_TYPE == HK_FIFO){
		strcpy(fifoName,"Telemetries");
		fifoDepth = FIFO_FPGA_TO_HPS_OUT_CSR_FIFO_DEPTH;
	}
	else if (FIFO_TYPE == DATA_FIFO){
		strcpy(fifoName,"Data");
		fifoDepth = FAST_FIFO_FPGA_TO_HPS_OUT_CSR_FIFO_DEPTH;
	}
	else
		strcpy(fifoName,"N.A.");


	error = StatusFifo(FIFO_TYPE, &fifo_level, &fifo_full, &fifo_empty, &fifo_almostfull, &fifo_almostempty, &almostfull_setting, &almostempty_setting);		// Estrai lo stato della FIFO.

	if (error)
		return (1);				// Se l'estrazione dello stato non è avvenuta con successo, restitusici un errore.
	else {
		printf("\n------------------------------------------------\n");
		printf("FIFO Name   : %s\n", fifoName);
		printf("A-full thr  : %d\n", almostfull_setting);
		printf("A-empty thr : %d\n", almostempty_setting);
		printf("Level       : %d/%d\n", fifo_level, fifoDepth);
		printf("Full        : %d\n", fifo_full);
		printf("Empty       : %d\n", fifo_empty);
		printf("A-full      : %d\n", fifo_almostfull);
		printf("A-empty     : %d\n", fifo_almostempty);
		printf("--------------------------------------------------\n");

		return (0);
	}
}

// Funzione di controllo del bit di overflow della FIFO.
int OverflowController(int FIFO_TYPE){		// (Selezione della FIFO)
	uint32_t *h2f_lw_fifo_event_reg_addr;

	if (FIFO_TYPE != CONFIG_FIFO){
		return (1);
	}

	h2f_lw_fifo_event_reg_addr = baseAddr.configFifoCsr + (unsigned long)ALTERA_AVALON_FIFO_EVENT_REG;

	// Azione
	if(((*h2f_lw_fifo_event_reg_addr) & ALTERA_AVALON_FIFO_EVENT_OVF_MSK) && 1){	// Se il bit di overflow è a "1", stampa un messaggio d'errore e termina la funzione con un errore.
		printf("Warning: attempted TX_FIFO_overflow\n");
		printf("\n");

		*h2f_lw_fifo_event_reg_addr &= ALTERA_AVALON_FIFO_EVENT_OVF_MSK;	// Reset del bit di overflow in modo che sia pronto a segnalarne uno nuovo.
		return (2);
	}
	else
		return (0);		// Altrimenti, se il bit di overflow è a "0", restituisci uno "0".
}

uint32_t crc_init(){
    return 0x46af6449;
}

uint32_t crc_update(uint32_t crc, const void *data, size_t data_len){
    const unsigned char *d = (const unsigned char *)data;
    unsigned int i;
    bool bit;
    unsigned char c;

    while (data_len--) {
        c = d[data_len];
        for (i = 0; i < 8; i++) {
            bit = crc & 0x80000000;
            crc = (crc << 1) | ((c >> (7 - i)) & 0x01);
            if (bit) {
                crc ^= 0x04c11db7;
            }
        }
        crc &= 0xffffffff;
    }
    return crc & 0xffffffff;
}

uint32_t crc_finalize(uint32_t crc){
    unsigned int i;
    bool bit;

    for (i = 0; i < 32; i++) {
        bit = crc & 0x80000000;
        crc <<= 1;
        if (bit) {
            crc ^= 0x04c11db7;
        }
    }
    return crc & 0xffffffff;
}

//Compute the parity of an incoming unsigned 8-bit
bool parity8(uint8_t dataIn){
	//bool b;
	//bool arr[8];
	//for(int i = 0; i < 8; i++){
	//	arr[i] = data & 1;
	//	data >>= 1;
	//}
	//b = arr[0] ^ arr[1] ^arr[2] ^ arr[3] ^ arr[4] ^ arr[5] ^ arr[6] ^ arr[7];
	//return b;

  //gcc specific
  return __builtin_parity(dataIn&0x000000FF);
}

//Compute 4 parity bits of an incoming unsigned 32-bit
uint8_t parity32(uint32_t dataIn){
  uint8_t parity = 0;
  uint8_t nibbles;
  for (int ii = 0; ii < 4; ii++){
    nibbles = (dataIn >> ii*8) & 0xFF;
    parity = parity | ((parity8(nibbles))<<ii);
  }
  return parity;
}

// Leggi Contenuto registro da PIO
void ReadReg(int regAddr, uint32_t *data){
	//Write the address of the register to be read
	*baseAddr.fpgaRegAddr = regAddr;
  usleep(1);
  //printf("Lettura registro %d \n",regAddr);
	//Read the register content
	*data = *baseAddr.fpgaRegCont;

  if(baseAddr.verbose > 2){
    printf("ReadREG: Register addr: %d - content: %08x\n", regAddr, *data);
  }
}

//Write a single register
void singleWriteReg(uint32_t regAddr, uint32_t regContent){
  uint32_t singleWrite[2];
  singleWrite[0] = regContent;
  singleWrite[1] = regAddr;
  writeReg(singleWrite, 2);
}

//Write registers via the HPS2FPGA FIFO
int writeReg(uint32_t * pktContent, int pktLen){
  uint32_t packet[pktLen+6];
  uint8_t parityMsb, parityLsb;
  uint32_t pktCrc;

  //Create the packet header
  pktCrc = crc_init();
  packet[0] = REG_SOP;
  packet[1] = (uint32_t)pktLen+5;
  packet[2] = kGwV; //@todo fetch the GW version from github and not from FPGA
  pktCrc = crc_update(pktCrc, &packet[2], sizeof(uint32_t));
  packet[3] = REG_HDR1;
  pktCrc = crc_update(pktCrc, &packet[3], sizeof(uint32_t));

  //Create the packet body
  for(int ii=0; ii<pktLen; ii=ii+2){
    parityLsb = parity32(pktContent[ii]);
    parityMsb = parity32(pktContent[ii+1]);
    packet[ii+4] = pktContent[ii];
    packet[ii+5] = ((uint32_t)parityMsb<<28) | ((uint32_t)parityLsb<<24) | pktContent[ii+1];
    pktCrc = crc_update(pktCrc, &packet[ii+4], sizeof(uint32_t));
    pktCrc = crc_update(pktCrc, &packet[ii+5], sizeof(uint32_t));
  }

  //Create the packet footer
  packet[pktLen+4] = REG_EOP;
  pktCrc = crc_finalize(pktCrc);
  packet[pktLen+5] = pktCrc;

  if (baseAddr.verbose > 2){
    printf("\nwriteReg: Packet Content:\n");
    for (int jj=0; jj<pktLen+6;jj++){
      printf("%08x\n", packet[jj]);
    }
  }

  //Send the packet
  WriteFifoBurst(CONFIG_FIFO, packet, pktLen+6);

  return 0;
}
