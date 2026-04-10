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


void drive(double inches, char direction);
void strafing(double inches, char direction);
void spinInPlace(int degrees, char direction);

void ERCMain()
{ 
    // PICK UP BUCKET AT 126. MAKE IT GO UP TO 70 FOR DEPOSITING.

    arm_servo_ARM.SetDegree(0.0);

    RCS.InitializeTouchMenu("1130D9ZBH");
    int correctLever = RCS.GetLever();

    int count = 0;
    float volt = cds.Value();
      
    //read starting voltage and continuous volt updates until a light source is read
    while (volt > 0.6  && count < 300) {
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

    arm_servo_RT.SetDegree(32.0);

    spinInPlace(135, 'r');
    Sleep(0.5);

    drive(4, 'b'); 
    Sleep(0.5);
    
    strafing(5.15, 'r');
    Sleep(0.5);

    drive(10.5, 'b'); 
    Sleep(0.5);


    arm_servo_RT.SetDegree(180.0);
    Sleep(0.5);

    drive(2, 'f');
    Sleep(0.5);

    arm_servo_RT.SetDegree(20.0);
    Sleep(0.5);

    drive(2, 'b');
    Sleep(0.5);

    arm_servo_RT.SetDegree(180.0);
    Sleep(1.5);

    arm_servo_RT.SetDegree(32.0);
    Sleep(0.5);

    drive(2, 'f');
    Sleep(0.5);

    arm_servo_RT.SetDegree(173.0);
    Sleep(0.5);

    drive(2.5, 'b');
    Sleep(0.5);

    arm_servo_RT.SetDegree(32.0);
    Sleep(1.0);

    drive(2, 'f');
    Sleep(0.5);

    strafing(16, 'l');
    Sleep(0.5);

    spinInPlace(180, 'r');
    Sleep(0.5);

    arm_servo_ARM.SetDegree(126.0);
    Sleep(3.0);

    drive(8.25, 'f');
    Sleep(0.5);

    arm_servo_ARM.SetDegree(70);
    Sleep(2.0);

    strafing(5.0, 'l');
    Sleep(0.5);

    spinInPlace(90, 'r');
    Sleep(0.5);

    strafing(16.0, 'r');
    Sleep(0.5);

    drive(32.75, 'f');
    Sleep(0.5);

    arm_servo_ARM.SetDegree(80.0);
    Sleep(0.5);

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