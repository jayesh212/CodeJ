#include<stdio.h>
#include"String.hpp"
typedef struct _MP3_Header
{
   unsigned int sync:12;
   unsigned int id:1;
   unsigned int layer:2;
   unsigned int protectedBit:1;
   unsigned int bitRate:4;
   unsigned int freq:2;
   unsigned int padB:1;
   unsigned int privBit:1;
   unsigned int mode:2;
   unsigned int modeExtension:2;
   unsigned int copy:1;
   unsigned int home:1;
   unsigned int emphasis:2;
}Header;
int main()
{
    FILE *mp3File;
    mp3File=fopen("c:/users/jshar/music/teeth.mp3","rb");
    int mp3Header;
    Header header;
    int step=0;
    int version;
    int mask=1;
    int j=0;
    int flag=0;
    while(1)
    {
        fread(&header,sizeof(Header),1,mp3File);
        if(feof(mp3File))break;
        for(int i=0;i<=11;i++)
        {
            if(!header.sync^mask<<i)
            {
                step=0;
                break;
            }
            step=1;
            flag=1;
        }
        mask=1;
        if(header.id&mask)version=1;
        else version=2;
        if(step==1)break;
        j++;
    }
    printf("Version : %d\n",version);
   if(flag) printf("%d\n",j);
    fclose(mp3File);
    return 0;
}
