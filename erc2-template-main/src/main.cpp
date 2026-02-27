#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHSD.h>
#include <Arduino.h>
#include <FEHMotor.h>
#include <FEHUtility.h>
#include <Encoder.h>

// Declarations for analog optosensors
AnalogInputPin right_opto(FEHIO::Pin8);
AnalogInputPin middle_opto(FEHIO::Pin9);
AnalogInputPin left_opto(FEHIO::Pin10);

FEHMotor right_motor(FEHMotor::Motor0, 9.0);
FEHMotor left_motor(FEHMotor::Motor1, 9.0);

DigitalEncoder left_encoder(FEHIO::Pin9);
DigitalEncoder right_encoder(FEHIO::Pin8);

void turn_right(int percent, int counts);
void turn_left(int percent, int counts);
void drive_forward(int percent, int counts);


enum LineStates {
    MIDDLE,
    RIGHT,
    LEFT
};

//line following
void ERCMain()
{
    int x, y; //for touch screen


    //Initialize the screen
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);


    LCD.WriteLine("Analog Optosensor Testing");
    LCD.WriteLine("Touch the screen");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed


    // Record values for optosensors on and off of the straight line
    // Left Optosensor on straight line
    LCD.Clear(BLACK);
    LCD.WriteLine("Place left optosensor on straight line");
    Sleep(0.25); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (1/8)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to the screen
    float leftOptosensorValue = left_opto.Value();
    LCD.Write("Left Optosensor Value:");
    LCD.WriteLine(leftOptosensorValue);

    Sleep(5.0);


    // Left Optosensor off straight line
    LCD.Clear(BLACK);
    LCD.WriteLine("Place left optosensor off straight line");
    Sleep(0.25); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (2/8)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to the screen
    float leftOptosensorValueOffStraight = left_opto.Value();
    LCD.Write("Left Optosensor Value:");
    LCD.WriteLine(leftOptosensorValueOffStraight);

    Sleep(5.0);

    // Record values for optosensors on and off of the straight line
    // right Optosensor on straight line
    LCD.Clear(BLACK);
    LCD.WriteLine("Place right optosensor on straight line");
    Sleep(0.25); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (3/8)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to the screen
    float rightOptosensorValue = right_opto.Value();
    LCD.Write("Right Optosensor Value:");
    LCD.WriteLine(rightOptosensorValue);

    Sleep(5.0);


    // right Optosensor off straight line
    LCD.Clear(BLACK);
    LCD.WriteLine("Place right optosensor off straight line");
    Sleep(0.25); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (4/8)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to the screen
    float rightOptosensorValueOffStraight = right_opto.Value();
    LCD.Write("Right Optosensor Value:");
    LCD.WriteLine(rightOptosensorValueOffStraight);

    Sleep(5.0);


