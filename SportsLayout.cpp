#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <random>
#include <algorithm>
#include <chrono>
#include <vector>


using namespace std;

#include "SportsLayout.h"

    SportsLayout::SportsLayout(string inputfilename)
    {
          
        readInInputFile(inputfilename);
        mapping= new int[z];

    }

    bool SportsLayout::check_output_format()
    {

        vector<bool> visited(l,false);
        for(int i=0;i<z;i++)
        {
            if((mapping[i]>=1 && mapping[i]<=l))
            {
                if(!visited[mapping[i]-1])
                visited[mapping[i]-1]=true;
                else
                {
                    std::cout<<"Repeated locations, check format\n";
                    return false;
                }
            }
            else
            {
                std::cout<<"Invalid location, check format\n";
                return false;
            }
        }

        return true;

    }

    // void SportsLayout::readOutputFile(string output_filename)
    // {
    //         fstream ipfile;
	//         ipfile.open(output_filename, ios::in);
    //         if (!ipfile) {
    //             std::cout << "No such file\n";
    //             exit( 0 );
    //         }
    //         else {
                
    //             vector<int> ip;

    //             while (1) {
    //                 int t;
    //                 ipfile >> t;
    //                 ip.push_back(t);
    //                 if (ipfile.eof())
    //                     break;
                    
    //             }
            
    //         if(ip.size()!=z)
    //         {
    //             std::cout<<"number of values not equal to number of zones, check output format\n";
    //             exit(0);
    //         }
    //         for(int i=0;i<z;i++)
    //         mapping[i]=ip[i];
    //     ipfile.close();

    //     if(!check_output_format())
    //         exit(0);
    //     std::cout<<"Read output file, format OK"<<endl;

    //         }
        
    // }


    long long SportsLayout::cost_fn(){


        long long cost=0;

        for(int i=0;i<z;i++)
        {
           for(int j=0;j<z;j++) 
           {
                cost+=(long long)N[i][j]*(long long)T[mapping[i]-1][mapping[j]-1];
           }
        }

        return cost;
    }

    void SportsLayout::readInInputFile(string inputfilename)
    {
            fstream ipfile;
	        ipfile.open(inputfilename, ios::in);
            if (!ipfile) {
                std::cout << "No such file\n";
                exit( 0 );
            }
            else {
                

                ipfile>> time;
                ipfile >> z;
                ipfile >> l;

                if(z>l)
                {
                    std::cout<<"Number of zones more than locations, check format of input file\n";
                    exit(0);
                }


            

            int **tempT;
            int **tempN;

          tempT = new int*[l];
         for (int i = 0; i < l; ++i)
            tempT[i] = new int[l];
        
        tempN = new int*[z];
        for (int i = 0; i < z; ++i)
            tempN[i] = new int[z];

        for(int i=0;i<z;i++)
        {
            for(int j=0;j<z;j++)
            ipfile>>tempN[i][j];
        }

        for(int i=0;i<l;i++)
        {
            for(int j=0;j<l;j++)
            ipfile>>tempT[i][j];
        }

        ipfile.close();

        T= tempT;
        N= tempN;
            }

    }

    void SportsLayout::write_to_file(string outputfilename){

         // Open the file for writing
    ofstream outputFile(outputfilename);

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        cerr << "Failed to open the file for writing." << std::endl;
        exit(0);
    }

    for(int i=0;i<z;i++)
    outputFile<<mapping[i]<<" ";

    // Close the file
    outputFile.close();

    std::cout << "Allocation written to the file successfully." << endl;

    }

    int* generate_intelligent_start_state(int z,int l,int** T) {
        int* initial_allocation = new int[z];
        int* availableLocations = new int[l];
        
        for (int i = 0; i < l; ++i) {
            availableLocations[i] = i+1;
        }

        // function to sort locations in ascending order based on sum of time to all other locations
        auto location_comparator = [&](int loc1, int loc2) {
            int total_time1 = 0, total_time2 = 0;
            for (int i = 0; i < l; ++i) {
                total_time1 += T[i][loc1 - 1]; 
                total_time2 += T[i][loc2 - 1];
            }
            return total_time1 > total_time2;
        };

        std::sort(availableLocations, availableLocations + l, location_comparator);
        return availableLocations;
    }

    void SportsLayout::compute_allocation()
    {
        //you can write your code here 
        //comment out following dummy code

        auto start = std::chrono::high_resolution_clock::now();
              
        // Stable Cost and Mapping for Dterministic Bounding
        int stable_cost;
        int stable_mapping[z];
        int temp = 0;

        int permutation[l];
        for (int i = 1; i <= l; i++) {
            permutation[i-1] = i;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        vector<int> locations_left;
        int r=0;
        while(1)
        {

            locations_left.clear();
            if(r == 0)
            {
                // Basic Start State: position 1 mapped to 1
                for (int i=0;i<z;i++)
                {
                    mapping[i] = i+1;
                }

                for(int i=z+1;i<=l;i++)
                {
                    locations_left.push_back(i);
                }

                stable_cost = cost_fn();
                for(int q=0;q<z;q++)
                {
                    stable_mapping[q] = mapping[q];
                }
            }
            else if(r==1)
            {
                // Intelligent Start State
                int* testing = generate_intelligent_start_state(z,l,T);
                for(int p=0;p<l;p++)
                {

                    if(p<z)
                    {
                        mapping[p] = testing[p];

                    }
                    else{
                        locations_left.push_back(testing[p]);
                    }
                }
            }
            else
            {
                //Random Start State
                std::shuffle(permutation, permutation+l, gen);
                for(int p=0;p<l;p++)
                {

                    if(p<z)
                    {
                        mapping[p] = permutation[p];

                    }
                    else{
                        locations_left.push_back(permutation[p]);
                    }
                }
                
            }


        int best_cost = cost_fn(); 
        int brk = 0;
         
        
        while(1)
        {
            // Loop for jumping to first best neighbors; Here Neighbors means only 1 of the position is changed while maintaining every distinct locations
            auto mid1 = std::chrono::high_resolution_clock::now();

            auto dur1 = std::chrono::duration_cast<std::chrono::milliseconds>(mid1 - start);
            if(dur1.count() > time*60*1000 - 20000)
            {
                break;
            }

            brk = 0;
            
            for(int k=0;k<z;k++)
            {
                for(int n=0;n<locations_left.size();n++)
                {
                    temp =mapping[k];

                    mapping[k] = locations_left[n];
                    
                    if(cost_fn() < best_cost)
                    {
                        best_cost = cost_fn();
                        // std::cout << "log: best cost = " << best_cost << " "<< locations_left[n] << " " << k << "\n";
                        locations_left[n] = temp;
                        brk = 1;

                        auto mid2 = std::chrono::high_resolution_clock::now();

                        auto dur2 = std::chrono::duration_cast<std::chrono::milliseconds>(mid2 - start);
                        if(dur2.count() > time*60*1000 - 20000)
                        {
                            brk = 0;
                            break;
                        }
                       
                    }
                    else
                    {
                        mapping[k] = temp;  
                    } 
                }
            }
            
            if(brk==0)
            {
                break;
            }
        }

        best_cost = cost_fn();

        while(1)
        {
            // Loop for swaping zone locations
            auto mid1 = std::chrono::high_resolution_clock::now();

            auto dur1 = std::chrono::duration_cast<std::chrono::milliseconds>(mid1 - start);
            if(dur1.count() > time*60*1000 - 20000)
            {
                break;
            }
            
            brk = 0;

            for(int k=0; k<z; k++)
            {
                for(int i=k+1;i<z;i++)
                {
                    temp = mapping[i];
                    mapping[i] = mapping[k];
                    mapping[k] = temp;

                    if(cost_fn() < best_cost)
                    {
                        best_cost = cost_fn();
                        // std::cout << "log: best cost swap = " << best_cost << "\n";
                        brk = 1;
                        auto mid2 = std::chrono::high_resolution_clock::now();

                        auto dur2 = std::chrono::duration_cast<std::chrono::milliseconds>(mid2 - start);
                        if(dur2.count() > time*60*1000 - 20000)
                        {
                            brk = 0;

                            break;
                        }
                    }
                    else{
                        mapping[k] = mapping[i];
                        mapping[i] = temp;
                    }
                }
            }
            if(brk==0)
            {
                break;
            }
        }

            
            if(stable_cost > cost_fn())
            {
                stable_cost = cost_fn();
                for(int q=0;q<z;q++)
                {
                    stable_mapping[q] = mapping[q];
                }
            }

            // Breaking based on time
            auto mid = std::chrono::high_resolution_clock::now();

            auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(mid - start);
            if(dur.count() > time*60*1000 - 20000)
            {
                break;
            }
            r+=1;
        } 
       
        
        for(int q=0;q<z;q++)
        {
            mapping[q] = stable_mapping[q];
        }


        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        // std::cout << "Time taken by code: " << duration.count() << " milliseconds" << std::endl;

    }


