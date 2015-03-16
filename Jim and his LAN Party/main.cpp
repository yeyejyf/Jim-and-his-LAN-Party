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
using namespace std;

class MultiGroups{
    long current, N;
    vector<set<long>> groups;
    vector<long> PlayerChoice;
    
public:
    MultiGroups(long N):N(N),current(0){
        PlayerChoice = vector<long>(N+1, -1);
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
    
    void mergeGroup(long g1, long g2){
        if (groups[g1].size() < groups[g2].size()) {
            mergeGroup(g2, g1);
            return;
        }
        for (long item: groups[g2]){
            groups[g1].insert(item);
            PlayerChoice[item] = g1;
        }
        groups[g2] = set<long>();
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
