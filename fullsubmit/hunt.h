////Project Identifier: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD
//  eecs281proj1
//
//  Created by Jevin Nishioka on 1/15/22.
//  Copyright © 2022 Jevin Nishioka. All rights reserved.
//
//reading from a 2D vector off the command line.
//Find initial location (map[x][y] == "@")
//Insert initial location into CaptainSearch function
//Captain searches until finding land or treasure
//If land is found call FirstMateSearch
//Insert locations into deque and pop from front
//If FirstMate finds land end the Captains Hunt and First Mate Hunt and begin backtracing
//If treasure is found begin backtrace
//Function of Search Containers
//ADD locations to container in Hunt Order and pop them off based on type specified at command line
//popped location is now current location
//locations in Search Containers are discovered


//backtracing
//where were you before the current location?
//previous must be documented/accessible
//search containers are not useful because they contain discovered locations and not ones that were taken
//make a queue of CurrentLocations and pop them off the front in order?
//inverse the hunt algorithm?
//for coordinate list output make an array of CurrentLocations ordered by how they were popped off the Queue of Visited Locations
//for map output could be more tricky
//2d vector but must change the visited locations to symbols based on direction of travel


//how do you deal with hunt order?
//north = map[x-1][y], south = map[x+1][y], east = map[x][y+1], west = map[x][y-1]
//order can be specified at command line, how do you implement this


//CaptainSearch Algorithm
//Need:Starting point,Hunt Order,Container
//Modifies:Search Container,Visited Locations Queue
//Returns void
//How do you run the First Mate function while pausing the CaptainSearch?
//if you were to make a new call to CaptainSearch at the conclusion of a FirstMateSearch would you be able to use the previous SearchContainer and be able to backtrace still?
//FirstMateSearch Algorithm
//Need:Starting point,Hunt Order,Container
//Modifies:FM Search Container, Visited Locations Queue?
//When backtracing do we care about FirstMate Searches or do just care about visited water locations?
//all of it

//based on size given
//in order from there

//Map Struct Importance
//Want to store discovered locations
//Store coordinates
//Store data that helps backtrace

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <istream>
#include <cstring>
#include <string.h>
#include "xcode_redirect.hpp"
#include <deque>
#include <getopt.h>

using namespace std;
#ifndef HUNT_H
#define HUNT_H
#endif


