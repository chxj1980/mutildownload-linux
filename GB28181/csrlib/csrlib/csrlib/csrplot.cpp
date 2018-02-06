#include "csrplot.h"

GLfloat ctrlpoints[4][3] = {
	{ -4, -4, 0 },
	{ -2, 4, 0 },
	{ 2, -4, 0 },
	{ 4, 4, 0 }
};

void initGLLib(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);	//����ɫ
	/*
	���Ƶ�ӳ�䵽������
	����1��GL_MAP1_VERTEX_3, 3ά������
	����2��3�����Ʋ���t����u��ȡֵ��Χ[0,1]
	����4�������ڲ�ֵ���Ĳ���3--��ά����
	����5�����߼�Ĳ���Ϊ������4��---�ܲ���12
	����6�����Ƶ��ά������Ԫ�ص�ַ
	*/
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
	glShadeModel(GL_FLAT);

	//���뿪��2��ȥ����ע�ͣ������÷�����
	/*
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);  //����ֱ�߷�����
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);  // Antialias the lines
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	*/
}

void displayPlot(void)
{
		int i = 0;
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0, 1.0, 1.0);

		//���뿪��1��ȥ����ע�ͣ��鿴��̬�����߻�ͼЧ������̬���¿��Ƶ�����
		/*
		for(int t = 0; t < 4; t++) {
		for(int j = 0; j < 3; j++)
		ctrlpoints[t][j] = (rand() % 1024 / 1024.0 - 0.5) * 10;
		}
		//��̬ӳ��
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
		*/

		glLoadIdentity();
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_STRIP);		//���������߶�

									//����t��uȡֵΪi/30,����31����
		for (i = 0; i <= 30; ++i)
			glEvalCoord1f((GLfloat)i / 30.0);		//�����ĸ����Ƶ������������ֵ

		glEnd();

		//��ʾ���Ƶ�
		glPointSize(5.0);
		glBegin(GL_POINTS);
		for (i = 0; i < 4; i++)
			glVertex3fv(&ctrlpoints[i][0]);
		glEnd();

		glTranslatef(-0.1f, 0.1f, 0.0f);
		glColor3f(0.0, 1.0, 0.0);

		glBegin(GL_LINE_STRIP);					//���������߶�Խ�࣬����Խ�⻬
		glBegin(GL_LINE_STRIP);
		//���ò���t��uȡֵΪi/60������61����
		//ʵ�飺����t��-2�仯��+2���ɿ���ʲôЧ��
		for (i = 0; i <= 60; i++)
			glEvalCoord1f((GLfloat)i / 60.0);  //����4�����Ƶ�����Ĳ�������ֵ
		glEnd();

		glTranslatef(-0.1f, 0.1f, 0.0f);
		glColor3f(1.0, 1.0, 1.0);
		//���������߶�
		glBegin(GL_LINE_STRIP);
		//���ò���t��uȡֵΪi/60������61����
		//ʵ�飺����t��-2�仯��+2���ɿ���ʲôЧ��
		for (i = 0; i <= 100; i++)
			glEvalCoord1f((GLfloat)i / 100.0);
		glEnd();

		glutSwapBuffers();
}

void drawLine(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2, 0xAAAA);
	glLineWidth(5.0);
	glBegin(GL_LINE_LOOP);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.25, 0.25, 0);
	glVertex3f(0.75, 0.25, 0);
	glVertex3f(0.75, 0.75, 0);
	glVertex3f(0.25, 0.75, 0);
	glEnd();

	glDisable(GL_LINE_STIPPLE);
	glFlush();
}

