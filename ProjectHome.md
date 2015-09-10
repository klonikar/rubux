An interface for remotely controlling X input (Mouse and Keyboard) from a smartphone / tablet device over a LAN. It is aimed primarily at the [Raspberry Pi](http://www.raspberrypi.org), but would work with just about any linux installation.

The project is in early development. It currently has:

A server that receives a few basic commands for mouse and keyboard inputs.

A handler that translates the commands to actual X window actions.

A demo Android app to send some test commands to the server. This part will eventually become a fully featured Mouse / Keyboard controller that will be used to control a Raspberry Pi over a LAN.

See the Raspberry Pi forum [discussion](http://www.raspberrypi.org/forum/projects-and-collaboration-general/using-iphone-to-control-r-pi-via-same-network).