class Hunt{
public:
    struct Coordinate{
        int x;
        int y;
    };
    struct Map{
        char type = '.';
        bool discovered = false;
        char direction = 'x';
    };
    Hunt(){}
    bool treasureFound = false;
    Coordinate treasure;
    bool firstMateQ = true;
    bool firstMateS = false;
    bool captainS = true;
    bool captainQ = false;
    bool mapMode = false;
    bool listMode = false;
    bool verbose = false;
    bool stats = false;
    bool retraced = false;
    string mode;
    string HUNT_ORDER = "NESW";
    vector<vector<Map> > grid;
    Coordinate start;
    void Sail();
    void Search(Coordinate curr);
    void Backtrace(Coordinate treasure);
    void MapBuilder(int size);
    void ListBuilder(int size);
    void getMode(int argc, char* argv[]);
    Coordinate curr;
    Coordinate currFM;
    int pathLength = 0;
    vector<Coordinate> ashore;
    vector<Coordinate> searched;
    vector<Coordinate> sailed;
    int waterInv = 0;
    int landInv = 0;
    int wentAshore = 0;
    int size = 0;
};
void Hunt::Backtrace(Coordinate treasure){
    Coordinate current;
    Coordinate prev;
    current.x = treasure.x;
    current.y = treasure.y;
    prev.x = treasure.x;
    prev.y = treasure.y;
    size_t temp1 = static_cast<size_t>(treasure.x);
    size_t temp2 = static_cast<size_t>(treasure.y);
    switch(grid[temp1][temp2].direction){
        case('N'):
            current.x = current.x + 1;
            break;
        case('S'):
            current.x = current.x - 1;
            break;
        case('W'):
            current.y = current.y + 1;
            break;
        case('E'):
            current.y = current.y - 1;
            break;
    }
    grid[temp1][temp2].type = 'X';
    while(retraced == false){
        ++pathLength;
        size_t temp3 = static_cast<size_t>(current.x);
        size_t temp4 = static_cast<size_t>(current.y);
        size_t Prev_x = static_cast<size_t>(prev.x);
        size_t Prev_y = static_cast<size_t>(prev.y);
        if(grid[temp3][temp4].type == 'o'){
            searched.push_back(current);
        }
        if(grid[temp3][temp4].type == '@'){
            retraced = true;
            sailed.push_back(start);
        }
        if(grid[temp3][temp4].type == '.'){
            sailed.push_back(current);
        }
        switch(grid[temp3][temp4].direction){
            case('E'):
                if(grid[Prev_x][Prev_y].direction == 'N' || grid[Prev_x][Prev_y].direction == 'S'){
                   grid[temp3][temp4].type = '+';
                    prev.y = current.y;
                    prev.x = current.x;
                    current.y = current.y - 1;
                }
                else{
                    grid[temp3][temp4].type = '-';
                    prev.y = current.y;
                    prev.x = current.x;
                    current.y = current.y-1;
                }
                break;
            case('W'):
                if(grid[Prev_x][Prev_y].direction == 'N' || grid[Prev_x][Prev_y].direction == 'S'){
                    grid[temp3][temp4].type = '+';
                    prev.y = current.y;
                    prev.x = current.x;
                    current.y = current.y + 1;
                }
                else{
                    grid[temp3][temp4].type = '-';
                    prev.y = current.y;
                    prev.x = current.x;
                    current.y = current.y+1;
   
                }
                break;
            case('N'):
                if(grid[Prev_x][Prev_y].direction == 'W' || grid[Prev_x][Prev_y].direction == 'E'){
                    grid[temp3][temp4].type = '+';
                    prev.x = current.x;
                    prev.y = current.y;
                    current.x = current.x + 1;
                }
                else{
                    grid[temp3][temp4].type = '|';
                    prev.x = current.x;
                    prev.y = current.y;
                    current.x = current.x+1;
    
                }
                break;
            case('S'):
                if(grid[Prev_x][Prev_y].direction == 'W' || grid[Prev_x][Prev_y].direction == 'E'){
                    grid[temp3][temp4].type = '+';
                    prev.x = current.x;
                    prev.y = current.y;
                    current.x = current.x - 1;
                }
                else{
                    grid[temp3][temp4].type = '|';
                    prev.x = current.x;
                    prev.y = current.y;
                    current.x = current.x-1;
                }
                break;
                
        }
    }
}

