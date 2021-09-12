# Time format converter

Converts the time from the received string to the format specified by the user.
The format of the original time is determined using regular expressions. 
<br>You should provide delimiters if they differ from ':' (ts == time separaor arg) and '.' (ds == date separator arg) respectively. 
<br>The timeConvert() function has a fifth optional argument - locale - set by default as "en_US.utf-8".
<br>Delimiters for otput time format and time formats like %c will be added later.

**Supported output time formats:**<br>
%H:%M:%S %d.%m.%Y<br>
%T %d.%m.%Y<br>
%H:%M %d.%m.%y<br>
%H:%M:%S %d %b %Y<br>
%H:%M:%S %d %B %Y<br>
%H:%M %d.%m.%Y<br>
%H:%M %d %b %Y<br>
%H:%M %d %B %Y<br>
%H:%M %d %b %y<br>
%H:%M %d %B %y<br>

*Reverse order*<br>

%d.%m.%Y %H:%M:%S<br>
%d.%m.%Y %T<br>
%d.%m.%y %H:%M<br>
%d %b %Y %H:%M:%S<br>
%d %B %Y %H:%M:%S<br>
%d.%m.%Y %H:%M<br>
%d %b %Y %H:%M<br>
%d %B %Y %H:%M<br>
%d %b %y %H:%M<br>
%d %B %y %H:%M<br>

