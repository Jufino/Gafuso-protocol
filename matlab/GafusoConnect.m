function [] = GafusoConnect(IpAddress,Port)
    global t;
    global posuvac;
    t = tcpip(IpAddress,Port,'NetworkRole','Client','InputBufferSize',1024,'OutputBufferSize',1024,'Timeout',100);
    while(1)
        try 
            fopen(t);
            break;
        catch 
            fprintf('%s \n','Cant find Server');
        end
    end
    posuvac=1;
end

