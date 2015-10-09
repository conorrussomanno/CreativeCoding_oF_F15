//
//  Ball.h
//  Dynamics_1
//
//  Created by Conor Russomanno on 10/8/15.
//
//

#include "ofMain.h"

class Ball : public ofBaseApp{
    
    public:
        void setup(); //quick setup
        void setup(float _xPos,
                   float _yPos,
                   float _xVel,
                   float _yVel,
                   float _xAcc,
                   float _yAcc,
                   float _diameter,
                   float _bounciness,
                   ofColor _ballColor); //fancy setup ... with ability to specify parameters
    
        void update();
        void draw();
        
        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);

    private:
    
        //Here are the variables that belong to every instance of the Ball class
    
        ofVec2f pos; //position of the Ball
        ofVec2f vel; //velocity (aka speed... change in position over time) ... as far as your computer is concered, this is how many pixels the Ball position changes each frame.
        ofVec2f acc; //acceleration (aka change in speed over time)
        float diameter; //how big is the circle??
        float bounciness;
        ofColor ballColor; //color of the ball
    
    
};