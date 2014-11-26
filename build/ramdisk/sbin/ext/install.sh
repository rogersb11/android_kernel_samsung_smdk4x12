#!/system/bin/sh

. /res/customconfig/customconfig-helper;
read_defaults;
read_config;

cd /;

#extract_kernel_payload()
#{
#	chmod 755 /sbin/read_boot_headers;
#	eval $(/sbin/read_boot_headers /dev/block/mmcblk0p5);
#	load_offset=$boot_offset;
#	load_len=$boot_len;
#	cd /;
#	dd bs=512 if=/dev/block/mmcblk0p5 skip=$load_offset count=$load_len | xzcat | tar x;
#}
#extract_kernel_payload; #disabled


#extract_payload()
#{
#	cd /res/misc/payload/;
#	$BB xzcat SuperSU.apk.tar.xz > SuperSU.apk.tar;
#	$BB xzcat su.tar.xz > su.tar;
#	$BB tar -xvf SuperSU.apk.tar;
#	$BB tar -xvf su.tar;
#	cd /;
#}
#extract_payload; #disabled

# copy cron files
cp -a /res/crontab/ /data/
rm -rf /data/crontab/cron/ > /dev/null 2>&1;
if [ ! -e /data/crontab/custom_jobs ]; then
touch /data/crontab/custom_jobs;
chmod 777 /data/crontab/custom_jobs;
fi;

# add gesture_set.sh with default gustures to data to be used by user.
if [ ! -e /data/gesture_set.sh ]; then
	$BB cp -a /res/misc/gesture_set.sh /data/;
fi;

# copy sqlite
cp -a /res/misc/sql/libsqlite.so /system/lib/libsqlite.so;
cp -a /res/misc/sql/sqlite3 /system/xbin/sqlite3;
chmod 644 /system/lib/libsqlite.so;
chmod 755 /system/xbin/sqlite3;
rm -rf /res/misc/sql;

mount -o remount,rw /;
mount -o remount,rw /system;
