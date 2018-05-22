#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

#ifndef GLEW_STATIC
#define GLEW_STATIC  
#endif // !GLEW_STATIC
#include <GL/glew.h> 

#include <GLFW/glfw3.h>  

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <openvr/openvr.h>

#include "CGLRenderModel.h"
class VRDriver
{
public:
	VRDriver();
	virtual ~VRDriver();

	bool Init(); 
	void Shutdown();

	//��VRBegin��VREnd֮���ͼ���Ѿ����ú�viewport��clearcolor��һ��begin��end��������Ҫһ��
	void VRBegin(bool isLeftEye);
	void VREnd(bool isLeftEye);
	//�ύ֡���浽VR�豸
	void Submit();
	//�������룬Ҫ���õ�ProcessVREvent
	bool HandleInput();

	//��ȡProjection Matrix��PoseEye Matrix���޷������ӽǴ�С
	mat4 GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye, float nearClip, float farClip);
	mat4 GetHMDMatrixPoseEye(vr::Hmd_Eye nEye);

private:
	void ProcessVREvent(const vr::VREvent_t & event);
	bool BInitCompositor();
	bool SetupStereoRenderTargets();

	void UpdateHMDMatrixPose();
	mat4 ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose);

private:
	vr::IVRSystem *m_pHMD;

	vr::TrackedDevicePose_t m_rTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];
	mat4 m_rmat4DevicePose[vr::k_unMaxTrackedDeviceCount];
	bool m_rbShowTrackedDevice[vr::k_unMaxTrackedDeviceCount];
	std::string m_strDriver;
	std::string m_strDisplay;

	uint32_t m_nRenderWidth;
	uint32_t m_nRenderHeight;

	std::string m_strPoseClasses;                            // what classes we saw poses for this frame
	char m_rDevClassChar[vr::k_unMaxTrackedDeviceCount];   // for each device, a character representing its class





public:
	//֡����
	struct FramebufferDesc
	{
		GLuint m_nDepthBufferId;
		GLuint m_nRenderTextureId;
		GLuint m_nRenderFramebufferId;
		GLuint m_nResolveTextureId;
		GLuint m_nResolveFramebufferId;
		int width;
		int height;
	};
	//������֡����
	FramebufferDesc leftEyeDesc;
	FramebufferDesc rightEyeDesc;
	bool CreateFrameBuffer(int nWidth, int nHeight, FramebufferDesc &framebufferDesc);

	//ͷ��λ�ú��ֱ�λ�ã��ֱ�����
	mat4 HMDPose, HMDPoseInverse, m_mat4Contraller1Pose, m_mat4Contraller2Pose;
	int controllerNum;
};
