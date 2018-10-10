#include <iostream>
#include "i3system_TE.h"
using namespace i3;
using namespace std;
BOOL Dialog::OnInitDialog()
{
    ...

    // Scan connected TE.

    SCANINFO *pScan = new SCANINFO[MAX_USB_NUM];

    ScanTE(this->GetSafeHwnd(), pScan);

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

        TE_B *pTE = OpenTE_B(this->GetSafeHwnd(), I3_TE_Q1, hnd_dev);

        bool exit = false;

        if(pTE){

            cout << "TE Opened" << endl;

            // Read Flash Data

            if(pTE->ReadFlashData() == 1){

                cout << "Read Flash Data" << endl;

                int width = pTE->GetImageWidth(), height = pTE->GetImageHeight();

                unsigned short *pImgBuf = new unsigned short[width*height];

                while(!exit){

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

LRESULT Dialog::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)

{

    int nRes = WindowProcTE(message, wParam, lParam);

    if (nRes == 1)

    {

        InsertString(L"Window Proc \r\n: USB device connection available (^~^)");

    }

    else if (nRes == 2) {

        InsertString(L"Window Proc \r\n: USB device connection not available(_|_)");

    }

    else if (nRes == 3) {

        InsertString(L"Window Proc \r\n: USB device removed (^-^)");

    }

    else if (nRes == 4) {

        InsertString(L"Window Proc \r\n: Failed to remove USB device (_|_)");

    }

    return CDialogEx::WindowProc(message, wParam, lParam);

}

 Generated by   doxygen  1.8.13 