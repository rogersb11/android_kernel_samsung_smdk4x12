#!/system/bin/sh

. /res/customconfig/customconfig-helper;
read_defaults;
read_config;

cd /;

# copy new sensors
rm -rf /system/bin/sensorservice;
rm -rf /system/lib/hw/sensors.smdk4x12.so;
cp -a /res/misc/sensors/sensorhubservice /system/bin/sensorhubservice;
cp -a /res/misc/sensors/libsensorhubservice.so /system/lib/libsensorhubservice.so;
cp -a /res/misc/sensors/sensorhubs.smdk4x12.so /system/lib/hw/sensorhubs.smdk4x12.so;
cp -a /res/misc/sensors/sensors.smdk4x12.so /system/lib/hw/sensors.smdk4x12.so;
rm -rf /res/misc/sensors;

mount -o remount,rw /;
mount -o remount,rw /system;
