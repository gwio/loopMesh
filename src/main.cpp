#include "ofMain.h"
#include "ofApp.h"

#ifdef __APPLE__
#ifdef TARGET_OS_MAC

int main(){

	ofSetupOpenGL(600,900,OF_WINDOW);			// <-------- setup the GL context
	ofRunApp(new ofApp());
    
}

#endif


#elif defined(_WIN32) || defined(_WIN64)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){

	ofSetupOpenGL(600,900,OF_WINDOW);			// <-------- setup the GL context
	ofRunApp(new ofApp());

}

#endif
