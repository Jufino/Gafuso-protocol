function [] = GafusoClose()
    global t;
    fclose(t);
    echotcpip('off');
    delete(t);
end

