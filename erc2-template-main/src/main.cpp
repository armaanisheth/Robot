#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHSD.h>
#include <Arduino.h>
#include <FEHMotor.h>
#include <FEHUtility.h>
#include <Encoder.h>
#include <FEHServo.h>
#include <FEHRCS.h>

//initialize all the servos and motors
AnalogInputPin cds(FEHIO::Pin2);

FEHMotor right_motor(FEHMotor::Motor0, 9.0);
DigitalEncoder right_encoder(FEHIO::Pin11);

FEHMotor left_motor(FEHMotor::Motor1, 9.0);
DigitalEncoder left_encoder(FEHIO::Pin14);

FEHMotor front_motor(FEHMotor::Motor2, 9.0);
DigitalEncoder front_encoder(FEHIO::Pin8);

FEHServo arm_servo_RT(FEHServo::Servo2);
FEHServo arm_servo_ARM(FEHServo::Servo4);

//declare the methods
void drive(double inches, char direction);
void strafing(double inches, char direction);
void spinInPlace(int degrees, char direction);

void ERCMain()
{ 
    //rcs code and receive the correct lever
    RCS.InitializeTouchMenu("1130D9ZBH");
    int correctLever = RCS.GetLever();

    //set the initial degree to 0 as the default position
    arm_servo_ARM.SetDegree(0.0);

    //cds cell initializing the starting voltage value 
    int count = 0;
    float volt = cds.Value();
    
    //last time we can touch the robot
    WaitForFinalAction();

    // PICK UP BUCKET AT 126. MAKE IT GO UP TO 70 FOR DEPOSITING.
    //read starting voltage and continuous volt updates until a light source with a red filter
    while (volt > 0.6  && count < 300) {
        //receive new voltage
       volt = cds.Value();
       Sleep(0.1);
       count++;
    }
   
    //drive backward to hit the final button
    drive(2, 'b'); 
    Sleep(0.5);

    //drive forward from the final button
    drive(2, 'f'); 
    Sleep(0.5);

    //set the spinner degree to 32 for compost drum starting position
    arm_servo_RT.SetDegree(32.0);

    //turn the robot 135 degrees right to face the spinner toward the compost drum
    spinInPlace(135, 'r');
    Sleep(0.5);

    //drive forward 4 inches toward composter
    drive(4, 'b'); 
    Sleep(0.5);
    
    //strafe 5.15 inches right to align close to the wall
    strafing(5.15, 'r');
    Sleep(0.5);

    //drive 10.5 inches backward to flush the spinner to the drum
    drive(10.5, 'b'); 
    Sleep(0.5);

    //shift the robot spinner 180 degrees to turn the drum
    arm_servo_RT.SetDegree(180.0);
    Sleep(0.5);

    //drive forward to allow the spinner to reposition itself
    drive(2, 'f');
    Sleep(0.5);

    //reposition the spinner
    arm_servo_RT.SetDegree(20.0);
    Sleep(0.5);

    //once again flush the spinner to the drum
    drive(2, 'b');
    Sleep(0.5);

    //set the degree to 180 to complete the first 300 degree rotation
    arm_servo_RT.SetDegree(180.0);
    Sleep(1.5);

    //set the spinner to 32 degrees to spin it back
    arm_servo_RT.SetDegree(32.0);
    Sleep(0.5);

    //move foward 2 inches to allow the spinner to reposition itself
    drive(2, 'f');
    Sleep(0.5);

    //reposition the spinner
    arm_servo_RT.SetDegree(173.0);
    Sleep(0.5);

    //last time to flush the spinner to the compost drum
    drive(2.5, 'b');
    Sleep(0.5);

    //set the spinner degree to 32 to finish the 300 degree rotation back
    arm_servo_RT.SetDegree(32.0);
    Sleep(1.0);

    //drive forward 2 inches away from the drum
    drive(2, 'f');
    Sleep(0.5);

    //strafe left to position the robot parallel to the apple basket
    strafing(16, 'l');
    Sleep(0.5);

    //spin the robot 180 degrees to face the arm toward the basket
    spinInPlace(180, 'r');
    Sleep(0.5);

    //set the degree of the front arm to 126 to position the arm for the apple basket handle
    arm_servo_ARM.SetDegree(126.0);
    Sleep(3.0);

    //drive forward to position hook under the apple basket handle
    drive(8.25, 'f');
    Sleep(0.5);

    //set the arm degree to 70 (upward) to lift basket
    arm_servo_ARM.SetDegree(70);
    Sleep(2.0);

    //strafe left to begin aligning with the ramp
    strafing(5.0, 'l');
    Sleep(0.5);

    //spin in place 90 degrees to face the front of the robot toward the ramp
    spinInPlace(90, 'r');
    Sleep(0.5);

    //strafe right so the robot is in front of the ramp
    strafing(16.0, 'r');
    Sleep(0.5);

    //drive up the ramp to the apple basket table
    drive(32.75, 'f');
    Sleep(0.5);

    //set the degree of the robot to 80 to deposit it
    arm_servo_ARM.SetDegree(80.0);
    Sleep(0.5);

    //drive backward to leave the basket on the table and remove the arm from the handle
    drive(5.75, 'b');
    Sleep(100.0);
   
    //attempt to read blue or red light value from the cds cell sensor
    //print message to the screen
    // String light;
    // volt = cds.Value();
    // count = 0;
    // while (!light.equals("blue") && !light.equals("red")) {
    //    volt = cds.Value();
    //    Sleep(0.1);
    //    count++;
    //    if (volt > 0.3 && volt < 0.6) {
    //         light = "blue";
    //         LCD.Write(light);
    //    }
    //    else if (volt < 0.25) {
    //         light = "red";
    //         LCD.Write(light);
    //    }
    //    else if (count >= 30) {
    //         if (volt < 0.25) {
    //             light = "red";
    //         }
    //         else {
    //             light = "blue";
    //         }
    //         LCD.Write("3 seconds have passed: ");
    //         LCD.Write(light);
    //    }
    // }

    // if (light.equals("blue")) {
    //     // strafe sideways to the left
    //     strafing(20, 66, 'l');
    //     Sleep(1.0);
    //     //drive forward to hit button
    //     drive_forward(20, 165);

    //     Sleep(2.0);
    //     //drive backwards
    //     drive_forward(-20, 150);
    //     Sleep(1.0);
    //     // strafe sideways to the right
    //     strafing(20, 66, 'r');
    //     Sleep(1.0);
    // }
    // else {
    //     // strafe sideways to the right
    //     strafing(20, 66, 'r');
    //     Sleep(1.0);
    //     //drive forward to hit button
    //     drive_forward(20, 165);

    //     Sleep(2.0);
    //     //drive backwards
    //     drive_forward(-20, 150);
    //     Sleep(1.0);
    //     // strafe sideways to the left
    //     strafing(20, 66, 'l');
    //     Sleep(1.0);
    // }

    



}

