#ifndef MONITOR_H
#define MONITOR_H

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

#include "Bat.h"

class Monitor
{
    public:
        Monitor(){
            pthread_mutex_init( &north_lock, NULL);
            pthread_mutex_init( &east_lock, NULL);
            pthread_mutex_init( &south_lock, NULL);
            pthread_mutex_init( &west_lock, NULL);

            pthread_mutex_init( &cross_lock, NULL);
            pthread_mutex_init( &print_lock, NULL);

            pthread_cond_init( &north_cross_cond, NULL);
            pthread_cond_init( &east_cross_cond, NULL);
            pthread_cond_init( &south_cross_cond, NULL);
            pthread_cond_init( &west_cross_cond, NULL);
        };
        virtual ~Monitor();

        void arrive(Bat b){
            if(b.get_type() == 0){
                pthread_mutex_lock(&print_lock);
                cout << "BAT " <<b.get_id()+1 << " from North arrives at crossing" << endl;
                pthread_mutex_unlock(&print_lock);
                north_bat = b;
                north_flag = true;
            }else if(b.get_type() == 1){
                pthread_mutex_lock(&print_lock);
                cout << "BAT " <<b.get_id()+1 << " from East arrives at crossing" << endl;
                pthread_mutex_unlock(&print_lock);
                east_bat = b;
                east_flag = true;
            }else if(b.get_type() == 2){
                pthread_mutex_lock(&print_lock);
                cout << "BAT " <<b.get_id()+1 << " from South arrives at crossing" << endl;
                pthread_mutex_unlock(&print_lock);
                south_bat = b;
                south_flag = true;
            }else{
                pthread_mutex_lock(&print_lock);
                cout << "BAT " <<b.get_id()+1 << " from West arrives at crossing" << endl;
                pthread_mutex_unlock(&print_lock);
                west_bat = b;
                west_flag = true;
            }
        }

        void cross(Bat b){
            if(b.get_type() == 0){
                if(west_flag == true){
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " is trying to cross" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " is waiting north signal" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_cond_wait(&north_cross_cond , &north_lock);
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " recieved north signal" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_mutex_lock(&cross_lock);
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " is crossing" << endl;
                    pthread_mutex_unlock(&print_lock);
                    north_flag = false;
                    std::this_thread::sleep_for (std::chrono::seconds(1));
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " has crossed" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_mutex_unlock(&cross_lock);
                }else{
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " is trying to cross" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_mutex_lock(&cross_lock);
                    if(west_flag == true){
                        pthread_mutex_unlock(&cross_lock);
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " is trying to cross" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " is waiting north signal" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_cond_wait(&north_cross_cond , &north_lock);
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " recieved north signal" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_mutex_lock(&cross_lock);
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " is crossing" << endl;
                        pthread_mutex_unlock(&print_lock);
                        north_flag = false;
                        std::this_thread::sleep_for (std::chrono::seconds(1));
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " has crossed" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_mutex_unlock(&cross_lock);
                    }else{
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " is crossing" << endl;
                        pthread_mutex_unlock(&print_lock);
                        north_flag = false;
                        std::this_thread::sleep_for (std::chrono::seconds(1));
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " has crossed" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_mutex_unlock(&cross_lock);
                    }
                }
            }else if(b.get_type() == 1){
                if(north_flag == true){
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " is trying to cross" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " is waiting east signal" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_cond_wait(&east_cross_cond , &east_lock);
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " recieved east signal" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_mutex_lock(&cross_lock);
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " is crossing" << endl;
                    pthread_mutex_unlock(&print_lock);
                    east_flag = false;
                    std::this_thread::sleep_for (std::chrono::seconds(1));
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " has crossed" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_mutex_unlock(&cross_lock);
                }else{
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " is trying to cross" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_mutex_lock(&cross_lock);
                    if(north_flag == true){
                        pthread_mutex_unlock(&cross_lock);
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " is trying to cross" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " is waiting east signal" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_cond_wait(&east_cross_cond , &east_lock);
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " recieved east signal" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_mutex_lock(&cross_lock);
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " is crossing" << endl;
                        pthread_mutex_unlock(&print_lock);
                        east_flag = false;
                        std::this_thread::sleep_for (std::chrono::seconds(1));
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " has crossed" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_mutex_unlock(&cross_lock);
                    }else{
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " is crossing" << endl;
                        pthread_mutex_unlock(&print_lock);
                        east_flag = false;
                        std::this_thread::sleep_for (std::chrono::seconds(1));
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " has crossed" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_mutex_unlock(&cross_lock);
                    }
                }
            }else if(b.get_type() == 2){
                if(east_flag == true){
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " is trying to cross" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " is waiting south signal" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_cond_wait(&south_cross_cond , &south_lock);
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " recieved south signal" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_mutex_lock(&cross_lock);
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " is crossing" << endl;
                    pthread_mutex_unlock(&print_lock);
                    south_flag = false;
                    std::this_thread::sleep_for (std::chrono::seconds(1));
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " has crossed" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_mutex_unlock(&cross_lock);
                }else{
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " is trying to cross" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_mutex_lock(&cross_lock);
                    if(east_flag == true){
                        pthread_mutex_unlock(&cross_lock);
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " is trying to cross" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " is waiting south signal" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_cond_wait(&south_cross_cond , &south_lock);
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " recieved south signal" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_mutex_lock(&cross_lock);
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " is crossing" << endl;
                        pthread_mutex_unlock(&print_lock);
                        south_flag = false;
                        std::this_thread::sleep_for (std::chrono::seconds(1));
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " has crossed" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_mutex_unlock(&cross_lock);
                    }else{
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " is crossing" << endl;
                        pthread_mutex_unlock(&print_lock);
                        south_flag = false;
                        std::this_thread::sleep_for (std::chrono::seconds(1));
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " has crossed" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_mutex_unlock(&cross_lock);
                    }
                }
            }else if(b.get_type() == 3){
                if(south_flag == true){
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " is trying to cross" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " is waiting west signal" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_cond_wait(&west_cross_cond , &west_lock);
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " recieved south signal" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_mutex_lock(&cross_lock);
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " is crossing" << endl;
                    pthread_mutex_unlock(&print_lock);
                    west_flag = false;
                    std::this_thread::sleep_for (std::chrono::seconds(1));
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " has crossed" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_mutex_unlock(&cross_lock);
                }else{
                    pthread_mutex_lock(&print_lock);
                    cout << "BAT" << b.get_id() + 1 << " is trying to cross" << endl;
                    pthread_mutex_unlock(&print_lock);
                    pthread_mutex_lock(&cross_lock);
                        if(south_flag == true){
                        pthread_mutex_unlock(&cross_lock);
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " is trying to cross" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " is waiting west signal" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_cond_wait(&west_cross_cond , &west_lock);
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " recieved south signal" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_mutex_lock(&cross_lock);
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " is crossing" << endl;
                        pthread_mutex_unlock(&print_lock);
                        west_flag = false;
                        std::this_thread::sleep_for (std::chrono::seconds(1));
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " has crossed" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_mutex_unlock(&cross_lock);
                    }else{
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " is crossing" << endl;
                        pthread_mutex_unlock(&print_lock);
                        west_flag = false;
                        std::this_thread::sleep_for (std::chrono::seconds(1));
                        pthread_mutex_lock(&print_lock);
                        cout << "BAT" << b.get_id() + 1 << " has crossed" << endl;
                        pthread_mutex_unlock(&print_lock);
                        pthread_mutex_unlock(&cross_lock);
                    }
                }
            }
        }

