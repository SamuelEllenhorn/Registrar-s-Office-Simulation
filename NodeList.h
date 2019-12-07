#ifndef NODELIST_H
#define NODELIST_H

template <typename T>
class NodeList;

template <typename T>
  struct Node{
  private:
    T elem;
    Node<T>* prev;
    Node<T>* next;
    friend class NodeList<T>;
  };

template <typename T>
class NodeList{
  public:

    class Iterator {
      public:
        T& operator*();
        bool operator==(const Iterator& p) const;
        bool operator!=(const Iterator& p) const;
        Iterator& operator++();
        Iterator& operator--();
        friend class NodeList<T>;
      private:
        Node<T>* v;
        Iterator(Node<T> * u);
    };
  public:
    NodeList();
    int size() const;
    bool Empty() const;
    Iterator begin() const;
    Iterator end() const;
    void insertFront(const T& e);
    void insertBack(const T& e);
    void insert(const Iterator& p, const T& e);
    void eraseFront();
    void eraseBack();
    void erase(const Iterator& p);
    friend class Iterator;
    friend struct Node<T>;

  private:
    int n;
    Node<T>* header;
    Node<T>* trailer;

};

template <typename T>
bool NodeList<T>::Empty() const {
  return n == 0;
}

template <typename T>
NodeList<T>::Iterator::Iterator(Node<T>* u)
{v=u;}

template <typename T>
T& NodeList<T>::Iterator::operator*()
{return v-> elem;}

template <typename T>
bool NodeList<T>::Iterator::operator==(const Iterator& p) const
{return v == p.v;}

template <typename T>
bool NodeList<T>::Iterator::operator!=(const Iterator& p) const
{return v != p.v;}

template <typename T>
typename NodeList<T>::Iterator & NodeList<T>::Iterator::operator++()
{v= v-> next; return *this;}

template <typename T>
typename NodeList<T>::Iterator& NodeList<T>::Iterator::operator--()
{v= v-> prev; return *this;}

template <typename T>
NodeList<T>::NodeList()
{
  n = 0;
  header = new Node<T>;
  trailer = new Node<T>;
  header -> next = trailer;
  trailer -> prev = header;
}

template <typename T>
int NodeList<T>::size() const
{return n;}


template <typename T>
typename NodeList<T>::Iterator NodeList<T>::begin() const
{return Iterator(header -> next);}

template <typename T>
typename NodeList<T>::Iterator NodeList<T>::end() const
{return Iterator(trailer);}

template <typename T>
void NodeList<T>::insert(const NodeList<T>::Iterator& p, const T& e)
{
  Node<T>* w = p.v;
  Node<T>* u = w -> prev;
  Node<T>* v = new Node<T>;
  v->elem = e;
  v->next = w; w -> prev =v;
  v->prev = u; u -> next = v;
  n++;
}

template <typename T>
void NodeList<T>::insertFront(const T& e)
{insert(begin(), e);}

template <typename T>
void NodeList<T>::insertBack(const T& e)
{insert(end(), e);}


template <typename T>
void NodeList<T>::erase(const Iterator& p)
{
  Node<T>* v = p.v;
  Node<T>* w = v -> next;
  Node<T>* u = v -> prev;
  u->next = w; w -> prev = u;
  delete v;
  n--;
}

template <typename T>
void NodeList<T>::eraseFront()
{
  erase(begin());
}

template <typename T>
void NodeList<T>::eraseBack()
{
  erase(--end());
}

#endif
