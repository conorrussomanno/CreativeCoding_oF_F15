//
//  Particles.cpp
//  myFlocking
//
//  Created by Regina Flores on 9/25/14.
//
//

#include "Particles.h"


Particle::Particle(){
    
    radius = 2;

}

void Particle::init(){
    
    //defining the position and velocity of the particles
    //pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2, -30);
    //using easy cam changes (0,0) to middle of screen
    pos = ofPoint(ofRandom(-ofGetWidth()/2, ofGetWidth()/2),ofRandom(-ofGetHeight()/2, ofGetHeight()/2), ofRandom(-200, 200));
//    vel = ofPoint(ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10));
    vel = ofPoint(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
    
}

void Particle::bounding(){
    
    //keeping the particles inside the screen
    //note: the new screen width is (-w/2,w/2), same for height
    if(pos.y > ofGetHeight()/2){
        vel = -vel;
    }
    if(pos.y < -ofGetHeight()/2){
        vel = -vel;
    }

    if(pos.x > ofGetWidth()/2){
        vel = -vel;
    }
    if(pos.x < -ofGetWidth()/2){
        vel = -vel;
    }
    if(pos.z < -200){
        vel = -vel;
    }
    if(pos.z > 200){
        vel = -vel;
    }
    
    
    //
    

}

void Particle::draw(){
    
    ofCircle(pos.x, pos.y, pos.z, radius);

}


//NOTE: Flocking Rules
// each particle compares his state (i.e position and vel) to others to change velocity
//we pass the vector of particles into the update function
//http://www.kfish.org/boids/pseudocode.html


ofPoint Particle::cohesion(vector<Particle> &particles){

    //RULE 1
    //finding the center of mass of the system
    ofPoint centerMass;
    for(int i = 0; i < particles.size(); i++){
        //determining if the particle in the loop is itself
        //to avoid itself
        if (&particles[i] == this) {
            continue;
        }
        
        centerMass += particles[i].pos;
    
    }
    
    centerMass = centerMass/(particles.size()-1);
    
    ofPoint cohesion_velocity;
    cohesion_velocity = (centerMass-pos)/100.0f;
    return cohesion_velocity;
}

ofPoint Particle::separation(vector<Particle> &particles){
    //RULE 2
    //particles keep a small distance from each other
    
    ofPoint displace;
    for(int i = 0; i < particles.size(); i++){
        //determining if the particle in the loop is itself
        //to avoid itself
        if (&particles[i] == this) {
            continue;
        }
        
        // distance between me and particles[i]
        float dist = pow(particles[i].pos.x - pos.x, 2) + pow(particles[i].pos.y - pos.y, 2) + pow(particles[i].pos.z - pos.z, 2);
        dist = sqrt(dist);

        if (dist < 10.0) {
            displace  = displace - (particles[i].pos - pos);
        }
        
    }
    
    ofPoint separation_velocity;
    separation_velocity = displace;
    return separation_velocity;
}

ofPoint Particle::allignment(vector<Particle> &particles){

    //RULE 3
    //match velocity
    
    ofPoint aveVel;
    for(int i = 0; i < particles.size(); i++){
        //determining if the particle in the loop is itself
        //to avoid itself
        if (&particles[i] == this) {
            continue;
        }
        
        aveVel += particles[i].vel;
        
    }
    
    aveVel = aveVel/(particles.size()-1);
    
    ofPoint allignment_velocity;
    allignment_velocity = (aveVel - vel)/8.0f;
    return allignment_velocity;
    
}

void Particle:: update( vector<Particle> &particles ){
    //& pointer notation (ref of the array)
    
    ofPoint v1 = cohesion(particles);
    ofPoint v2 = separation(particles);
    ofPoint v3 = allignment(particles);
    
    vel = vel + v1 + v2 + v3;
    pos = pos + vel;

}


