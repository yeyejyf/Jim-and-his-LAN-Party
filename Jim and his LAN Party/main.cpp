//
//  main.cpp
//  Jim and his LAN Party
//
//  Created by Yunfan Jin on 3/15/15.
//  Copyright (c) 2015 yunfan.jin. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
using namespace std;

class Game;

class MultiGroups{
    long current, N;
    vector<set<long>> groups;
    vector<long> PlayerChoice;
    
public:
    MultiGroups(long N):N(N),current(0){
        PlayerChoice = vector<long>(N, -1);
    }
    void addToGroup(long player, long GroupNo){
        PlayerChoice[player] = GroupNo;
        groups[GroupNo].insert(player);
    }
    long newGroup(){
        long tmp = current;
        current ++;
        groups.push_back(set<long>());
        return tmp;
    }
    
    const set<long>& mergeGroup(long g1, long g2){
        if (groups[g1].size() < groups[g2].size()) {
            return mergeGroup(g2, g1);
        }
        vector<long> output;
        for (long item: groups[g2]){
            groups[g1].insert(item);
            PlayerChoice[item] = g1;
            output.push_back(item);
        }
        groups[g2] = set<long>();
        return groups[g1];
    }
    
    long getGroupNo(long player) const{
        return PlayerChoice[player];
    }
    
    friend class Game;
    
};

class Game{
    long N, M;
    vector<set<long>> game;
    const vector<long>& player;
    vector<long> output;
public:
    Game(long N, long M, const vector<long> &list):N(N), M(M), player(list){
        game.resize(M, set<long>());
        output.resize(M, -1);
        for (long i=0; i<N; i++) {
            long g = list[i];
            game[g].insert(i);
        }
        
        for (long i=0; i<M; i++) {
            if (game[i].size() <= 1) {
                output[i] = 0;
            }
        }
    }
    
    void run(MultiGroups &groups, long count, long p1, long p2){
        long n1 = groups.getGroupNo(p1);
        long n2 = groups.getGroupNo(p2);
        vector<long> affectedPlayer;
        if (n1 == -1 && n2 == -1) {
            long tmp = groups.newGroup();
            groups.addToGroup(p1, tmp);
            groups.addToGroup(p2, tmp);
        }else if (n1 == -1){
            groups.addToGroup(p1, n2);
        }else if (n2 == -1){
            groups.addToGroup(p2, n1);
        }else if (n1 != n2){
            groups.mergeGroup(p1, p2);
        }
    }
    
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
