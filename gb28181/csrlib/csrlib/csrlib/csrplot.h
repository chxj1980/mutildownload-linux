#ifndef _CSR_PLOT_H_
#define _CSR_PLOT_H_

#include "comheader.h"

//��������ͼ


//���Ƶ���ͼ


//������״ͼ


void drawLineNew(void);

//���Ʊ���������
void initGLLib(void);

void displayPlot(void);

void drawLine(void);

//3D�ռ��л���2DЧ������������ͶӰ
void reshape(GLsizei w, GLsizei h);

void keyboard(unsigned char key, int x, int y);

//�ı��Сʱ���õĺ���
void ChangeSize(GLsizei w, GLsizei h);

//���ڳ�ʼ�������������ó�������Ⱦ״̬
void SetupRC(void);



#endif
