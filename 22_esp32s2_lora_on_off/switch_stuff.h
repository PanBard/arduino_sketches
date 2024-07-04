#define pin 3 //analogpin x pin 3

void pin_start() 
{ 
 pinMode(pin, OUTPUT);
}

void switch_on() 
{ 
 digitalWrite(pin, HIGH); //because we control switch with npn transistor, so high on base 
}

void switch_off() 
{ 
 digitalWrite(pin, LOW);
}
