GafusoConnect('192.168.2.11',1213);
GafusoAdd('next',4);
Sensor1=[];
Sensor2=[];
for I=0:15:360
    sprintf('Point robot to 0 degree %d',I);
    waitforbuttonpress;
    GafusoSend();
    GafusoRecv();
    Sensor1 = [Sensor1 GafusoLoad()];
    Sensor2 = [Sensor2 GafusoLoad()];
end
GafusoClose();