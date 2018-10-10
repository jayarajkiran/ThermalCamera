#include <iostream.h>
#include "/usr/local/include/i3system/i3system_TE.h"
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
        TE_B *pTE = OpenTE_B(I3_TE_Q1,hnd_dev);
        bool exit = false;
        if(pTE){
            cout << "TE Opened" << endl;
            // Read Flash Data
            if(pTE->ReadFlashData() == 1){
                cout << "Read Flash Data" << endl;
                int width = pTE->GetImageWidth(), height = pTE->GetImageHeight();
                unsigned short *pImgBuf = new unsigned short[width*height];
                for(int i = 0; i < 10; ++i){
                    // Get Image Data
                    if(pTE->RecvImage(pImgBuf)){
                        cout << "Image Received" << endl;
                        // Get Tamperature at (x, y)
                        int x = 100, y = 100;
                        float temp = pTE->CalcTemp(x, y);
                        cout << "Temperature = " << temp << endl;
                    }
                    else{
                        cout << "Image not received" << endl;
                    }
                }
                delete pImgBuf;
            }
            else{
                cout << "Fail to Read Flash Data" << endl;
            }
            // Close Device
            pTE->CloseTE();
            cout << "Close Usb" << endl;
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
