================================================================================
    MICROSOFT FOUNDATION CLASS LIBRARY : ScreenScannerServer Project Overview
===============================================================================

The application wizard has created this ScreenScannerServer application for
you.  This application not only demonstrates the basics of using the Microsoft
Foundation Classes but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your ScreenScannerServer application.

ScreenScannerServer.vcxproj
    This is the main project file for VC++ projects generated using an application wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    application wizard.

ScreenScannerServer.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the assciation between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

ScreenScannerServer.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CScreenScannerServerApp application class.

ScreenScannerServer.cpp
    This is the main application source file that contains the application
    class CScreenScannerServerApp.

ScreenScannerServer.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++. Your project resources are in 1033.

res\ScreenScannerServer.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file ScreenScannerServer.rc.

res\ScreenScannerServer.rc2
    This file contains resources that are not edited by Microsoft
    Visual C++. You should place all resources not editable by
    the resource editor in this file.


/////////////////////////////////////////////////////////////////////////////

The application wizard creates one dialog class:

ScreenScannerServerDlg.h, ScreenScannerServerDlg.cpp - the dialog
    These files contain your CScreenScannerServerDlg class.  This class defines
    the behavior of your application's main dialog.  The dialog's template is
    in ScreenScannerServer.rc, which can be edited in Microsoft Visual C++.

/////////////////////////////////////////////////////////////////////////////

Help Support:

hlp\ScreenScannerServer.hhp
    This file is a help project file. It contains the data needed to
    compile the help files into a .chm file.

hlp\ScreenScannerServer.hhc
    This file lists the contents of the help project.

hlp\ScreenScannerServer.hhk
    This file contains an index of the help topics.

hlp\afxcore.htm
    This file contains the standard help topics for standard MFC
    commands and screen objects. Add your own help topics to this file.

hlp\afxprint.htm
    This file contains the help topics for the printing commands.

makehtmlhelp.bat
    This file is used by the build system to compile the help files.

hlp\Images\*.gif
    These are bitmap files required by the standard help file topics for
    Microsoft Foundation Class Library standard commands.


/////////////////////////////////////////////////////////////////////////////

Other Features:

ActiveX Controls
    The application includes support to use ActiveX controls.

Printing and Print Preview support
    The application wizard has generated code to handle the print, print setup, and print preview
    commands by calling member functions in the CView class from the MFC library.

/////////////////////////////////////////////////////////////////////////////

Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named ScreenScannerServer.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

ScreenScannerServer.manifest
	Application manifest files are used by Windows XP to describe an applications
	dependency on specific versions of Side-by-Side assemblies. The loader uses this
	information to load the appropriate assembly from the assembly cache or private
	from the application. The Application manifest  maybe included for redistribution
	as an external .manifest file that is installed in the same folder as the application
	executable or it may be included in the executable in the form of a resource.
/////////////////////////////////////////////////////////////////////////////

Other notes:

The application wizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, you will need
to redistribute the MFC DLLs. If your application is in a language
other than the operating system's locale, you will also have to
redistribute the corresponding localized resources MFC100XXX.DLL.
For more information on both of these topics, please see the section on
redistributing Visual C++ applications in MSDN documentation.

/////////////////////////////////////////////////////////////////////////////

//
λͼ�ļ�����


λͼ�ļ�ͷ-----λͼ��Ϣ��-----λͼ��ɫ�壨���У�------λͼ���ݣ�RGB���أ�������������

λͼ�ļ�ͷ
WORD    bfType;   ˵���ļ������ͣ���ֵ������0x4D42��Ҳ�����ַ�'BM'�������ʾ��������BMP
DWORD   bfSize;   ˵����λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ
WORD    bfReserved1;   ��������������Ϊ0
WORD    bfReserved2;   ��������������Ϊ0
DWORD   bfOffBits;   ˵�����ļ�ͷ��ʼ��ʵ�ʵ�ͼ������֮����ֽڵ�ƫ��������������Ƿǳ����õģ���Ϊλͼ��Ϣͷ�͵�ɫ��ĳ��Ȼ���ݲ�ͬ������仯����������������ƫ��ֵѸ�ٵĴ��ļ��ж�ȡ��λ���ݡ�


