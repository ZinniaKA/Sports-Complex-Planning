#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <chrono>

#include "SportsLayout.h"

using namespace std;

int main(int argc, char** argv )
{

    auto start = std::chrono::high_resolution_clock::now();

     // Parse the input.
    if ( argc < 3 )
    {   
        cout<<"Missing arguments\n";
        cout<<"Correct format : \n";
        cout << "./main <input_filename> <output_filename>";
        exit ( 0 );
    }
    string inputfilename ( argv[1] );
    string outputfilename ( argv[2] );
    
    SportsLayout *s  = new SportsLayout( inputfilename );
    s->compute_allocation();
    s->write_to_file(outputfilename);

    long long cost = s->cost_fn ();
    cout<< "cost:"<<cost<<endl;

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    // std::cout << "Time taken by code: " << duration.count() << " milliseconds" << std::endl;


    return 0;

}