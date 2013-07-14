GafusoConnect('192.168.2.8',1213);
%GafusoClose();
%GafusoAdd('data',4);
%GafusoSend();
GafusoRecv();
GafusoBuffDel();
[data] = GafusoLoadAll()
%GafusoConnect('192.168.2.8',1213);
%GafusoAdd('100',3);
%GafusoSend();
%GafusoBuffDel();
GafusoClose();