void drawLineNew(void)
{
	//�����ɫ�������������ڵı���ɫ
	glClear(GL_COLOR_BUFFER_BIT);

	//���õ�ǰ��ͼʹ�õ���ɫ
	glColor3f(0.0f, 0.0f, 0.0f);

	//ʹ�õ�ǰ����ɫ������һ������
	//    glRectf(100.0f, 150.0f, 150.0f, 100.0f);

	//   1.����
	GLfloat sizesPoint[2];//�����߿�ĳߴ緶Χ
	GLfloat stepPoint;//�����߿�ȳߴ����С���
	GLfloat curSizePoint;

	glGetFloatv(GL_POINT_SIZE_RANGE, sizesPoint);
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &stepPoint);
	curSizePoint = sizesPoint[0];
	for (int i = 0;i < 25;i++) {
		glPointSize(curSizePoint);
		glBegin(GL_POINTS);
		glVertex3f(25.0 + i * 8, 200.0f, 0.0f);
		glEnd();
		curSizePoint += stepPoint * 2;
	}


	//  2. ��ֱ��

	//    GLfloat sizesLine[2];//�����߿�ĳߴ緶Χ
	//    GLfloat stepLine;//�����߿�ȳߴ����С���
	GLfloat curSizeLine = 5;
	//    glGetFloatv(GL_LINE_WIDTH_RANGE,sizesLine);
	//    glGetFloatv(GL_LINE_WIDTH_GRANULARITY,&stepLine);
	glLineWidth(curSizeLine);
	glBegin(GL_LINES);
	glVertex3f(25.0f, 160.0f, 0.0f);
	glVertex3f(225.0f, 160.0f, 0.0f);

	glEnd();

	//   3.��������ֱ��
	glBegin(GL_LINE_STRIP);
	glVertex3f(25.0f, 150.0f, 0.0f);
	glVertex3f(100.0f, 150.0f, 0.0f);
	glVertex3f(100.0f, 130.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 10.0f, 0.0f);
	glVertex3f(20.0f, 5.0f, 0.0f);
	glEnd();

	//   4.�����ʽֱ��
	glBegin(GL_LINE_LOOP);
	glVertex3f(125.0f, 150.0f, 0.0f);
	glVertex3f(200.0f, 150.0f, 0.0f);
	glVertex3f(200.0f, 130.0f, 0.0f);
	glEnd();

	//   ������
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0x00FF);//��һ�������Ǳ������ڶ���������һ��ʮ����������������ʾ�����ʾ��
	glBegin(GL_LINES);
	glVertex3f(25.0f, 120.0f, 0.0f);
	glVertex3f(225.0f, 120.0f, 0.0f);
	glEnd();


	glLineWidth(3);
	glLineStipple(1, 0xFF0C);
	glBegin(GL_LINES);
	glVertex3f(25.0f, 80.0f, 0.0f);
	glVertex3f(225.0f, 80.0f, 0.0f);
	glEnd();


	glLineStipple(4, 0xFF0C);
	glBegin(GL_LINES);
	glVertex3f(25.0f, 40.0f, 0.0f);
	glVertex3f(225.0f, 40.0f, 0.0f);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	//ˢ��opengl�������
	glFlush();
}

void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-5.0, 5.0, -5.0*(GLfloat)h / (GLfloat)w, 5.0*(GLfloat)h / (GLfloat)w, -5.0, 5.0);
	else
		glOrtho(-5.0*(GLfloat)w / (GLfloat)h, 5.0*(GLfloat)w / (GLfloat)h, -5.0, 5.0, -5.0, 5.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
	case 'X':
	case 27:   //ESC��
		exit(0);
		break;
	default:
		break;
	}
}

void ChangeSize(GLsizei w, GLsizei h)
{
	if (h == 0) {
		h = 1;
	}
	//���������ߴ�
	glViewport(0, 0, w, h);
	//��������ϵͳ��ʹ��ͶӰ�任��λ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		glOrtho(0.0f, 250.0f, 0.0f, 250.0f*h / w, 1.0f, -1.0f);
	}
	else
	{
		glOrtho(0.0f, 250.0f*w / h, 0.0f, 250.0f, 1.0f, -1.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

