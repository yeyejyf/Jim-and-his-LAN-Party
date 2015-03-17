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
    vector<set<long>> groups; // groups -> player (1 to N)
    vector<long> PlayerChoice; // player -> groups (N to 1)
    
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
    vector<set<long>> game;  // game -> palyer (1 to N)
    const vector<long>& player; // player -> game (N to 1)
    vector<long> output;  // game record
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
    
    bool checkTogether(const MultiGroups &groups, long game_id){
        if (output[game_id] != -1) {
            return false;
        }
        auto iter = game[game_id].begin();
        long groupId = groups.getGroupNo(*iter);
        for (iter++; iter!= game[game_id].end(); iter++) {
            if (groups.getGroupNo(*iter) != groupId) {
                return false;
            }
        }
        return true;
    }
    
    void affected(const MultiGroups &groups, const set<long> &players, long count){
        set<long> affectedGames;
        for (long p:players){
            affectedGames.insert(player[p]);
        }
        for (long game_id: affectedGames){
            if (checkTogether(groups, game_id)) {
                output[game_id] = count;
            }
        }
    }
    
    void run(MultiGroups &groups, long count, long p1, long p2){
        long n1 = groups.getGroupNo(p1);
        long n2 = groups.getGroupNo(p2);
        if (n1 == -1 && n2 == -1) {
            long tmp = groups.newGroup();
            groups.addToGroup(p1, tmp);
            groups.addToGroup(p2, tmp);
            affected(groups, {p1}, count);
        }else if (n1 == -1){
            groups.addToGroup(p1, n2);
            affected(groups, {p1}, count);
        }else if (n2 == -1){
            groups.addToGroup(p2, n1);
            affected(groups, {p2}, count);
        }else if (n1 != n2){
            auto const& result = groups.mergeGroup(p1, p2);
            affected(groups, result, count);
        }
    }
    
    const vector<long>& getRecord(){
        return output;
    }
    
};

int main(int argc, const char * argv[]) {
    
    long N, M, Q, tmp1, tmp2;
    cin >> N >> M >> Q;
    MultiGroups groups(N);
    vector<long> list;
    for (long i=0; i<N; i++) {
        cin >> tmp1;
        list.push_back(tmp1-1);
    }
    Game game(N, M, list);
    for (long i=0; i<Q; i++) {
        cin >> tmp1 >> tmp2;
        game.run(groups, i+1, tmp1-1, tmp2-1);
    }
    
    vector<long> output = game.getRecord();
    
    for (long i=0; i<output.size(); i++) {
        cout << output[i] << endl;
    }
    
    return 0;
}
