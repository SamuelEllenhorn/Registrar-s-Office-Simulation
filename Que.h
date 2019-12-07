#ifndef QUE_H
#define QUE_H

#include <cstddef>
#include <string>
#include "NodeList.h"

class QueueEmpty : public std::logic_error {
public:
  QueueEmpty(std::string what) : std::logic_error(what) {}
};

template <typename E>
class Queue {
private:
  NodeList<E> list;
public:
  int size() const {return list.size();}
  bool empty() const{return list.Empty();}
  const E& front()const throw (QueueEmpty) {
    if(list.Empty()){
      throw QueueEmpty("Tried to get front of empty queue");
    }
    return *list.begin();
  }
  void enqueue (const E& e) {list.insertBack(e);}
  void dequeue()throw(QueueEmpty) {
    if(list.Empty()){
      throw QueueEmpty("Tried to dequeue from empty queue");
    }
    list.eraseFront();
  };

};




#endif
