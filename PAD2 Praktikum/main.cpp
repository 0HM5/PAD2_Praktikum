//main.cpp

#include <cstdlib>
#include <fstream>
#include "GameEngine.h"

using namespace std;

void loadFromFile(const string& filename, vector <string>& data) {
    string next;
    ifstream source;

    source.open(filename.c_str(), ios::in);

    if (!source.good()) {
        cerr << filename << " can not be opened!\n";
        exit(-1);
    }

    while (!source.eof()) {
        getline(source, next);
        data.push_back(next);
    }
    source.close();
}

void cout_string(const vector <string>& data) {
    unsigned int size = data.size();
    for (unsigned int counter = 0; counter < size; counter++) {
        cout << data[counter] << endl;
    }
}

int main() {
    vector <string> data, act_pass;
    if (0) {
        data = {//Tiles
            //0123456789
            "##########", //0
            "####.....#", //1
            "###......#", //2
            "##.......#", //3
            "#........#", //4
            "#........#", //5
            "#........#", //6
            "#........#", //7
            "#........#", //8
            "##########", //9
        };
        act_pass = {//pairs of Active_Passive Tiles by position
            "Character @ 5 5 ConsoleController 3 3",
            "Character % 2 3 StationaryController 3 4",
            "Door 5 5 Switch 4 4",
            "Door 4 8 Switch 2 7",
            "Door 1 6 Lever 1 4",
            "Greatsword 1 4",
            "Trap 8 8",
        };
    }
    else if (0) {
        data = {
            "####################",
            "#......#############",
            "#..#.#.............#",
            "####.###############",
            "#..................#",
            "#..................#",
            "#..................#",
            "#..................#",
            "#..................#",
            "#..................#",
            "#..................#",
            "#..................#",
            "#..................#",
            "#########.##########",
            "#..................#",
            "#..................#",
            "#..................#",
            "#..................#",
            "#..................#",
            "####################",
        };
        act_pass = {
            "Character @ 5 5 ConsoleController 9 9",
            "Character % 2 2 StationaryController 3 4",
            "Greatsword 1 4",
            "Door 13 9 Lever 11 9",
            "Trap 10 9",
        };
    }
    else {
        loadFromFile("lvl1map.txt", data);
        loadFromFile("lvl1act.txt", act_pass);
    }

    cout_string(data);
    cout << "---------------------------------" << endl;
    cout_string(act_pass);


    GameEngine ge(data, act_pass);
    ge.run();
    return 0;
}