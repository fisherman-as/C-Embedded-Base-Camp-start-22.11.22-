#include <stdio.h>
#include <stdlib.h>
#include "book.h"

int main()
{
  struct Book Book1;
  struct Book Book2;
  struct Book Book3;
  struct Book Book4;

  Book_Link(&Book1, &Book2);
  Book_Link(&Book2, &Book3);
  Book_Link(&Book3, &Book4);
  Book_Link(&Book4, NULL);

  Book_Init(&Book1, "Harry Potter and the Philosophers Stone", 347.2, 948, "English", 300, 1997);
  Book_Init(&Book2, "Harry Potter and the Chamber of Secrets", 412.0, 932, "French", 275, 1998);
  Book_Init(&Book3, "Harry Potter and the Prisoner of Azkaban", 403.32, 1027, "Ukrainian", 399, 2000);
  Book_Init(&Book4, "Harry Potter and the Goblet of Fire", 455, 812, "Spanish", 308, 2002);

  Book_PrintAll(&Book1);
}

void Book_Link(struct Book* this, const struct Book* link)
{
  this->next=link;
  return;
}

void Book_Init(struct Book* this, const char* title, float price, int NumberOfPages, const char* language, int weight, int year)
{
  this->title=title;
  this->price=price;
  this->NumberOfPages=NumberOfPages;
  this->language=language;
  this->weight=weight;
  this->year=year;
  return;
}

void Book_Print(struct Book* this)
{
  printf(" Title: %s\r\n Price: %.2f\r\n Pages: %d\r\n Language:%s\r\n Weight: %d\r\n Year: %d\r\n"\
  ,this->title,this->price,this->NumberOfPages,this->language,this->weight,this->year);
  printf("------------------------\r\n\r\n");
  return;
}

void Book_PrintAll(struct Book* this)
{
while(this!=NULL)
  {
    Book_Print(this);
    this=this->next;
  }
}