void drive(double inches, char direction)
{
    double percent = 40.0;
    double counts;
    // Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    if (direction == 'f'){
        counts =  inches * 33.94;
        left_motor.SetPercent(percent+2.5);
        percent = (percent * -1);
        right_motor.SetPercent(percent);
    }
    else {
        counts =  inches * 34.57;
        right_motor.SetPercent(percent);
        percent = (percent * -1);
        left_motor.SetPercent(percent-2.5);
    }

    // Keep running until the average counts reach the target
    while ((abs(left_encoder.Counts()) + abs(right_encoder.Counts())) / 2 < counts) {
         // Keep running
    }

    // Turn off motors  
    right_motor.Stop();
    left_motor.Stop();
}

void strafing(double inches, char direction) {

    double percent = 20.0;
    double counts = inches * 40.4040;
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    front_encoder.ResetCounts();
    
    //determine direction
    if (direction == 'r') {
        right_motor.SetPercent((-1 * percent) - 1);
        left_motor.SetPercent(-1 * percent);
        front_motor.SetPercent(percent + 19);
    }
    else {
        right_motor.SetPercent(percent + 1);
        left_motor.SetPercent(percent);
        front_motor.SetPercent((-1 * percent) - 19);
    }

    //While the front encoder is less than counts, keep running
    while (abs(front_encoder.Counts()) < counts) {
        //keep running
    }

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
    front_motor.Stop();
}

void spinInPlace(int degrees, char direction) {
    double percent = 30.0;
    if (direction == 'l') {
        right_motor.SetPercent((-1 * percent));
        left_motor.SetPercent((-1 * percent));
        front_motor.SetPercent((-1 * percent) - 10);

        Sleep(0.008056 * degrees);

        //Turn off motors
        right_motor.Stop();
        left_motor.Stop();
        front_motor.Stop();
    }
    if (direction == 'r') {
        right_motor.SetPercent(percent);
        left_motor.SetPercent(percent);
        front_motor.SetPercent(percent + 10);

        Sleep(0.008056 * degrees);

        //Turn off motors
        right_motor.Stop();
        left_motor.Stop();
        front_motor.Stop();
    }
}