// middle Optosensor on straight line
    LCD.Clear(BLACK);
    LCD.WriteLine("Place middle optosensor on straight line");
    Sleep(0.25); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (3/8)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to the screen
    float middleOptosensorValue = middle_opto.Value();
    LCD.Write("Middle Optosensor Value:");
    LCD.WriteLine(middleOptosensorValue);

    Sleep(5.0);


    // right Optosensor off straight line
    LCD.Clear(BLACK);
    LCD.WriteLine("Place middle optosensor off straight line");
    Sleep(0.25); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (4/8)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to the screen
    float middleOptosensorValueOffStraight = middle_opto.Value();
    LCD.Write("Middle Optosensor Value:");
    LCD.WriteLine(middleOptosensorValueOffStraight);

    Sleep(5.0);


    // Record values for optosensors on and off of the curved line
    // Left Optosensor on curved line
    LCD.Clear(BLACK);
    LCD.WriteLine("Place left optosensor on curved line");
    Sleep(0.25); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (5/8)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to the screen
    float leftOptosensorValueCurve = left_opto.Value();
    LCD.Write("Left Optosensor Value:");
    LCD.WriteLine(leftOptosensorValueCurve);

    Sleep(5.0);

    // Left Optosensor off curved line
    LCD.Clear(BLACK);
    LCD.WriteLine("Place left optosensor off curved line");
    Sleep(0.25); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (6/8)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to the screen
    float leftOptosensorValueOffCurve = left_opto.Value();
    LCD.Write("Left Optosensor Value:");
    LCD.WriteLine(leftOptosensorValueOffCurve);
   
    // Record values for optosensors on and off of the curved line
    // right Optosensor on curved line
    LCD.Clear(BLACK);
    LCD.WriteLine("Place right optosensor on curved line");
    Sleep(0.25); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (7/8)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to the screen
    float rightOptosensorValueCurve = right_opto.Value();
    LCD.Write("Right Optosensor Value:");
    LCD.WriteLine(rightOptosensorValueCurve);

    Sleep(5.0);

    // right Optosensor off curved line
    LCD.Clear(BLACK);
    LCD.WriteLine("Place right optosensor off curved line");
    Sleep(0.25); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (8/8)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to the screen
    float rightOptosensorValueOffCurve = right_opto.Value();
    LCD.Write("Right Optosensor Value:");
    LCD.WriteLine(rightOptosensorValueOffCurve);

    Sleep(5.0);

 // middle Optosensor on curved line
    LCD.Clear(BLACK);
    LCD.WriteLine("Place middle optosensor on curved line");
    Sleep(0.25); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (7/8)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to the screen
    float middleOptosensorValueCurve = middle_opto.Value();
    LCD.Write("Middle Optosensor Value:");
    LCD.WriteLine(middleOptosensorValueCurve);

    Sleep(5.0);

    // middle Optosensor off curved line
    LCD.Clear(BLACK);
    LCD.WriteLine("Place middle optosensor off curved line");
    Sleep(0.25); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (8/8)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to the screen
    float middleOptosensorValueOffCurve = middle_opto.Value();
    LCD.Write("Middle Optosensor Value:");
    LCD.WriteLine(middleOptosensorValueOffCurve);

    Sleep(5.0);

    // Print end message to screen
    LCD.Clear(BLACK);
    LCD.WriteLine("Test Finished");


    float leftThreshold = (leftOptosensorValue + leftOptosensorValueOffStraight + leftOptosensorValueCurve + leftOptosensorValueOffCurve) / 4.0;
    float rightThreshold = (rightOptosensorValue + rightOptosensorValueOffStraight + rightOptosensorValueCurve + rightOptosensorValueOffCurve)/ 4.0;
    float middleThreshold = (middleOptosensorValue + middleOptosensorValueOffStraight + middleOptosensorValueCurve + middleOptosensorValueOffCurve)/ 4.0;


    int state = MIDDLE;

    while (true) {
        float currentLeft = left_opto.Value();
        float currentRight = right_opto.Value();
        float currentMiddle = middle_opto.Value();

        switch(state) {


            case MIDDLE:
                right_motor.SetPercent(-30.0);
                left_motor.SetPercent(30.0);
                if (currentMiddle > middleThreshold) {
                    state = MIDDLE;
                }
                else if (currentRight > rightThreshold) {
                    state = RIGHT;
                }
                else if (currentLeft > leftThreshold) {
                    state = LEFT;
                }
                break;


            case LEFT:
                right_motor.SetPercent(-20.0);
                left_motor.SetPercent(5.0);
                if (currentMiddle > middleThreshold) {
                    state = MIDDLE;
                }
                else if (currentRight > rightThreshold) {
                    state = RIGHT;
                }
                break;


            case RIGHT:
                right_motor.SetPercent(-5.0);
                left_motor.SetPercent(20.0);
                if (currentMiddle > middleThreshold) {
                    state = MIDDLE;
                }
                else if (currentLeft > leftThreshold) {
                    state = LEFT;
                }
                break;


            default:
                right_motor.Stop();
                left_motor.Stop();
                break;
            }


        Sleep(0.01);
        // Abhi Kanakia

        // float lowthreshold = LOW;
        // float highthreshold = HIGH;


        // left_encoder.SetThresholds(lowthreshold, highthreshold);
        // right_encoder.SetThresholds(lowthreshold, highthreshold);

        // 1. Drive 14 inches (14 inches * 40 counts/inch = 560 counts)
        drive_forward(40, 560);
        Sleep(1.0);

        // 2. Turn left 90 degrees
        // You will need to use trial and error to find the correct counts for a 90-degree turn
        turn_left(40, 200); // 200 is just a placeholder guess!
        Sleep(1.0);

        // 3. Drive 10 inches (10 * 40 = 400 counts)
        drive_forward(40, 400);
        Sleep(1.0);

        // 4. Turn right 90 degrees
        turn_right(40, 200); // Placeholder guess!
        Sleep(1.0);

        // 5. Drive 4 inches (4 * 40 = 162 counts)
        drive_forward(40, 160);
    }
}
//     void ERCMain()
// {
//     // float lowthreshold = //LOW NUM
//     // float highthreshold = //HIGH NUM

//     //Setting thresholds to the left encoder
//     // left_encoder.SetThresholds(lowthreshold, highthreshold);
//     // right_encoder.SetThresholds(lowthreshold, highthreshold);

//     // 1. Drive 14 inches (14 inches * 40 counts/inch = 560 counts)
//     drive_forward(40, 560);
//     Sleep(1.0);

//     // 2. Turn left 90 degrees
//     // You will need to use trial and error to find the correct counts for a 90-degree turn
//     turn_left(40, 200); // 200 is just a placeholder guess!
//     Sleep(1.0);

//     // 3. Drive 10 inches (10 * 40 = 400 counts)
//     drive_forward(40, 400);
//     Sleep(1.0);

//     // 4. Turn right 90 degrees
//     turn_right(40, 200); // Placeholder guess!
//     Sleep(1.0);

//     // 5. Drive 4 inches (4 * 40 = 162 counts)
//     drive_forward(40, 160);
// }

void drive_forward(int percent, int counts)
{
    // Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);

    // Keep running until the average counts reach the target
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts) {
       // Keep running
    }

    // Turn off motors  
    right_motor.Stop();
    left_motor.Stop();
}

void turn_right(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    right_motor.SetPercent(-percent);
    left_motor.SetPercent(percent);

    //While the average of the left and right encoder is less than counts, keep running motors
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts) {
       //keep running
    }

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void turn_left(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(-percent);

    //While the average of the left and right encoder is less than counts, keep running motors
    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < counts) {
        //keep running
    }

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}