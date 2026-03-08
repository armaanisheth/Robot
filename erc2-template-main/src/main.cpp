#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHSD.h>
#include <Arduino.h>
#include <FEHMotor.h>
#include <FEHUtility.h>
#include <Encoder.h>

FEHMotor right_motor(FEHMotor::Motor0, 9.0);
DigitalEncoder right_encoder(FEHIO::Pin8);

FEHMotor left_motor(FEHMotor::Motor1, 9.0);
DigitalEncoder left_encoder(FEHIO::Pin14);

FEHMotor front_motor(FEHMotor::Motor2, 9.0);
DigitalEncoder front_encoder(FEHIO::Pin11);

void drive_forward(int percent, int counts);
void turn(int percent, int counts, char direction);
void sideways(int percent, int counts, char direction);

void ERCMain()
{
    
    Sleep(1.0);
    // 35.7143 Counts/ Inch
    // First part (right to left)
    drive_forward(30, 1000);
    Sleep(2.0);
    drive_forward(-30, 1000);
    Sleep(2.0);

    char direction = 'r';
    turn(20, 280, direction);
    Sleep(2.0);
    
    // 35.7143 * 8 inches = 285
    sideways(30, 285, 'r');
    Sleep(2.0);


    // For the second part of Milestone 1.
    // Driving around 35-40 inches forward, and backwards
    drive_forward(30, 1200);
    Sleep(2.0);
    drive_forward(-20, 1000);




}

void drive_forward(int percent, int counts)
{
    
    // Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    left_motor.SetPercent(percent);

    if (percent > 0){
        percent = (percent * -1) - 2;
    }
    else {
        percent = (percent * -1) + 2;
    }

    right_motor.SetPercent(percent);

    // Keep running until the average counts reach the target
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts) {
         // Keep running
    }


    // Turn off motors  
    right_motor.Stop();
    left_motor.Stop();

}

void turn(int percent, int counts, char direction) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    front_encoder.ResetCounts();

    //determine direction
    if (direction == ('l')) {
        //Set both motors to desired percent
        right_motor.SetPercent(-1 * percent);
        // left_motor.SetPercent(-1 * percent);
        // front_motor.SetPercent(percent);
    } else {
        // right_motor.SetPercent(percent);
        left_motor.SetPercent(percent);
        // front_motor.SetPercent(-1 * percent);
    }

    //While the average of the left and right encoder is less than counts, keep running motors
    while ((left_encoder.Counts() + right_encoder.Counts() + front_encoder.Counts()) / 3 < counts) {
        //keep running
    }

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
    front_motor.Stop();
}

void sideways(int percent, int counts, char direction) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    front_encoder.ResetCounts();

    //determine direction
    if (direction == ('l')) {
        front_motor.SetPercent(-1 * percent);
        left_motor.SetPercent(percent);
    } else {
        front_motor.SetPercent(percent);
        left_motor.SetPercent(-1 * percent);
    }

    //While the average of the left and right encoder is less than counts, keep running motors
    while ((front_encoder.Counts() + left_encoder.Counts()) / 2 < counts) {
        //keep running
    }

    
    front_motor.Stop();
    left_motor.Stop();
}

