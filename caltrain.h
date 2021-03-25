#include <pthread.h>

struct station {
	// FILL ME IN
    pthread_mutex_t pc_mutex;
    pthread_cond_t cond_trainArrived;
    pthread_cond_t cond_traintoLeave;
    int noOfPassengers;
    int trainFreeSeats;
    int isSeated;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);
