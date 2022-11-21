#pragma once

#ifndef application_h
#define application_h



#include "server.h"


void app_start(void);

ST_cardData_t* a;
ST_accountsDB_t* b;
ST_terminalData_t* c;
ST_transaction_t* d;

EN_serverError_t AA;
EN_transState_t BB;

#endif