#ifndef USER_H
#define USER_H

class User{
  protected:
    int arrivalTime;
    int neededTime;

  public:
    User () {}
    User(int AT, int NT){
      arrivalTime = AT;
      neededTime = NT;
    }
    int getArrivalTime(){
      return arrivalTime;
    }

};


class ProcessedUser:public User{
  private:
    int servingTime;
  public:
    ProcessedUser() : User() {
      servingTime = -1;
    }

    ProcessedUser(User u, int ST) : User(u){
      servingTime = ST;
    }

    int getExitTime(){
      return neededTime + servingTime;
    }

    int getWaitTime() const {
      return servingTime - arrivalTime;
    }

    friend bool operator<(const ProcessedUser& a, const ProcessedUser& b) {
      return a.getWaitTime() < b.getWaitTime();
    }

};

class Window{
  private:
    bool occupied;
    ProcessedUser pUser;

  public:
    bool isOccupied(){
      return occupied;
    }

    Window(){
      occupied = false;
    }

    void serveUser(int time, User u){

      pUser = ProcessedUser(u, time); //
      occupied = true;
    }

    bool finish(int time, ProcessedUser& pU){

      if (!isOccupied()){
        return false;
      }
      if (pUser.getExitTime()==time){
        occupied = false;
        pU = pUser;
        return true;
      }
      return false;
    }
};

#endif
