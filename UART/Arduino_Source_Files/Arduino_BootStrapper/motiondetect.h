#ifndef MOTIONDETECT_H_INC
#define MOTIONDETECT_H_INC

#include <stdint.h>

const int mot_thresh=20; //change this value

void motiondetect(){
	uint16_t ranges[32];
	int diffs[24];
	int tot_time=2*5;
	stop();
	sonarEnable(0xff);

	for(int i=0;i<8;++i){
		ranges[i]=ranges[i+8]=ranges[i+16]
		=ranges[i+24]=getSonar(i);
	}

	for(int t=0;t<tot_time;++t){
		delay(500);
		for(int i=31;i>=8;--i) { ranges[i]=ranges[i-8]; }

		for(int i=0;i<8;++i) { ranges[i]=getSonar(i); }

		for(int i=0;i<24:++i) { diff[i]=abs(ranges[i]-ranges[i+8]); }

		for(int i=0;i<8;++i)
			if((diff[i]>=thresh) && (diff[i+8]>=thresh)
			   && (diff[x+16]>=thresh)) {
				beep(8,0x40);
			}
	}

}


#endif
