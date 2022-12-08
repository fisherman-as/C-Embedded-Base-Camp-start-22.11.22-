#include <stdio.h>
#include <stdlib.h>
#define GROUPNUMBER         "group1-mentor-artem"
#define FULLNAME            "Yabanzhi Aleksey Sergeevich"
#define EMAIL               "Aleksey.Yabanzhi@avtor.ua (fisherman-as@ukr.net as well)"
#define REPOSITORYLINK      "https://github.com/fisherman-as/C-Embedded-Base-Camp-start-22.11.22-.git"
#define SHAREDFOLDERLINK    "https://drive.google.com/drive/folders/1KANUB3yTg5UlKE-ZHvXg77VEXRSzX_DO?usp=share_link"


int main()
{
    const char* a=GROUPNUMBER;      //added const
    const char* b=FULLNAME;         //added const
    const char* c=EMAIL;            //added const
    const char* d=REPOSITORYLINK;   //added const
    const char* e=SHAREDFOLDERLINK; //added const

    printf("Group number:       %s\n\n\n", a);
    printf("Full name:          %s\n\n\n", b);
    printf("E-mail:             %s\n\n\n", c);
    printf("Repository link: %s\n\n\n", d);
    printf("Shared folder link: %s\n\n\n", e);
    getchar();
    return 0;
}
