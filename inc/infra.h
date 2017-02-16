/*
 * infra.h
 *
 *  Created on: 16 de fev de 2017
 *      Author: Levi
 */
#include "stm32_ub_irsnd.h"

#ifndef INFRA_H_
#define INFRA_H_

void sendInfraData(IRMP_DATA irData);
void initINFRA(void);
int infraPair(void);

#endif /* INFRA_H_ */
