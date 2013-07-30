function [] = GafusoRecv()
    global t;
    global dataRaw;
    global lengthInt;
    length = fread(t, 10);
    try
        lengthInt = str2double(char(length(:))');
        dataRaw = fread(t, lengthInt);
    catch
    end
end

