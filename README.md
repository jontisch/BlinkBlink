# BlinkBlink
A system for managing and controlling RF wall socket switches

The socket server is running on port 9999 (hard coded atm).

Daemon script placed in /usr/local/bin or other appropriate dir:
________________________________________________________________________________
#!/bin/bash																		|
until /path/to/compiled/file/a.out >> /path/to/rcswitch.log; do 				|
    echo "Image deamon 'a.out' crashed with exit code $?.  Respawning.." >&2	|
    sleep 1 																	|
done																			|
________________________________________________________________________________|


Add to crontab to keep log 10000 lines every 5 minutes
_________________________________________________________________________________________________________________
*/5 * * * * (tail -n10000 /path/to/rcswitch.log > /path/to/.rctmp; cat /path/to/.rctmp > /path/to/rcswitch.log)  |
_________________________________________________________________________________________________________________|


Add to /etc/rc.local or other appropriate boot script manager
____________________________________________
bash /usr/local/bin/rcswitch-monitor.sh &   |
____________________________________________|