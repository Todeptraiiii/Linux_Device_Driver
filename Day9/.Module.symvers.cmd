cmd_/home/todz/Linux_Driver/Linux_Device_Driver/Day9/Module.symvers := sed 's/\.ko$$/\.o/' /home/todz/Linux_Driver/Linux_Device_Driver/Day9/modules.order | scripts/mod/modpost -m -a  -o /home/todz/Linux_Driver/Linux_Device_Driver/Day9/Module.symvers -e -i Module.symvers   -T -
