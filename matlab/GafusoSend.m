function GafusoSend()
global t;
global dataSend;
size = sprintf('%.10d',length(dataSend));
fwrite(t,size+dataSend);
end

