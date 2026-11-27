/*
=============================================
 Name: storage.h
 Author: Morgan YU
 Version: 1.0
 Copyright: Your copyright notice
 Description: head file
============================================= 
*/
#ifndef STORAGE_H
#define STORAGE_H

#define MAX_TEXT 256
#define MAX_CATEGORY 50
#define CATEGORY_COUNT 5

//store one FAQ record
typedef struct {
    char question[MAX_TEXT];
    char answer[MAX_TEXT];
    char category[MAX_CATEGORY];
} FAQ;

//check whether a category is valid
int isValidCategory(const char *category);

//get all non-empty categories
int getCategories(char categories[][MAX_CATEGORY]);

//load FAQs from one category file
int loadFAQs(const char *category, FAQ faqs[], int capacity);

//save all FAQs to one category file
int saveFAQs(const char *category, const FAQ faqs[], int count);

//append one FAQ to its category file
int appendFAQ(const FAQ *faq);

//import FAQs from an external file
int importFAQs(const char *filename);

#endif
