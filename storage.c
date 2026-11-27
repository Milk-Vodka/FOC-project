/*
=============================================
 Name: storage.c
 Author: Morgan YU
 Version: 1.0
 Copyright: Your copyright notice
 Description: storeddata
============================================= 
*/


/*
最大长度设为256
最大类别数设为50
类别为5
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "storage.h"

static const char categories[CATEGORY_COUNT][MAX_CATEGORY] = {
    "Academic issues",
    "Career development",
    "Food Dormitory",
    "Graduate study",
    "Transportation"
};

int isValidCategory(const char *category)
{
    int i;
	// compare with 5 different categories
    if (category == NULL)
    {
        return 0;
    }

    for (i = 0; i < CATEGORY_COUNT; i++)
    {
        if (strcmp(category, categories[i]) == 0)//string compare
        {
            return 1;
        }
    }

    return 0;
}

int appendFAQ(const FAQ *faq)
{
    FILE *fp;
    char filename[100];
	//check if is null
    if (faq == NULL)
    {
        return 0;
    }
	//check if is invalid
    if (!isValidCategory(faq->category))
    {
        return 0;
    }
	//open a file
    sprintf(filename, "%s.txt", faq->category);

    fp = fopen(filename, "a");

    if (fp == NULL)
    {
        return 0;
    }
	//write into the file
    fprintf(fp, "Q: %s\n", faq->question);
    fprintf(fp, "A: %s\n", faq->answer);

    fclose(fp);

    return 1;
}

static void removeNewline(char *str)
{
    size_t len = strlen(str);

    // Remove '\n' and '\r' from the end of the string
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r'))
    {
        str[len - 1] = '\0';
        len--;
    }
}

int loadFAQs(const char *category, FAQ faqs[], int capacity)
{
    FILE *fp;
    char filename[100];
    char line[512];
    char question[MAX_TEXT] = "";
    int count = 0;

    //check input arguments
    if (!isValidCategory(category) || faqs == NULL || capacity <= 0)
    {
        return -1;
    }

    //create the category file
    sprintf(filename, "%s.txt", category);
    fp = fopen(filename, "r");

    //a missing file means this category currently has no FAQs
    if (fp == NULL)
    {
        return 0;
    }

    //read the file line by line
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        removeNewline(line);

        //store the question temporarily
        if (strncmp(line, "Q: ", 3) == 0)
        {
            strcpy(question, line + 3);
        }

        //complete one FAQ when its answer is found
        else if (strncmp(line, "A: ", 3) == 0 && question[0] != '\0')
        {
            if (count >= capacity)
            {
                break;
            }

            strcpy(faqs[count].question, question);
            strcpy(faqs[count].answer, line + 3);
            strcpy(faqs[count].category, category);

            count++;
            question[0] = '\0';
        }
    }

    fclose(fp);
    return count;
}

int saveFAQs(const char *category, const FAQ faqs[], int count)
{
    FILE *fp;
    char filename[100];
    int i;

    //check input arguments
    if (!isValidCategory(category) || count < 0)
    {
        return 0;
    }

    if (count > 0 && faqs == NULL)
    {
        return 0;
    }
    //create the category file name
    sprintf(filename, "%s.txt", category);

    //open the file in write mode
    fp = fopen(filename, "w");

    if (fp == NULL)
    {
        return 0;
    }

    //write all FAQs back to the file
    for (i = 0; i < count; i++)
    {
        fprintf(fp, "Q: %s\n", faqs[i].question);
        fprintf(fp, "A: %s\n", faqs[i].answer);
    }
    fclose(fp);

    return 1;
}

int getCategories(char outputCategories[][MAX_CATEGORY])
{
    FAQ temp[1];
    int count = 0;
    int i;
    int faqCount;
    //check output array
    if (outputCategories == NULL)
    {
        return -1;
    }
    //check all five valid categories
    for (i = 0; i < CATEGORY_COUNT; i++)
    {
        //only need to check whether at least one exists
        faqCount = loadFAQs(categories[i], temp, 1);

        if (faqCount > 0)
        {
            strcpy(outputCategories[count], categories[i]);
            count++;
        }
    }
    return count;
}

int importFAQs(const char *filename)
{
    FILE *fp;
    char line[512];
    FAQ faq;
    int importedCount = 0;

    //check the file name
    if (filename == NULL)
    {
        return -1;
    }

    //open the import file
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        return -1;
    }

    //initialize the FAQ fields
    faq.question[0] = '\0';
    faq.answer[0] = '\0';
    faq.category[0] = '\0';

    //read the import file line by line
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        removeNewline(line);
        if (strncmp(line, "Q: ", 3) == 0)
        {
            strcpy(faq.question, line + 3);
        }
        else if (strncmp(line, "A: ", 3) == 0)
        {
            strcpy(faq.answer, line + 3);
        }
        else if (strncmp(line, "C: ", 3) == 0)
        {
            strcpy(faq.category, line + 3);
            //a complete FAQ is ready after reading the category
            if (appendFAQ(&faq))
            {
                importedCount++;
            }
            //clear the fields for the next FAQ
            faq.question[0] = '\0';
            faq.answer[0] = '\0';
            faq.category[0] = '\0';
        }
    }
    fclose(fp);
    return importedCount;
}
