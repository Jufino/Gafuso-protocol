function [data] = GafusoLoadAll()
global posuvac;
global dataRaw;
global lengthInt;
posuvac=1;
data = [];
while lengthInt > posuvac
    lengthData = str2double(char(dataRaw(posuvac:(posuvac+6))'));
    data = [data;char(dataRaw((posuvac+7):(posuvac+lengthData+6)))'];
    posuvac=posuvac+lengthData+7;
    end
end