void Hunt::Search(Coordinate curr){
        deque<Hunt::Coordinate> FirstMate;
        size_t tempx = static_cast<size_t>(curr.x);
        size_t tempy = static_cast<size_t>(curr.y);
    if(grid[tempx][tempy].type == '$'){
        treasureFound = true;
        treasure.x = curr.x;
        treasure.y = curr.y;
        searched.push_back(treasure);
        if(firstMateQ){
            FirstMate.push_back(treasure);
            landInv++;
            
        }
        if(firstMateS){
            FirstMate.push_front(treasure);
            landInv++;
        }
    }
        grid[tempx][tempy].discovered = true;
        FirstMate.push_back(curr);
        while(FirstMate.size() != 0 && treasureFound == false){
            Coordinate coord = FirstMate.front();
            FirstMate.pop_front();
            landInv += 1;
            currFM.x = coord.x;
            currFM.y = coord.y;
            size_t FM_X = static_cast<size_t>(currFM.x);
            size_t FM_Y = static_cast<size_t>(currFM.y);
            for(int i= 0; i < 4;i++){
                size_t tempi = static_cast<size_t>(i);
               if(treasureFound){
                    break;
            }
                switch(HUNT_ORDER[tempi]){
                    case('N'):
                    if(currFM.x - 1 < 0){
                            break;
                        }
                    else if(grid[FM_X-1][FM_Y].discovered == false){
                        if(grid[FM_X-1][FM_Y].type == 'o'){
                            Coordinate c;
                            c.x = currFM.x-1;
                            c.y = currFM.y;
                            grid[FM_X-1][FM_Y].discovered = true;
                            grid[FM_X-1][FM_Y].direction = 'N';
                            if(firstMateQ){
                            FirstMate.push_back(c);
                                
                            }
                            if(firstMateS){
                            FirstMate.push_front(c);
                            }
                            
                        }
                        else if(grid[FM_X-1][FM_Y].type == '$'){
                            grid[FM_X-1][FM_Y].discovered = true;
                            grid[FM_X-1][FM_Y].direction = 'N';
                            treasureFound = true;
                            treasure.x = currFM.x-1;
                            treasure.y = currFM.y;
                            landInv += 1;
                            searched.push_back(treasure);
                            
                        }

                        }
                        break;
                    case('E'):
                    if(currFM.y + 1 > size - 1){
                            break;
                        }
                    else if(grid[FM_X][FM_Y+1].discovered == false){
                        if(grid[FM_X][FM_Y+1].type == 'o'){
                            Coordinate c;
                            c.x = currFM.x;
                            c.y = currFM.y+1;
                            grid[FM_X][FM_Y+1].discovered = true;
                            grid[FM_X][FM_Y+1].direction = 'E';
                            if(firstMateQ){
                                FirstMate.push_back(c);
                                
                            }
                            if(firstMateS){
                                FirstMate.push_front(c);
                                
                            }
                        }
                        else if(grid[FM_X][FM_Y+1].type == '$'){
                            grid[FM_X][FM_Y+1].discovered = true;
                            grid[FM_X][FM_Y+1].direction = 'E';
                            treasureFound = true;
                            treasure.x = currFM.x;
                            treasure.y = currFM.y+1;
                            landInv += 1;
                            searched.push_back(treasure);
                        }
                    }
                        break;
                    case('S'):
                    if(currFM.x + 1 > size - 1){
                            break;
                        }
                    else if(grid[FM_X+1][FM_Y].discovered == false){
                        if(grid[FM_X+1][FM_Y].type == 'o'){
                            Coordinate c;
                            c.x = currFM.x+1;
                            c.y = currFM.y;
                            grid[FM_X+1][FM_Y].direction = 'S';
                            grid[FM_X+1][FM_Y].discovered = true;
                            if(firstMateQ){
                                FirstMate.push_back(c);
                                
                            }
                            if(firstMateS){
                                FirstMate.push_front(c);
                                
                            }
                        }
                        else if(grid[FM_X+1][FM_Y].type == '$'){
                            treasureFound = true;
                            grid[FM_X+1][FM_Y].discovered = true;
                            grid[FM_X+1][FM_Y].direction = 'S';
                            treasure.x = currFM.x+1;
                            treasure.y = currFM.y;
                            landInv += 1;
                            searched.push_back(treasure);
                        }
                    }
                        break;
                    case('W'):
                    if(currFM.y - 1 < 0){
                            break;
                        }
                    else if(grid[FM_X][FM_Y-1].discovered == false){
                        if(grid[FM_X][FM_Y-1].type == 'o'){
                            Coordinate c;
                            c.x = currFM.x;
                            c.y = currFM.y-1;
                            grid[FM_X][FM_Y-1].direction = 'W';
                            grid[FM_X][FM_Y-1].discovered = true;
                            if(firstMateQ){
                                FirstMate.push_back(c);
                            }
                            if(firstMateS){
                                FirstMate.push_front(c);
                            }
                        }
                        else if(grid[FM_X][FM_Y-1].type == '$'){
                            treasureFound = true;
                            grid[FM_X][FM_Y-1].discovered = true;
                            grid[FM_X][FM_Y-1].direction = 'W';
                            treasure.x = currFM.x;
                            treasure.y = currFM.y-1;
                            landInv += 1;
                            searched.push_back(treasure);
                        }
                }
                        break;
                }
            }
            }
}


