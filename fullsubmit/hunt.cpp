
//Project Identifier: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD
//
//  main.cpp
//  eecs281proj1
//
//  Created by Je/Users/jevinnishioka/Desktopvin Nishioka on 12/20/21.
//  Copyright © 2021 Jevin Nishioka. All rights reserved.
//
#include <iostream>
#include <vector>
#include <string>
#include <istream>
#include <cstring>
#include <string.h>
#include "xcode_redirect.hpp"
#include <algorithm>
#include "hunt.h"
using namespace std;
int main(int argc, char * argv[]){
    ios_base::sync_with_stdio(false);
    Hunt hunt;
    hunt.getMode(argc,argv);
    
    string junk;
    xcode_redirect(argc,argv);
    while(getline(cin,junk)){
        if(junk[0] == 'M'){
            cin >> hunt.size;
    //        size_t temp2 = static_cast<size_t>(hunt.size);
   //         hunt.grid.reserve(temp2);
            hunt.MapBuilder(hunt.size);
            break;
        }
        else if(junk[0] == 'L'){
            cin >> hunt.size;
   //         size_t temp2 = static_cast<size_t>(hunt.size);
       //     hunt.grid.reserve(temp2);
            hunt.ListBuilder(hunt.size);
            break;
        }
    }
    hunt.Sail();
    if(hunt.treasureFound == true){
    hunt.Backtrace(hunt.treasure);
    }
        if(hunt.verbose){
        cout << "Treasure hunt started at: " << hunt.start.x << "," << hunt.start.y << endl;
            int counter = 0;
            size_t temp1 = static_cast<size_t>(counter);
            if(hunt.wentAshore > 0){
            while(hunt.ashore.size()-1 > temp1){
                cout << "Went ashore at: " << hunt.ashore[temp1].x << "," << hunt.ashore[temp1].y << endl;
                cout << "Searching island... party returned with no treasure." << endl;
                temp1 += 1;
            }
            cout << "Went ashore at: " << hunt.ashore[temp1].x << "," << hunt.ashore[temp1].y << endl;
                if(hunt.treasureFound == true){
                    cout << "Searching island... party found treasure at " << hunt.treasure.x << "," << hunt.treasure.y << "." << endl;
                }
                else if(hunt.treasureFound == false){
                    cout << "Searching island... party returned with no treasure." << endl;
            }
            
                
    }
            else{
            cout << "Treasure hunt failed" << endl;
            }
}
        if(hunt.stats){
        cout << "--- STATS ---" << endl;
        cout << "Starting location: " << hunt.start.x << "," << hunt.start.y << endl;
        cout << "Water locations investigated: " << hunt.waterInv << endl;
        cout << "Land locations investigated: " << hunt.landInv << endl;
        cout << "Went ashore: " << hunt.wentAshore << endl;
        if(hunt.treasureFound == true){
        cout << "Path length: " << hunt.pathLength << endl;
        cout << "Treasure location: " << hunt.treasure.x << "," << hunt.treasure.y << endl;
        }
        cout << "--- STATS ---" << endl;
    }
    if(hunt.mapMode && hunt.treasureFound){
        for(int i= 0; i < hunt.size; i++){
            size_t temp1 = static_cast<size_t>(i);
            for(int x= 0; x < hunt.size; x++){
                size_t temp2 = static_cast<size_t>(x);
                cout << hunt.grid[temp1][temp2].type;
            }
            cout << endl;
        }
    }
    
    if(hunt.listMode && hunt.treasureFound){
        cout << "Sail:" << endl;
        int count = 0;
        size_t temp = static_cast<size_t>(count);
        size_t sze = hunt.sailed.size()-1;
        while(hunt.sailed.size() != temp){
            cout << hunt.sailed[sze-temp].x << "," << hunt.sailed[sze-temp].y << endl;
            temp = temp + 1;
        }
        cout << "Search:" << endl;
        count = 0;
        temp = 0;
        while(hunt.searched.size() != temp){
            cout << hunt.searched[temp].x << "," << hunt.searched[temp].y << endl;
            temp = temp + 1;
        }
        
    }
    if(hunt.treasureFound == true){
        cout << "Treasure found at " << hunt.treasure.x << "," << hunt.treasure.y << " with path length " << hunt.pathLength << "." << endl;
    }
    else{
        cout << "No treasure found after investigating " << hunt.waterInv + hunt.landInv << " locations." << endl;
    }
    return 0;
    
}

