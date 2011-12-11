#include "kolejka.hpp"

garbage g;

element::~element()
{
    if(next != NULL)
        next->prev = prev;
    if(prev != NULL)
        prev->next = next;
}

garbage::garbage(int ile, int m)
{
    element *tmp;
    mutex = new sem(1);
    head = NULL;
    for(int i=0; i<ile; i++)
    {
        tmp = new element;
        tmp->next = head;
        if(head != NULL)
            head->prev = tmp;
        tmp->prev = NULL;
        head = tmp;
    }
    max = m;
}

garbage::~garbage()
{
    if(head != NULL)
    {
        while(head->next != NULL)
        {
            head = head->next;
            delete head->prev;
        }
        delete head;
    }
    delete mutex;
}

int garbage::push(element *e)
{
    int ret;
    ret = e->val;
    mutex->wait();
    if(count < max)
    {
        e->next->prev = e->prev;
        e->prev->next = e->next;

        e->next = head;
        e->prev = NULL;
        if(head != NULL)
            head->prev = e;
        head = e;
        count++;
    }
    else
    {
        delete e;
    }
    mutex->post();
    return ret;
}

element *garbage::pop(element *n, element *p, int val)
{
    element *tmp;
    mutex->wait();
    if(head != NULL)
    {
        tmp = head;
        head = head->next;
        if(head != NULL)
            head->prev = NULL;
        count--;
        mutex->post();
        tmp->next = n;
        tmp->prev = p;
    }
    else
    {
        tmp = new element(n,p);
    }
    p->next = tmp;
    n->prev = tmp;
    tmp->val = val;
    mutex->post();
    return tmp;
}


fifo::fifo()
{
    head = new element();
    head->next = head;
    head->prev = head;
    count = 0;
    mutex = new sem(1);
}

fifo::~fifo()
{
    while(head->next != head)
    {
        g.push(head->next);
    }
    g.push(head);
    delete mutex;
}

void fifo::dodaj(int i)
{
    mutex->wait();
    g.pop(head ,head->prev ,i);
    count++;
    mutex->post();
}

int fifo::pobierz()
{
    int ret;
    mutex->wait();
    if(head->prev != head)
        ret = g.push(head->next);
    count--;
    mutex->post();
    return ret;
}

k1::k1(kontener *_k)
{
    k = _k;
    a1 = new sem(10);
    b1 = new sem(0);
}

k2::k2(kontener *_k, sem *_k1)
{
    k = _k;
    a2 = new sem(10);
    b2 = new sem(0);
    k1 = _k1;
}

void k1::A1()
{
    while(true)
    {
        a1.wait();
        mtex.wait();
        
    }
}

void k1::B1()
{
    while(true)
    {
        b1.wait();
    }
}

void k2::A2()
{
    while(true)
    {
        
    }

}

void k2::B2()
{
    
    while(true)
    {
        b2.wait();
    }
}
