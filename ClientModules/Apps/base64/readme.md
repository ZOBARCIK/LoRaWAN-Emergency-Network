#base64 encoder-decoder\


#NEEDS TWEAKING IN THE FUTURE BUT FINISHED OTHERWISE





client app should handle the naming of the input file, modify the header later accordingly

obviously I/O operations will be abolished for text input-output, it should be written directly via serial/uart once gateway come together

at the moment I'm handling the media extension seperately rather than appending it at the end of the encoded message for robustness, I thought we could cast it seperately and get a little ack for it, also would be better for error correction

if you have any problems Okan, FU, I wont answer bc I'm probably playing KCD2 in my room sipping my large BK chocolate milkshake

KNOWN PROBLEMS: SO extension decoding may return null for some reason idk. when I tried to get the extension from the Dataext struct for jpg, it returned null but it worked for the .wav file. same for the .wav file but vice versa. I would guess its only a carriage return or a null termination issue but Im just leaving it as it is since the client side will handle that part.

thats all about it, seeya



changes:\
fixed the memory bugs\
completed the image decoder\


todo: \
catching nulls \
back propogation \

~ZOBARCIK
