#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();


	this->len = 10;
	this->values = vector<vector<vector<bool>>>(this->len, vector<vector<bool>>(this->len, vector<bool>(this->len)));
	this->tmp_values = this->values;

	for (int x = 0; x < this->len; x++) {

		for (int y = 0; y < this->len; y++) {

			for (int z = 0; z < this->len; z++) {

				this->values[x][y][z] = ofRandom(2) < 1.0 ? true : false;
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	if (ofGetFrameNum() % 15 != 0) { return; }

	for (int x = 0; x < this->len; x++) {

		for (int y = 0; y < this->len; y++) {

			for (int z = 0; z < this->len; z++) {
	
				int count = 0;
				int t = 0;
				for (int tmp_x = x - 1; tmp_x <= x + 1; tmp_x++) {

					for (int tmp_y = y - 1; tmp_y <= y + 1; tmp_y++){ 

						for (int tmp_z = z - 1; tmp_z <= z + 1; tmp_z++) {

							if (x == tmp_x && y == tmp_y && z == tmp_z) { continue; }
							if (tmp_x < 0 || tmp_x > this->len - 1 || tmp_y < 0 || tmp_y > this->len - 1 || tmp_z < 0 || tmp_z > this->len - 1) { continue; }

							if (this->values[tmp_x][tmp_y][tmp_z]) {

								count++;
							}
						}
					}
				}

				if (count == 5) {

					this->tmp_values[x][y][z] = true;
				}
				else if (count >= 3 && count <= 6) {

					this->tmp_values[x][y][z] = this->values[x][y][z];
				}
				else{

					this->tmp_values[x][y][z] = false;
				}
			}
		}
	}

	this->values = this->tmp_values;
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	int box_size = 25;
	ofColor color;
	for (int x = 0; x < this->len; x++) {

		for (int y = 0; y < this->len; y++) {
			
			for (int z = 0; z < this->len; z++) {

				color.setHsb(ofRandom(255), 255, 255);

				if (this->values[x][y][z]) {

					ofFill();
					ofSetColor(39);
					ofDrawBox(x * box_size - box_size * this->len * 0.45,
						y * box_size - box_size * this->len * 0.45,
						z * box_size - box_size * this->len * 0.45,
						box_size * 0.95);

					ofSetColor(255);
					ofNoFill();
					ofDrawBox(x * box_size - box_size * this->len * 0.45,
						y * box_size - box_size * this->len * 0.45,
						z * box_size - box_size * this->len * 0.45,
						box_size * 0.95 + 1);
				}
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}