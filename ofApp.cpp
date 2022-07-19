#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetColor(255);
	ofEnableDepthTest();


	int span = 20;
	for (int x = -220; x <= 220; x += span) {

		for (int y = -220; y <= 220; y += span) {

			for (int z = -220; z <= 220; z += 440) {

				this->location_list.push_back(glm::vec3(x, y, z));
			}
		}
	}

	for (int x = -220; x <= 220; x += 440) {

		for (int y = -220; y <= 220; y += span) {

			for (int z = -220 + span; z <= 220 - span; z += span) {

				this->location_list.push_back(glm::vec3(x, y, z));
			}
		}
	}

	for (int x = -220 + span; x <= 220 - span; x += span) {

		for (int y = -220; y <= 220; y += 440) {

			for (int z = -220 + span; z <= 220 - span; z += span) {

				this->location_list.push_back(glm::vec3(x, y, z));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {


}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.42);
	ofRotateY(ofGetFrameNum() * 0.74);
	
	for (auto location : this->location_list) {
		
		auto noise_value = ofNoise(glm::vec4(location * 0.0025, ofGetFrameNum() * 0.01));

		if (noise_value > 0.55) {

			auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(location * 0.0025, ofGetFrameNum() * 0.01)), 0.55, 1, 0, 190) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
			auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(location * 0.0025, ofGetFrameNum() * 0.01)), 0.55, 1, 0, 190) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
			auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(location * 0.0025, ofGetFrameNum() * 0.01)), 0.55, 1, 0, 190) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

			location = glm::vec4(location, 0) * rotation_z * rotation_y * rotation_x;
			ofDrawSphere(location, 3);
		}
		else {

			ofDrawSphere(location, 3);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}