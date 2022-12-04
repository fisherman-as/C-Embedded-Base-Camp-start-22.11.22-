#include <stdio.h>
#include <stdlib.h>
#define GroupNumber "group1-mentor-artem"
#define FullName "Yabanzhi Aleksey Sergeevich"
#define Email "Aleksey.Yabanzhi@avtor.ua (fisherman-as@ukr.net as well)"
#define RepositoryLink "https://github.com/fisherman-as/C-Embedded-Base-Camp-start-22.11.22-.git"
#define SharedFolderLink "https://drive.google.com/drive/folders/1KANUB3yTg5UlKE-ZHvXg77VEXRSzX_DO?usp=share_link"


int main()
{
    char* a=GroupNumber;
    char* b=FullName;
    char* c=Email;
    char* d=RepositoryLink;
    char* e=SharedFolderLink;

    printf("The group number is      :  %s\n", a); printf("\r\n\r\n");
    printf("The full name is         :  %s\n", b); printf("\r\n\r\n");
    printf("The E-mail is            :  %s\n", c); printf("\r\n\r\n");
    printf("The repository link is   :  %s\n", d); printf("\r\n\r\n");
    printf("The shared folder link is:  %s\n", e);
    return 0;
}
