#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

int number_of_elements;
int unsorted_array[100];

int get_an_element(ifstream& file);
void merg_sort(int *arr , int left , int right);
void merg(int *arr , int left , int mid , int right);
void print_array(int *arr);

int main()
{
    ifstream in_file;
    in_file.open("input 4.txt.txt");

    if(in_file.is_open()){
        number_of_elements = get_an_element(in_file);

        for(int i = 0 ; i < number_of_elements ; i++){
            unsorted_array[i] = get_an_element(in_file);
        }
    }

    cout << "Number Of Elements: ";
    cout << number_of_elements << endl;


    cout << "Unsorted Array:" << endl;
    print_array(unsorted_array);
    cout << endl;

    std::thread t1(merg_sort , unsorted_array , 0 ,number_of_elements-1);
    t1.join();
    //merg_sort(unsorted_array , 0 , number_of_elements-1);

    cout << "Sorted Array:" << endl;
    print_array(unsorted_array);

    return 0;
}

int get_an_element(ifstream& file){
    int element;
    file >> element;
    return element;
}

void print_array(int *arr){
    for(int i = 0 ; i < number_of_elements ; i++){
        cout << unsorted_array[i];
        cout <<" ";
    }
}

void merg_sort(int *arr , int left , int right){
    if(right > left){
        int mid = left + (right - left)/2;
        std::thread t1(merg_sort , arr , left , mid);
        t1.join();
        //merg_sort(arr , left , mid);
        std::thread t2(merg_sort , arr , mid+1 ,right);
        t2.join();
        //merg_sort(arr , mid+1 , right);
        std::thread t3(merg , arr , left , mid , right);
        t3.join();
        //merg(arr , left , mid , right);
    }
}

void merg(int *arr , int left , int mid , int right){
    int size_left_array = mid - left + 1;
    int size_right_array = right - mid;

    int left_array[size_left_array];
    int right_array[size_right_array];

    for(int i = 0 ; i < size_left_array ; i++){
        left_array[i] = arr[left + i];
    }
    for(int i = 0 ; i < size_right_array ; i++){
        right_array[i] = arr[mid+1+i];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < size_left_array && j < size_right_array) {
        if (left_array[i] <= right_array[j]){
            arr[k] = left_array[i];
            i++;
        }else{
            arr[k] = right_array[j];
            j++;
        }
        k++;
    }

    while (i < size_left_array){
        arr[k] = left_array[i];
        i++;
        k++;
    }

    while (j < size_right_array){
        arr[k] = right_array[j];
        j++;
        k++;
    }
}
