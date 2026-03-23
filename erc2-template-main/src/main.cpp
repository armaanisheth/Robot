#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHSD.h>
#include <Arduino.h>
#include <FEHMotor.h>
#include <FEHUtility.h>
#include <Encoder.h>

AnalogInputPin cds(FEHIO::Pin4);

FEHMotor right_motor(FEHMotor::Motor0, 9.0);
DigitalEncoder right_encoder(FEHIO::Pin8);

FEHMotor left_motor(FEHMotor::Motor1, 9.0);
DigitalEncoder left_encoder(FEHIO::Pin14);

FEHMotor front_motor(FEHMotor::Motor2, 9.0);
DigitalEncoder front_encoder(FEHIO::Pin11);

void drive_forward(int percent, int counts);
void strafing(int percent, int counts, char direction);
void spinInPlace(int percent, int degrees, char direction);

void ERCMain()
{
    //read in the start line and begin driving
    //default 30 sec wait time, if light is not read
    int count = 0;
    float volt = cds.Value();
    //print wait message
    LCD.Write("Waiting for start light ");
    //read starting voltage and continuous volt updates until a light source is read
    while (volt > 0.6  && count < 300) {
       volt = cds.Value();
       Sleep(0.1);
       count++;
    }
    //print starting message
    LCD.Write("Starting...");
   
    //drive backward to hit the final button
    drive_forward(-30, 90); //change counts
    Sleep(1.0);

    // 35.7143 Counts/ Inch
    // Driving around 4 inches forward
    drive_forward(30, 145); //adjust
    Sleep(1.0);

    // rotate 45 degrees to the right (20 for percent always)
    spinInPlace(20, 45, 'r');
    Sleep(1.0);

    // strafe 3.5 inches right
    strafing(20, 133, 'r');
    Sleep(1.0);
   
    // 35.7143 Counts/ Inch
    // Driving around 35-40 inches forward up the ramp
    drive_forward(30, 1343); //adjust
    Sleep(1.0);

    // rotate 90 degrees to the left (20 for percent always)
    spinInPlace(20, 90, 'l');
    Sleep(1.0);

    // drive backwards to set ourselves up
    drive_forward(-30, 275); //adjust
    Sleep(1.0);

    //strafe 2 inches to the right to line us up
    strafing(20, 66, 'r');
    Sleep(1.0);

    // drive forward to light
    drive_forward(30, 635); //adjust
    Sleep(1.0);

    //attempt to read blue or red light value from the cds cell sensor
    //print message to the screen
    String light;
    volt = cds.Value();
    count = 0;
    while (!light.equals("blue") && !light.equals("red")) {
       volt = cds.Value();
       Sleep(0.1);
       count++;
       if (volt > 0.3 && volt < 0.6) {
            light = "blue";
            LCD.Write(light);
       }
       else if (volt < 0.25) {
            light = "red";
            LCD.Write(light);
       }
       else if (count >= 30) {
            if (volt < 0.25) {
                light = "red";
            }
            else {
                light = "blue";
            }
            LCD.Write("3 seconds have passed: ");
            LCD.Write(light);
       }
    }

    if (light.equals("blue")) {
        // strafe sideways to the left
        strafing(20, 66, 'l');
        Sleep(1.0);
        //drive forward to hit button
        drive_forward(20, 165);

        Sleep(2.0);
        //drive backwards
        drive_forward(-20, 150);
        Sleep(1.0);
        // strafe sideways to the right
        strafing(20, 66, 'r');
        Sleep(1.0);
    }
    else {
        // strafe sideways to the right
        strafing(20, 66, 'r');
        Sleep(1.0);
        //drive forward to hit button
        drive_forward(20, 165);

        Sleep(2.0);
        //drive backwards
        drive_forward(-20, 150);
        Sleep(1.0);
        // strafe sideways to the left
        strafing(20, 66, 'l');
        Sleep(1.0);
    }

    //drive backwards to align with ramp
    drive_forward(-30, 650);
    Sleep(1.0);

    // drive forward a few inches
    drive_forward(30, 110);
    Sleep(1.0);

    //spin in place 90 degrees left
    spinInPlace(20, 90, 'l');
    Sleep(1.0);

    //strafe right about 1.5 inches
    // strafing(20, 50, 'r');
    // Sleep(1.0);

    //drive forwards down the ramp
    drive_forward(30, 1450);
    Sleep(1.0);

    //drive backwards 4 inches
    drive_forward(-30, 140);
    Sleep(1.0);

    //turn 45 degrees left
    spinInPlace(20, 45, 'l');
    Sleep(1.0);

    // drive forward 5 inches
    drive_forward(30, 200);
    Sleep(1.0);


}

void drive_forward(int percent, int counts)
{
   
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