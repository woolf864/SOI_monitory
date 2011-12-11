#include <iostream>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

typedef boost::interprocess::interprocess_semaphore sem;

class element
{
  public:
    element *next;
    element *prev;
    int val;
    element(){}
    element(element *n, element *p) : next(n),
                                      prev(p){}
    ~element();
};

class garbage
{
  private:
    int count;
    int max;
    sem *mutex;
    element *head;
  public:
    garbage(int ile=50, int m=100);
    ~garbage();
    int push(element *e);
    element *pop(element *n, element *p, int val);
};

extern garbage g;

class fifo
{
  private:
    element *head;
    int count;
    sem *mutex;
  public:
    fifo();
    ~fifo();
    void dodaj(int i);
    int pobierz();
    
};

class kontener;

class k1 : private fifo
{
    friend class kontener;
  private:
    kontener *k;
    sem *a1;
    sem *b1;
    sem *mutex;
  public:
    k1(kontener *_k);
    ~k1();
    void A1();
    void B1();
};

class k2 : private fifo
{
    friend class kontener;
  private:
    kontener *k;
    sem *a2;
    sem *b2;
    sem *k1;
    sem *mutex;
  public:
    k2(kontener *_k, sem *_k1);
    ~k2();
    void A2();
    void B2();
};

class kontener
{
    friend class k1;
    friend class k2;
  private:
    k1 *kol1;
    k2 *kol2;
  public:
    kontener();
    ~kontener();
    void make_A1();
    void make_A2();
    void make_B1();
    void make_B2();
    void wait_for_all();
};
