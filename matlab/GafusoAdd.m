function GafusoAdd(dataAdd,length)
global dataSend;
length = sprintf('%.7d',length);
dataSend = [dataSend length dataAdd];
end