/*
 * tago_task.h
 *
 *  Created on: Jun 20, 2019
 *      Author: Bruno
 */

#ifndef COMPONENTS_TASKS_TAGO_INCLUDE_TAGO_TASK_H_
#define COMPONENTS_TASKS_TAGO_INCLUDE_TAGO_TASK_H_

typedef enum{
	TAGO_IDLE,
	TAGO_WF_CONNECTED,
	TAGO_TRANSMIT,
	TAGO_WF_DISCONNECTED,
	TAGO_STATES
}tago_states_t;

void tago_set_state(tago_states_t state);
void tago_task();


#endif /* COMPONENTS_TASKS_TAGO_INCLUDE_TAGO_TASK_H_ */
