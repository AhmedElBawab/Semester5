#include <iostream>
#include <thread>
#include <queue>
#include <pthread.h>

#include "Bat.h"
#include "Monitor.h"

using namespace std;

string input;

int north_counter= 0;
int east_counter= 0;
int south_counter= 0;
int west_counter= 0;

bool north_signal_flag = false;
bool east_signal_flag = false;
bool south_signal_flag = false;
bool west_signal_flag = false;

pthread_mutex_t north_queue_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t east_queue_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t south_queue_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t west_queue_lock = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t apply_north_queue_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t apply_east_queue_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t apply_south_queue_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t apply_west_queue_lock = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t apply_waiting_north_queue_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t apply_waiting_east_queue_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t apply_waiting_south_queue_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t apply_waiting_west_queue_lock = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t flag_north_queue_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t flag_east_queue_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t flag_south_queue_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t flag_west_queue_lock = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t arrive_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t leave_lock = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t north_queue_can_arrive_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t east_queue_can_arrive_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t south_queue_can_arrive_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t west_queue_can_arrive_cond = PTHREAD_COND_INITIALIZER;

Monitor m;

void deal_with_bat(Bat b);
void apply_queue(Bat b);

int main(){

    pthread_mutex_init( &north_queue_lock, NULL);
    pthread_mutex_init( &east_queue_lock, NULL);
    pthread_mutex_init( &south_queue_lock, NULL);
    pthread_mutex_init( &west_queue_lock, NULL);

    pthread_mutex_init( &apply_north_queue_lock, NULL);
    pthread_mutex_init( &apply_east_queue_lock, NULL);
    pthread_mutex_init( &apply_south_queue_lock, NULL);
    pthread_mutex_init( &apply_west_queue_lock, NULL);

    pthread_mutex_init( &apply_waiting_north_queue_lock, NULL);
    pthread_mutex_init( &apply_waiting_east_queue_lock, NULL);
    pthread_mutex_init( &apply_waiting_south_queue_lock, NULL);
    pthread_mutex_init( &apply_waiting_west_queue_lock, NULL);

    pthread_mutex_init( &flag_north_queue_lock, NULL);
    pthread_mutex_init( &flag_east_queue_lock, NULL);
    pthread_mutex_init( &flag_south_queue_lock, NULL);
    pthread_mutex_init( &flag_west_queue_lock, NULL);

    pthread_mutex_init( &arrive_lock, NULL);
    pthread_mutex_init( &leave_lock, NULL);

    pthread_cond_init( &north_queue_can_arrive_cond, NULL);
    pthread_cond_init( &east_queue_can_arrive_cond, NULL);
    pthread_cond_init( &south_queue_can_arrive_cond, NULL);
    pthread_cond_init( &west_queue_can_arrive_cond, NULL);

    cin >> input;

    thread my_threads[input.size()];

    for(int i = 0 ; i < input.size() ; i++){
        Bat b;

        if(input[i] == 'n'){
            b.set_type(0);
        }else if(input[i] == 'e'){
            b.set_type(1);
        }else if(input[i] == 's'){
            b.set_type(2);
        }else if(input[i] == 'w'){
            b.set_type(3);
        }

        b.set_id(i);

        my_threads[i] = thread(deal_with_bat ,b);
    }

    for(int i = 0 ; i < input.size() ; i++){
        my_threads[i].join();
    }

    return 0;
}

