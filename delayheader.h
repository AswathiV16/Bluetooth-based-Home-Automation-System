void seconds(unsigned int secs){
	T0PR=15000000-1;
	T0TCR=0x01;
	while(T0TC<secs);
	T0TCR=0x03;
	T0TCR=0x00;
}

void milliseconds(unsigned int seconds){
	T0PR=15000-1;
	T0TCR=0x01;
	while(T0TC<seconds);
	T0TCR=0x03;
	T0TCR=0x00;
}

void microseconds(unsigned int seconds){
	T0PR=15-1;
	T0TCR=0x01;
	while(T0TC<seconds);
	T0TCR=0x03;
	T0TCR=0x00;
}
