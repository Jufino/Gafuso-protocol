function [data] = GafusoLoad(mode)
global posuvac;
global dataRaw;
if mode==1 
    posuvac=1;
end
lengthData = str2double(char(dataRaw(posuvac:(posuvac+6))'));
data = char(dataRaw((posuvac+7):(posuvac+lengthData+6)))';
posuvac=posuvac+lengthData+7;
end

