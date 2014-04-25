#include "schleife.h"


Schleife::Schleife(bool closed_,bool flip_, int polyPoints_, int lineSteps_, float alpha_, bool addNoise_, float radius_, ofVec3f pos_, float color_) {

	polyPoints = polyPoints_;
	lineSteps = lineSteps_;
	alpha = alpha_;
	closed = closed_;
	flip = flip_;
	addNoise = addNoise_;
	radius = radius_;
	pos = pos_;
	color = color_;

	mesh.clear();
	//mesh.setMode(OF_PRIMITIVE_POINTS);
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);

	noiseC = 12.322;

	polyLine.clear();
	polyLinePoints.clear();
	polyEndPoints.clear();


	float angle = 0;




	for (int i = 0; i < polyPoints+2; i++) {
		float s = ofMap( float(i), 0, polyPoints+2, 0, TWO_PI);
		float sA = (sin(s)+1) /2;
		float sB = ofMap(sA, 0,1,0.5,1);
		//ofVec3f temp = ofVec3f( 1400*sin( (alpha/sB)*i )*sB, 1400*cos( (alpha/sB)*i )*sB, i*18*sB );
		ofVec3f temp = ofVec3f( radius*sin( (alpha)*i ), radius*cos( (alpha)*i ), 0);



		//ofVec3f temp = ofVec3f(2*i,0,0);
		polyLinePoints.push_back(temp);
		polyLine.curveTo(temp);
	}

	for (int i=1 ; i < polyLinePoints.size(); i++) {
		ofVec3f temp = polyLinePoints[i]-polyLinePoints[i-1];
		ofPushMatrix();
		ofTranslate(polyLinePoints[i]);
		rotateToNormal(temp);

		float alpha = ofMap(i, 1, polyLinePoints.size()-1, 0, TWO_PI*4 );
		alpha = ((sin(alpha)+1)/2)+1;

		ofVec3f pointA;
		ofVec3f pointB;
		if ( (flip) && (i%2==0) ){
			pointA = ofVec3f(lineSteps*0.8*alpha,0,0);
			pointB = -ofVec3f(lineSteps*0.8*alpha,0,0);
		} else {
			pointA = -ofVec3f(lineSteps*0.8*alpha,0,0);
			pointB = ofVec3f(lineSteps*0.8*alpha,0,0);

		}


		GLfloat m[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		ofMatrix4x4 mat = m;

		pointA = pointA*mat;
		polyEndPoints.push_back(pointA);
		pointB = pointB*mat;
		polyEndPoints.push_back(pointB);

		ofPopMatrix();

	}

	for(int i = 0; i < polyEndPoints.size(); i+=2) {

		ofVec3f direction = polyEndPoints[i]-polyEndPoints[i+1];

		float tempDist = polyEndPoints[i].distance(polyEndPoints[i+1]);
		direction.normalize();

		tempDist/=lineSteps;

		for (int j = 0; j <= lineSteps; j++) {

			ofVec3f temp = polyEndPoints[i+1] + (direction*(tempDist*j));

			mesh.addVertex( temp );
			mesh.addNormal(ofVec3f(0,0,1));

			if ((j<=2) || (j>lineSteps-2)) {
				mesh.addColor( ofColor::fromHsb(color,255,255,100));
			} else if ((j<=8) || (j>lineSteps-8)) {
				mesh.addColor( ofColor::fromHsb(color,122,205));

			} else if (j == lineSteps/2) {
				mesh.addColor( ofColor::fromHsb(color/2,255,255,100));

			} else if( (j == lineSteps/3) || (j == (lineSteps/3)*2) ){
				mesh.addColor( ofColor::fromHsb(color/2,255,255,100));

			} else {

				float cMap = ofMap(j, 0, lineSteps, -70, 70);
				mesh.addColor( ofColor::fromHsb(color/2,abs(cMap),255));

			}
		}

	}


	if (!closed) {
		for (int i = 0; i < polyPoints-1; i++) {
			for (int j = 0; j < lineSteps; j++) {

				int index = (i*(lineSteps+1))+j;

				mesh.addIndex(index);
				mesh.addIndex(index+lineSteps+1);
				mesh.addIndex(index+1);

				mesh.addIndex(index+lineSteps+1);
				mesh.addIndex(index+lineSteps+1+1);
				mesh.addIndex(index+1);

			}
		}
	} else {
		for (int i = 0; i < polyPoints; i++) {
			for (int j = 0; j < lineSteps; j++) {

				if (i != polyPoints-1) {
					int index = (i*(lineSteps+1))+j;


					mesh.addIndex(index);
					mesh.addIndex(index+lineSteps+1);
					mesh.addIndex(index+1);

					mesh.addIndex(index+lineSteps+1);
					mesh.addIndex(index+lineSteps+1+1);
					mesh.addIndex(index+1);

				} else {

					int index = (i*(lineSteps+1))+j;	

					mesh.addIndex(index);
					mesh.addIndex(j);
					mesh.addIndex(index+1);

					mesh.addIndex(j);
					mesh.addIndex(j+1);
					mesh.addIndex(index+1);
				}

			}
		}

	}


}

void Schleife::setup(){

}

void Schleife::draw() {
	//polyLine.draw();
	//mesh.drawWireframe();
	ofPushMatrix();
	ofTranslate(pos);
	mesh.draw();
	ofPopMatrix();
}

void Schleife::update() {

	// generate a noisy 3d position over time 


	if ((ofGetFrameNum() < 200) && (addNoise) ){
		for (int i = 0; i < mesh.getNumVertices(); i++) {
			float t = noiseC *0.02;
			ofVec3f current;
			current.x = ofSignedNoise(t, 0, 0);
			noiseC += 0.01;
			current.y = ofSignedNoise(0, t, 0);
			noiseC += 0.01;
			current.z = ofSignedNoise(0, 0, t);
			current *= 1; // scale from -1,+1 range to -400,+400

			mesh.setVertex(i, mesh.getVertex(i)+current) ;

			noiseC += 0.01;
		}

	}



}

void Schleife::rotateToNormal(ofVec3f normal) {

	normal.normalize();

	float rotationAmount;
	ofVec3f rotationAngle;
	ofQuaternion rotation;

	ofVec3f axis(0, 0, 1);
	rotation.makeRotate(axis, normal);
	rotation.getRotate(rotationAmount, rotationAngle);
	ofRotate(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);

}
