#include <stdio.h>
#include <string.h>
#include "storage.h"

int main(void)
{
    FAQ faq;
    FAQ faqs[50];

    char categoryList[CATEGORY_COUNT][MAX_CATEGORY];

    int count;
    int categoryCount;
    int i;

    printf("===== Storage Module Test =====\n\n");

    /* Test 1: isValidCategory() */
    printf("Test 1: Category validation\n");

    printf("Academic issues: %d\n",
           isValidCategory("Academic issues"));

    printf("Transportation: %d\n",
           isValidCategory("Transportation"));

    printf("Sports: %d\n\n",
           isValidCategory("Sports"));


    /* Test 2: appendFAQ() */
    printf("Test 2: Append FAQ\n");

    strcpy(faq.question, "Where is the library?");
    strcpy(faq.answer, "The library is on campus.");
    strcpy(faq.category, "Academic issues");

    if (appendFAQ(&faq))
    {
        printf("FAQ added successfully.\n\n");
    }
    else
    {
        printf("Failed to add FAQ.\n\n");
    }


    /* Test 3: loadFAQs() */
    printf("Test 3: Load FAQs\n");

    count = loadFAQs("Academic issues", faqs, 50);

    printf("Number of FAQs: %d\n", count);

    for (i = 0; i < count; i++)
    {
        printf("%d. %s\n", i + 1, faqs[i].question);
        printf("   %s\n", faqs[i].answer);
    }

    printf("\n");


    /* Test 4: saveFAQs() */
    printf("Test 4: Save FAQs\n");

    if (count > 0)
    {
        strcpy(faqs[0].answer,
               "The library is near the main building.");

        if (saveFAQs("Academic issues", faqs, count))
        {
            printf("FAQ file saved successfully.\n");
        }
        else
        {
            printf("Failed to save FAQ file.\n");
        }
    }

    printf("\n");


    /* Test 5: getCategories() */
    printf("Test 5: Get non-empty categories\n");

    categoryCount = getCategories(categoryList);

    printf("Number of categories: %d\n", categoryCount);

    for (i = 0; i < categoryCount; i++)
    {
        printf("%d. %s\n", i + 1, categoryList[i]);
    }

    printf("\n");


    /* Test 6: importFAQs() */
    printf("Test 6: Import FAQ files\n");

    count = importFAQs("import01.txt");
    printf("import01.txt: %d FAQ(s) imported.\n", count);

    count = importFAQs("import02.txt");
    printf("import02.txt: %d FAQ(s) imported.\n", count);

    count = importFAQs("import03.txt");
    printf("import03.txt: %d FAQ(s) imported.\n", count);

    printf("\n");


    /* Final category check */
    printf("Final category list:\n");

    categoryCount = getCategories(categoryList);

    for (i = 0; i < categoryCount; i++)
    {
        printf("%d. %s\n", i + 1, categoryList[i]);
    }

    printf("\n===== Test Finished =====\n");

    return 0;
}
