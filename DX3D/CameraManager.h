#pragma once

#define g_pCameraManager CameraManager::GetInstance()
#define g_pCurrentCamera CameraManager::GetInstance()->GetCurrentCamera()
//#define CameraChangeSpeed 6.0f
class ICamera;

class CameraManager
{
    SINGLETON(CameraManager)

private:
    ICamera * m_pCurrentCamera;
    map<int, ICamera*> m_mapList;
    bool isVkeyPressed = false;

public:
    //�̷��� ���� �� �ʿ䰡 ������? ���� First�� Third�� ����� ���̱� ������?
    //�׷� enum�� ��𿡴ٰ� �־�� �ϴ°�?
    void AddCamera(int cameraState, ICamera* pCamera)
    {
        if (m_mapList.count(cameraState) == 1)
            return;
        m_mapList[cameraState] = pCamera;
    }
    void SetCurrentCamera(int cameraState);
    ICamera* GetCurrentCamera() { return m_pCurrentCamera; }

    void Init();    
    void Destroy();
    void Update();

    void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