void deal_with_bat(Bat b){
    if(b.get_type() == 0){
        pthread_mutex_lock(&north_queue_lock);
        if(north_counter == 0){
            north_counter++;
            pthread_mutex_unlock(&north_queue_lock);
            apply_queue(b);
        }else{
            north_counter++;
            pthread_mutex_unlock(&north_queue_lock);
            pthread_mutex_lock(&apply_waiting_north_queue_lock);
            if(north_signal_flag == false){
                pthread_cond_wait(&north_queue_can_arrive_cond , &apply_north_queue_lock );
            }
            pthread_mutex_lock(&flag_north_queue_lock);
            north_signal_flag = false;
            pthread_mutex_unlock(&flag_north_queue_lock);
            pthread_mutex_unlock(&apply_waiting_north_queue_lock);
            apply_queue(b);
        }
    }else if(b.get_type() == 1){
            pthread_mutex_lock(&east_queue_lock);
        if(east_counter == 0){
            east_counter++;
            pthread_mutex_unlock(&east_queue_lock);
            apply_queue(b);
        }else{
            east_counter++;
            pthread_mutex_unlock(&east_queue_lock);
            pthread_mutex_lock(&apply_waiting_east_queue_lock);
            if(east_signal_flag == false){
                pthread_cond_wait(&east_queue_can_arrive_cond , &apply_east_queue_lock );
            }
            pthread_mutex_lock(&flag_east_queue_lock);
            east_signal_flag = false;
            pthread_mutex_unlock(&flag_east_queue_lock);
            pthread_mutex_unlock(&apply_waiting_east_queue_lock);
            apply_queue(b);
        }
    }else if(b.get_type() == 2){
            pthread_mutex_lock(&south_queue_lock);
        if(south_counter == 0){
            south_counter++;
            pthread_mutex_unlock(&south_queue_lock);
            apply_queue(b);
        }else{
            south_counter++;
            pthread_mutex_unlock(&south_queue_lock);
            pthread_mutex_lock(&apply_waiting_south_queue_lock);
            if(south_signal_flag == false){
                pthread_cond_wait(&south_queue_can_arrive_cond , &apply_south_queue_lock );
            }
            pthread_mutex_lock(&flag_south_queue_lock);
            south_signal_flag = false;
            pthread_mutex_unlock(&flag_south_queue_lock);
            pthread_mutex_unlock(&apply_waiting_south_queue_lock);
            apply_queue(b);
            }
    }else{
        pthread_mutex_lock(&west_queue_lock);
        if(west_counter == 0){
            west_counter++;
            pthread_mutex_unlock(&west_queue_lock);
            apply_queue(b);
        }else{
            west_counter++;
            pthread_mutex_unlock(&west_queue_lock);
            pthread_mutex_lock(&apply_waiting_west_queue_lock);
            if(west_signal_flag == false){
                pthread_cond_wait(&west_queue_can_arrive_cond , &apply_west_queue_lock );
            }
            pthread_mutex_lock(&flag_west_queue_lock);
            west_signal_flag = false;
            pthread_mutex_unlock(&flag_west_queue_lock);
            pthread_mutex_unlock(&apply_waiting_west_queue_lock);
            apply_queue(b);
            }
    }
}

void apply_queue(Bat b){
    pthread_mutex_lock(&arrive_lock);
    m.arrive(b);
    pthread_mutex_unlock(&arrive_lock);
    m.check();
    m.cross(b);
    pthread_mutex_lock(&leave_lock);
    m.leave(b);
    pthread_mutex_unlock(&leave_lock);
    if(b.get_type() == 0){
        pthread_mutex_lock(&north_queue_lock);
        north_counter--;
        pthread_mutex_unlock(&north_queue_lock);
        pthread_cond_signal(&north_queue_can_arrive_cond);
        pthread_mutex_lock(&flag_north_queue_lock);
        north_signal_flag = true;
        pthread_mutex_unlock(&flag_north_queue_lock);
    }else if(b.get_type() == 1){
        pthread_mutex_lock(&east_queue_lock);
        east_counter--;
        pthread_mutex_unlock(&east_queue_lock);
        pthread_cond_signal(&east_queue_can_arrive_cond);
        pthread_mutex_lock(&flag_east_queue_lock);
        east_signal_flag = true;
        pthread_mutex_unlock(&flag_east_queue_lock);
    }else if(b.get_type() == 2){
        pthread_mutex_lock(&south_queue_lock);
        south_counter--;
        pthread_mutex_unlock(&south_queue_lock);
        pthread_cond_signal(&south_queue_can_arrive_cond);
        pthread_mutex_lock(&flag_south_queue_lock);
        south_signal_flag = true;
        pthread_mutex_unlock(&flag_south_queue_lock);
    }else{
        pthread_mutex_lock(&west_queue_lock);
        west_counter--;
        pthread_mutex_unlock(&west_queue_lock);
        pthread_cond_signal(&west_queue_can_arrive_cond);
        pthread_mutex_lock(&flag_west_queue_lock);
        west_signal_flag = true;
        pthread_mutex_unlock(&flag_west_queue_lock);
    }
}
