#ifndef _BOOK_H_
#define _BOOK_H_
#pragma once
struct Book
  {
    struct Book* next;
    const char* title;
    float price;
    int NumberOfPages;
    const char* language;
    int weight;
    int year;
  };

void Book_Link(struct Book* this, const struct Book* other);
void Book_Init(struct Book* this, const char* title, float price, int NumberOfPages, const char* language, int weight, int year);
void Book_Print(struct Book* this);
//void Book_PrintAll(struct Book* this);

#endif // _BOOK_H_