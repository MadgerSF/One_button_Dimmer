#include "header.hpp"

PwmOut lights[] = {(PD_15),(PA_13),(PA_9)};
InterruptIn button(PA_0);
bool state = 0;
Timeout clk, blink;

void start_timer(){
    clk.attach(&intensity,1);
    button.fall(&transition);
}

void transition(){
    clk.detach();

    lights[position] = 0;
    position = !position;
    lights[position] = 1;
}

void intensity(){
    button.fall(&blink_off);

    if(state==blue){
        if(lights[2]<1.0){
            lights[2] = lights[2] + 0.05; //increase 5% at the 2 light
            rising();
        }
        if(lights[2]>=1.0){
            blink_blue();
        }
    }
    if(state==orange){
        if(lights[2]>0.0){
            lights[2] = lights[2] - 0.05; //decrease 5% at the 2 light
            falling();
        }
        if(lights[2]<=0.0){
            blink_orange();
        }
    }
    clk.attach(&intensity,1);

}
void rising(){
    if(lights[blue]==1){
            lights[blue]=0;
            blink.attach(&rising, 0.2);
        }
        else
        {
            lights[blue]=1;
        }
}

void blink_blue(){
    lights[blue] = !lights[blue];
    clk.attach(&blink_blue,0.1);
    button.fall(&transition);
}

void falling(){
    if(lights[orange]==1){
            lights[orange]=0;
            blink.attach(&falling, 0.2);
        }
        else
        {
            lights[orange]=0;
        }
}

void blink_orange(){
    lights[orange] = !lights[orange];
    clk.attach(&blink_orange,0.1);
    button.fall(&transition);
}

void blink_off(){
    blink.detach();
    clk.detach();
    lights[position] = 0;
    lights[!position] = 1;
}