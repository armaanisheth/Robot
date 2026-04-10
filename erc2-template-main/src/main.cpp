#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHSD.h>
#include <Arduino.h>
#include <FEHMotor.h>
#include <FEHUtility.h>
#include <Encoder.h>
#include <FEHServo.h>
#include <FEHRCS.h>

AnalogInputPin cds(FEHIO::Pin2);

FEHMotor right_motor(FEHMotor::Motor0, 9.0);
DigitalEncoder right_encoder(FEHIO::Pin11);

FEHMotor left_motor(FEHMotor::Motor1, 9.0);
DigitalEncoder left_encoder(FEHIO::Pin14);

FEHMotor front_motor(FEHMotor::Motor2, 9.0);
DigitalEncoder front_encoder(FEHIO::Pin8);

FEHServo arm_servo_RT(FEHServo::Servo2);
FEHServo arm_servo_ARM(FEHServo::Servo4);


void drive_forward(int percent, int counts);
void strafing(int percent, int counts, char direction);
void spinInPlace(int percent, int degrees, char direction);

void ERCMain()
{ 
    // PICK UP BUCKET AT 126. MAKE IT GO UP TO 70 FOR DEPOSITING.
    
    
    
    //Sleep(30.0);



    arm_servo_ARM.SetDegree(170.0);
    Sleep(2.0);

    arm_servo_ARM.SetDegree(160.0);
    Sleep(3.0);

    arm_servo_ARM.SetDegree(150.0);
    Sleep(3.0);

    arm_servo_ARM.SetDegree(140.0);
    Sleep(3.0);

    RCS.InitializeTouchMenu("1130D9ZBH");
    int correctLever = RCS.GetLever();

    // arm_servo_ARM.SetDegree(0.0);
    // Sleep(2.0);

    // arm_servo_ARM.SetDegree(180.0);
    // Sleep(10.0);

    int count = 0;
    float volt = cds.Value();
    
    //read starting voltage and continuous volt updates until a light source is read
    while (volt > 0.6  && count < 300) {
       volt = cds.Value();
       Sleep(0.1);
       count++;
    }
   
    //drive backward to hit the final button
    drive_forward(-30, 70); //change counts
    Sleep(0.5);

    //drive forward from the final button
    drive_forward(30, 70); //change counts
    Sleep(0.5);

    arm_servo_RT.SetDegree(32.0);
    Sleep(0.5);

    spinInPlace(20, 140, 'r');
    Sleep(0.5);

    drive_forward(-30, 175); //change counts
    Sleep(0.5);
    
    strafing(20, 190, 'r');
    Sleep(0.5);

    drive_forward(-30, 250); //change counts
    Sleep(0.5);

    // strafing(20, 35, 'r');
    // Sleep(0.5);

    // drive_forward(-30, 200); //change counts
    // Sleep(0.5);

    

    arm_servo_RT.SetDegree(180.0);
    Sleep(0.5);

    drive_forward(30, 70);
    Sleep(0.5);

    arm_servo_RT.SetDegree(20.0);
    Sleep(1.0);

    drive_forward(-30, 80);
    Sleep(0.5);

    arm_servo_RT.SetDegree(180.0);
    Sleep(1.0);

    arm_servo_RT.SetDegree(32.0);
    Sleep(0.5);

    drive_forward(30, 70);
    Sleep(0.5);

    arm_servo_RT.SetDegree(173.0);
    Sleep(1.0);

    drive_forward(-30, 80);
    Sleep(1.0);

    arm_servo_RT.SetDegree(45.0);
    Sleep(1.0);

    drive_forward(30, 125);
    Sleep(1.0);

    strafing(20, 840, 'l');
    Sleep(1.0);

    spinInPlace(20,200,'r');
    Sleep(1.0);


    arm_servo_ARM.SetDegree(126.0);
    Sleep(3.0);

    drive_forward(30,185);
    Sleep(1.0);

    arm_servo_ARM.SetDegree(70);

   
    
    

    



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

void drive_forward(int percent, int counts)
{
    // double counts = inches * 35.7143;
    // Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    left_motor.SetPercent(percent);

    if (percent > 0){
        percent = (percent * -1);
    }
    else {
        percent = (percent * -1);
    }

    right_motor.SetPercent(percent);

    // Keep running until the average counts reach the target
    while ((abs(left_encoder.Counts()) + abs(right_encoder.Counts())) / 2 < counts) {
         // Keep running
    }


    // Turn off motors  
    right_motor.Stop();
    left_motor.Stop();

}

void strafing(int percent, int counts, char direction) {
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    front_encoder.ResetCounts();

    // double counts = inches * 33;
    
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

void spinInPlace(int percent, int degrees, char direction) {
    if (direction == 'l') {
        right_motor.SetPercent((-1 * percent) - 0.25);
        left_motor.SetPercent((-1 * percent) - 0.25);
        front_motor.SetPercent((-1 * percent) - 10);

        // seconds per degree times degree value
        Sleep(0.0115 * degrees);

        //Turn off motors
        right_motor.Stop();
        left_motor.Stop();
        front_motor.Stop();
    }
    if (direction == 'r') {
        right_motor.SetPercent(percent + 0.25);
        left_motor.SetPercent(percent + 0.25);
        front_motor.SetPercent(percent + 10);

        // seconds per degree times degree value
        Sleep(0.0115 * degrees);

        //Turn off motors
        right_motor.Stop();
        left_motor.Stop();
        front_motor.Stop();
    }
}