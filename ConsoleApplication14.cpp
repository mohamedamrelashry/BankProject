
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsDate.h"
#include "clsUtil.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsLoginScreen.h"
#include <iomanip>
using namespace std;  


int main()
{  
    
   
    while(true){
        if (!clsLoginScreen::ShowLoginScreen()) {
            break; 
        }
    }
    return 0;
}   

