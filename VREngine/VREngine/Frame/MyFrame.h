#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC  
#endif // !GLEW_STATIC
#include <GL/glew.h> // Contains all the necessery OpenGL includes

#include <SOIL/SOIL.h>

#include <iostream>
#include <string>
using namespace std;

//֡�����࣬�ó����ʼ��������һ��framebuffer
//createNormal()��framebuffer������3��renderbuffer��color��depth��stencil��һ������������Ӧ��С�ڴ�ռ����ڱ�����ɫ֡����
//createDepthTexture()�ǽ�framebuffer������һ����ȵ���ͼ������createNormal()����֮ǰ���òź�ʹ
//readColor()�ɽ�֡�������ݴ�������������imageData���棬saveToFile(int FrameNumber)�ǰ�imageData�������ݱ����ͼƬ
///����createDepthTexture()���ƵĿ��Ա�д������ɫ��ͼ������û�о���ʵ�֣�ʵ�ʿ��Ը��������д
class MyFramebuffer {
public:
	int width;
	int height;
	MyFramebuffer(int nWidth, int nHeight) {
		width = nWidth;
		height = nHeight;

		glGenFramebuffers(1, &FramebufferId);
		ColorBufferId = DepthBufferId = StencilBufferId = 0;
		imageData = new unsigned char[4 * height*width];
	}
	~MyFramebuffer() {
		delete[] imageData;
		if(ColorBufferId!=0)
			glDeleteBuffers(1, &ColorBufferId);
		if (DepthBufferId != 0)
			glDeleteBuffers(1, &DepthBufferId);
		if (StencilBufferId != 0)
			glDeleteBuffers(1, &StencilBufferId);
	}
	//ȫ����Ϊrenderbuffer,idΪ0�Żᴴ����Ӧ����
	bool createNormal();
	bool createDepthTexture();

	//Ĭ��Stencil��renderbuffer
	GLuint DepthBufferId;
	bool isDepthTexture;
	GLuint ColorBufferId;
	bool isColorTexture;
	GLuint StencilBufferId;

	GLuint FramebufferId;

	unsigned char* imageData;
	void readColor();

	void saveToFile(int FrameNumber);

};
