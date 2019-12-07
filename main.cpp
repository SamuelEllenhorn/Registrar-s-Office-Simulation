#include "Simulate.h"
#include "Que.h"

#include <iostream>
using namespace std;


  void test1(){

    Queue<User> line1;
    User u1(1,10);
    User u2(1,5);
    User u3(3,4);
    line1.enqueue(u1);
    line1.enqueue(u2);
    line1.enqueue(u3);

    Simulate sim(2, line1);

    sim.runSim();

    cout << "Mean: " << sim.getMeanWaitTime() << endl;
    cout << "Median: " << sim.getMedianWaitTime() << endl;
    cout << "Over10: " << sim.getNumStudentsOver10Min() << endl;
    cout << "Longest Wait: " << sim.getLongestTime() << endl;


  }


int main(int argc, const char * argv[]) {



  test1();

}
