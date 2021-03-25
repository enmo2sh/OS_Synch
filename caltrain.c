#include <pthread.h>
#include "caltrain.h"


void station_init(struct station *station){
	pthread_mutex_init(&(station->pc_mutex), NULL);
	pthread_cond_init(&(station->cond_trainArrived), NULL);
	pthread_cond_init(&(station->cond_traintoLeave), NULL);
	station->noOfPassengers=0;
	station->trainFreeSeats=0;
	station->isSeated=0;
}

void station_load_train(struct station *station, int count){
	pthread_mutex_lock(&(station->pc_mutex));
	 if (count ==0 || station->noOfPassengers==0){
        pthread_mutex_unlock(&(station->pc_mutex));
        return;
	 }
    station->trainFreeSeats=count;
    pthread_cond_broadcast(&(station->cond_trainArrived));
    pthread_cond_wait(&(station->cond_traintoLeave),&(station->pc_mutex));
    station->trainFreeSeats=0;
    pthread_mutex_unlock(&(station->pc_mutex));
}

void station_wait_for_train(struct station *station){
	pthread_mutex_lock(&(station->pc_mutex));
	station->noOfPassengers++;
	while(station->trainFreeSeats==0)
        pthread_cond_wait(&(station->cond_trainArrived),&(station->pc_mutex));
    station->noOfPassengers--;
    station->trainFreeSeats--;
    station->isSeated++;
    pthread_mutex_unlock(&(station->pc_mutex));
}

void station_on_board(struct station *station){
	pthread_mutex_lock(&(station->pc_mutex));
	station->isSeated--;
    if((station->noOfPassengers==0 || station->trainFreeSeats==0)&&(station->isSeated==0))
         pthread_cond_signal(&(station->cond_traintoLeave));
    pthread_mutex_unlock(&(station->pc_mutex));

}
