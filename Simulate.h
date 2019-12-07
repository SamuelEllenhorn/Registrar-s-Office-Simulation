#ifndef SIMULATE_H
#define SIMULATE_H
#include "Que.h"
#include "User.h"
#include <cstddef>
#include <vector>

//takes in 1 vector of users

using std::vector ;
using std::logic_error;

class Simulate{
  public:
    Simulate(int numWindows, Queue<User> q){
      for (int i = 0; i < numWindows; i++){
        windows.emplace_back(); //cited bc no-arg constructer
      }

      queue = q;
      simRun = false;


    }
    bool tryServe(User u, int time){
      for (int i = 0; i < windows.size(); i ++){
        if (!windows[i].isOccupied()){
          windows[i].serveUser(time, u);
          return true;
        }
      }
      return false;//found no open windows
    }

    void fillWindowsFromQueue(int time) {
      while(!queue.empty()){
        //look at current person in line
        User user  = queue.front();

          //while arrival time < current neededTime
        if (user.getArrivalTime() <= time) {
          if (tryServe(user, time))
            queue.dequeue();
          else
            break;
        } else {
          break;
        }
      }
    }

    void ejectFinishedUsers(int time) {
      for (int i = 0; i < windows.size(); i ++) {
        ProcessedUser pUser;

        if( windows[i].finish(time, pUser) ) {
          processedUsers.push_back(pUser);
        }
      }
    }


    void runSim() {
        
        for (int time = 0; time < 120; time ++){
          ejectFinishedUsers(time);
          fillWindowsFromQueue(time);
        }

        sort(processedUsers.begin(), processedUsers.end());
        simRun = true;
      }

    double getMeanWaitTime() {
      if(!simRun)
        throw logic_error("Called get mean before simulation run");

      double sum = 0;
      for(vector<ProcessedUser>::iterator it = processedUsers.begin(); it != processedUsers.end(); it++) {
        sum += it->getWaitTime();
      }
      return sum/processedUsers.size();

    }

    double getMedianWaitTime(){
      if(!simRun)
        throw logic_error("Called get mean before simulation run");


      int n = processedUsers.size();
      if(n % 2 == 0) {
        int a = processedUsers[n/2].getWaitTime();
        int b = processedUsers[n/2 + 1].getWaitTime();
        return (a+b)/2.0;
      } else {
        return processedUsers[n/2].getWaitTime();
      }

    }

    double getLongestTime(){
      if(!simRun)
        throw logic_error("Called get longest before simulation run");
      return processedUsers.rbegin()->getWaitTime();
    }

    double getNumStudentsOver10Min(){
      if(!simRun)
        throw logic_error("Called get longest before simulation run");

      int count = 0;

      for(vector<ProcessedUser>::iterator it = processedUsers.begin(); it != processedUsers.end(); it++) {
        if(it->getWaitTime() > 10)
          count++;
      }
      return count;
    }



  private:
    vector<Window> windows;
    vector<ProcessedUser> processedUsers;
    Queue<User> queue;
    bool simRun = false;

};
#endif