void Hunt::Sail(){
    deque<Hunt::Coordinate> Captain;
    size_t temp1 = static_cast<size_t>(start.x);
    size_t temp2 = static_cast<size_t>(start.y);
    grid[temp1][temp2].discovered = true;
    Coordinate curr;
    curr.x = start.x;
    curr.y = start.y;
    Captain.push_front(start);
        while(Captain.size() != 0 && treasureFound == false){
            Coordinate coord = Captain.front();
    //        sailed.push_back(coord);
            cout << coord.x << "," << coord.y << endl;
            Captain.pop_front();
            waterInv += 1;
            curr.x = coord.x;
            curr.y = coord.y;
            size_t temp1 = static_cast<size_t>(curr.x);
            size_t temp2 = static_cast<size_t>(curr.y);
            for(int i = 0; i < 4; i++){
            size_t tempi = static_cast<size_t>(i);
               if(treasureFound){
                    break;
                }
            switch(HUNT_ORDER[tempi]){
                case('N'):
                    if(curr.x - 1 < 0){
                        break;
                    }
                    else if(grid[temp1-1][temp2].discovered == false){
                    if(grid[temp1-1][temp2].type == 'o' || grid[temp1-1][temp2].type == '$'){
                        curr.x = curr.x - 1;
                        ashore.push_back(curr);
                        grid[temp1-1][temp2].direction = 'N';
                        Hunt::Search(curr);
                        wentAshore += 1;
                        curr.x = curr.x + 1;
                        if(treasureFound == true){
                            break;
                        }
                        else{
                            searched.clear();
                        }
                    }
                    else if(grid[temp1-1][temp2].type == '#'){
                        grid[temp1-1][temp2].discovered = true;
                        break;
                    }
                    else{
                        Coordinate c;
                        c.x = curr.x-1;
                        c.y = curr.y;
                        grid[temp1-1][temp2].direction = 'N';
                        if(captainQ){
                            Captain.push_back(c);
                            
                            
                        }
                        if(captainS){
                            Captain.push_front(c);
                            
                        }
                        grid[temp1-1][temp2].discovered = true;}
                    }
                    break;
                case('E'):
                    if(curr.y + 1 > (size - 1)){
                        break;
                    }
                    else if(grid[temp1][temp2+1].discovered == false){
                        if(grid[temp1][temp2+1].type == 'o'||grid[temp1][temp2+1].type == '$'){
                            curr.y = curr.y+1;
                            ashore.push_back(curr);
                            grid[temp1][temp2+1].direction = 'E';
                            Hunt::Search(curr);
                            wentAshore += 1;
                            curr.y = curr.y - 1;
                            if(treasureFound == true){
                                break;
                            }
                            else{
                                searched.clear();
                            }
                            
                        }
                        else if(grid[temp1][temp2+1].type == '#'){
                            grid[temp1][temp2+1].discovered = true;
                            break;
                        }
                        else{
                            Coordinate c;
                            c.x = curr.x;
                            c.y = curr.y+1;
                            grid[temp1][temp2+1].direction = 'E';
                            grid[temp1][temp2+1].discovered = true;
                            if(captainQ){
                                Captain.push_back(c);
                                
                            }
                            if(captainS){
                                Captain.push_front(c);
                                
                            }
                        }
                    }
                    break;
                case('S'):
                    if(curr.x + 1 > (size - 1)){
                        break;
                    }
                    //make sure south location is not disocvered
                    else if(grid[temp1+1][temp2].discovered == false){
                        //deploy firstMate if land
                        if(grid[temp1+1][temp2].type == 'o'||grid[temp1+1][temp2].type == '$'){
                            curr.x = curr.x +1;
                            ashore.push_back(curr);
                            grid[temp1+1][temp2].direction = 'S';
                            Hunt::Search(curr);
                            wentAshore += 1;
                            curr.x = curr.x - 1;
                            if(treasureFound == true){
                                break;
                            }
                            else{
                                searched.clear();
                            }
                            
                        }
                        //ignore if impassable
                        else if(grid[temp1+1][temp2].type == '#'){
                            grid[temp1+1][temp2].discovered = true;
                            break;
                        }
                        else{
                            //if not impassable, out of bounds or land then add coordinates to captain vector
                            Coordinate c;
                            c.x = curr.x+1;
                            c.y = curr.y;
                            grid[temp1+1][temp2].direction = 'S';
                            grid[temp1+1][temp2].discovered = true;
                            if(captainQ){
                                Captain.push_back(c);
                                
                                
                            }
                            if(captainS){
                                Captain.push_front(c);
                                
                                
                            }
                        }
                    }
                    break;
                case('W'):
                    if(curr.y - 1 < 0){
                        break;
                    }
                    else if(grid[temp1][temp2-1].discovered == false){
                    if(grid[temp1][temp2-1].type == 'o'||grid[temp1][temp2-1].type == '$'){
                        curr.y = curr.y-1;
                        ashore.push_back(curr);
                        grid[temp1][temp2-1].direction = 'W';
                        Hunt::Search(curr);
                        wentAshore += 1;
                        curr.y = curr.y+1;
                        if(treasureFound == true){
                            break;
                        }
                        else{
                            searched.clear();
                        }
                    }
                    else if(grid[temp1][temp2-1].type == '#'){
                        grid[temp1][temp2-1].discovered = true;
                        break;
                    }
                    else{
                            Coordinate c;
                            c.x = curr.x;
                            c.y = curr.y-1;
                            grid[temp1][temp2-1].direction = 'W';
                            grid[temp1][temp2-1].discovered = true;
                        if(captainQ){
                            Captain.push_back(c);
                            
                        }
                        if(captainS){
                            Captain.push_front(c);
                            
                        }
                    }
                                }
                    break;
                }
                }
            
            }
        }
