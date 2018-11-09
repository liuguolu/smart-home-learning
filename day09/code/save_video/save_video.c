#include <stdio.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <pthread.h>
#include <strings.h>

#include <linux/input.h>

#include "lcd.h"
#include "api_v4l2.h"

int main(int argc,char**argv)
{
	int fd = -1;
	int tmp = 200;
	char pic_name[50]={0};
	FrameBuffer freambuf;
	/* ��LCD��Ļ*/
	lcd_open();
	
	/* ��ʼ������ͷ�豸*/
	linux_v4l2_device_init("/dev/video7");
	
	/* ��������ͷ*/
	linux_v4l2_start_capturing();
	
	int count = 1;
	
	// ɾ�������ͼƬ
	system("rm video/pic/*");
	
	// ɾ��ת������Ƶ
	system("rm video/sp/video.avi");
	
	while(tmp--)
	{	
		/* ��ȡ����ͷ����      ���jpg�ļ���*/
		linux_v4l2_get_fream(&freambuf);
		
		/* ��ʾ����ͷͼ��*/
		lcd_draw_jpg(80, 0, NULL, freambuf.buf, freambuf.length, 0);
		
		sprintf(pic_name, "video/pic/%d.jpg", count++);
		printf("pic_name = %s\n", pic_name);
		
		/* ����ͼ���ļ�*/
		fd = open(pic_name, O_RDWR|O_CREAT, 0777);
		write(fd, freambuf.buf, freambuf.length);
		close(fd);
	}
	
	// ת����Ƶ                      
	system("ffmpeg -f image2 -i video/pic/%d.jpg video/sp/video.avi");
	
	/* ֹͣ����ͷ*/
	linux_v4l2_stop_capturing();
	
	/* ж������ͷ*/
	linux_v4l2_device_uinit();

	lcd_close();
	return 0;
}