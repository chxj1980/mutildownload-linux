#ifndef _CSR_LOG_H_
#define _CSR_LOG_H_

#include "comheader.h"

//��־ϵͳ
bool InitLogSys();

void LogWrite(std::string strLog = "");

void EndLogSys();



#endif // _CSR_LOG_H_
