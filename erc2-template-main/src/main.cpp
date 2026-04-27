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

FEHServo arm_servo_RT(FEHServo::Servo7);
FEHServo arm_servo_ARM(FEHServo::Servo4);

//declare the methods
void drive(double inches, char direction);
void driveApples(double inches);
void strafing(double inches, char direction);
void spinInPlace(int degrees, char direction);

void ERCMain()
{ 
    //set the initial degree to 0 as the default position
    arm_servo_ARM.SetDegree(0.0);

    //rcs code and receive the correct lever
    RCS.InitializeTouchMenu("1130D9ZBH");

    // cds cell initializing the starting voltage value 
    int count = 0;
    float volt = cds.Value();
    
    //last time we can touch the robot
    WaitForFinalAction();

    // START OF CODE FOR THE TASKS BELOW THE RAMP
    //read starting voltage and continuous volt updates until a light source with a red filter
    while (volt > 0.6  && count < 300) {
        //receive new voltage
       volt = cds.Value();
       Sleep(0.1);
       count++;
    }
   
    //drive backward to hit the final button
    drive(2, 'b'); 
    Sleep(0.2);

    //drive forward from the final button
    drive(2, 'f'); 
    Sleep(0.2);

    //turn the robot 130 degrees right to face the spinner toward the compost drum
    spinInPlace(45, 'r');
    Sleep(0.2);

    strafing(4, 'l');
    Sleep(0.2);

    drive(8, 'b');
    Sleep(0.5);

    drive(1.25, 'f');
    Sleep(0.2);

    spinInPlace(92, 'r');
    Sleep(0.2);

    //drive 10.5 inches backward to flush the spinner to the drum
    drive(5, 'b'); 
    Sleep(0.2);

    strafing(0.35, 'r');
    Sleep(0.2);

    //drive 10.5 inches backward to flush the spinner to the drum
    drive(5.5, 'b'); 
    Sleep(0.2);

    arm_servo_RT.SetDegree(135);
    Sleep(1.5);

    arm_servo_RT.SetDegree(45);
    Sleep(1.5);
    
    arm_servo_RT.Off();

    //drive forward 2 inches away from the drum
    drive(2, 'f');
    Sleep(0.2);

    //strafe left to position the robot parallel to the apple basket
    strafing(19.95, 'l');
    Sleep(0.2);

    //spin the robot 180 degrees to face the arm toward the basket
    spinInPlace(183, 'r');
    Sleep(0.2);

    //set the degree of the front arm to 126 to position the arm for the apple basket handle
    arm_servo_ARM.SetDegree(126.0);
    Sleep(0.5);

    //drive forward to position hook under the apple basket handle
    drive(5.75, 'f');
    Sleep(0.2);

    //set the arm degree to 70 (upward) to lift basket
    arm_servo_ARM.SetDegree(70);
    Sleep(1.0);

    drive(2, 'b');
    Sleep(0.2);

    //strafe left to begin aligning with the ramp
    strafing(8.25, 'l');
    Sleep(0.2);

    drive(25, 'b');
    Sleep(0.3);

    drive(3, 'f');
    Sleep(0.2);

    spinInPlace(97, 'r');
    Sleep(0.2);

    //drive up the ramp to the apple basket table
    driveApples(29.75);
    Sleep(0.2);

    strafing(1, 'l');
    Sleep(0.2);

    spinInPlace(96, 'l');
    Sleep(0.2);

    drive(10, 'b');
    Sleep(0.5);

    drive(2, 'f');
    Sleep(0.2);

    spinInPlace(96, 'r');
    Sleep(0.2);

    //drive rest of way up the ramp to the apple basket table
    driveApples(7);
    Sleep(0.2);


    drive(1, 'b');
    Sleep(0.2);

    spinInPlace(22, 'r');
    Sleep(0.2);

    drive(1, 'f');
    Sleep(1.0);

    //set the degree of the robot to 97 to deposit it
    arm_servo_ARM.SetDegree(94.0);
    drive(1.25, 'b');
    Sleep(0.2);

    spinInPlace(22, 'l');

    arm_servo_ARM.SetDegree(0);
    Sleep(0.2);

    strafing(1.5, 'l');
    Sleep(0.2);

    // START OF CODE FOR THE TASKS ABOVE THE RAMP
    //drive backward away from the table
    drive(7, 'b');
    Sleep(0.2);


    //set the degree of the arm to 140 to posiiton it for the window
    arm_servo_ARM.SetDegree(140.0);
    Sleep(0.2);

    //turn left 90 degrees to move the arm at the same level as the window handle
    spinInPlace(89, 'l');
    Sleep(0.2);

    drive(8, 'b');
    Sleep(0.2);

    drive(0.75, 'f');
    Sleep(0.2);

    strafing(1.15, 'l');
    Sleep(0.2);

    //drive forward to close window
    drive(3.5, 'f');
    Sleep(0.2);

    strafing(0.45, 'l');
    Sleep(0.2);

    drive(6, 'f');
    Sleep(0.2);


    //strafe right to reposition the arm outside the front handle
    strafing(3.35, 'r');
    Sleep(0.2);

    //drive forward
    drive(2, 'f');
    Sleep(0.2);

    //strafe left to position arm behind handle 
    strafing(3, 'l');
    Sleep(0.2);

    //move backward to open window again
    drive(6.5, 'b');
    Sleep(0.2);

    // drive(0.25, 'f');
    // Sleep(0.2);

    // strafing(0.3, 'l');
    // Sleep(0.2);

    // //move backward to open window again
    // drive(3, 'b');
    // Sleep(0.2);

    //strafe right to align with center line in front of humidifer
    strafing(2, 'r');
    Sleep(0.2);

    //set arm to default position
    arm_servo_ARM.SetDegree(0.0);
    Sleep(0.2);

    drive(10, 'b');
    Sleep(0.2);

    drive(1, 'f');
    Sleep(0.2);

    strafing(4, 'r');
    Sleep(0.2);

    drive(4, 'b');
    Sleep(0.5);

    drive(18.0, 'f');
    Sleep(0.5); 
   
    //attempt to read blue or red light value from the cds cell sensor
    //print message to the screen
    String light="";
    volt = cds.Value();
    count = 0;
    strafing(0.75, 'r');
    while (!light.equals("blue") && !light.equals("red")) {
       volt = cds.Value();
       LCD.WriteAt(volt, 200, 100);
       Sleep(0.1);
       count++;

       if (volt < 0.5) {
            light = "red";
            // strafe sideways to the right
            strafing(1.5, 'r');
            Sleep(0.5);
            //drive forward to hit button
            drive(5, 'f');

            Sleep(0.5);

            drive(5, 'b');
            Sleep(0.5);
            strafing(1.5, 'l');
       }
    //    else if (volt > 0.60 && volt < 1.1) {
    //         light = "blue";
    //         strafing(1.5, 'l');
    //         Sleep(0.5);
    //         //drive forward to hit button
    //         drive(5, 'f');

    //         Sleep(0.5);

    //         drive(5, 'b');
    //         Sleep(0.5);
    //         strafing(1.5, 'r');
           
    //         //drive forward to hit button
            
    //    }
       else if (count >= 30) {
            //choose blue by randomness

            light = "blue";
            strafing(2.25, 'l');
            Sleep(0.5);
            //drive forward to hit button
            drive(5, 'f');

            Sleep(0.5);

            drive(5, 'b');
            Sleep(0.5);
            strafing(1.5, 'r');
            
       }
    }

    Sleep(0.2);

    strafing(9, 'r');
    Sleep(0.2);

    spinInPlace(45, 'r');
    Sleep(0.2);

    drive(2, 'b');
    Sleep(0.2);

    int correctLever = RCS.GetLever();
    LCD.WriteAt(correctLever, 150, 150);
    if (correctLever == 0){
        strafing(3.5, 'l');
        Sleep(0.2);

        arm_servo_ARM.SetDegree(160);
        Sleep(0.5);

        drive(5, 'b');
        Sleep(0.2);

        arm_servo_ARM.SetDegree(170);
        Sleep(0.5);

        drive(5, 'f');

        Sleep(4.0);

        arm_servo_ARM.SetDegree(140);
        Sleep(0.2);

        arm_servo_ARM.SetDegree(170);
        Sleep(0.2);

        // code to put it back to a centralized spot

        drive(8, 'b');
        Sleep(0.2);

        strafing(5, 'r');
        Sleep(0.2);

    }
    else if (correctLever == 1){
        arm_servo_ARM.SetDegree(160);
        Sleep(0.5);

        drive(5, 'b');
        Sleep(0.2);

        arm_servo_ARM.SetDegree(170);
        Sleep(0.5);

        drive(5, 'f');

        Sleep(4.0);

        arm_servo_ARM.SetDegree(140);
        Sleep(0.2);

        arm_servo_ARM.SetDegree(170);
        Sleep(0.2);

        // code to put it back to a centralized spot

        drive(8, 'b');
        Sleep(0.2);

    }
    else {
        strafing(4.5, 'r');
        Sleep(0.2);

        arm_servo_ARM.SetDegree(160);
        Sleep(0.5);

        drive(5, 'b');
        Sleep(0.2);

        arm_servo_ARM.SetDegree(170);
        Sleep(0.5);

        drive(5, 'f');

        Sleep(4.0);

        arm_servo_ARM.SetDegree(140);
        Sleep(0.2);

        arm_servo_ARM.SetDegree(170);
        Sleep(0.2);

        // code to put it back to a centralized spot

        drive(8, 'b');
        Sleep(0.2);

        strafing(5, 'l');
        Sleep(0.2);

    }

    arm_servo_ARM.SetDegree(0);
    Sleep(0.2);

    spinInPlace(45, 'l');
    Sleep(0.2);

    strafing(6, 'l');
    Sleep(0.2);

    drive(20, 'b');
    Sleep(0.5);

    drive(3, 'f');
    Sleep(0.2);

    spinInPlace(90, 'l');
    Sleep(0.2);

    drive(33, 'f');
    Sleep(0.2);

    strafing(6, 'l');
    Sleep(0.2);

    drive(5, 'f');
    Sleep(0.5);


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
        right_motor.SetPercent(percent-1);
    }
    else {
        counts =  inches * 34.57;
        right_motor.SetPercent(percent+0.5);
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

void driveApples(double inches)
{
    double percent = 40.0;
    double counts;
    // Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    counts =  inches * 33.94;
    left_motor.SetPercent(percent);
    percent = (percent * -1);
    right_motor.SetPercent(percent - 2.5);

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
        left_motor.SetPercent(percent + 1);
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

        Sleep(0.008276 * degrees);

        //Turn off motors
        right_motor.Stop();
        left_motor.Stop();
        front_motor.Stop();
    }
    if (direction == 'r') {
        right_motor.SetPercent(percent);
        left_motor.SetPercent(percent + 1.5);
        front_motor.SetPercent(percent + 10);

        Sleep(0.008000 * degrees);

        //Turn off motors
        right_motor.Stop();
        left_motor.Stop();
        front_motor.Stop();
    }
}