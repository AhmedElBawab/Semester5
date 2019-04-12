#include <iostream>
#include <fstream>
#include <thread>
#include <time.h>

using namespace std;

int a_row;
int a_column;
int b_row;
int b_column;
int array_a[100][100];
int array_b[100][100];
int array_answer_element[100][100];
int array_answer_row[100][100];

clock_t element_time_start;
clock_t element_time_end;
clock_t row_time_start;
clock_t row_time_end;

int get_an_element(ifstream& file);
void print_array_a();
void print_array_b();
void print_array_answer_element();
void print_array_answer_row();
void calculate_matrix_element(int i , int j);
void calculate_matrix_row(int i);

int main()
{
    ifstream in_file;
    in_file.open("input4.txt.txt");

    if(in_file.is_open()){
        a_row = get_an_element(in_file);
        a_column = get_an_element(in_file);

        for(int i = 0 ; i < a_row ; i++){
            for(int j = 0 ; j < a_column ; j++){
                array_a[i][j] = get_an_element(in_file);
            }
        }

        b_row = get_an_element(in_file);
        b_column = get_an_element(in_file);

        for(int i = 0 ; i < b_row ; i++){
            for(int j = 0 ; j < b_column ; j++){
                array_b[i][j] = get_an_element(in_file);
            }
        }
    }

    if(a_column != b_row){
        cout << "Error!" << endl;
        return 0;
    }

    element_time_start = clock();

    for(int i = 0 ; i < a_row ; i++){
        for(int j = 0 ; j < b_column ; j++){
            std::thread t1(calculate_matrix_element , i ,j);
            t1.join();
            //calculate_matrix_element(i , j);
        }
    }

    element_time_end = clock();

    row_time_start = clock();

    for(int i = 0 ; i < a_row ; i++){
        std::thread t2(calculate_matrix_row , i);
        t2.join();
        //calculate_matrix_row(i);
    }

    row_time_end = clock();

    print_array_a();
    print_array_b();
    print_array_answer_element();
    print_array_answer_row();

    cout << "Element method time:" << element_time_end - element_time_start << endl;
    cout << "Row method time:" << row_time_end - row_time_start << endl;

    ofstream out_file;
    out_file.open ("matrix_output.txt");

    out_file << "Element Method:";
    out_file << "\n";

    for(int i = 0 ; i < a_row ; i++){
        for(int j = 0 ; j < b_column ; j++){
            out_file << array_answer_element[i][j];
            out_file << " ";
        }
        out_file << "\n";
    }

    out_file << "Element Method Time:";
    out_file << element_time_end - element_time_start;
    out_file << "\n";

    out_file << "Row Method:";
    out_file << "\n";

    for(int i = 0 ; i < a_row ; i++){
        for(int j = 0 ; j < b_column ; j++){
            out_file << array_answer_row[i][j];
            out_file << " ";
        }
        out_file << "\n";
    }

    out_file << "Row Method Time:";
    out_file << row_time_end - row_time_start;
    out_file << "\n";


    out_file.close();

    return 0;
}

int get_an_element(ifstream& file){
    int element;
    file >> element;
    return element;
}

void print_array_a(){
    cout << "Array A:" << endl;
    for(int i = 0 ; i < a_row ; i++){
        for(int j = 0 ; j < a_column ; j++){
            cout << array_a[i][j] << " ";
        }
        cout << " " << endl;
    }
}

void print_array_b(){
    cout << "Array B:" << endl;
    for(int i = 0 ; i < b_row ; i++){
        for(int j = 0 ; j < b_column ; j++){
            cout << array_b[i][j] << " ";
        }
        cout << " " << endl;
    }
}

void print_array_answer_element(){
    cout << "Array Element:" << endl;
    for(int i = 0 ; i < a_row ; i++){
        for(int j = 0 ; j < b_column ; j++){
            cout << array_answer_element[i][j] << " ";
        }
        cout << " " << endl;
    }
}

void print_array_answer_row(){
    cout << "Array Row:" << endl;
    for(int i = 0 ; i < a_row ; i++){
        for(int j = 0 ; j < b_column ; j++){
            cout << array_answer_row[i][j] << " ";
        }
        cout << " " << endl;
    }
}

void calculate_matrix_element(int i , int j){
    int temp = 0 ;
    for(int k = 0 ; k < a_column ; k++){
        temp = temp + array_a[i][k] * array_b[k][j];
    }
    array_answer_element[i][j] = temp;
}

void calculate_matrix_row(int i){
    for(int k = 0 ; k < b_column ; k++){
        int temp = 0;
        for(int l = 0 ; l < a_column ; l++){
            temp = temp + array_a[i][l] * array_b[l][k];
        }
        array_answer_row[i][k] = temp;
    }
}
