#include <iostream>
#include "i3system_TE.h"
using namespace i3;
using namespace std;
void Hotplug_Callback(TE_STATE _teState);
int main()
{
    // Set Hotplug Callback Function
    SetHotplugCallback(Hotplug_Callback);
    // Scan connected TE.
    SCANINFO *pScan = new SCANINFO[MAX_USB_NUM];
    ScanTE(pScan);
    int hnd_dev = -1;
    for(int i = 0; i < MAX_USB_NUM; i++){
        if(pScan[i].bDevCon){
            hnd_dev = i;
            break;
        }
    }
    delete pScan;
    // Open Connected Device
    if(hnd_dev != -1){
        TE_A *pTE = OpenTE_A(hnd_dev);
        bool exit = false;
        if(pTE){
            int width = pTE->GetImageWidth(), height = pTE->GetImageHeight();
            unsigned short *pImgBuf = new unsigned short[width*height];
            unsigned short *pwTempBuf = new unsigned short[width*height];
            float *pfTempBuf = new float[width*height];
            while(!exit){
                // Get Image Data
                if(pTE->RecvImage(pImgBuf,false)){
                    cout << "Image Received" << endl;
                    // Get Temperature
                    pTE->CalcTemp(pwTempBuf);
                    for(int i=0; i < width * height; i++){
                        pfTempBuf[i] = ((float)(pwTempBuf[i]-5000)) / 100.f;
                    }
                    cout << "Get Temperature" << endl;
                }
                else{
                    cout << "Image not received" << endl;
                }
            }
            // Close Device
            pTE->CloseTE();
            cout << "Close Usb" << endl;
            delete pImgBuf;
            delete pwTempBuf;
            delete pfTempBuf;
        }
        else{
            cout << "Open Failed" << endl;
        }
    }
    else{
        cout << "Device Not Connected" << endl;
    }
    return 0;
}
// Callback function executed when TE is arrived to or removed from usb port.
void Hotplug_Callback(TE_STATE _teState){
    if(_teState.nUsbState == TE_ARRIVAL){
        // Do something ...
    }
    else if(_teState.nUsbState == TE_REMOVAL){
        // Do something ...
    }
}
