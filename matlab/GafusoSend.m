function GafusoSend()
global t;
global dataSend;
size = sprintf('%.10d',length(dataSend));
check = [];
while check != 'OK'
    fwrite(t,size+dataSend);
    check = fread(t, 2);
end
end