λͼ��Ϣ��
DWORD  biSize;   ˵��BITMAPINFOHEADER�ṹ����Ҫ���ֽ���
LONG   biWidth;   ˵��ͼ��Ŀ�ȣ�������Ϊ��λ
LONG   biHeight;   ˵��ͼ��ĸ߶ȣ�������Ϊ��λ��ע�����ֵ������������ͼ��ĸ߶�֮�⣬��������һ���ô�������ָ����ͼ���ǵ����λͼ�����������λͼ�������ֵ��һ��������˵��ͼ���ǵ���ģ��������ݵĵ�һ����ʵ��ͼ������һ�У������ֵ��һ����������˵��ͼ��������ġ��������BMP�ļ����ǵ����λͼ��Ҳ����ʱ���߶�ֵ��һ��������
WORD   biPlanes;   ��ʾbmpͼƬ��ƽ��������Ȼ��ʾ��ֻ��һ��ƽ�棬���Ժ����1
WORD   biBitCount   ˵��������/���أ���ֵΪ1��4��8��16��24����32��
DWORD  biCompression;   ˵��ͼ������ѹ�������ͣ����У� BI_RGB��û��ѹ�� BI_RLE8��ÿ������8���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����(�ظ����ؼ�������ɫ����)��BI_RLE4��ÿ������4���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ���� BI_BITFIELDS��ÿ�����صı�����ָ�������������BI_JPEG��JPEG��ʽ
DWORD  biSizeImage;   ˵��ͼ��Ĵ�С�����ֽ�Ϊ��λ������BI_RGB��ʽʱ��������Ϊ0��
LONG   biXPelsPerMeter;   ˵��ˮƽ�ֱ��ʣ�������/�ױ�ʾ��
LONG   biYPelsPerMeter;   ˵����ֱ�ֱ��ʣ�������/�ױ�ʾ��
DWORD  biClrUsed;   ˵��λͼʵ��ʹ�õĲ�ɫ���е���ɫ����������Ϊ0�Ļ�����˵��ʹ�����е�ɫ�����
DWORD  biClrImportant; ˵����ͼ����ʾ����ҪӰ�����ɫ��������Ŀ�������0����ʾ����Ҫ��

���ڵ�ǰǶ��ʽ�豸ʹ�õ���ʾ�ӿ�ΪRGB565��ʽ,ѡ��biBitCountΪ16�ĸ�ʽ���洢��ʾ������.��ʾ����СΪ800x600

#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <sys/ioctl.h>  
#include <sys/soundcard.h>  
#include <stdio.h>  
#include <unistd.h>  
#include <math.h>  
#include <string.h>  
#include <stdlib.h>  
  
static unsigned char sg_BHeader[] = {  
    0x42, 0x4D, 0x36, 0x58, 0x02, 0x00, 0x00, 0x00,  0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,   
    0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0xF0, 0x00,  0x00, 0x00, 0x01, 0x00, 0x10, 0x00, 0x00, 0x00,   
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00  
};  
#define RGB565TO1555(rgb) ((unsigned short)((unsigned short)(rgb & 0x001f) | ((unsigned short)(rgb & 0xffc0) >> 1)))  
void SaveBMPFile(unsigned char *raw, char *filename)  
{  
    unsigned short *p = (unsigned short *)raw;  
    typedef unsigned int UINT;  
    typedef unsigned char UCHAR;  
    UINT m_Width = 800, m_Height = 480;  
    UINT i, j;  
    int bmp = open(filename, O_WRONLY | O_CREAT);  
    if(bmp < 0)  
        return;  
    sg_BHeader[0x02] = (UCHAR)(m_Width * m_Height * 2 + 0x36) & 0xff;  
    sg_BHeader[0x03] = (UCHAR)((m_Width * m_Height * 2 + 0x36) >> 8) & 0xff;  
    sg_BHeader[0x04] = (UCHAR)((m_Width * m_Height * 2 + 0x36) >> 16) & 0xff;  
    sg_BHeader[0x05] = (UCHAR)((m_Width * m_Height * 2 + 0x36) >> 24) & 0xff;  
    sg_BHeader[0x12] = (UCHAR)m_Width & 0xff;  
    sg_BHeader[0x13] = (UCHAR)(m_Width >> 8) & 0xff;  
    sg_BHeader[0x14] = (UCHAR)(m_Width >> 16) & 0xff;  
    sg_BHeader[0x15] = (UCHAR)(m_Width >> 24) & 0xff;  
    sg_BHeader[0x16] = (UCHAR)m_Height & 0xff;  
    sg_BHeader[0x17] = (UCHAR)(m_Height >> 8) & 0xff;  
    sg_BHeader[0x18] = (UCHAR)(m_Height >> 16) & 0xff;  
    sg_BHeader[0x19] = (UCHAR)(m_Height >> 24) & 0xff;  
    write(bmp, sg_BHeader, sizeof(sg_BHeader));  
    for(i = 0; i < m_Height; i++)  
    {  
        unsigned short *c = p + (m_Height - 1 - i) * m_Width;  
        unsigned short cc;  
        for(j = 0; j < m_Width; j++)  
        {  
            cc = RGB565TO1555(*(c + j));  
//            cc = *(c + j);  
            write(bmp, &cc, 2);  
        }  
    }  
    close(bmp);  
}  
int main(int argc, char *argv[])  
{  
    unsigned char buf[800*480*2];  
    char *filename;  
    int fb;  
    fb = open("/dev/fb0", O_RDONLY);  
    if(fb < 0)  
        exit(1);  
    if(argc == 2)  
        filename = argv[1];  
    else  
        exit(1);  
    printf("reading screen...\n");  
    read(fb, buf, 800*480*2);  
    close(fb);  
    printf("saving screen...\n");  
    SaveBMPFile(buf, filename);  
    printf("file %s created successfully\n", filename);  
    exit(0);  
}  