        void leave(Bat b){
            if(b.get_type() == 0){
                pthread_mutex_lock(&print_lock);
                cout << "BAT " <<b.get_id()+1 << " from North leaving crossing" << endl;
                pthread_mutex_unlock(&print_lock);
                north_flag = false;
                pthread_cond_signal(&east_cross_cond);
            }else if(b.get_type() == 1){
                pthread_mutex_lock(&print_lock);
                cout << "BAT " <<b.get_id()+1 << " from East leaving crossing" << endl;
                pthread_mutex_unlock(&print_lock);
                east_flag = false;
                pthread_cond_signal(&south_cross_cond);
            }else if(b.get_type() == 2){
                pthread_mutex_lock(&print_lock);
                cout << "BAT " <<b.get_id()+1 << " from South leaving crossing" << endl;
                pthread_mutex_unlock(&print_lock);
                south_flag = false;
                pthread_cond_signal(&west_cross_cond);
            }else{
                pthread_mutex_lock(&print_lock);
                cout << "BAT " <<b.get_id()+1 << " from West leaving crossing" << endl;
                pthread_mutex_unlock(&print_lock);
                west_flag = false;
                pthread_cond_signal(&north_cross_cond);
            }
        }

        void check(){
            if(north_flag == true && east_flag == true && south_flag == true && west_flag == true){
                pthread_mutex_lock(&print_lock);
                cout << "DEADLOCK: BAT jam detected, signalling North to go" << endl;
                pthread_mutex_unlock(&print_lock);
                pthread_cond_signal(&north_cross_cond);
            }
        }

    protected:

    private:
    Bat north_bat;
    Bat east_bat ;
    Bat south_bat ;
    Bat west_bat ;

    bool north_flag = false;
    bool east_flag = false;
    bool south_flag = false;
    bool west_flag = false;

    pthread_mutex_t north_lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t east_lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t south_lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t west_lock = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_t cross_lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t print_lock = PTHREAD_MUTEX_INITIALIZER;

    pthread_cond_t north_cross_cond = PTHREAD_COND_INITIALIZER;
    pthread_cond_t east_cross_cond = PTHREAD_COND_INITIALIZER;
    pthread_cond_t south_cross_cond = PTHREAD_COND_INITIALIZER;
    pthread_cond_t west_cross_cond = PTHREAD_COND_INITIALIZER;
};

#endif // MONITOR_H
