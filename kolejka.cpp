#include "kolejka.hpp"

element::~element()
{
    if(next != NULL)
        next->prev = prev;
    if(prev != NULL)
        prev->next = next;
}

garbage::garbage(int ile=50, int m=100)
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

void garbage::push(element *e)
{
    mutex->wait();
    if(count < max)
    {
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
}

element *garbage::pop()
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
    }
    else
    {
        tmp = new element;
    }
    mutex->post();
    return tmp;
}


void fifo::fifo()
{
    head = new element;
    head->next = head;
    head->prev = head;
    count = 0;
    mutex = new sem(1);
}

void fifo::~fifo()
{
    while(head->next != head)
        delete head->next;
    delete head;
}

void lista::dodaj(int i)
{
    
}
