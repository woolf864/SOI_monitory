typedef boost::interprocess::interprocess_semaphore sem;

class element
{
    friend class garbage;
  private:
    element *next;
    element *prev;
  public:
    element(){}
    ~element();
};

class fifo
{
  private:
    element *head;
    int count;
  public:
    lista();
    ~lista();
    void dodaj(int i);
    int pobierz();
    
};

class garbage : private fifo
{
  private:
    int count;
    int max;
    sem *s;
  prublic:
    garbage(int ile, int m);
    ~garbage();
    void push(element *e);
    element *pop();
};

class kontener;

class k1 : private fifo
{
  private:
    kontener *k;
    sem *s;
    head *h;
  public:
}

class k2 : private fifo
{
  private:
    kontener *k;
    sem *s;
    head *h;
  public:
}
