/*
 * tasks.c
 *
 *  Created on: Jun 20, 2019
 *      Author: Bruno
 */


#include "tasks_start.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/***** incluir tasks includes *****/
#include "tago_task.h"
#include "events_task.h"
/**********************************/

#include "stddef.h"
#include "stdio.h"



#define TASK_CREATE(task_table, index)									\
	xTaskCreate(task_table[index].pvTaskCode, task_table[index].pcName,	\
	task_table[index].usStackDepth, task_table[index].pvParameters,		\
	task_table[index].uxPriority, task_table[index].pvCreatedTask)		\

typedef struct{
	TaskFunction_t pvTaskCode;
	char* pcName;
	uint32_t usStackDepth;
	void* pvParameters;
	UBaseType_t uxPriority;
	TaskHandle_t * const pvCreatedTask;
}task_template_t;

/**
 * preencher a tabela com as tasks do sistema, os parâmetros são:
 *
 *		pvTaskCode:			a task em si,
 *		pcName:				string de referencia para a task,
 *		usStackDepth:		numero de variaveis que a task podera ter, reflete no tamanho alocado para a task
 *		pvParameters:		parametros para inicialização da task (arg),
 *		uxPriority:			prioridade da task,
 *		pvCreatedTask:		variavel handler da task, utilizado para deletar a task, por exemplo
 *
 *		obs.: ao adicionar uma task, deve-se adicionar um novo enum em @task_index_t e criar um novo @TaskHandle_t
 */

TaskHandle_t tago_task_handler, events_task_handler;

typedef enum{
	TAGO_TASK,
	EVENTS_TASK,
	TASKS_NUMBER
}task_index_t;

static const task_template_t task_table[] =
{
		{		tago_task, 			"tago_task", 		2048,		NULL,		10,		&tago_task_handler		},
		{		events_task, 		"events_task", 		2048,		NULL,		10,		&events_task_handler	},
												{NULL}
};

BaseType_t tasks_init()
{
	BaseType_t ret = pdPASS;
	uint8_t i = 0;
	uint8_t tasks_number = 0;

	for ( i = 0; i < TASKS_NUMBER && ret == pdPASS; i++)
	{
		ret = TASK_CREATE(task_table, i);
		if (ret == pdPASS)
			tasks_number++;
		else
			printf("%d error task number %d\n", ret, i);
	}

	printf("\n\n\nInitialized %d tasks!!\n\n\n", tasks_number);

	return ret;
}
