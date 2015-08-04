#pragma once
#include "ofMain.h"

class Schleife {
public:
	Schleife(bool,bool,int,int,float,bool,float, ofVec3f, float, int);

	void setup();
	void draw();
	void update();
	void rotateToNormal(ofVec3f);

	ofPolyline polyLine;
	ofVboMesh mesh;

	vector<ofVec3f> polyLinePoints;
	vector<ofVec3f> polyEndPoints;
	
	float noiseC;
	int lineSteps;
	int polyPoints;
	float alpha;
	bool closed;
	bool flip;
	bool addNoise;
	float radius;
	float color;
	int wrap;

	ofVec3f pos;
};

