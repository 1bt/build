if [ $OUTPUT_MODE = hil ]
then
set HIL_ARG $OUTPUT_MODE
fi
if [ $USE_IO = yes -a $IO_PRESENT = yes ]
then
if px4io start $HIL_ARG
then
px4io recovery
px4io limit 400
else
echo "PX4IO start failed" >> $LOG_FILE
tune_control play -t 20
fi
fi
