function [] = GafusoCreate(IpAddress,Port )
    global t;
    t = tcpip(IpAddress, Port, 'NetworkRole', 'server');
    fopen(t)
    pause(0.01);
end