void Hunt::MapBuilder(int size){
    string junk;
    getline(cin,junk);
    for(int row = 0; row < size; row++){
        vector<Map> tiles;
        string str;
        getline(cin,str);
        for(int col = 0; col < size; col++){
            Map map;
            size_t temp = static_cast<size_t>(col);
            map.type = str[temp];
            tiles.push_back(map);
            if(map.type == '@'){
                start.x = row;
                start.y = col;
                
            }
        }
        grid.push_back(tiles);
        tiles.clear();
    }
}
void Hunt::ListBuilder(int size){
    int row;
    int col;
    char type;
    string junk;
    getline(cin,junk);
    for(int i = 0; i < size;i++){
        vector<Map> tiles;
        for(int x = 0; x < size;x++){
            Map map;
            map.type = '.';
            tiles.push_back(map);
        }
        grid.push_back(tiles);
        tiles.clear();
    }
    vector<Map> tiles;
    while(cin >> row >> col >> type){
        size_t temp2 = static_cast<size_t>(col);
        size_t temp1 = static_cast<size_t>(row);
        grid[temp1][temp2].type = type;
        if(type == '@'){
            start.x = row;
            start.y = col;
            
           }
    }
     
}
void Hunt::getMode(int argc,char * argv[]) {
    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    int choice;
    bool p = false;
    int option_index = 0;
    option long_options[] = {
        // Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
        // ./project0 -m nosize
        // ./project0 --help
        { "verbose", no_argument,nullptr, 'v'},
        { "help", no_argument, nullptr,'h'},
        {"captain",required_argument,nullptr,'c'},
        {"first-mate",required_argument,nullptr,'f'},
        {"stats",no_argument,nullptr,'s'},
        {"hunt-order",required_argument,nullptr,'o'},
        {"show-path", required_argument,nullptr,'p'},
        { nullptr, 0,                 nullptr, '\0' }
    };
    //Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "hc:f:svo:p:", long_options, &option_index)) != -1) {
        switch (choice) {
            case 'h':
       //         printHelp(argv);
                exit(0);
                break;
            case 'c':
                mode = optarg;
                if(mode == "QUEUE"){
                    captainQ = true;
                    captainS = false;
                }
                else if(mode == "STACK"){
                    captainQ = false;
                    captainS = true;
                }
                else{
                    cerr << "Invalid argument to --captain" << endl;
                    exit(1);
                }
                break;
            case 'f':
                mode = optarg;
                if(mode == "QUEUE"){
                    firstMateQ = true;
                    firstMateS = false;
                }
                else if(mode == "STACK"){
                    firstMateS = true;
                    firstMateQ  = false;
                }
                else{
                    cerr << "Invalid argument to --firstmate" << endl;
                    exit(1);
                }
                break;
            case 's':
                if(stats == true){
                    cerr << "Invalid argument to --show-path" << endl;
                }
                stats = true;
                break;
            case 'v':
                verbose = true;
                break;
            case 'o':{
                HUNT_ORDER = optarg;
                int e = 0;
                int n = 0;
                int s = 0;
                int w = 0;
                for(int i = 0; i < 4; i++){
                    size_t temp = static_cast<size_t>(i);
                    if(HUNT_ORDER[temp] == 'E'){
                        e++;
                    }
                    else if(HUNT_ORDER[temp] == 'N'){
                        n++;
                    }
                    else if(HUNT_ORDER[temp] == 'S'){
                        s++;
                    }
                    else if(HUNT_ORDER[temp] == 'W'){
                        w++;
                    }
                }
                if((e =! 1) || (n != 1) || (s != 1) || (w != 1)){
                    cerr << "Invalid argument to hunt order\n";
                    exit(1);
                }
                break;
            }
            case 'p':
                if(p){
                    cerr << "Specify --show-path only once\n";
                    exit(1);
                }
                else{
                    p = true;
                }
                mode = optarg;
                if(mode == "M"){
                    mapMode = true;
                }
                else if(mode == "L"){
                    listMode = true;
                }
                else{
                    cerr << "Invalid argument to --show-path" << endl;
                    exit(1);
                }
                break;
            default:
                cout << "Invalid argument" << endl;
                exit(1);
        } // switch
    } // while
} 
 


