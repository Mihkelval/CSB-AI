#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <cmath>

using namespace std;

//code to calculate angle to next point, based on distance to it
int calcAngle(int distanceX, int distanceY){
    float normalized = sqrt(distanceX*distanceX + distanceY*distanceY);
    int angle = acos(distanceX/normalized) * 180/ M_PI;
    if (distanceY/normalized < 0){
        angle = 360 - angle;
    }
    return angle;
}
int main()
{
    vector<array<int, 2>> checkpoints;
    int laps;
    bool boosted = false;
    cin >> laps; cin.ignore();
    int checkpointCount;
    cin >> checkpointCount; cin.ignore();
    checkpoints.reserve(checkpointCount);
    for (int i = 0; i < checkpointCount; i++) {
        int checkpointX;
        int checkpointY;
        cin >> checkpointX >> checkpointY; cin.ignore();
        checkpoints[i] = {checkpointX,checkpointY};
    }

    // game loop
    while (1) {
        for (int i = 0; i < 2; i++) {
            int x; // x position of your pod
            int y; // y position of your pod
            int vx; // x speed of your pod
            int vy; // y speed of your pod
            int angle; // angle of your pod
            int thrust = 100;
            int nextCheckPointId; // next check point id of your pod
            cin >> x >> y >> vx >> vy >> angle >> nextCheckPointId; cin.ignore();
            int distanceX = checkpoints[nextCheckPointId][0] - x;
            int distanceY = checkpoints[nextCheckPointId][1] - y;
            int AbsCheckpointAngle = abs(calcAngle(distanceX,distanceY) - angle);
            int nextCheckpointDist = sqrt(pow(distanceX, 2) + pow(distanceY,2)); 
            //slightly slow down as the pod approaches the checkpoint
            if(AbsCheckpointAngle >= 5){
                thrust = 100 * std::clamp(1- AbsCheckpointAngle/90.f,0.f,1.f) * std::clamp(nextCheckpointDist /(4*600.f), 0.f, 1.f);
            }
            //main driving logic for both pods
            //logic for using boost
            if(!boosted and AbsCheckpointAngle < 5 and nextCheckpointDist > 6000 and i == 0){
                cout << checkpoints[nextCheckPointId][0] << " " << checkpoints[nextCheckPointId][1] << " BOOST" << endl;
                boosted = true;
            }
            //logic to start turning before reaching the checkpoint
            else if(nextCheckpointDist < 2000 and abs(vx)+abs(vy)>300 and AbsCheckpointAngle < 30){
                int targetCheckpointId = nextCheckPointId+1 == checkpointCount ? 0 : nextCheckPointId+1;
                cout << checkpoints[targetCheckpointId][0] << " " <<checkpoints[targetCheckpointId][1] << " 100"<< endl;
            }
            //logic for offsetting the centre of the target
            else{
                cout << checkpoints[nextCheckPointId][0]-2*vx << " " <<checkpoints[nextCheckPointId][1]-2*vy << " " << thrust<< endl;
            }  
        }
        
        //read in enemy pod, ignored
        for (int i = 0; i < 2; i++) {
            int x2; // x position of the opponent's pod
            int y2; // y position of the opponent's pod
            int vx2; // x speed of the opponent's pod
            int vy2; // y speed of the opponent's pod
            int angle2; // angle of the opponent's pod
            int nextCheckPointId2; // next check point id of the opponent's pod
            cin >> x2 >> y2 >> vx2 >> vy2 >> angle2 >> nextCheckPointId2; cin.ignore();
        }

    }
}
